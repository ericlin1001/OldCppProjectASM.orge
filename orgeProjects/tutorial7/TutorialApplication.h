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
    virtual void createScene(void);
	virtual void createFrameListener(void);

	 // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	bool quit(const CEGUI::EventArgs &e);
	//
	CEGUI::OgreRenderer* mRender;

};

#endif // #ifndef __TutorialApplication_h_
