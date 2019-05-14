#pragma once
#include "MiniginPCH.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include "fmod.h"
#include "fmod.hpp"

//Sources used for this feature: 
//	Game Programming Patterns by Robert Nystrom
class Audio
{
public:
	virtual ~Audio() {}
	void init();
	bool checkResult(const std::string& message,FMOD_RESULT res);
	virtual void addSound(std::string filename, std::string soundName) = 0;
	virtual void playSound(std::string filename) = 0;
	virtual void stopSound(std::string filename) = 0;
	virtual void stopAllSounds() = 0;

protected:
	FMOD::System* m_pFmodSystem = nullptr;
	std::map<std::string,FMOD::Sound*> m_pSounds;
};

class ConsoleAudio final : public Audio
{
public:
	virtual void addSound(std::string filename, std::string soundName); 
	


  virtual void playSound(std::string soundname);
 

  virtual void stopSound(std::string filename) {UNREFERENCED_PARAMETER(filename);}

  virtual void stopAllSounds(){  }
};

class NullAudio: public Audio
{
public:
	virtual void addSound(std::string filename, std::string soundName) override {UNREFERENCED_PARAMETER(filename); UNREFERENCED_PARAMETER(soundName); }
	virtual void playSound(std::string filename) override{  UNREFERENCED_PARAMETER(filename);/* Do nothing. */ }
	virtual void stopSound(std::string filename) override{  UNREFERENCED_PARAMETER(filename);/* Do nothing. */ }
	virtual void stopAllSounds()override{ /* Do nothing. */ }
};

class LoggedAudio : public Audio
{
public:
  LoggedAudio(Audio &wrapped)
  : wrapped_(wrapped)
  {}

	virtual void addSound(std::string filename, std::string soundName);

  virtual void playSound(std::string filename);

  virtual void stopSound(std::string filename)
  {
    log("stop sound");
    wrapped_.stopSound(filename);
  }

  virtual void stopAllSounds()
  {
    log("stop all sounds");
    wrapped_.stopAllSounds();
  }

private:
  void log(const char* message)
  {
    std::cout << message << std::endl;
  }

  Audio &wrapped_;
};