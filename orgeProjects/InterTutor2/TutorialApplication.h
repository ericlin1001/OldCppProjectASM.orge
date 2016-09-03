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
		mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5,0.5,0.5));
		mSceneMgr->setSkyDome(true,"Examples/CloudySky",5,8);
		mSceneMgr->setWorldGeometry("terrain.cfg");
		//
		mCamera->setPosition(40,100,580);
		mCamera->pitch(Ogre::Degree(-30));
		mCamera->yaw(Ogre::Degree(-45));
		//
	
		 //mGUIRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

  
	}
	 virtual void chooseSceneManager(void){
		 BaseApplication::chooseSceneManager();
	 }
	 virtual void createFrameListener(void){
		 BaseApplication::createFrameListener();
	 }
	//
	// Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt){
		bool ret=BaseApplication::frameRenderingQueued(evt);
		return ret;
	}

	// OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg ){
		if(!BaseApplication::keyPressed(arg))return false;

		return true;
	}
    virtual bool keyReleased( const OIS::KeyEvent &arg ){
		if(!BaseApplication::keyReleased(arg))return false;

		return true;
	}
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg ){
		if(!BaseApplication::mouseMoved(arg))return false;

		return true;
	}
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
		if(!BaseApplication::mousePressed(arg,id))return false;

		return true;
	}
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
		if(!BaseApplication::mouseReleased(arg,id))return false;

		return true;
	}
	//
	Ogre::RaySceneQuery *mRaySceneQuery;
	bool mLMouseDown,mRMouseDown;
	int mCount;
	Ogre::SceneNode *mCurrentObject;
	CEGUI::Renderer *mGUIRenderer;
	float mRotateSpeed;

};

#endif // #ifndef __TutorialApplication_h_
