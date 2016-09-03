#include "StdAfx.h"

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_
#include "BaseApplication.h"

class TutorialApplication : public BaseApplication
{
public:
	TutorialApplication(void){}
	virtual ~TutorialApplication(void){}
protected:
    virtual void createScene(void){
		this->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2,0.2,0.2));
		Ogre::Light *light=this->mSceneMgr->createLight();
		light->setPosition(Ogre::Vector3(20,80,50));
		//
		mCamera->setPosition(Ogre::Vector3(60,70,200));
		mCamera->lookAt(Ogre::Vector3(0,0,0));
		//
		Ogre::Entity *ent;
		Ogre::SceneNode *node;
		const int num=6;
		const Ogre::Real dist=75;
		for(int i=0;i<num;i++){
			ent=mSceneMgr->createEntity("ogrehead"+Ogre::StringConverter::toString(i),"ogrehead.mesh");
			node=mSceneMgr->getRootSceneNode()->createChildSceneNode();
			node->attachObject(ent);
			Ogre::Real theta=(Ogre::Real)i/(Ogre::Real)num*2*Ogre::Math::PI;
			node->setPosition(Ogre::Math::Cos(theta)*dist,0,Ogre::Math::Sin(theta)*dist);
			node->yaw(Ogre::Radian(0-(theta-Ogre::Math::PI/2)));

		}
		//
		this->createProjector();
		for(int i=0;i<ent->getNumSubEntities();i++){
			this->makeMaterialReceiveDecal(ent->getSubEntity(i)->getMaterialName());
		}
		mAnim=10;

	}

	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt){
		bool ret=BaseApplication::frameRenderingQueued(evt);
		this->mProjectorNode->rotate(Ogre::Quaternion(Ogre::Degree(this->mAnim*evt.timeSinceLastFrame),Ogre::Vector3::UNIT_Y));

		return ret;
	}	
	void createProjector(){
		this->mDecalFrustum=new Ogre::Frustum();
		this->mProjectorNode =mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mProjectorNode->attachObject(mDecalFrustum);
		mProjectorNode->setPosition(0,5,0);
		//
		this->mFilterFrustum=new Ogre::Frustum();
		mFilterFrustum->setProjectionType(Ogre::ProjectionType::PT_ORTHOGRAPHIC);
		Ogre::SceneNode *node=this->mProjectorNode->createChildSceneNode();
		node->attachObject(this->mFilterFrustum);
		node->setOrientation(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y));

	}
	void makeMaterialReceiveDecal(const Ogre::String &matname){
		Ogre::MaterialPtr mat=(Ogre::MaterialPtr)Ogre::MaterialManager::getSingleton().getByName(matname);
		Ogre::Pass *pass=mat->getTechnique(0)->getPass(0);
		//
		pass->setSceneBlending(Ogre::SceneBlendType::SBT_REPLACE);
pass->setDepthBias(1);
//pass->setLightingEnabled(false);
		//
		Ogre::TextureUnitState *texture = pass->createTextureUnitState("Decal.png");
texture->setProjectiveTexturing(true, mDecalFrustum);
texture->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
texture->setTextureFiltering(Ogre::FO_POINT, Ogre::FO_LINEAR, Ogre::FO_NONE);
//
		texture=pass->createTextureUnitState("Decal_filter.png");
		texture->setProjectiveTexturing(true,this->mFilterFrustum);
		texture->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
		texture->setTextureFiltering(Ogre::TFO_NONE);

	}
	Ogre::SceneNode *mProjectorNode;
	Ogre::Frustum *mDecalFrustum;
	Ogre::Frustum *mFilterFrustum;
	Ogre::Real mAnim;
};

#endif // #ifndef __TutorialApplication_h_
