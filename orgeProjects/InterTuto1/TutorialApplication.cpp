#include "StdAfx.h"
#include "TutorialApplication.h"
/*Ogre::Real mDistance;                  // The distance the object has left to travel
Ogre::Vector3 mDirection;              // The direction the object is moving
Ogre::Vector3 mDestination;            // The destination the object is moving towards

Ogre::AnimationState *mAnimationState; // The current animation state of the object

Ogre::Entity *mEntity;                 // The Entity we are animating
Ogre::SceneNode *mNode;                // The SceneNode that the Entity is attached to
std::deque<Ogre::Vector3> mWalkList;   // The list of points we are walking to

Ogre::Real mWalkSpeed;                */
void TutorialApplication::roateRobot(void){
	/*Ogre::Vector3 src=this->mNode->getOrientation() * Ogre::Vector3::UNIT_X;
	src.y=0;
	this->mDestination.y=0;
	src.normalise();
	this->mDirection.normalise();
	Ogre::Quaternion quat=src.getRotationTo(this->mDirection);
	this->mNode->rotate(quat);*/
	Ogre::Vector3 src= mNode->getOrientation()*Ogre::Vector3::UNIT_X;
	mNode->rotate(src.getRotationTo(this->mDirection));

}
void TutorialApplication::createScene(void){
	
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1,1,1));
	mEntity=mSceneMgr->createEntity("Robot","robot.mesh");
	mNode=mSceneMgr->getRootSceneNode()->createChildSceneNode("RobotNode",Ogre::Vector3(0,0,0));
	mNode->attachObject(mEntity);
	mNode->setPosition(0,0,0);
	//
	for(int t=0;t<4;t++){
		const Ogre::Real range=300;
		Ogre::Real x=Ogre::Math::RangeRandom(-range,range);
		Ogre::Real z=Ogre::Math::RangeRandom(-range,range);
		mWalkList.push_back(Ogre::Vector3(x,-10,z));
	/*mWalkList.push_back(Ogre::Vector3(550,0,50));
	mWalkList.push_back(Ogre::Vector3(-100,0,200));*/
	}
	//
	for(int i=0;i< (this->mWalkList.size());i++){
		Ogre::Vector3 d=this->mWalkList[i];
		Ogre::Entity *ent=mSceneMgr->createEntity("knot.mesh");
		Ogre::SceneNode *node=mSceneMgr->getRootSceneNode()->createChildSceneNode();
		node->setPosition(d);
		node->attachObject(ent);
		node->setScale(0.05,0.05,0.05);
		
	}
	 mCamera->setPosition(90.0f, 280.0f, 535.0f);
        mCamera->pitch(Ogre::Degree(-30.0f));
        mCamera->yaw(Ogre::Degree(-15.0f));
	//

	//
	//this->mCamera->setPosition(Ogre::Vector3(0,100,100));
	//this->mCamera->lookAt(Ogre::Vector3(0,0,0));
	/*
	Ogre::Entity * ent;Ogre::SceneNode * node;
	ent=mSceneMgr->createEntity("Knot1","knot.mesh");
	node=mSceneMgr->getRootSceneNode()->createChildSceneNode("KnotNode1");
	node->attachObject(ent);
	node->setScale(0.1,0.1,0.1);
	*/
	//
	/*
	//
	ent = mSceneMgr->createEntity("Knot2", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot2Node",
	Ogre::Vector3(550.0f, -10.0f,  50.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);

	ent = mSceneMgr->createEntity("Knot3", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot3Node",
	Ogre::Vector3(-100.0f, -10.0f,-200.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);
	//*/
	/*mCamera->setPosition(90,280,535);
	mCamera->pitch(Ogre::Degree(-30));
	mCamera->yaw(Ogre::Degree(-15));*/
}
//
void TutorialApplication::createFrameListener(void){
	BaseApplication::createFrameListener();
	mAnimationState=mEntity->getAnimationState("Idle");mAnimationState->setEnabled(true);
	mAnimationState->setLoop(true);
	//init
	mWalkSpeed=30;
	mDirection=Ogre::Vector3::ZERO;
	//
	/*mNode->setPosition(mWalkList.front());
	Ogre::SceneNode *node=mSceneMgr->getSceneNode("KnotNode");
	node->setPosition(mWalkList.front());*/

}
bool TutorialApplication::nextLocation(void){
	if(mWalkList.empty())return false;
	return true;
}
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent &evt){
	bool r=BaseApplication::frameRenderingQueued(evt);
	mAnimationState->addTime(evt.timeSinceLastFrame);
	if(mDirection==Ogre::Vector3::ZERO){
		if(nextLocation()){
			mAnimationState=mEntity->getAnimationState("Walk");mAnimationState->setEnabled(true);
			mAnimationState->setLoop(true);
			//
			this->mDestination=this->mWalkList.front();
			this->mWalkList.pop_front();
			this->mDirection=this->mDestination-this->mNode->getPosition();
			this->mDistance=this->mDirection.normalise();
			//
			this->roateRobot();
			//to move
			/*Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
			mDistance -= move;
			if(mDistance<=0){
				mNode->setPosition(mDestination);
				mDirection=Ogre::Vector3::ZERO;
			}else{
				//to move the robot.
				mNode->translate(mDirection * move);
			}*/
		}else{
			//stop.
			mAnimationState = mEntity->getAnimationState("Idle");
			mAnimationState->setLoop(true);
			mAnimationState->setEnabled(true);
		}
	}else{
		Ogre::Real move=this->mWalkSpeed*evt.timeSinceLastFrame;
		this->mDistance-=move;
		if(this->mDistance<0){
			this->mNode->setPosition(this->mDestination);
			this->mDirection=Ogre::Vector3::ZERO;
		}else{
			this->mNode->translate(this->mDirection*move);
		}
	}



	return r;

}
