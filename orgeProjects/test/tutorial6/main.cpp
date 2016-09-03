#include "StdAfx.h"



void trace(const char *str,const char *cap="Test"){
	MessageBox(NULL,str,"",0);
}
class MyOgre:public Ogre::WindowEventListener,public Ogre::FrameListener{
public:
	MyOgre(void):mRoot(0)
		,mPluginsCfg(Ogre::StringUtil::BLANK)
		,mResourcesCfg(Ogre::StringUtil::BLANK)
	{


	}
	~MyOgre(){
		Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
windowClosed(mWindow);
delete mRoot;
	}
	bool go(void);
protected:
	// Ogre::WindowEventListener
virtual void windowResized(Ogre::RenderWindow* rw);
virtual void windowClosed(Ogre::RenderWindow* rw);
	//Ogre::FrameListener
virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
private:
	Ogre::Root *mRoot;
	Ogre::String mPluginsCfg;
	Ogre::String mResourcesCfg;
	//
	Ogre::RenderWindow * mWindow;
	//
	Ogre::SceneManager *mSceneMgr;
	Ogre::Camera * mCamera;
	Ogre::SceneNode *rootNode;
	//
	OIS::InputManager * mInputManager;
	OIS::Mouse *mMouse;
	OIS::Keyboard *mKeyboard;

};
bool MyOgre::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;
 
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;
 
    return true;
}

//Adjust mouse clipping area
void MyOgre::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);
 
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}
 
//Unattach OIS before window shutdown (very important under Linux)
void MyOgre::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );
 
            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}
//
bool MyOgre::go(void){
#ifdef _DEBUG
	mPluginsCfg="plugins_d.cfg";

	mResourcesCfg="resources_d.cfg";
#else
	mPluginsCfg="plugins.cfg";
	mResourcesCfg="resources.cfg";
#endif
	mRoot=new Ogre::Root(mPluginsCfg);
	//
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);
	//
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))return false;
	//
	mWindow=mRoot->initialise(true,"MyOgre Program");
	//
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	//
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");
	//
	mCamera=mSceneMgr->createCamera("mainCamera");
	mCamera->setPosition(Ogre::Vector3(0,0,80));
	mCamera->lookAt(0,0,-300);
	mCamera->setNearClipDistance(5);
	mCamera->setFarClipDistance(300);//need to change.
	//
	Ogre::Viewport *vp=mWindow->addViewport(mCamera,0,0,0,1,1);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
	
	//add some contents to the scene.
	rootNode=mSceneMgr->getRootSceneNode();
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5,0.5,0.5));
	//

	Ogre::Entity *ninjaEnt=mSceneMgr->createEntity("ninja","ninja.mesh");
	Ogre::SceneNode *node1=rootNode->createChildSceneNode("node1");
	node1->attachObject(ninjaEnt);
	//
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("orgerhead", "ogrehead.mesh");
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);/**/
	//
	/**/Ogre::Light *l=mSceneMgr->createLight("mainlight");
	l->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
	l->setDiffuseColour(Ogre::ColourValue(0.5,0.5,0.5));
	l->setSpecularColour(Ogre::ColourValue(0.5,0.5,0.5));
	l->setDirection(Ogre::Vector3(0,-1,-1));
	//input:
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd=0;
	std::ostringstream windowsHndStr;
	mWindow->getCustomAttribute("WINDOW",&windowHnd);
	windowsHndStr<<windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"),windowsHndStr.str()));
	//
	mInputManager=OIS::InputManager::createInputSystem(pl);
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, false ));
	//
	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	//
	mRoot->addFrameListener(this);
mRoot->startRendering();
/*
	//render loop
	while(1){
		Ogre::WindowEventUtilities::messagePump();
		if(mWindow->isClosed()){
			return false;
		}
		if(!mRoot->renderOneFrame())return false;
	}
	*/
	//

	//trace("at the end");
	return true;
}
bool f1(bool b){
	trace("f1");
	return b;
}
bool f2(bool b){
	trace("f2");
	return b;
}
//
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		MyOgre app;

		/*if(f1(false) && f2(true)){
		trace("in");
		}
		trace("out");*/
		try {

			app.go();
		} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}
		//MessageBox(NULL,"exiting...","",0);
		return 0;
	}

#ifdef __cplusplus
}
#endif
