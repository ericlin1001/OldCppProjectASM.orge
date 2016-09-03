#include "StdAfx.h"
#include "TutorialApplication.h"
void TutorialApplication::createScene(void){
	/*Ogre::Entity *fish=mSceneMgr->createEntity("fish","penguin.mesh");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(fish);
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25,0.25,0.25));
	*/
	/**/mRender=&CEGUI::OgreRenderer::bootstrapSystem();
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	//
	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook","MouseArrow");
	//
	/*CEGUI::Window *guiRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout("TextDemo.layout"); 
CEGUI::System::getSingleton().setGUISheet(guiRoot);*/
	CEGUI::WindowManager &wmgr=CEGUI::WindowManager::getSingleton();
	CEGUI::Window * sheet=wmgr.createWindow("DefaultWindow","CEGUIDemo/Sheet");
	CEGUI::Window *quit=wmgr.createWindow("TaharezLook/Button","CEGUIDemo/QuitButton");
	//quit->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&quit,this));
	quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TutorialApplication::quit, this));
	
	quit->setText("Quit");
	quit->setSize(CEGUI::UVector2(CEGUI::UDim(0,300),CEGUI::UDim(0,100)));
	sheet->addChildWindow(quit);
	CEGUI::System::getSingleton().setGUISheet(sheet);
	//

	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, -300));
headNode->attachObject(ogreHead);
//
Ogre::TexturePtr tex=mRoot->getTextureManager()->createManual("RTT",
	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	Ogre::TEX_TYPE_2D,
	512,
	512,
	0,
	Ogre::PF_R8G8B8,
	Ogre::TU_RENDERTARGET);
Ogre::RenderTexture *rtex=tex->getBuffer()->getRenderTarget();
//
Ogre::Camera *cam = mSceneMgr->createCamera("RTTCam");
cam->setPosition(100, -100, -400);
cam->lookAt(0, 0, -300);
Ogre::Viewport *v = rtex->addViewport(cam);
v->setOverlaysEnabled(false);
v->setClearEveryFrame(true);
v->setBackgroundColour(Ogre::ColourValue::Black);
//
CEGUI::Texture &guiTex = mRender->createTexture(tex);
//
CEGUI::Imageset &imageSet =
  CEGUI::ImagesetManager::getSingleton().create("RTTImageset", guiTex);
imageSet.defineImage("RTTImage",
                     CEGUI::Point(0.0f, 0.0f),
                     CEGUI::Size(guiTex.getSize().d_width,
                                 guiTex.getSize().d_height),
                     CEGUI::Point(0.0f, 0.0f));
//
CEGUI::Window *si = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "RTTWindow");
si->setSize(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),
                            CEGUI::UDim(0.4f, 0)));
si->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),
                                CEGUI::UDim(0.0f, 0)));
//
si->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet.getImage("RTTImage")));
sheet->addChildWindow(si);

}


void  TutorialApplication::createFrameListener(void){
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
 
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
 
    mInputManager = OIS::InputManager::createInputSystem( pl );
 
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
 
    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);
 
    //Set initial mouse clipping size
    windowResized(mWindow);
 
    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
 
    mRoot->addFrameListener(this);

	/*
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    mTrayMgr->hideCursor();

    // create a params panel for displaying sample details
    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(9, "Bilinear");
    mDetailsPanel->setParamValue(10, "Solid");
    mDetailsPanel->hide();

    mRoot->addFrameListener(this);*/
}

// Ogre::FrameListener
bool  TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt){
	if(mWindow->isClosed())
        return false;
 
    if(mShutDown)
        return false;
 
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
 
    //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
 /*
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }*/
    return true;

}

// OIS::KeyListener
bool  TutorialApplication::keyPressed( const OIS::KeyEvent &arg ){
	/*bool ret=BaseApplication::keyPressed(arg);
	return ret;*/
	CEGUI::System &sys = CEGUI::System::getSingleton();
sys.injectKeyDown(arg.key);
sys.injectChar(arg.text);
return true;
}
bool  TutorialApplication::keyReleased( const OIS::KeyEvent &arg ){
	/*bool ret=BaseApplication::keyReleased(arg);
	return ret;*/
	CEGUI::System::getSingleton().injectKeyUp(arg.key);
return true;
}
CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}

// OIS::MouseListener
bool  TutorialApplication::mouseMoved( const OIS::MouseEvent &arg ){
	/*bool ret=BaseApplication::mouseMoved(arg);
	return ret;*/
	CEGUI::System &sys = CEGUI::System::getSingleton();
sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
// Scroll wheel.
if (arg.state.Z.rel)
    sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
return true;
}
bool  TutorialApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	/*bool ret=BaseApplication::mousePressed(arg,id);
	return ret;*/
	CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
return true;
}
bool  TutorialApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	/*bool ret=BaseApplication::mouseReleased(arg,id);
	return ret;*/
	CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
return true;
}
bool TutorialApplication::quit(const CEGUI::EventArgs &e)
{
	
	mShutDown=true;
    return true;
}