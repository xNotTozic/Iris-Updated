#pragma once

#include "../../SDK/GameCore/Game/MinecraftUIRenderContext/MinecraftUIRenderContext.h"
#include "../../SDK/GameCore/Game/MinecraftUIRenderContext/ScreenContext/ScreenContext.h"

enum Type
{
	INTERNAL = 0,
	EXTERNAL = 1,
};

class RenderUtil
{
public:
	static inline MinecraftUIRenderContext* renderContext = nullptr;
	static inline TextureData* textureData = nullptr;
	static inline MaterialPtr* uiMaterial = nullptr;
	static inline Tessellator* tess = nullptr;
	static inline float* colorHolder;

	enum class Direction { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

	struct CornerRadius {
		union {
			struct {
				float topR, topL, bottomR, bottomL;
			};
			float corners[4];
		};

		CornerRadius(const float radius) {
			this->topL = radius;
			this->topR = radius;
			this->bottomL = radius;
			this->bottomR = radius;
		};

		CornerRadius(const int radius) {
			this->topL = (float)radius;
			this->topR = (float)radius;
			this->bottomL = (float)radius;
			this->bottomR = (float)radius;
		};

		CornerRadius(const float topL, const float topR, const float bottomL, const float bottomR) {
			this->topL = topL;
			this->topR = topR;
			this->bottomL = bottomL;
			this->bottomR = bottomR;
		};

		CornerRadius(const int topL, const int topR, const int bottomL, const int bottomR) {
			this->topL = (float)topL;
			this->topR = (float)topR;
			this->bottomL = (float)bottomL;
			this->bottomR = (float)bottomR;
		};
	};

	inline static void setCTX(MinecraftUIRenderContext* context)
	{
		renderContext = context;
		tess = renderContext->ScreenContext->getTessellator();
		colorHolder = renderContext->ScreenContext->getColorHolder();

		uintptr_t offset = reinterpret_cast<uintptr_t>(Addresses::Render::uiMaterial);
		int* intOffset = reinterpret_cast<int*>(offset + 3);
		static int offsetValue = *intOffset;
		uiMaterial = reinterpret_cast<MaterialPtr*>(offsetValue + offset + 7);
	}

	inline static MinecraftUIRenderContext* GetCTX()
	{
		return renderContext;
	}

	inline static void flushString()
	{
		renderContext->flushString(0);
	}

	inline static float getTextWidth(std::string* str, float size)
	{
		TextHolder text(*str);
		return renderContext->getMeasureData(nullptr, &text, size, true);
	}

	inline static Vector2<float> getScreenSize()
	{
		return GuiInfo::ScreenRes;
	}

	inline static void drawString(Vector2<float> pos, std::string* str, UIColor color, float size, float alpha, bool shadow)
	{
		TextHolder text(*str);
		static CaretMeasureData black = CaretMeasureData(20, false);

		float tPos[4] = { pos.x, pos.x, pos.y, pos.y };
		TextMeasureData data = TextMeasureData(size, shadow);
		
		renderContext->drawText(nullptr, tPos, &text, color.arr, alpha, 0, &data, &black);
	}

	inline static void fillRectangle(Vector4<float> pos, UIColor col, float alpha)
	{
		setColor(col.r, col.g, col.b, alpha);
		drawQuad({ pos.x, pos.w }, { pos.z, pos.w }, { pos.z, pos.y }, { pos.x, pos.y });
	}

	static void rotate(float angle, Vector2<float> pivot)
	{
		tess->setRotation(angle, Vector3<float>(pivot.x, pivot.y, GuiInfo::ScreenRes.x / 2));
	}

	static void resetRotate()
	{
		tess->resetTransform(false);
	}

	static void drawCorner(Vector2<float> center, UIColor color, float radius, float alpha, Direction direction, int smoothing) {
		const float angleIncrement = PI / (2 * smoothing);
		float angleStart = 0.0f;

		switch (direction) 
		{
			case Direction::TOP_LEFT: angleStart = PI; break;
			case Direction::TOP_RIGHT: angleStart = PI * -0.5f; break;
			case Direction::BOTTOM_LEFT: angleStart = PI * 0.5f; break;
			case Direction::BOTTOM_RIGHT: angleStart = 0.0f; break;
		}

		tess->begin(VertextFormat::TRIANGLE_STRIP, static_cast<int>(ceil(PI * radius / 20.f)) * 3);

		for (int i = 0; i < smoothing; i++) 
		{
			const float angle1 = angleStart + i * angleIncrement;
			const float angle2 = angleStart + (i + 1) * angleIncrement;

			const Vector2 p1 = center + (Vector2(radius * cos(angle1), radius * sin(angle1)));
			const Vector2 p2 = center + (Vector2(radius * cos(angle2), radius * sin(angle2)));

			tess->vertex(center.x, center.y, 0);
			tess->vertex(p1.x, p1.y, 0);
			tess->vertex(p2.x, p2.y, 0);
		}

		setColor(color.r, color.g, color.b, alpha);
		tess->renderMeshImmediately(renderContext->ScreenContext, uiMaterial);
	}

	static void roundRectangle(Vector4<float> pos, UIColor col, float alpha, float radius, int smoothing) {
		pos.x += radius;
		pos.y += radius;
		pos.z -= radius;
		pos.w -= radius;

		fillRectangle(Vector4(pos.x, pos.y - radius, pos.z, pos.y), col, alpha);
		fillRectangle(Vector4(pos.x, pos.w, pos.z, pos.w + radius), col, alpha);
		fillRectangle(Vector4(pos.x - radius, pos.y, pos.z + radius, pos.w), col, alpha);

		if (smoothing > 0)
		{
			drawCorner(Vector2(pos.x, pos.y), col, radius, alpha, Direction::TOP_LEFT, smoothing);
			drawCorner(Vector2(pos.z, pos.y), col, radius, alpha, Direction::TOP_RIGHT, smoothing);
			drawCorner(Vector2(pos.x, pos.w), col, radius, alpha, Direction::BOTTOM_LEFT, smoothing);
			drawCorner(Vector2(pos.z, pos.w), col, radius, alpha, Direction::BOTTOM_RIGHT, smoothing);
		}
	}

	static void setColor(float r, float g, float b, float a) 
	{
		if (colorHolder) 
		{
			colorHolder[0] = r;
			colorHolder[1] = g;
			colorHolder[2] = b;
			colorHolder[3] = a;
			*reinterpret_cast<uint8_t*>(colorHolder + 4) = 1;
		}
	}

	static void drawQuad(Vector2<float> p1, Vector2<float> p2, Vector2<float> p3, Vector2<float> p4) {
		if (!tess || !uiMaterial) return;
		tess->begin(VertextFormat::QUAD);

		tess->vertex(p1.x, p1.y, 0);
		tess->vertex(p2.x, p2.y, 0);
		tess->vertex(p3.x, p3.y, 0);
		tess->vertex(p4.x, p4.y, 0);

		tess->renderMeshImmediately(renderContext->ScreenContext, uiMaterial);
	}

	inline static void fillRectangle(Vector4<float> pos, UIColor* col, float alpha)
	{
		renderContext->fillRectangle(Vector4<float>(pos.x, pos.z, pos.y, pos.w), col, alpha);
	}

	inline static void drawRectangle(Vector4<float> pos, UIColor col, float thickness, float alpha)
	{
		renderContext->drawRectangle(Vector4<float>(pos.x, pos.z, pos.y, pos.w), col, alpha, thickness);
	}

	static void drawGradientRectangle(const Vector4<float>& rect, float alpha, int quality, int speed, float saturation, int brightness, int index)
	{
		int i = 0;
		for (float x = rect.x; x < rect.z; x += quality)
		{
			fillRectangle(Vector4<float>(x, rect.y, x + quality, rect.w), ColorUtil::getClientColor(speed, saturation, brightness, i * index), alpha);
			i++;
		}
	}

	inline static void yeemi_fillRectangle(Vector4<float> pos, UIColor col, float alpha)
	{
		renderContext->fillRectangle(pos, col, alpha);
	}

	static void drawGradientScaleString(Vector2<float> pos, std::string* text, float size, float alpha, bool shadow, int speed, float saturation, int brightness, int index)
	{
		TextHolder str(*text);
		int ind = 0;

		// Get the start time for the animation
		static auto start_time = std::chrono::high_resolution_clock::now();
		const float amplitude = 0.5f; // how much to scale up/down from the middle
		const float speedFactor = 0.006f; // how fast to oscillate
		const float phaseShift = 0.2f; // to make each letter start its oscillation at a different time
		const float baseScale = 1.0f; // starting scale factor

		for (char c : std::string(str.getText()))
		{
			std::string string = combine(c, "");

			// Current color index
			int colorIndex = ind * index;

			// Get each char's width
			float charWidth = getTextWidth(&string, size);

			// Compute the scale factor using sine wave with the scale speed
			auto now = std::chrono::high_resolution_clock::now();
			float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
			float phase = phaseShift * ind;
			float scale = baseScale + amplitude * sin(speedFactor * elapsed + phase);

			// Compute the position for the scaled string
			Vector2<float> charPos(pos.x + charWidth * 0.5f, pos.y - size * 0.5f);
			Vector2<float> scaledPos(charPos.x - charWidth * 0.5f * scale, charPos.y - size * 0.5f * scale);

			// Draw the scaled string
			drawString(scaledPos, &string, ColorUtil::getClientColor(speed, saturation, brightness, colorIndex), size * scale, alpha, shadow);

			// Increment the pos and ind index
			pos.x += charWidth += scale;
			++ind;
		}
	}

	static void drawGradientString(Vector2<float> pos, std::string* text, float size, float alpha, bool shadow, int speed, float saturation, int brightness, int index)
	{
		TextHolder str(*text);
		int ind = 0;

		for (char c : std::string(str.getText()))
		{
			std::string string = combine(c, "");

			// Current color index
			int colorIndex = ind * index;

			// Get each char's width and draw
			float charWidth = getTextWidth(&string, size);

			drawString(Vector2<float>(pos.x, pos.y), &string, ColorUtil::getClientColor(speed, saturation, brightness, colorIndex), size, alpha, shadow);

			// Increment the color and pos index
			pos.x += charWidth;
			++ind;
		}
	}

	static void drawGradientString(Vector2<float> pos, std::string* text, float size, float alpha, bool shadow, UIColor frstColor, UIColor scndColor, int speed, int index)
	{
		TextHolder str(*text);
		int ind = 0;

		for (char c : std::string(str.getText()))
		{
			std::string string = &c;

			// Current color index
			int colorIndex = ind * index;

			// Get each char's width and draw
			float charWidth = getTextWidth(&string, size); //Size no fucking work??!?!
			drawString(Vector2<float>(pos.x, pos.y), &string, ColorUtil::lerpColors(speed, colorIndex, frstColor, scndColor), size, alpha, shadow);

			// Increment the color and pos index
			pos.x += charWidth;
			++ind;
		}
	}

	static void renderImage(std::string filePath, Vector4<float> rectPosition, Vector2<float> uvPos = Vector2<float>(0.f,0.f), Vector2<float> uvSize = Vector2<float>(1.f, 1.f), Type type = EXTERNAL)
	{
		ResourceLocation location = ResourceLocation(filePath, type);

		location = ResourceLocation(filePath, type);
		TextureData* textureData = new TextureData();
		renderContext->getTexture(textureData, &location);

		renderContext->drawImage(textureData, Vector2<float>(rectPosition.x, rectPosition.y), Vector2<float>(rectPosition.z - rectPosition.x, rectPosition.w - rectPosition.y), uvPos, uvSize);
	}

	static void drawGif(const Vector4<float>& rect, const std::string& dirPath, int fps)
	{
		static bool hasRenderedOnce = false;
		static std::chrono::high_resolution_clock::time_point lastRender = std::chrono::high_resolution_clock::now();
		static float indOverflow = 0.0f;
		static int ind = 0;

		// some calculation to get the time since the last frame
		auto deltaDiscrete = std::chrono::high_resolution_clock::now() - lastRender;
		float delta = std::chrono::duration_cast<std::chrono::microseconds>(deltaDiscrete).count() / 1000000.f;
		delta = fmaxf(0.f, delta);

		int currFps = hasRenderedOnce ? fps : 300;
		indOverflow += delta / (1.f / currFps);
		ind += (int)indOverflow;
		indOverflow -= (int)indOverflow;

		// Basically we get every png or jpg file in a dir and loop through them
		std::vector<std::string> imageFileNames;
		
		static int count = 0;
		if (imageFileNames.empty() && Util::doesClientPathExist(dirPath))
		{
			for (auto& entry : std::filesystem::directory_iterator(dirPath))
			{
				if (entry.is_regular_file() && (entry.path().extension() == ".png" || entry.path().extension() == ".jpg"))
				{
					imageFileNames.push_back(entry.path().filename().string());
				}
			}
		}
		count++;

		if (!imageFileNames.empty())
		{
			if (count >= imageFileNames.size()) hasRenderedOnce = true;

			int currentFrame = ind % imageFileNames.size();
			std::string imagePath = dirPath + imageFileNames[currentFrame];
			renderImage(imagePath, rect);

		}
		// Update lastRender time
		lastRender = std::chrono::high_resolution_clock::now();
	}

	static void drawLine(Vector2<int> start, Vector2<int> end, float lineWidth) {
		float modX = 0 - (start.y - end.y);
		float modY = start.x - end.x;

		float len = sqrtf(modX * modX + modY * modY);

		modX /= len;
		modY /= len;
		modX *= lineWidth;
		modY *= lineWidth;

		tess->begin(VertextFormat::TRIANGLE_STRIP);

		tess->vertex(start.x + modX, start.y + modY, 0);
		tess->vertex(start.x - modX, start.y - modY, 0);
		tess->vertex(end.x - modX, end.y - modY, 0);

		tess->vertex(start.x + modX, start.y + modY, 0);
		tess->vertex(end.x + modX, end.y + modY, 0);
		tess->vertex(end.x - modX, end.y - modY, 0);

		tess->renderMeshImmediately(renderContext->ScreenContext, uiMaterial);
	}

	static void tessLine(Vector2<int> start, Vector2<int> end, float lineWidth) {
		float modX = 0 - (start.y - end.y);
		float modY = start.x - end.x;

		float len = sqrtf(modX * modX + modY * modY);

		modX /= len;
		modY /= len;
		modX *= lineWidth;
		modY *= lineWidth;

		tess->vertex(start.x + modX, start.y + modY, 0);
		tess->vertex(start.x - modX, start.y - modY, 0);
		tess->vertex(end.x - modX, end.y - modY, 0);

		tess->vertex(start.x + modX, start.y + modY, 0);
		tess->vertex(end.x + modX, end.y + modY, 0);
		tess->vertex(end.x - modX, end.y - modY, 0);
	}

	static void flushImage(UIColor color = UIColor(255, 255, 255), float alpha = 1.f)
	{
		static StringHasher flushString = StringHasher(0xA99285D21E94FC80, "ui_flush");
		renderContext->flushImages(color, alpha, flushString);
	}

	inline static float getDeltaTime()
	{
		return GuiInfo::DeltaTime;
	}

	inline static void resetClipRect() {
		renderContext->restoreSavedClippingRectangle();
	}

	inline static void setClipRect(Vector4<float> position) {
		renderContext->saveCurrentClippingRectangle();
		renderContext->setClippingRectangle(Vector4<float>(position.x, position.z, position.y, position.w));
	}

	inline static bool isMouseOver(Vector4<float>(pos))
	{
		Vector2<short> mousePos = GuiInfo::MousePos;
		return mousePos.x >= pos.x && mousePos.y >= pos.y && mousePos.x < pos.z&& mousePos.y < pos.w;
	}
};

#include "3DRenderUtil.h"
#include "ImRenderUtil.h"