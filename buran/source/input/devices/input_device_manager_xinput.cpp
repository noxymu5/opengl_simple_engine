#include "input_device_manager_xinput.h"

#include <Windows.h>
#include <Xinput.h>

#include <glm/glm.hpp>

#include "core/logging.h"

#define XINPUT_SUCCESS 0

static constexpr float analogueStickDeadZone = 0.2f;
static constexpr float analogueStickMaxValue = 32767.0f;

static constexpr float maxTriggerValue = 255.0f;

static std::unordered_map<KeyCode, int> keyToKeyCode = {
    {KeyCode::XB_A, XINPUT_GAMEPAD_A},
    {KeyCode::XB_B, XINPUT_GAMEPAD_B},
    {KeyCode::XB_X, XINPUT_GAMEPAD_X},
    {KeyCode::XB_Y, XINPUT_GAMEPAD_Y},
    {KeyCode::XB_DPAD_UP, XINPUT_GAMEPAD_DPAD_UP},
    {KeyCode::XB_DPAD_DOWN, XINPUT_GAMEPAD_DPAD_DOWN},
    {KeyCode::XB_DPAD_LEFT, XINPUT_GAMEPAD_DPAD_LEFT},
    {KeyCode::XB_DPAD_RIGHT, XINPUT_GAMEPAD_DPAD_RIGHT},
    {KeyCode::XB_START, XINPUT_GAMEPAD_START},
    {KeyCode::XB_BACK, XINPUT_GAMEPAD_BACK},
    {KeyCode::XB_LEFT_STICK, XINPUT_GAMEPAD_LEFT_THUMB},
    {KeyCode::XB_RIGHT_STICK, XINPUT_GAMEPAD_RIGHT_THUMB},
    {KeyCode::XB_LB, XINPUT_GAMEPAD_LEFT_SHOULDER},
    {KeyCode::XB_RB, XINPUT_GAMEPAD_RIGHT_SHOULDER}
};

InputDeviceManagerXinput::InputDeviceManagerXinput(GLFWwindow* window) : InputDeviceManager(window) {
    for (auto& pair : keyToKeyCode) {
        keyStates[pair.first] = KeyState::RELEASED;
    }

    axisStates[AxisType::XB_HORIZONTAL_L] = {};
    axisStates[AxisType::XB_VERTICAL_L] = {};
    axisStates[AxisType::XB_HORIZONTAL_R] = {};
    axisStates[AxisType::XB_VERTICAL_R] = {};
    axisStates[AxisType::XB_TRIGGER_L] = {};
    axisStates[AxisType::XB_TRIGGER_R] = {};
}

void InputDeviceManagerXinput::ProcessInput() {
    XINPUT_STATE state;
    DWORD result = XInputGetState(0, &state);

    if (result != XINPUT_SUCCESS) {
        return;
    }

    ParseAnalogueStick(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, AxisType::XB_HORIZONTAL_L, AxisType::XB_VERTICAL_L);
    ParseAnalogueStick(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, AxisType::XB_HORIZONTAL_R, AxisType::XB_VERTICAL_R);

    ParseTrigger(state.Gamepad.bLeftTrigger, AxisType::XB_TRIGGER_L);
    ParseTrigger(state.Gamepad.bRightTrigger, AxisType::XB_TRIGGER_R);

    ParseButtons(state.Gamepad.wButtons);
}

void InputDeviceManagerXinput::ParseButtons(unsigned short buttonsState) {
    for (auto& pair : keyToKeyCode) {
        const int xInputCode = pair.second;
        const KeyCode keyCode = pair.first;

        if (buttonsState & xInputCode) {

            KeyState currentState = keyStates[keyCode];
            switch (currentState)
            {
            case KeyState::PRESSED:
                keyStates[keyCode] = KeyState::HELD;
                break;
            case KeyState::RELEASED:
                keyStates[keyCode] = KeyState::PRESSED;
                break;
            }
        }
        else {
            keyStates[keyCode] = KeyState::RELEASED;
        }
    }
}

void InputDeviceManagerXinput::ParseAnalogueStick(short horizontalAxis, short verticalAxis, AxisType horizontalAxisType, AxisType verticalAxisType) {
    glm::vec2 axis {horizontalAxis, verticalAxis};

    glm::vec2 axisNormalized = axis / analogueStickMaxValue;
    float normalizedLength = glm::length(axisNormalized);

    if (normalizedLength <= analogueStickDeadZone) {
        axis.x = axis.y = 0;
    }

    AxisState& horizontalState = axisStates[horizontalAxisType];
    horizontalState.raw = axis.x;
    horizontalState.normalized = axis.x / analogueStickMaxValue;

    AxisState& verticalState = axisStates[verticalAxisType];
    verticalState.raw = axis.y;
    verticalState.normalized = axis.y / analogueStickMaxValue;
}

void InputDeviceManagerXinput::ParseTrigger(unsigned char triggerState, AxisType triggerAxis) {
    AxisState& state = axisStates[triggerAxis];

    state.raw = static_cast<float>(triggerState);
    state.normalized = static_cast<float>(triggerState) / maxTriggerValue;
}

bool InputDeviceManagerXinput::IsWithinLimits(KeyCode code) {
    return code >= KeyCode::XB_A && code <= KeyCode::XB_RIGHT_STICK;
}

KeyState InputDeviceManagerXinput::CheckKeyInternal(KeyCode code) {
    return keyStates[code];
}

bool InputDeviceManagerXinput::IsValidAxis(AxisType axisType) {
    return axisType >= AxisType::XB_HORIZONTAL_L && axisType <= AxisType::XB_TRIGGER_R;
}

float InputDeviceManagerXinput::GetAxisInternal(AxisType axisType) {
    return axisStates[axisType].normalized;
}

float InputDeviceManagerXinput::GetAxisRawInternal(AxisType axisType) {
    return axisStates[axisType].raw;
}
