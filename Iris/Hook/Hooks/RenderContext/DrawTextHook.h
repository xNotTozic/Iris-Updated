#pragma once

void DrawTextDetour(
    MinecraftUIRenderContext* _this,
    FontBitmap* font,
    Vector4<float> const& pos,
    TextHolder* str,
    UIColor const& colour,
    float alpha,
    float alinM,
    TextMeasureData const& textdata,
    CaretMeasureData const& caretdata
)
{
    Game::FontRepos::PutFont(font);

    if (strcmp(str->getText(), "©Mojang AB") == 0)
    {
        str->setText(combine("©", Game::Iris::ClientName));
    }

    if (colour.r == 1 && colour.g == 0 && colour.b == 0 && colour.a == 1)
    {
        return; // cancel
    }

    CallFunc<void, MinecraftUIRenderContext*, FontBitmap*, Vector4<float> const&, TextHolder*, UIColor const&, float, float, TextMeasureData const&, CaretMeasureData const&>(
        __o__DrawText,
        _this,
        font,
        pos,
        str,
        colour,
        alpha,
        alinM,
        textdata,
        caretdata
    );
}