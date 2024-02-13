#pragma once

struct UIColor
{
	union
	{
		struct {
			float r, g, b, a;
		};
		float arr[4]{};
	};

	UIColor() 
	{
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->a = 1;
	};

	UIColor(const float r, const float g, const float b, const float a = 255)
	{
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	};

	UIColor lerp(UIColor target, float pct) {
		return UIColor((this->r + (target.r - this->r) * pct) * 255, (this->g + (target.g - this->g) * pct) * 255, (this->b + (target.b - this->b) * pct) * 255, 255);
	}

	ImVec4 toImVec4() {
		return ImVec4(this->r, this->g, this->b, this->a);
	}
};
