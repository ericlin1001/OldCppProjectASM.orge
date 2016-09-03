#include "StdAfx.h"

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_
#include "BaseApplication.h"

class TutorialApplication : public BaseApplication
{
public:
	TutorialApplication(void){isdual=false;}
	virtual ~TutorialApplication(void){}
protected:
    virtual void createScene(void);
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	//
private:
	Ogre::SceneManager *mSceneMgr_1;
	Ogre::SceneManager *mSceneMgr_2;
	//
	Ogre::Camera *mCamera_1;
	Ogre::Camera *mCamera_2;
	//
	Ogre::Viewport *mViewport_1;
	Ogre::Viewport *mViewport_2;
	//
	bool isdual;
	//
	void setupViewport(Ogre::SceneManager *c);
	void setupDualViewport(Ogre::SceneManager *c,Ogre::SceneManager *b);
	//
	void refreshVP();
};

#endif // #ifndef __TutorialApplication_h_
