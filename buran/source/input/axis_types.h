#pragma once

enum class AxisType {
	//xinput axis
	XB_HORIZONTAL_L,
	XB_VERTICAL_L,
	XB_HORIZONTAL_R,
	XB_VERTICAL_R,
	XB_TRIGGER_L,
	XB_TRIGGER_R,

	//keyboard axis
	KB_SYM_HORIZONTAL,
	KB_SYM_VERTICAL,

	//mous axis
	MS_HORIZONTAL,
	MS_VERTICAL
};

struct AxisState {
	float raw;
	float normalized;
};