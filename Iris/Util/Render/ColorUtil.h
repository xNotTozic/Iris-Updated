#pragma once
#include <random>

class ColorUtil
{
public:
	inline static UIColor lerpColor(UIColor color1, UIColor color2, float amount)
	{
		amount = std::min(1.f, std::max(0.f, amount));
		return UIColor(Math::lerpInt(color1.r * 255, color2.r * 255, amount), Math::lerpInt(color1.g * 255, color2.g * 255, amount), Math::lerpInt(color1.b * 255, color2.b * 255, amount), Math::lerpInt(color1.a * 255, color2.a * 255, amount));
	}

	inline static UIColor lerpColors(int seconds, int index, UIColor start, UIColor end)
	{
		int angle = (int)(((TimeUtil::getCurrentMs()) / seconds + index) % 360);
		return lerpColor(start, end, ((angle >= 180 ? 360 - angle : angle) * 2) / 360.0f);
	}

	inline static UIColor getRainbow(float seconds, float saturation, float brightness, int index)
	{
		float hue = ((TimeUtil::getCurrentMs() + index) % (int)(seconds * 1000)) / (float)(seconds * 1000);
		float r, g, b = 0;
		hsvToRgb(hue, saturation, brightness, r, g, b);
		return UIColor(r * 255, g * 255, b * 255);
	}

	inline static UIColor getCustomColors(float seconds, int index, const std::vector<std::pair<float, UIColor>>& colorMap)
	{
		float hue = ((TimeUtil::getCurrentMs() + index) % (int)(seconds * 1000)) / (float)(seconds * 1000);

		UIColor currentColor = UIColor(0, 0, 0);
		for (int i = 0; i < colorMap.size() - 1; i++) 
		{
			if (hue >= colorMap[i].first && hue <= colorMap[i + 1].first) 
			{
				float amount = (hue - colorMap[i].first) / (colorMap[i + 1].first - colorMap[i].first);
				currentColor = lerpColor(colorMap[i].second, colorMap[i + 1].second, amount);
				break;
			}
		}
		return UIColor(currentColor.r * 255, currentColor.g * 255, currentColor.b * 255);
	}

	inline static UIColor getAstolfoRainbow(float seconds, float saturation, float brightness, int index)
	{
		float hue = 0;
		float speed = seconds * 1450.f;
		float tempHue = (float)((TimeUtil::getCurrentMs() + index) % (int)speed);
		while (tempHue > speed)
			tempHue -= speed;
		tempHue /= speed;
		if (tempHue > 0.5)
			tempHue = 0.5F - (tempHue - 0.5f);
		tempHue += 0.5F;
		hue = tempHue;


		float r, g, b = 0;
		hsvToRgb(hue, saturation, brightness, r, g, b);
		return UIColor(r * 255, g * 255, b * 255);
	}

	inline static UIColor getClientColor(float seconds, float saturation, float brightness, int index)
	{
		std::vector<std::pair<float, UIColor>> colorMap;
		switch (Game::Iris::ClientColor)
		{
		case 0:
			return getRainbow(seconds, saturation, brightness, index);
			break;
		case 1: // Trans colors
			colorMap =
			{
				{0.0f, UIColor(91, 206, 250, 255.0f)},
				{0.25f, UIColor(245, 169, 184, 255.0f)},
				{0.5f, UIColor(255.0f, 255.0f, 255.0f)},
				{0.75f, UIColor(245, 169, 184, 255.0f)},
				{1.0f, UIColor(91, 206, 250, 255.0f)}
			};
			return getCustomColors(seconds, index, colorMap);
			break;
		case 2: // Weather colors, sorta
			colorMap =
			{
				{0.0f, UIColor(255, 255, 255)},
				{0.25f, UIColor(255, 0, 255)},
				{0.5f, UIColor(255, 255, 255)},
				{0.75f, UIColor(0, 255, 255)},
				{1.0f, UIColor(255, 255, 255)}
			};
			return getCustomColors(seconds, index, colorMap);
			break;
		case 3: // Bubblegum idk
			colorMap = 
			{
				{0.0f, UIColor(255, 192, 203)},
				{0.2f, UIColor(255, 153, 204)},
				{0.4f, UIColor(255, 102, 178)},
				{0.6f, UIColor(255, 51, 180)},
				{0.8f, UIColor(255, 0, 128)},
				{1.0f, UIColor(255, 192, 203)}
			};
			return getCustomColors(seconds, index, colorMap);
			break;
		case 4: // cherry
			colorMap = 
			{
				{0.0f, UIColor(139, 0, 0)},
				{0.25f, UIColor(205, 92, 92)},
				{0.5f, UIColor(220, 20, 60)},
				{0.75f, UIColor(255, 36, 0)},
				{1.0f, UIColor(139, 0, 0)},
			};
			return getCustomColors(seconds, index, colorMap);
			break;
		case 5: //fadeaway
			colorMap =
			{
				{0.0f, UIColor(148, 35, 217)},
				{0.5f, UIColor(46, 23, 60)},
				{1.0f, UIColor(148, 35, 217)}
			};
			return getCustomColors(seconds, index, colorMap);
			break;
		case 6: //xextreame
			colorMap =
			{
				{0.0f, UIColor(230, 0, 0)},
				{0.5f, UIColor(100, 0, 0)},
				{1.0f, UIColor(230, 0, 0)}
			};
			return getCustomColors(seconds, index, colorMap);
			break;
		case 7: // Astoldo
			return getAstolfoRainbow(seconds, saturation * 0.5f, brightness, index);
			break;
		case 8:
		{
			colorMap =
			{
				{0.0f, UIColor(236.f, 133.f, 209.f)},
				{0.5f, UIColor(28.f, 167.f, 222.f)},
				{1.0f, UIColor(236.f, 133.f, 209.f)}
			};
			return getCustomColors(seconds, index, colorMap);
		}
		case 9:
		{
			colorMap = 
			{
				{0.0f, UIColor(150, 45, 255)},
				{0.25f, UIColor(150, 140, 255)},
				{0.5f, UIColor(0, 0, 255)},
				{0.75f, UIColor(0, 135, 255)},
				{1.0f, UIColor(150, 45, 255)}
			};

			return getCustomColors(seconds, index, colorMap);
		}
		}
	}

private:
	inline static void hsvToRgb(float h, float s, float v, float& rOut, float& gOut, float& bOut)
	{

		if (s == 0.0f)
		{
			// gray
			rOut = gOut = bOut = v;
			return;
		}

		h = fmodf(h, 1.0f) / (60.0f / 360.0f);
		int i = (int)h;
		float f = h - (float)i;
		float p = v * (1.0f - s);
		float q = v * (1.0f - s * f);
		float t = v * (1.0f - s * (1.0f - f));

		switch (i)
		{
		case 0:
			rOut = v;
			gOut = t;
			bOut = p;
			break;
		case 1:
			rOut = q;
			gOut = v;
			bOut = p;
			break;
		case 2:
			rOut = p;
			gOut = v;
			bOut = t;
			break;
		case 3:
			rOut = p;
			gOut = q;
			bOut = v;
			break;
		case 4:
			rOut = t;
			gOut = p;
			bOut = v;
			break;
		case 5:
		default:
			rOut = v;
			gOut = p;
			bOut = q;
			break;
		}
	}
};
