
#include "StdAfx.h"
#include "DemoApp.h"


DemoApp::DemoApp(void)
{
	new OgreFramework();
}


DemoApp::~DemoApp(void)
{
	delete OgreFramework::getSingletonPtr();
}
bool DemoApp::keyPressed(const OIS::KeyEvent &arg) {
	OgreFramework::getSingleton().keyPressed(arg);
	if(OgreFramework::getSingleton().mKeyboard->isKeyDown(OIS::KeyCode::KC_W)){
	}
	return true;
}
bool DemoApp::keyReleased(const OIS::KeyEvent &arg) {
	OgreFramework::getSingleton().keyReleased(arg);
	return true;
}
	//
void DemoApp::start(void){
	if(!OgreFramework::getSingleton().init("Eric's test framework!",this))return;
	this->isShutdown=false;
	OgreFramework::getSingletonPtr()->mLog->logMessage("DemoApp start()!");
	this->setup();
	this->run();


}
void DemoApp::setup(void){
	OgreFramework::getSingleton().mSceneMgr->setSkyBox(true,"Examples/SpaceSkyBox");
	Ogre::SceneManager *mgr=OgreFramework::getSingleton().mSceneMgr;
	Ogre::Light *light=mgr->createLight("MainLight");
	light->setPosition(75,75,75);
	light->setSpecularColour(Ogre::ColourValue(0.25,0,0));
	light->setDiffuseColour(Ogre::ColourValue(0.25,0,0));
	//
	Ogre::Entity * ogreHead=mgr->createEntity("ogreHead","ogrehead.mesh");
	Ogre::SceneNode *node=mgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ogreHead);
	node->setPosition(0,0,0);
	//

	
}
void DemoApp::run(void){
	OgreFramework::getSingleton().mLog->logMessage("Start main loop");
	double timeSinceLastFrame=0;
	double startTime=0;
	OgreFramework::getSingleton().mRenderWnd->resetStatistics();
	while(!this->isShutdown && !OgreFramework::getSingleton().isOgreToBeShutdown()){
		if(OgreFramework::getSingleton().mRenderWnd->isClosed())this->isShutdown=true;
		Ogre::WindowEventUtilities::messagePump();
		if(OgreFramework::getSingleton().mRenderWnd->isActive()){
			//
			startTime=OgreFramework::getSingleton().mTimer->getMicrosecondsCPU();
			//
			OgreFramework::getSingleton().mMouse->capture();
			OgreFramework::getSingleton().mKeyboard->capture();
			//
			OgreFramework::getSingleton().updateOgre(timeSinceLastFrame);
			OgreFramework::getSingleton().mRoot->renderOneFrame();
			//
			timeSinceLastFrame=OgreFramework::getSingleton().mTimer->getMicrosecondsCPU()-startTime;
		}else{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			Sleep(1000);
#else
			sleep(1);
#endif
		}


	}
	OgreFramework::getSingleton().mLog->logMessage("Main loop quit...\nShutdow ogre...");
}