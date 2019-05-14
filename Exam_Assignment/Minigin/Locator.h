#pragma once
#include "Audio.h"
#include "fmod.hpp"
#include <map>

class Locator
{
public:

  static void initialize() { service_ = &nullService_;}

  static Audio& getAudio() { return *service_; }

  static void provide(Audio* service)
  {
    if (service == NULL)
    {
      // Revert to null service.
      service_ = &nullService_;
    }
    else
    {
      service_ = service;
    }
  }

private:
	static Audio* service_;
	static NullAudio nullService_;

};
