#include "GamePch.h"
#include "Input.h"

void Input::Update()
{
	for (const auto& pair : states)
	{
		if (GetKeyState(static_cast<int>(pair.first)) & 0x8000)
		{
			states[pair.first] = KEY_STATE::PRESSED;
			keyAction[pair.first]();
		}
		else
		{
			states[pair.first] = KEY_STATE::NONE;
		}
	}
}

void Input::BindAction(KEY_TYPE key, function<void()> action)
{
	keyAction[key] = action;
	states[key] = KEY_STATE::NONE;
}

void Input::ClearBind()
{
	keyAction.clear();
	states.clear();
}
