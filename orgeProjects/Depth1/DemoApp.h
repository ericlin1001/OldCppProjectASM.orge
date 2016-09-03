#pragma once
#include "StdAfx.h"
#include "ogreframework.h"
class DemoApp :public OIS::KeyListener
{
public:
	DemoApp(void);
	~DemoApp(void);
	//
		virtual bool keyPressed(const OIS::KeyEvent &arg) ;
		virtual bool keyReleased(const OIS::KeyEvent &arg) ;
	//
	void start(void);
	void setup(void);
	void run(void);
	//
	bool isShutdown;

};

