#pragma once

#include <unordered_map>

#include "input_device_manager.h"

class InputDeviceManagerXinput : public InputDeviceManager {
public:
	InputDeviceManagerXinput(GLFWwindow* window);

	virtual void ProcessInput() override;

private:
	unsigned long lastPacketNumber = 0;

	std::unordered_map<KeyCode, KeyState> keyStates;
	std::unordered_map<AxisType, AxisState> axisStates;

	virtual bool IsWithinLimits(KeyCode code) override;
	virtual KeyState CheckKeyInternal(KeyCode code) override;

	virtual bool IsValidAxis(AxisType axisType) override;
	virtual float GetAxisInternal(AxisType axisType) override;
	virtual float GetAxisRawInternal(AxisType axisType) override;

	void ParseButtons(unsigned short gamepadState);
	void ParseAnalogueStick(short horizontalAxis, short verticalAxis, AxisType horizontalAxisType, AxisType verticalAxisType);
	void ParseTrigger(unsigned char triggerState, AxisType triggerAxis);
};

