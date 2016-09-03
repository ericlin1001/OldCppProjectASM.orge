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
    virtual void destroyScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	//
private:
	Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
    bool mTerrainsImported;
 
    void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);
};

#endif // #ifndef __TutorialApplication_h_
