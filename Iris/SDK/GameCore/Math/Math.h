#pragma once
constexpr float PI = (3.1415927f);

class Math
{
public:

	static const float& fdmin(const float& a, const float& b)
	{
		return (a < b) ? a : b;
	}

	inline static float animate(float endPoint, float current, float speed) {
		if (speed < 0.0) speed = 0.0;
		else if (speed > 1.0) speed = 1.0;

		float dif = std::max(endPoint, current) - std::min(endPoint, current);
		float factor = dif * speed;
		return current + (endPoint > current ? factor : -factor);
	}

	inline static float lerp(float a, float b, float c) 
	{
		return a + c * (b - a);
	}

	__forceinline static float wrap(float value, float min, float max) {
		return fmod(fmod(value - min, max - min) + (max - min), max - min) + min;
	}

	inline static int lerpInt(int a1, int a2, double a3) 
	{
		return (int)lerp((float)a1, (float)a2, (float)a3);
	}

	static inline float clamp(float value, float min_val, float max_val) {
		return value < min_val ? min_val : (value > max_val ? max_val : value);
	}


	static double pow(double a, double b)
	{
		double c = 1;
		for (int i = 0; i < b; i++)
		{
			c *= a;
		}
		return c;
	}

	static double fact(double x)
	{
		double ret = 1;
		for (int i = 1; i <= x; i++)
		{
			ret *= i;
		}
		return ret;
	}

	static float sin(float x)
	{
		float res = 0, pow = x, fact = 1;
		for (int i = 0; i < 5; i++)
		{
			res += pow / fact;
			pow *= -1 * x * x;
			fact *= (2 * (i + 1)) * (2 * (i + 1) + 1);
		}
		return res;
	}

	static double cos(double x)
	{
		double y = 1;
		double s = -1;
		for (int i = 2; i <= 100; i += 2)
		{
			y += s * (pow(x, i) / fact(i));
			s *= -1;
		}
		return y;
	}
};