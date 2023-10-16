#include "input_device_manager.h"

InputDeviceManager::InputDeviceManager(GLFWwindow* window) {
	this->window = window;
}

bool InputDeviceManager::CheckKey(KeyCode code, KeyState& state) {
	if (!IsWithinLimits(code)) {
		return false;
	}

	state = CheckKeyInternal(code);
	return true;
}

bool InputDeviceManager::GetAxis(AxisType axisType, float& axisOut) {
	if (!IsValidAxis(axisType)) {
		return false;
	}

	axisOut = GetAxisInternal(axisType);
	return true;
}

bool InputDeviceManager::GetAxisRaw(AxisType axisType, float& axisOut)
{
	if (!IsValidAxis(axisType)) {
		return false;
	}

	axisOut = GetAxisRawInternal(axisType);
	return true;
}
