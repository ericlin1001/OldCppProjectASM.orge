#include "StdAfx.h"
#include "TutorialApplication.h"
/*
Ogre::SceneManager *mSceneMgr_1;
	Ogre::SceneManager *mSceneMgr_2;
	//
	Ogre::Camera *mCamera_1;
	Ogre::Camera *mCamera_2;
	//
	Ogre::Viewport *mViewport_1;
	Ogre::Viewport *mViewport_2;*/
  void TutorialApplication::createScene(void){
	  mSceneMgr=mRoot->createSceneManager(Ogre::ST_GENERIC,"firstSM");
	  /* *mFirstSceneMgr;
	Ogre::SceneManager *mSecondSceneMgr;
	*/
	mSceneMgr_1=mRoot->createSceneManager(Ogre::ST_GENERIC,"1SM");
	mSceneMgr_2=mRoot->createSceneManager(Ogre::ST_GENERIC,"2SM");
	//
	mCamera_1=mSceneMgr_1->createCamera("maincamera");
	mCamera_2=mSceneMgr_2->createCamera("maincamera");
	//
	mSceneMgr_1->setSkyBox(true,"Examples/SpaceSkyBox");
	mSceneMgr_2->setSkyDome(true, "Examples/CloudySky", 5, 8);
	//
	//setupViewport(mSceneMgr_1);
	refreshVP();


}
  void TutorialApplication::setupViewport(Ogre::SceneManager *c){
	 mWindow->removeAllViewports();
	 Ogre::Camera *cam=c->getCamera("maincamera");
	 Ogre::Viewport *vp=mWindow->addViewport(cam,0,0,0,1,1);
	 vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	 cam->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
 }
void TutorialApplication::setupDualViewport(Ogre::SceneManager *c,Ogre::SceneManager *b){
	 mWindow->removeAllViewports();
	 Ogre::Camera *cam=c->getCamera("maincamera");
	 Ogre::Viewport *vp=mWindow->addViewport(cam,0,0,0,0.5,1);
	 vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	 cam->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
	 //
	 cam=b->getCamera("maincamera");
	 vp=mWindow->addViewport(cam,1,0.5,0,0.5,1);
	 vp->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5));
	 cam->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));

}
template <class T>
inline void swap(T &a,T &b){T c=b;b=a;a=c;}
bool TutorialApplication::keyPressed( const OIS::KeyEvent &arg ){
	
	switch(arg.key){
	case OIS::KC_V:
		isdual=!isdual;
		refreshVP();
		break;
	case OIS::KC_C:
		swap(mSceneMgr_1,mSceneMgr_2);
		refreshVP();
		break;
	}
	BaseApplication::keyPressed(arg);
	return true;
}
void TutorialApplication::refreshVP(){
	if(isdual){
		setupViewport(mSceneMgr_1);

	}else{
		setupDualViewport(mSceneMgr_1,mSceneMgr_2);
	}
}