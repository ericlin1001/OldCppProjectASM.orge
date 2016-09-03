#include "StdAfx.h"

#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{;;
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	//below codes can be run.
	/*
	// Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
 
    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);
	//MessageBox( NULL, "asdf", "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	//
	
	//
    //head1
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
    Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    headNode->attachObject(ogreHead);
	headNode->yaw(Ogre::Degree(-90));//->
 
    
	//head2
	Ogre::Entity* ogreHead2=mSceneMgr->createEntity("Head2","ogrehead.mesh");
	Ogre::SceneNode*headNode2= mSceneMgr->getRootSceneNode()->
	createChildSceneNode("HeadNode2",Ogre::Vector3(100,0,0));
	headNode2->attachObject(ogreHead2);
	headNode2->pitch(Ogre::Degree(-90));

	//head3
	Ogre::Entity* ogreHead3=mSceneMgr->createEntity("Head3","ogrehead.mesh");
	Ogre::SceneNode*headNode3=mSceneMgr->getRootSceneNode()->
	createChildSceneNode("HeadNode3",Ogre::Vector3(200,0,0));
	headNode3->attachObject(ogreHead3);
	headNode3->roll(Ogre::Degree(-90));
	headNode3->translate(0,0,20);
	*/
}

