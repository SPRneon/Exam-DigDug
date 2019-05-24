#include "MiniginPCH.h"
#include "InputManager.h"
#include <minwinbase.h>
#include <iostream>



//*******************//
//***INPUTMANAGER***//
//*******************//
dae::InputManager::InputManager()
{
	
}

//CLEANUP
void dae::InputManager::CleanUp()
{
	for(auto& gamepad : m_pGamePads)
		gamepad->CleanUp();
	m_pGamePads.clear();
	m_pCurrentGamePad = nullptr;
	m_InputActions.clear();
	m_pCommands.clear();
	
}

void dae::Gamepad::CleanUp()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&previousState, sizeof(XINPUT_STATE));
}



void dae::InputManager::Init()
{
	if(m_IsInitialized)
		throw std::exception("InputManager::Init() > The inputmanager has already been initalized");
	//Init keyboard and mouse

	m_UseKeyboard = true;

	KBcurrentState.fill(false);
	KBpreviousState.fill(false);
	

	if(InitGamepads())
		m_UseGamepad = true;

	std::cout<< "Finished initalizing the input manager" << std::endl;
	std::cout << "Number of connected gamepads: " << nGamepads << std::endl;

	m_IsInitialized = true;
	
}

bool dae::InputManager::InitGamepads()
{
	int playerID = -1;
	XINPUT_STATE state;
	for (DWORD i = 0; i < XUSER_MAX_COUNT && playerID == -1; i++)
	{
	ZeroMemory(&state, sizeof(XINPUT_STATE));

    if (XInputGetState(i, &state) == ERROR_SUCCESS)
		playerID = i;
	}
	
	if(playerID != -1)
	{
		m_pGamePads.push_back(std::make_shared<Gamepad>(playerID));
	}
	//Set number of gamepads
	nGamepads = (unsigned int)m_pGamePads.size();
	//Does every player have a gamepad?
	if (nGamepads != nPlayers)
			return false;

	// select current player
	currentlyActivePlayer = 0;
	if(m_pGamePads.size() > 0)
		m_pCurrentGamePad = m_pGamePads[0];

	
	return true;
}
 



void dae::InputManager::ProcessInput()
{

	if(m_UseKeyboard)
		ProcessKeyboardInput();
	if(m_UseGamepad)
		ProcessGamePadInput();
	HandleInput();
}

void dae::InputManager::RefreshInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&previousState, sizeof(XINPUT_STATE));
}






bool dae::InputManager::AddInput(InputAction action, std::shared_ptr<BaseCommand> pCommand, bool replaceCommand)
{
	auto got = m_InputActions.find(action.ActionId);
	if(got == m_InputActions.end()) //Input action was not yet present
	{
		//Add new vector to key in the map
		auto v = std::vector<std::shared_ptr<BaseCommand>>();
		v.push_back(pCommand);
		m_InputActions.insert_or_assign(action.ActionId, action);
		m_pCommands.insert_or_assign(action.ActionId, v);
		return true;
	}
	else if(replaceCommand)
	{	auto v = std::vector<std::shared_ptr<BaseCommand>>();
		v.push_back(pCommand);
		m_InputActions.emplace(action.ActionId, action);
		m_pCommands.emplace(action.ActionId, v);
		return true;
	}
	else
		return false;
}

bool dae::InputManager::SetActionCommand(int actionID,std::shared_ptr<BaseCommand> pCommand, bool addToCurrentCommands)
{
	auto got = m_pCommands.find(actionID);
	if(got != m_pCommands.end())
	{
		if(!addToCurrentCommands) //Clear previous commands	
			got->second.clear();

		got->second.push_back(pCommand); //add/set to vector with commands
		return true;
	}
	//Return false if the action id was not in the map
	return false;
}


void dae::InputManager::HandleInput()
{

	//Loop for every inputaction that is mapped
	for(auto it = m_InputActions.begin(); it != m_InputActions.end(); ++it)
	{
		 auto currAction = &(it->second);
		 currAction->IsTriggered = false;

		//GAMEPAD
		if(m_UseGamepad && currAction->GamepadButtonCode != 0)
		{
			if(m_pGamePads[currAction->PlayerIndex])
			{	//TODO:
				//Currently playerindex of gamepad changes if one disconnects
				auto ks = m_pGamePads[currAction->PlayerIndex]->GetButtonState(currAction->GamepadButtonCode);
				if(ks == currAction->KeyState)
					currAction->IsTriggered = true;
			}
		}
		//KEYBOARD
		if(!currAction->IsTriggered && m_UseKeyboard && currAction->KeyboardCode != -1)
		{		
			auto ks = GetKeystrokeState(currAction->KeyboardCode);
			if(ks == currAction->KeyState)
				currAction->IsTriggered = true;
		}

		//MOUSE
		


		if(currAction->IsTriggered)
		{	
			for(auto command : m_pCommands[currAction->ActionId])
			{
				if(currAction->ActionId == 69)
					command->execute();
				else
				command->AddToCommandStream();
				
			}
			
		}
	}

}

//*******************//
//*****KEYBOARD*****//
//*******************//

//Setting the current and previous states for the Keyboard
void dae::InputManager::ProcessKeyboardInput()
{
	KBpreviousState = KBcurrentState;
	for(unsigned int i = 0; i < KBcurrentState.size();++i)
		KBcurrentState[i] = GetAsyncKeyState(i);
}

const dae::KeyState dae::InputManager::GetKeystrokeState( int key) const
{
	KeyState outKS = KeyState::Idle;
    if (IsKeyPressed(key, true))
	{
		if (IsKeyPressed(key))
			outKS =  KeyState::Pressed;
		else
			outKS =  KeyState::Released;
	}
	else
	{
		if (IsKeyPressed(key))
			outKS =  KeyState::JustPressed;
		else
			outKS =  KeyState::Idle;
	}
	return outKS;
}

bool dae::InputManager::IsKeyPressed(int key, bool prevFrame) const
{
	if(!prevFrame)
		return  (KBcurrentState[key] != 0);
	else
		return  (KBpreviousState[key] != 0);
	
}


//*******************//
//******GAMEPAD******//
//*******************//

dae::Gamepad::Gamepad(const unsigned playerId)
	: playerID(playerId)
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&previousState, sizeof(XINPUT_STATE));

	//Thumbsticks
	m_ThumbStickL = glm::vec2(0,0);
	m_ThumbStickR = glm::vec2(0,0);
}

//Setting the current and previous states for the gamepads
void dae::InputManager::ProcessGamePadInput()
{
	for(auto& gamepad : m_pGamePads)
	{
		gamepad->GetState();

	}
}

//Keystates
const dae::KeyState dae::Gamepad::GetButtonState(WORD button) const
{
	KeyState outKS = KeyState::Idle;
	if (WasPressed(button))
	{
		if (IsPressed(button))
			outKS =  KeyState::Pressed;
		else
			outKS =  KeyState::Released;
	}
	else
	{
		if (IsPressed(button))
			outKS =  KeyState::JustPressed;
		else
			outKS =  KeyState::Idle;
	}
	return outKS;
}

//Double buffer the input
bool dae::Gamepad::WasPressed(WORD button) const
{
		return (previousState.Gamepad.wButtons& button) != 0;	
}

bool dae::Gamepad::IsPressed(WORD button) const
{
		return (currentState.Gamepad.wButtons& button) != 0;	
}

// thumb sticks
const float dae::InputManager::getLX() const
{
	return m_pCurrentGamePad->m_ThumbStickL.x;
}
const float dae::InputManager::getLY() const
{
	return m_pCurrentGamePad->m_ThumbStickL.y;
}
const float dae::InputManager::getRX() const
{
		return m_pCurrentGamePad->m_ThumbStickR.x;
}
const float dae::InputManager::getRY() const
{
		return m_pCurrentGamePad->m_ThumbStickR.y;
}

bool dae::Gamepad::checkConnection()
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	return(XInputGetState(playerID, &state) == ERROR_SUCCESS);			
}

void dae::Gamepad::GetState()
{
	//Check if still connected
	if(!checkConnection())
		throw std::exception("Gamepad::GetState() > Controller was disconnected");

	// save state
	CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));

	// get current state
	if (XInputGetState(playerID, &currentState) != ERROR_SUCCESS)
		throw std::exception("Gamepad::GetState() > Unable to poll gamepad!");

	// check if something changed
	if (previousState.dwPacketNumber == currentState.dwPacketNumber)
		return;

	// get axes
	m_ThumbStickL.x = static_cast<float>(currentState.Gamepad.sThumbLX);
	m_ThumbStickL.y = static_cast<float>(currentState.Gamepad.sThumbLY);
	m_ThumbStickR.x = static_cast<float>(currentState.Gamepad.sThumbRX);
	m_ThumbStickR.y = static_cast<float>(currentState.Gamepad.sThumbRY);

	GetFixedThumbStick(m_ThumbStickL, true);
	GetFixedThumbStick(m_ThumbStickR, false);

}



void dae::Gamepad::GetFixedThumbStick(glm::vec2& thumbStick, bool isLeft)
{
	float magnitude = sqrt(thumbStick.x*thumbStick.x + thumbStick.y*thumbStick.y);
	//determine the direction the controller is pushed
	float normalizedLX = thumbStick.x / magnitude;
	float normalizedLY = thumbStick.y / magnitude;

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > (isLeft ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;
  		//adjust magnitude relative to the end of the dead zone
		magnitude -= (isLeft ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		 normalizedMagnitude = magnitude / (32767 - (isLeft ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
    magnitude = 0.0;
    normalizedMagnitude = 0.0;
	}
	thumbStick.x = normalizedLX * normalizedMagnitude;
	thumbStick.y = normalizedLY * normalizedMagnitude;
}


