#pragma once
#include <string>
#include <iostream>

class View{
public:
  static std::string getString();
  static int getInt();
  static void inform(std::string msg);
  static void prompt(std::string msg);
};