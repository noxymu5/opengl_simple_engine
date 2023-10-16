#pragma once

#include "input/key_codes.h"
#include "input/axis_types.h"

struct GLFWwindow;

class InputDeviceManager {
public:
	InputDeviceManager(GLFWwindow* window);

	virtual void ProcessInput() = 0;
	
	bool CheckKey(KeyCode code, KeyState& state);
	bool GetAxis(AxisType axisType, float& axisOut);
	bool GetAxisRaw(AxisType axisType, float& axisOut);

protected:
	GLFWwindow* window;

	virtual bool IsWithinLimits(KeyCode code) = 0;
	virtual bool IsValidAxis(AxisType axisType) = 0;

	virtual KeyState CheckKeyInternal(KeyCode code) = 0;
	virtual float GetAxisInternal(AxisType axisType) = 0;
	virtual float GetAxisRawInternal(AxisType axisType) = 0;
};