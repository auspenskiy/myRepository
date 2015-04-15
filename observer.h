#pragma once

/*
Class Observable: Abstract class used to implement the map observer pattern
*/
class Observer{
public:
  virtual void update()=0;
};