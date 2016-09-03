#include "StdAfx.h"

#include "TutorialApplication.h"
void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
	img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	if (flipX)
		img.flipAroundY();
	if (flipY)
		img.flipAroundX();

}
//
void TutorialApplication::createScene(void)
{
	mCamera->setPosition(Ogre::Vector3(1683,50,2116));
	mCamera->lookAt(Ogre::Vector3(1963,50,1660));
	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(50000);
	//mCameraMan=&OgreBites::SdkCameraMan(mCamera);

	if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE)){
		mCamera->setFarClipDistance(0);
	}
	// create your scene here :)
	Ogre::Vector3 lightdir(0.55,-0.3,0.75);
	lightdir.normalise();
	Ogre::Light * light=mSceneMgr->createLight("tstLight");
	light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL );
	light->setDirection(lightdir);
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(.4,.4,.4);
	//
	mSceneMgr->setAmbientLight(Ogre::ColourValue(.2,.2,.2));
	//
	mTerrainGlobals=OGRE_NEW Ogre::TerrainGlobalOptions();
	mTerrainGroup=OGRE_NEW Ogre::TerrainGroup(mSceneMgr,Ogre::Terrain::Alignment::ALIGN_X_Z,513,12000.0f);
	mTerrainGroup->setFilenameConvention(Ogre::String("BasicTutorial3Terrain"),Ogre::String("dat"));
	mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
	//
	configureTerrainDefaults(light);
	//
	for (long x = 0; x <= 0; ++x)
		for (long y = 0; y <= 0; ++y)
			defineTerrain(x, y);

	// sync load since we want everything in place when we start
	mTerrainGroup->loadAllTerrains(true);
	if (mTerrainsImported)
	{
		Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
		while(ti.hasMoreElements())
		{
			Ogre::Terrain* t = ti.getNext()->instance;
			initBlendMaps(t);
		}
	}

	mTerrainGroup->freeTemporaryResources();
	//
	//
	/*Ogre::Plane plane;
	plane.d=1000;
	plane.normal=Ogre::Vector3::NEGATIVE_UNIT_Y;
	mSceneMgr->setSkyPlane(true, plane, "Examples/SpaceSkyPlane", 1500, 75,true,1.5f,120,120);
	//
	Ogre::ColourValue fadeColour(0.9,0.9,0.9);
	mWindow->getViewport(0)->setBackgroundColour(fadeColour);
	//
	mSceneMgr->setFog(Ogre::FOG_EXP,fadeColour,0.0003);*/

	/*Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 1200);
mWindow->getViewport(0)->setBackgroundColour(fadeColour);*/
mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8, 500);
//
Ogre::Entity * ninja=mSceneMgr->createEntity("ninja","ninja.mesh");
Ogre::SceneNode *node=mSceneMgr->getRootSceneNode()->createChildSceneNode("ninjaNode");
node->attachObject(ninja);

}
//


//
void TutorialApplication
	::createFrameListener(void)
{
	    BaseApplication::createFrameListener();
 
    mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "TInfo", "", 350);
}
void TutorialApplication
	::destroyScene(void)
{
	    OGRE_DELETE mTerrainGroup;
    OGRE_DELETE mTerrainGlobals;
}
bool TutorialApplication
	::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
	bool ret = BaseApplication::frameRenderingQueued(evt);
 
    if (mTerrainGroup->isDerivedDataUpdateInProgress())
    {
        mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
        mInfoLabel->show();
        if (mTerrainsImported)
        {
            mInfoLabel->setCaption("Building terrain, please wait...");
        }
        else
        {
            mInfoLabel->setCaption("Updating textures, patience...");
        }
    }
    else
    {
        mTrayMgr->removeWidgetFromTray(mInfoLabel);
        mInfoLabel->hide();
        if (mTerrainsImported)
        {
            mTerrainGroup->saveAllTerrains(true);
            mTerrainsImported = false;
        }
    }
	if(!processUnbufferedInput(evt))return false;
    return ret;
}


/*Ogre::TerrainGlobalOptions *mTerrainGlobals;
Ogre::TerrainGroup *mTerrainGroup;
bool mTerrainsImported;*/
void TutorialApplication::defineTerrain(long x,long y){
	Ogre::String filename = mTerrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    {
        mTerrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        getTerrainImage(x % 2 != 0, y % 2 != 0, img);
        mTerrainGroup->defineTerrain(x, y, &img);
        mTerrainsImported = true;
    }

}
void TutorialApplication::initBlendMaps(Ogre::Terrain *terrain){
	  Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
	//
    Ogre::Real minHeight0 = 70;
    Ogre::Real fadeDist0 = 40;
    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 15;
	//
    float* pBlend0 = blendMap0->getBlendPointer();
    float* pBlend1 = blendMap1->getBlendPointer();
	//
    for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;
 
            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend0++ = val;
 
            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();

}
void TutorialApplication::configureTerrainDefaults(Ogre::Light * light){
	 mTerrainGlobals->setMaxPixelError(8);
    // testing composite map
    mTerrainGlobals->setCompositeMapDistance(3000);
	
	// Important to set these so that the terrain knows what to use for derived (non-realtime) data
    mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

	// Configure default import settings for if we use imported image
    Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 513;
    defaultimp.worldSize = 12000.0f;
    defaultimp.inputScale = 600; // due terrain.png is 8 bpp
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;
	// textures
    defaultimp.layerList.resize(3);
    defaultimp.layerList[0].worldSize = 100;
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");

    defaultimp.layerList[1].worldSize = 30;
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");

    defaultimp.layerList[2].worldSize = 200;
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
}
//
//-------------------------------------------------------------------------------------
bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent &evt){
	Ogre::Vector3 trans =Ogre::Vector3::ZERO;
	Ogre::Real speed=200;
	if(mKeyboard->isKeyDown(OIS::KC_I)){
		trans.z-=speed;
	}
	if(mKeyboard->isKeyDown(OIS::KC_K)){
		trans.z+=speed;
	}
	if(mKeyboard->isKeyDown(OIS::KC_J)){
		trans.x-=speed;
	}
	if(mKeyboard->isKeyDown(OIS::KC_L)){
		trans.x+=speed;
	}if(mKeyboard->isKeyDown(OIS::KC_U)){
		trans.y+=speed;
	}
	if(mKeyboard->isKeyDown(OIS::KC_O)){
		trans.y-=speed;
	}
	mSceneMgr->getSceneNode("ninjaNode")->translate(trans*evt.timeSinceLastFrame);
	return true;
}