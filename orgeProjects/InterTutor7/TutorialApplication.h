#include "StdAfx.h"

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_
#include "BaseApplication.h"

class TutorialApplication : public BaseApplication,public Ogre::RenderTargetListener
{
public:
	TutorialApplication(void){}
	virtual ~TutorialApplication(void){}
protected:
    virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent&evt);
	virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent &evt);
	virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent &evt);
	//

	Ogre::MovablePlane * mPlane;
	Ogre::Entity * mPlaneEnt;
	Ogre::SceneNode* mPlaneNode;
	Ogre::Rectangle2D *mMiniScreen;
};

#endif // #ifndef __TutorialApplication_h_
