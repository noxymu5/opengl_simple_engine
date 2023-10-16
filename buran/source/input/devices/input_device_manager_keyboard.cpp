#include "input_device_manager_keyboard.h"

#include <GLFW/glfw3.h>

#include "core/asserts.h"

InputDeviceManagerKeyboard::InputDeviceManagerKeyboard(GLFWwindow* window) : InputDeviceManager(window) {
    axisStates[AxisType::KB_SYM_HORIZONTAL] = {};
    axisStates[AxisType::KB_SYM_VERTICAL] = {};
}

void InputDeviceManagerKeyboard::ProcessInput() {
	glfwPollEvents();

    AxisState& horizontal = axisStates[AxisType::KB_SYM_HORIZONTAL];
    AxisState& vertical = axisStates[AxisType::KB_SYM_VERTICAL];

    {
        float axisValue = .0f;
        int glfwState = glfwGetKey(window, static_cast<int>(KeyCode::KB_A));

        if (glfwState == GLFW_PRESS || glfwState == GLFW_REPEAT) {
            axisValue -= 1;
        }

        glfwState = glfwGetKey(window, static_cast<int>(KeyCode::KB_D));
        if (glfwState == GLFW_PRESS || glfwState == GLFW_REPEAT) {
            axisValue += 1;
        }


        horizontal.raw = horizontal.normalized = axisValue;
    }

    {
        float axisValue = .0f;
        int glfwState = glfwGetKey(window, static_cast<int>(KeyCode::KB_S));

        if (glfwState == GLFW_PRESS || glfwState == GLFW_REPEAT) {
            axisValue -= 1;
        }

        glfwState = glfwGetKey(window, static_cast<int>(KeyCode::KB_W));
        if (glfwState == GLFW_PRESS || glfwState == GLFW_REPEAT) {
            axisValue += 1;
        }


        vertical.raw = vertical.normalized = axisValue;
    }

}

bool InputDeviceManagerKeyboard::IsWithinLimits(KeyCode code) {
	return code >= KeyCode::KB_A && code <= KeyCode::KB_LEFT_CTRL;
}

KeyState InputDeviceManagerKeyboard::CheckKeyInternal(KeyCode code) {
    int glfwState = glfwGetKey(window, static_cast<int>(code));

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

bool InputDeviceManagerKeyboard::IsValidAxis(AxisType axisType) {
    return axisType == AxisType::KB_SYM_HORIZONTAL || axisType == AxisType::KB_SYM_VERTICAL;
}

float InputDeviceManagerKeyboard::GetAxisInternal(AxisType axisType) {
    return axisStates[axisType].normalized;
}

float InputDeviceManagerKeyboard::GetAxisRawInternal(AxisType axisType) {
    return axisStates[axisType].raw;
}
