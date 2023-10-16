#include "input_device_manager_mouse.h"

#include "core/asserts.h"

InputDeviceManagerMouse::InputDeviceManagerMouse(GLFWwindow* window) : InputDeviceManager(window) {
	axisStates[AxisType::MS_HORIZONTAL] = {};
	axisStates[AxisType::MS_VERTICAL] = {};
}

void InputDeviceManagerMouse::ProcessInput() {
	glfwPollEvents();

    double posX = .0f;
    double posY = .0f;

    glfwGetCursorPos(window, &posX, &posY);

    double diffX = posX - lastPosX;
    double diffY = posY - lastPosY;

    AxisState& horizontal = axisStates[AxisType::MS_HORIZONTAL];
    horizontal.raw = diffX;
    horizontal.normalized = diffX < 0 ? -1 : diffX > 0 ? 1 : 0;

    AxisState& vertical = axisStates[AxisType::MS_VERTICAL];
    vertical.raw = diffY;
    vertical.normalized = diffY < 0 ? -1 : diffY > 0 ? 1 : 0;

    lastPosX = posX;
    lastPosY = posY;
}

bool InputDeviceManagerMouse::IsWithinLimits(KeyCode code) {
	return code == KeyCode::MS_LEFT || code == KeyCode::MS_RIGHT || code == KeyCode::MS_MIDDLE;
}

KeyState InputDeviceManagerMouse::CheckKeyInternal(KeyCode code) {
    int glfwState = glfwGetMouseButton(window, static_cast<int>(code));

    switch (glfwState)
    {
    case GLFW_REPEAT:
        return KeyState::HELD;
        break;
    case GLFW_PRESS:
        return KeyState::PRESSED;
        break;
    case GLFW_RELEASE:
        return KeyState::RELEASED;
        break;
    }

    ASSERT_FAIL("Unknown KeyState")
    return KeyState::HELD;
}

bool InputDeviceManagerMouse::IsValidAxis(AxisType axisType) {
	return axisType == AxisType::MS_HORIZONTAL || axisType == AxisType::MS_VERTICAL;
}

float InputDeviceManagerMouse::GetAxisInternal(AxisType axisType) {
	return axisStates[axisType].normalized;
}

float InputDeviceManagerMouse::GetAxisRawInternal(AxisType axisType) {
	return axisStates[axisType].raw;
}
