#pragma once
#include "observer.h"

/*
Class Observable: Abstract class used to implement the map observer pattern
*/
class Observable{
  
public:
	virtual void attach(Observer & ob)=0;
	virtual void detach(Observer & ob)=0;
	virtual void notify()=0;
};