#pragma once
#include <XInput.h>
#include "Singleton.h"

#pragma once
#include "BaseCommand.h"
#include <array>
#include <vector>


#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#include <unordered_map>
#pragma warning(pop)

//Sources used for this feature: 
//	Xinput and Gamepads by Gilles Bellot(https://bell0bytes.eu/xinput-and-gamepads/)

namespace dae
{
	

	enum class KeyState
	{
		JustPressed = 0,
		Pressed = 1,
		Released = 2,
		Idle = 3
	};

	struct InputAction
	{
		InputAction():
			ActionId(-1),
			KeyState(KeyState::Pressed),
			KeyboardCode(-1),
			MouseButtonCode(-1),
			GamepadButtonCode(0),
			PlayerIndex(0),
			IsTriggered(false){}

		InputAction(int actionID, KeyState keyState = KeyState::Pressed, int keyboardCode = -1, int mouseButtonCode = -1, WORD gamepadButtonCode = 0, unsigned int playerIndex = 0):
		ActionId(actionID),
		KeyState(keyState), 
		KeyboardCode(keyboardCode), 
		MouseButtonCode(mouseButtonCode),
		GamepadButtonCode(gamepadButtonCode),
		PlayerIndex(playerIndex),
		IsTriggered(false){}	

		int ActionId;
		KeyState KeyState;
		int KeyboardCode;
		int MouseButtonCode;
		WORD GamepadButtonCode;
		unsigned int PlayerIndex;
		bool IsTriggered;
	};

	class Gamepad
	{
	public:
		Gamepad(const unsigned int playerId);
		~Gamepad() = default;

		friend class InputManager;

		//BUTTONS
		const KeyState GetButtonState(WORD button) const;
		bool WasPressed(WORD button) const;
		bool IsPressed(WORD button) const;
		


	private:
		XINPUT_STATE currentState;		// the state of the gamepad in the current frame
		XINPUT_STATE previousState;		// the state of the game in the previous frame
		const unsigned int playerID;	// player number (0-3)

		glm::vec2 m_ThumbStickL;
		glm::vec2 m_ThumbStickR;

		bool checkConnection();
		void GetState();
		void GetFixedThumbStick(glm::vec2& thumbStick, bool isLeft = true);
	};

	class KeyboardMouse
	{
	public:
		KeyboardMouse();
		~KeyboardMouse() = default;

		friend class InputHandler;
	private:
 //Hold Mouse coordinates
	};
	
	class InputManager :public Singleton<InputManager>
	{
	public:
		InputManager();
		void Init();
		bool InitGamepads();
		void ProcessInput();
		const KeyState GetKeystrokeState(int key) const;
		bool IsKeyPressed(int key, bool prevFrame = false) const;
		glm::vec2 GetThumbSticksGamePad(int playerIndex) const;
		void HandleInput();
		
		void ProcessKeyboardInput();
		void ProcessGamePadInput();
		bool AddInput(InputAction action,std::shared_ptr<BaseCommand> pCommand, bool replaceCommand = true);
		bool SetActionCommand(int actionID,std::shared_ptr<BaseCommand> pCommand, bool addToCurrentCommands = false);
		void RefreshInput();

		//GAMEPADS
		// thumb sticks
		const float getLX() const;
		const float getLY() const;
		const float getRX() const;
		const float getRY() const;

	private:
		bool m_IsInitialized = false;

		//Keyboad and mouse
		std::array<bool,256> KBcurrentState, KBpreviousState; //Array to hold previous state of keystrokes
		bool KBstate0InUse = false;
		POINT mouseXY;

		//GAMEPADS
		std::vector<Gamepad*> m_pGamePads;
		Gamepad* m_pCurrentGamePad;
		unsigned int currentlyActivePlayer;
		unsigned int nGamepads;						
		unsigned int nPlayers = 1;

		XINPUT_STATE currentState{};
		XINPUT_STATE previousState{};

		//TODO:
		//Choice between map and unordered. 
		//Now action gets hashed. usefull so you dont have to remember all actions to map (if you want 1 input to perform multiple commands)
		//Con: with action ID actions doesnt need to get hashed, can be sorted map, quicker. Have to be sure you dont map over different actionID 
		std::map<int,InputAction> m_InputActions;
		std::map<int, std::vector<std::shared_ptr<BaseCommand>>> m_pCommands;

		std::shared_ptr<BaseCommand> m_ButtonX;
		std::shared_ptr<BaseCommand> m_ButtonY;
		std::shared_ptr<BaseCommand> m_ButtonA;
		std::shared_ptr<BaseCommand> m_ButtonB;

		bool m_UseGamepad = false;
		bool m_UseKeyboard = true;
	};
}