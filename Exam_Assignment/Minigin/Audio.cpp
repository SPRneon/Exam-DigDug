#include "MiniginPCH.h"
#include "Audio.h"
#include "fmod_errors.h"
#include <Windows.h>

//BASECLASS
//*********
void Audio::init()
{
	FMOD_RESULT res;
	unsigned int ver;
	int nrDrivers;

	res = FMOD::System_Create(&m_pFmodSystem);
	checkResult("Audio::init > Failed to create FMOD system",res);
	res = m_pFmodSystem->getVersion(&ver);
	checkResult("Audio::init > Failed to get FMOD version",res);
	
	if (ver < FMOD_VERSION)
	{
		std::cout << L"SoundManager Initialization Failed!\n\nYou are using an old version of FMOD %08x. This program requires %08x\n",
		ver, FMOD_VERSION;
		return;
	}

	res = m_pFmodSystem->getNumDrivers(&nrDrivers);
	checkResult("Audio::init > Failed to get number of FMOD drivers",res);
	if (nrDrivers == 0)
	{
		res = m_pFmodSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		checkResult("Audio::init > Failed to set FMOD outputtype to no sound",res);
	}
	else
	{
		res = m_pFmodSystem->init(32, FMOD_INIT_NORMAL, nullptr);
		checkResult("Audio::init > Failed to set FMOD output (normal)",res);
	}
}

bool Audio::checkResult(const std::string& message,FMOD_RESULT res)
{
	 if (res != FMOD_OK) {
        std::cerr << message << ": " << res << " " << FMOD_ErrorString(res) << std::endl;

        return false;
    }
    return true;
}

//CONSOLEAUDIO
//************
void ConsoleAudio::addSound(std::string filename, std::string soundName) 
{
		FMOD::Sound* pSound = nullptr;
		auto res = m_pFmodSystem->createSound(filename.c_str(),FMOD_DEFAULT,nullptr, &pSound);
		checkResult("ConsoleAudio::addSound > Failed to create sound", res);
		m_pSounds.insert_or_assign(soundName,pSound);
}

void ConsoleAudio::playSound(std::string soundname)
  {
	FMOD::Channel *channel = nullptr;
	auto sound = m_pSounds.at(soundname);
	if(sound)
		m_pFmodSystem->playSound(sound, nullptr, false, &channel);
	else
		std::cout << "ConsoleAudio::playSound() > There was no soundfile for " << soundname << std::endl;
  }

//LOGGEDAUDIO
//***********
void LoggedAudio::addSound(std::string filename, std::string soundName) 
{
		FMOD::Sound* pSound = nullptr;
		auto res = m_pFmodSystem->createSound(filename.c_str(),FMOD_DEFAULT,nullptr, &pSound);
		checkResult("ConsoleAudio::addSound > Failed to create sound", res);
		m_pSounds.insert_or_assign(soundName,pSound);
}


void LoggedAudio::playSound(std::string filename)
  {
	auto pos = filename.rfind("/");
	std::string str = "Playing: ";
	str.append(filename.substr(pos + 1, filename.size() - pos + 1));
    log(str.c_str());
    wrapped_.playSound(filename);
  }
