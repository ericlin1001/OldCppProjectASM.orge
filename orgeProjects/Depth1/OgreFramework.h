#pragma once
#include"StdAfx.h"
#include "ogresingleton.h"
class OgreFramework :
	public Ogre::Singleton<OgreFramework>,OIS::KeyListener,OIS::MouseListener,OgreBites::SdkTrayListener
{
public:
	OgreFramework(void);
	~OgreFramework(void);
	//
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) ;
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) ;
	//
	virtual bool keyPressed(const OIS::KeyEvent &arg) ;
	virtual bool keyReleased(const OIS::KeyEvent &arg);	
	//
	bool init(const Ogre::String title,OIS::KeyListener *pKeyListener=0,OIS::MouseListener *pMouseListener=0);
	
	//
	Ogre::Root *mRoot;
	Ogre::SceneManager *mSceneMgr;
	Ogre::RenderWindow *mRenderWnd;
	Ogre::Camera *mCamera;
	Ogre::Viewport *mViewport;

	//
	Ogre::Log * mLog;
	OIS::InputManager *mInputMgr;
	OIS::Keyboard *mKeyboard;
	OIS::Mouse *mMouse;
	//
	Ogre::Timer *mTimer;
	//
	bool isOgreToBeShutdown()const{return isShutdown;}
	void updateOgre(Ogre::Real t);
private:
	void moveCamera();
	OgreFramework(const OgreFramework&);
	OgreFramework& operator=(const OgreFramework&);
	//
	OgreBites::SdkTrayManager *mTrayMgr;
	Ogre::FrameEvent mFrameEvt;
	//
	bool isShutdown;

};

