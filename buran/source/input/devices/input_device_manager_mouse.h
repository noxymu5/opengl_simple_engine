#pragma once

#include <unordered_map>

#include "input_device_manager.h"

class InputDeviceManagerMouse : public InputDeviceManager {
public:
	InputDeviceManagerMouse(GLFWwindow* window);

	virtual void ProcessInput() override;

private:
	std::unordered_map<AxisType, AxisState> axisStates;

	double lastPosX = .0f;
	double lastPosY = .0f;

	virtual bool IsWithinLimits(KeyCode code) override;
	virtual KeyState CheckKeyInternal(KeyCode code) override;

	virtual bool IsValidAxis(AxisType axisType) override;
	virtual float GetAxisInternal(AxisType axisType) override;
	virtual float GetAxisRawInternal(AxisType axisType) override;
};

