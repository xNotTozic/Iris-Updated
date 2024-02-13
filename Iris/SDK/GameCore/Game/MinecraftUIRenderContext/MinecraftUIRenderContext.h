#pragma once

#include <cstdint>

#include "TextMeasureData.h"

class ComponentRenderBatch;
class NinesliceInfo;
class HashedString;

class MinecraftUIRenderContext
{
public:
    uintptr_t** VTable;
    ClientInstance* ClientInstance;
    ScreenContext* ScreenContext;
    void* MeasureStrag;
    UIScene* UIScene;
    float TextAlpha;

public: // functions
    auto GetVTable(int index)
    {
        return VTable[index];
    }

    void drawRectangle(Vector4<float> const& rect, UIColor const& colour, float alpha, int radius)
    {
        return CallFunc<void, uintptr_t, Vector4<float> const&, UIColor const&, float, int>(
            GetVTable(12),
            (uintptr_t)this,
            rect, // * GuiInfo::GuiScale
            colour,
            alpha,
            radius
        );
    }

    void fillRectangle(Vector4<float> const& rect, UIColor const& colour, float alpha)
    {
        //uintptr_t tertsfd = reinterpret_cast<uintptr_t>((void*(*)())GetVTable(13));
        return CallFunc<void, uintptr_t, Vector4<float> const&, UIColor const&, float>(GetVTable(13), (uintptr_t)this, rect, colour, alpha);
    }

    void fillRectangle(Vector4<float> const& rect, UIColor const* colour, float alpha)
    {
        //uintptr_t tertsfd = reinterpret_cast<uintptr_t>((void*(*)())GetVTable(13));
        return CallFunc<void, uintptr_t, Vector4<float> const&, UIColor const*, float>(GetVTable(13), (uintptr_t)this, rect, colour, alpha);
    }

    float getMeasureData(void* font, TextHolder* str, float textSize, bool calcWidth)
    {
        if (!font) font = Game::FontRepos::GetClientFont();

        if (!calcWidth)
            textSize * 10;

        return CallFunc<float, uintptr_t, void*, TextHolder*, float, bool>(GetVTable(1), (uintptr_t)this, font, str, textSize, calcWidth);
    }

    __int64 drawText(FontBitmap* font, const float* pos, TextHolder* text, const float* color, float alpha, unsigned int textAlignment, const TextMeasureData* textMeasureData, const CaretMeasureData* caretMeasureData) {
        if (!font) font = Game::FontRepos::GetClientFont();
        return CallVFunc<5, __int64, FontBitmap*, const float*, TextHolder*, const float*, float, unsigned int, const TextMeasureData*, const CaretMeasureData*>(this, font, pos, text, color, alpha, textAlignment, textMeasureData, caretMeasureData);
    };

    __int64 drawImage(const TextureData* a2, Vector2<float> const& ImagePos, Vector2<float> const& ImageDimension, Vector2<float> const& uvPos, Vector2<float> const& uvSize)
    {
        return CallVFunc<7, __int64, const TextureData*, Vector2<float> const&, Vector2<float> const&, Vector2<float> const&, Vector2<float> const&>(this, a2, ImagePos, ImageDimension, uvPos, uvSize);
    };

    __int64 flushImages(UIColor& color, float opacity, class StringHasher& hashedString)
    {
        return CallVFunc<9, __int64, UIColor&, float, class StringHasher&>(this, color, opacity, hashedString);
    };

    void setClippingRectangle(Vector4<float> const& pos)
    {
        return CallVFunc<20, void, Vector4<float> const&>(this, pos);
    };

    void saveCurrentClippingRectangle()
    {
        return CallVFunc<22, void>(this);
    };

    void restoreSavedClippingRectangle()
    {
        return CallVFunc<23, void>(this);
    };

    void flushString(float delta) {
        return CallVFunc<6, void, float>(this, delta);
    };

    TextureData* getTexture(TextureData* texture, ResourceLocation* resourceLocation)
    {
        return CallVFunc<29, TextureData*, TextureData*, ResourceLocation*>(this, texture, resourceLocation);
    };
};