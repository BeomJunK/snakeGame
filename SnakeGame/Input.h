#pragma once
#include "GamePch.h"

class Input
{
public:
	void Update();

	inline bool GetButton(KEY_TYPE key) { return GetState(key) == KEY_STATE::PRESSED; }
	inline KEY_STATE GetState(KEY_TYPE key) { return states.find(key) == states.end() ? KEY_STATE::NONE : states[key]; }

	void BindAction(KEY_TYPE key, function<void()> action);
	void ClearBind();

private:
	map<KEY_TYPE, function<void()>> keyAction;
	map<KEY_TYPE, KEY_STATE> states;
};

