#include "StdAfx.h"
#include "TutorialApplication.h"
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent &evt){
	mPlaneNode->yaw(Ogre::Radian(evt.timeSinceLastFrame));
	return BaseApplication::frameRenderingQueued(evt);
}
 void TutorialApplication::createScene(void){
	 mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2,0.2,0.2));
	 Ogre::Light *light=mSceneMgr->createLight("MainLight");
	 light->setPosition(20,80,50);
	 //
	 mCamera->setPosition(60,200,70);
	 mCamera->lookAt(0,0,0);
	 //
	 Ogre::MaterialPtr mat=Ogre::MaterialManager::getSingleton().create("PlaneMat",
		 Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	 Ogre::TextureUnitState *tuisTexture=mat->getTechnique(0)->getPass(0)->createTextureUnitState("grass_1024.jpg");
	//
	 mPlane=new Ogre::MovablePlane("Plane");
	 mPlane->d=10;
	 mPlane->normal=Ogre::Vector3::UNIT_Y;
	 Ogre::MeshManager::getSingleton().createPlane("PlaneMesh",
		 Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		 *mPlane,
		 120,120,1,1,true,1,1,1,Ogre::Vector3::UNIT_Z);
	 //
	 mPlaneEnt=mSceneMgr->createEntity("PlaneEntity","PlaneMesh");
	 mPlaneEnt->setMaterialName("PlaneMat");
	 mPlaneNode=mSceneMgr->getRootSceneNode()->createChildSceneNode();
	 mPlaneNode->attachObject(mPlaneEnt);
	 //
	 Ogre::TexturePtr rtt_texture=Ogre::TextureManager::getSingleton().createManual("RttTex",
		 Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		 Ogre::TextureType::TEX_TYPE_2D,mWindow->getWidth(),mWindow->getHeight(),0
		 ,Ogre::PixelFormat::PF_R8G8B8,Ogre::TU_RENDERTARGET);
	 Ogre::RenderTexture * renderTexture=rtt_texture->getBuffer()->getRenderTarget();
	 //
	 renderTexture->addViewport(mCamera);
	 renderTexture->getViewport(0)->setClearEveryFrame(true);
	 renderTexture->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
	 renderTexture->getViewport(0)->setOverlaysEnabled(false);
	 //
	 renderTexture->setAutoUpdated(true);
	 renderTexture->update();
	 renderTexture->writeContentsToFile("tutor7.png");
	 
	 //
	 mMiniScreen=new Ogre::Rectangle2D(true);
	 mMiniScreen->setCorners(0.5,1,1,0.5);
	 mMiniScreen->setBoundingBox(Ogre::AxisAlignedBox(-100000*Ogre::Vector3::UNIT_SCALE,100000*Ogre::Vector3::UNIT_SCALE));
	 Ogre::SceneNode *miniScreenNode=mSceneMgr->getRootSceneNode()->createChildSceneNode("miniScreenNode");
	 miniScreenNode->attachObject(mMiniScreen);
	 //
	 Ogre::MaterialPtr renderMaterial=Ogre::MaterialManager::getSingleton().create("RttMat",
		 Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	 Ogre::Technique * matTec=renderMaterial->createTechnique();
	 matTec->createPass();
	 renderMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	 renderMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("RttTex");
	
	 mMiniScreen->setMaterial("RttMat");
	 //
	 renderTexture->addListener(this);
	 //
	 Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().getByName("Sepia");
	 material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName("OtherRttTex");

}
 void TutorialApplication::preRenderTargetUpdate(const Ogre::RenderTargetEvent &evt){
	 mMiniScreen->setVisible(false);
 }
 void TutorialApplication::postRenderTargetUpdate(const Ogre::RenderTargetEvent &evt){
	 mMiniScreen->setVisible(true);
 }
 //172.18.157.121
 /*Ogre::MovablePlane * mPlane;
	Ogre::Entity * mPlaneEnt;
	Ogre:SceneNode* mPlaneNode;*/
