// test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

namespace SpaceInvader{
	#include<vector>
#include<iostream>
#include<string>
	using namespace std;
	//
	class GameState;
	class Object;
	class Character;

	class Vector2D{
	public:
		Vector2D(){
			assign(0,0);
		}
		Vector2D(int x,int y){
			assign(x,y);
		}
		void assign(int x,int y){
			this->x=x;
			this->y=y;
		}
		void print(){
			cout<<"Vector2D("<<x<<","<<y<<")";
		}
		int x;int y;
	};
	typedef Real double;
	//

	class GameState{
	public:
		GameState(){
			time=0;
		}
		int getNumberCharacters()const{
			return characters.size();
		}
		int getNumberObjects()const {
			return objects.size();
		}
		inline Object*getObject(int i){
			return objects[i];
		}
		void addObject(Object *o){
			objects.push_back(o);
		}
		void addCharacter(Character *c){
			characters.push_back(c);
		}
		inline Character*getCharacter(int i){
			return characters[i];
		}
		Real getTime()const {return time;}
		inline void setTime(Real time){this->time=time;}
	private:
		Real time;
		vector<Object *>objects;
		vector<Character *>characters;
	};

	class Object{
	public:
		Object(GameState *gs){
			this->gs=gs;
		}
		virtual ~Object();
		inline Vector2D const &getPosition()const{return pos;}
		inline void setPosition(Vector2D const& pos){this->pos=pos;}
		inline Real const &getMass()const{return this->mass;}
		inline void setMass(Real const& mass){this->mass=mass;}
	protected:
		GameState *gs;
	private:
		Vector2D pos;
		Real mass;
	};
	class Character:public Object{
	public:
		Character(GameState *gs,Controller *controller){
			Object::Object(gs);
			this->controller=controller;
		}
		~Character(){
		}
		inline Controller*getController(){
			return this->controller;
		}
		inline void setController(Controller *controller){
			this->controller=controller;
		}
		inline Vector2D const & getVelocity(){return this->vel;}
		inline void setVecocity(Vector2D const &vel){this->vel=vel;}
	protected:

	private:
		Controller *controller;
		Vector2D vel;
	};
	class Action{
	public:
		typedef union{
			Real angle;
			int bulletType;
			Vector2D trans;
		} Arg;
		enum Action_Type{UNKNOWN,ROTATE,MOVEBY,FIRE};
		Action(){
			setType(Action_Type::UNKNOWN);
		}
		void setType(int type){
			this->type=type;
			switch(type){
			case Action_Type::ROTATE:
				name="ROTATE";
				break;
			case Action_Type::MOVEBY:
				name="MOVEBY";
				break;
			case Action_Type::FIRE:
				name="FIRE";
				break;
			default:
				name="UNKNOWN";
			}
		}
		Arg &getArg(){
			return this->arg;
		}
		void print(){
			cout<<"Action("<<name<<"(";
			switch(type){
			case Action_Type::ROTATE:
				cout<<arg.angle;
				break;
			case Action_Type::MOVEBY:
				cout<<arg.trans;
				break;
			case Action_Type::FIRE:
				cout<<arg.bulletType;
				break;
			default:
			}
			cout<<"))";
		}
	protected:

	private:
		int type;
		string name;
		Arg arg;
	};
class Bullet:public Object{
	public:
		Bullet(){
		}
	protected:

	private:

	};
	class Perception{
	public:
		Perception(GameState *gs){
			this->gs=gs;
		}
		void setIndex(int i){
			this->myIndex=i;
		}
		GameState *getGameState(){
			return gs;
		}
	protected:
	private:
		GameState *gs;
		int myIndex;
	};
	class Stimulator{
	};

	class Controller{
	public:
		Controller( Perception *perception){
			this->perception=perception;
		}
		virtual void calAction(int const myIndex)=0;
		inline Action const &getAction(){return this->action;}
	protected:

	private:
		Perception *perception;
		Action action;
	};
	class ControllerPC:public Controller{
	public:
		ControllerPC( Perception *perception){
			Controller::Controller(perception);
		}
		void up(){
		}
		void down(){
		}
		void left(){
		}
		void rotateLeft(){
		}
		void rotateRight(){
		}
		void fire(){
		}
		void selectBullet(int type){
		}
		void calAction(int const myIndex){}
	};
	class ControllerNPC:public Controller{
	public:
		ControllerNPC( Perception *perception){
			Controller::Controller(perception);
		}
		void calAction(int const myIndex){
			this->perception->setIndex(myIndex);
		}
	private:
	
	};
	class Render{
	};

	//global variables:
	GameState gs;
	void init(){
		Perception perception(&gs);

		const int numCharacters=2;
		for(int i=0;i<numCharacters;i++){
			Character *c=NULL;
			if(i==0){//the player
				c=new Character(&gs,new Controller(&perception));
			}else{//the computor player:
				c=new Character(&gs,new Controller(&perception));
			}
			gs.addCharacter(c);
		}
	}

}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

