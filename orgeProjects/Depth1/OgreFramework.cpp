#include "StdAfx.h"
#include "OgreFramework.h"
OgreFramework* Ogre::Singleton<OgreFramework>::ms_Singleton=0;
OgreFramework::OgreFramework(void):
	mRoot(0),
	mTimer(0),
	mInputMgr(0),
	isShutdown(false)
{
	this->mFrameEvt= Ogre::FrameEvent();
}
bool OgreFramework::init(const Ogre::String title,OIS::KeyListener *pKeyListener,OIS::MouseListener *pMouseListener){
	Ogre::LogManager *logMgr=new Ogre::LogManager();
	this->mLog=Ogre::LogManager::getSingleton().createLog("EricTest/EricOgreFramework.log",true,true,false);
	this->mLog->setDebugOutputEnabled(false);
	//
	this->mRoot=new Ogre::Root("EricTest/ericplugins_d.cfg","EricTest/EricOgre.cfg");
	//
	
	if(!this->mRoot->restoreConfig() && !this->mRoot->showConfigDialog())return false;
	this->mRenderWnd=mRoot->initialise(true,title);
	//
	this->mSceneMgr=mRoot->createSceneManager(Ogre::SceneType::ST_GENERIC);
	//
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2,0.2,0.2));
	this->mCamera=mSceneMgr->createCamera("MainCamera");
	mCamera->setPosition(0,60,80);
	mCamera->lookAt(0,0,0);
	mCamera->setNearClipDistance(1);
	//mCamera->setFarClipDistance(100000);
	//
	this->mViewport=this->mRenderWnd->addViewport(this->mCamera,0,0,0,1,1);
	this->mViewport->setBackgroundColour(Ogre::ColourValue::Black);
	mCamera->setAspectRatio((Ogre::Real)mViewport->getActualWidth()/(Ogre::Real)mViewport->getActualHeight());
	//
	//setup the OIS.
	size_t hWnd=0;
	OIS::ParamList paramList;
	this->mRenderWnd->getCustomAttribute("WINDOW",&hWnd);
	paramList.insert(OIS::ParamList::value_type("WINDOW",Ogre::StringConverter::toString(hWnd)));

	//test 
	this->mLog->logMessage("hWnd="+Ogre::StringConverter::toString(hWnd));
	this->mLog->logMessage("window's name="+this->mRenderWnd->getName());
	//
	this->mInputMgr=OIS::InputManager::createInputSystem(paramList);
	this->mKeyboard =static_cast<OIS::Keyboard*>(this->mInputMgr->createInputObject(OIS::Type::OISKeyboard,true));
	this->mMouse=static_cast<OIS::Mouse*>(this->mInputMgr->createInputObject(OIS::Type::OISMouse,true));
	mMouse->getMouseState().height=mRenderWnd->getHeight();
	mMouse->getMouseState().width=mRenderWnd->getWidth();

	//
	if(pKeyListener==0)this->mKeyboard->setEventCallback(this);
	else this->mKeyboard->setEventCallback(pKeyListener);
	if(pMouseListener==0)this->mMouse->setEventCallback(this);
	else this->mMouse->setEventCallback(pMouseListener);

	//setup the resource....
	Ogre::ConfigFile cf;
	cf.load("EricTest/ericresources_d.cfg");
	Ogre::ConfigFile::SectionIterator cfi=cf.getSectionIterator();
	while(cfi.hasMoreElements()){
		Ogre::String sceName=cfi.peekNextKey();//no use.
		Ogre::ConfigFile::SettingsMultiMap *settings=cfi.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for(i=settings->begin();i!=settings->end();i++){
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(i->second,i->first);
		}
	}
	//
	mLog->logMessage("default resourceGroupName="+Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	//
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	//
	this->mTimer=new Ogre::Timer();
	mTimer->reset();
	//
	this->mTrayMgr=new OgreBites::SdkTrayManager("TrayMgr",this->mRenderWnd,this->mMouse,this);
	this->mTrayMgr->showFrameStats(OgreBites::TrayLocation::TL_BOTTOMLEFT);
	//mTrayMgr->showLogo(OgreBites::TrayLocation::TL_BOTTOMRIGHT);
	mTrayMgr->hideCursor();



	//
	mRenderWnd->setActive(true);
	this->isShutdown=false;
	//

	return true;
}
//172.18.157.121
OgreFramework::~OgreFramework(void){
	
	if(mTimer!=0)delete mTimer;
	if(mInputMgr!=0)OIS::InputManager::destroyInputSystem(this->mInputMgr);
	
	if(mRoot!=0)delete mRoot;
}
void OgreFramework::updateOgre(Ogre::Real t){
	moveCamera();
}
void OgreFramework::moveCamera(void){
		const Ogre::Real camMove=0.5;
	Ogre::Vector3 camVec=Ogre::Vector3::ZERO;
	if(this->mKeyboard->isKeyDown(OIS::KeyCode::KC_W)){
		camVec.z-=camMove;
	}
	if(this->mKeyboard->isKeyDown(OIS::KeyCode::KC_S)){
		camVec.z+=camMove;
	}
	if(this->mKeyboard->isKeyDown(OIS::KeyCode::KC_A)){
		camVec.x-=camMove;
	}
	if(this->mKeyboard->isKeyDown(OIS::KeyCode::KC_D)){
		camVec.x+=camMove;
	}
	mCamera->moveRelative(camVec);
	}
bool OgreFramework:: mouseMoved( const OIS::MouseEvent &arg ){
	mCamera->yaw(Ogre::Degree(-arg.state.X.rel*0.1));
	mCamera->pitch(Ogre::Degree(-arg.state.Y.rel*0.1));
	
	return true;
}
bool OgreFramework::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return true;
}
bool OgreFramework::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return true;
}
//
bool OgreFramework::keyPressed(const OIS::KeyEvent &arg) {
	if(this->mKeyboard->isKeyDown(OIS::KeyCode::KC_ESCAPE)){
		this->isShutdown=true;return true;
	}
	if(this->mKeyboard->isKeyDown(OIS::KeyCode::KC_F5)){
		this->mRenderWnd->writeContentsToTimestampedFile("EricTest/pic",".png");return true;
	}
	static int polygonMode=0;
	if(this->mKeyboard->isKeyDown(OIS::KeyCode::KC_R)){
		polygonMode=++polygonMode%3;
		switch(polygonMode){
		case 0:
			
			mCamera->setPolygonMode(Ogre::PolygonMode::PM_SOLID);
			break;
		case 1:
			mCamera->setPolygonMode(Ogre::PolygonMode::PM_WIREFRAME);
			break;
		case 2:
			mCamera->setPolygonMode(Ogre::PolygonMode::PM_POINTS);
			break;
		}
		return true;
	}
	return true;
}
bool OgreFramework::keyReleased(const OIS::KeyEvent &arg){

	return true;
}
/*OgreFramework(void);
~OgreFramework(void);
//
bool mouseMoved( const MouseEvent &arg );
bool mousePressed( const MouseEvent &arg, MouseButtonID id ) ;
bool mouseReleased( const MouseEvent &arg, MouseButtonID id ) ;
//
bool keyPressed(const KeyEvent &arg) ;
bool keyReleased(const KeyEvent &arg);	
//
bool init(Ogre::String title,OIS::KeyListener *pKeyListener=0,OIS::MouseListener *pMouseListener=0);

//
Ogre::Root *mRoot;
Ogre::SceneManager *mSceneMgr;
Ogre::RenderWindow *mRenderWnd;
Ogre::Log * mLog;
OIS::InputManager *mInputMgr;
OIS::Keyboard *mKeyboard;
OIS::Mouse *mMouse;
//
private:
OgreFramework(const OgreFramework&);
OgreFramework& operator=(const OgreFramework&);
//
OgreBites::SdkTrayManager *mTrayMgr;
Ogre::FrameEvent mFrameEvt;
//
bool isShutdown;*/