#include "StdAfx.h"
/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
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
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &e);

private:
	bool processUnbufferedInput(const Ogre::FrameEvent &evt);
	//
	Ogre::TerrainGlobalOptions *mTerrainGlobals;
	Ogre::TerrainGroup *mTerrainGroup;
	bool mTerrainsImported;
	//
	void defineTerrain(long x,long y);
	void initBlendMaps(Ogre::Terrain *terrain);
	void configureTerrainDefaults(Ogre::Light * light);
	//
	OgreBites::Label* mInfoLabel;
};

#endif // #ifndef __TutorialApplication_h_
