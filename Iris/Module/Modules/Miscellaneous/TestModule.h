#pragma once
int rotation_start_index;
class TestModule : public Module
{
public:
    TestModule(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("TestModule", "Misc", "For testin purposes my niga xD", keybind, enabled)
    {
    }
    void ImRotateStart()
    {
        rotation_start_index = ImGui::GetBackgroundDrawList()->VtxBuffer.Size;
    }
    int mode = 0;
    float range = 30;
    float delayMS = 4;

    UIColor getClientColor(int theme, float index = 0)
    {
        switch (theme)
        {
        case 0: // Rainbow
            return ColorUtil::getRainbow(5, 1, 1, index);
        case 1: // Trans colors
            return ColorUtil::getCustomColors(5, index, {
                {0.0f, UIColor(91, 206, 250, 255.0f)},
                {0.25f, UIColor(245, 169, 184, 255.0f)},
                {0.5f, UIColor(255.0f, 255.0f, 255.0f)},
                {0.75f, UIColor(245, 169, 184, 255.0f)},
                {1.0f, UIColor(91, 206, 250, 255.0f)}
                });
        case 2: // Weather colors
            return ColorUtil::getCustomColors(5, index, {
                {0.0f, UIColor(255, 255, 255)},
                {0.25f, UIColor(255, 0, 255)},
                {0.5f, UIColor(255, 255, 255)},
                {0.75f, UIColor(0, 255, 255)},
                {1.0f, UIColor(255, 255, 255)}
                });
        case 3: // Bubblegum
            return ColorUtil::getCustomColors(5, index, {
                {0.0f, UIColor(255, 192, 203)},
                {0.2f, UIColor(255, 153, 204)},
                {0.4f, UIColor(255, 102, 178)},
                {0.6f, UIColor(255, 51, 180)},
                {0.8f, UIColor(255, 0, 128)},
                {1.0f, UIColor(255, 192, 203)}
                });
        case 4: // Cherry
            return ColorUtil::getCustomColors(5, index, {
                {0.0f, UIColor(139, 0, 0)},
                {0.25f, UIColor(205, 92, 92)},
                {0.5f, UIColor(220, 20, 60)},
                {0.75f, UIColor(255, 36, 0)},
                {1.0f, UIColor(139, 0, 0)}
                });
        case 5: // Fadeaway
            return ColorUtil::getCustomColors(5, index, {
                {0.0f, UIColor(148, 35, 217)},
                {0.5f, UIColor(46, 23, 60)},
                {1.0f, UIColor(148, 35, 217)}
                });
        case 6: // Xextreame
            return ColorUtil::getCustomColors(5, index, {
                {0.0f, UIColor(230, 0, 0)},
                {0.5f, UIColor(100, 0, 0)},
                {1.0f, UIColor(230, 0, 0)}
                });
        case 7: // Astoldo
            return ColorUtil::getAstolfoRainbow(5, 0.5f, 1, index);
        case 8: // Randomized colors
        {
            return ColorUtil::getCustomColors(5, index, {
                {0.0f, UIColor(236.f, 133.f, 209.f)},
                {0.5f, UIColor(28.f, 167.f, 222.f)},
                {1.0f, UIColor(236.f, 133.f, 209.f)}
                });
            break;
        }
        }

        return UIColor(); // Return a default color if the theme is not recognized
    }

    void onEvent(ImGUIRenderEvent* event) {
        /*static EasingUtil ease;

        static std::string targetName;

        if (!Game::TargetLists::auraList.empty()) {
            targetName = Game::TargetLists::auraList[0]->getNameTag()->getText();
            targetName = Util::sanitizeName(targetName);
            ease.incrementPercentage(ImRenderUtil::getDeltaTime() * 2);
        }
        else {
            ease.decrementPercentage(ImRenderUtil::getDeltaTime() * 2);
        }

        float transfromEase = ease.easeOutBack();
        float opacityEase = ease.easeOutExpo();

        Vector2<float> res = ImRenderUtil::getScreenSize() / 2;
        const float posX = res.x + 40;
        const float posY = res.y + 20;

        const float rectLength = 225.f;
        const float rectHeight = 75.f;

        Vector4<float> rect = Vector4<float>(posX, posY, posX + rectLength, posY + rectHeight)
            .scaleToCenter(transfromEase);

        ImRenderUtil::fillRectangle(rect, UIColor(0, 0, 0), opacityEase * 0.6f);

        Vector2<float> textPos = Vector2<float>(rect.getCenter().x, rect.getCenter().y).lerp(Vector2<float>(posX + 4.f, posY + 4.f), transfromEase);
        ImRenderUtil::drawText(textPos, &targetName, UIColor(255, 255, 255), transfromEase * 1.2, opacityEase, true);*/

    }

    void drawTarget(Player* plr) {
        /*static EasingUtil ease;

        static std::string targetName;

        if (plr) {
            targetName = plr->getNameTag()->getText();
            targetName = Util::sanitizeName(targetName);
            ease.incrementPercentage(ImRenderUtil::getDeltaTime() * 5);
        }
        else {
            ease.decrementPercentage(ImRenderUtil::getDeltaTime() * 5);
        }

        float transfromEase = ease.easeOutExpo();
        float opacityEase = ease.easeOutExpo();

        Vector2<float> res = ImRenderUtil::getScreenSize() / 2;
        const float posX = res.x + 40;
        const float posY = res.y + 20;

        const float rectLength = 225.f;
        const float rectHeight = 75.f;

        Vector4<float> rect = Vector4<float>(posX, posY, posX + rectLength, posY + rectHeight)
            .scaleToCenter(transfromEase);

        ImRenderUtil::fillRectangle(rect, UIColor(0, 0, 0), opacityEase * 0.6f);

        Vector2<float> textPos = Vector2<float>(rect.getCenter().x, rect.getCenter().y).lerp(Vector2<float>(posX + 4.f, posY + 4.f), transfromEase);
        ImRenderUtil::drawText(textPos, &targetName, UIColor(255, 255, 255), transfromEase * 1.2, opacityEase, true);*/
        
    }
    void onEvent(UpdateTickEvent* event) {/*
        Game::GetLocalPlayer()->getRenderPositionComponent()->renderPos.x = 90;*/
    }
    //void onEvent(ImGUIRenderEvent* event)
    //{
    //    /*float index = 0;
    //    const float spacing = 55.f;

    //    float width = 300.f;
    //    float height = 350.f;

    //    std::string titleStr = "Select a theme!";

    //    Vector2<float> res = ImRenderUtil::getScreenSize();

    //    Vector4<float> rect = Vector4<float>((res.x / 2) - width, (res.y / 2) - height, (res.x / 2) + width, (res.y / 2) + height);

    //    ImRenderUtil::fillRectangle(rect, UIColor(0, 0, 0), 0.6f, 60.f);

    //    ImRenderUtil::drawText(Vector2<float>(rect.x + rect.getWidth() / 2 - ImRenderUtil::getTextWidth(&titleStr, 1.4f) / 2, rect.y + 25.f), &titleStr, UIColor(255, 255, 255), 1.4f, 1.f, true);
    //    ImRect clip_rect(rect.x, rect.y, rect.x, rect.x);
    //    clip_rect.Min.x = rect.x;
    //    clip_rect.Min.y = rect.y;
    //    clip_rect.Max.x = rect.z;
    //    clip_rect.Max.y = rect.w - heig;

    //    ImDrawList* list = ImGui::GetBackgroundDrawList();
    //    list->PushClipRect(clip_rect.Min, clip_rect.Max, true);
    //    for (auto& command : Game::Iris::commands)
    //    {
    //        int theme = command.second;
    //        std::string themeName = command.first;
    //        themeName[0] = std::toupper(themeName[0]);

    //        UIColor themeColor = getClientColor(theme, 0);
    //        UIColor themeColor2 = getClientColor(theme, 800);

    //        Vector4<float> pos = Vector4<float>(rect.x + 25.f, rect.y + 120.f + index, rect.x + rect.getWidth() - 25.f, rect.y + 150.f + index);
    //        Vector2<float> pos2 = Vector2<float>(rect.x + 25.f, rect.y + 120.f + index + pos.getHeight() / 2 - (ImRenderUtil::getTextHeight(1.2f) / 2));

    //        ImRenderUtil::fillGradientOpaqueRectangle(pos, themeColor, themeColor2, 1.f, 1.f);
    //        ImRenderUtil::drawText(pos2, &themeName, UIColor(255, 255, 255), 1.2f, 1.f, true);

    //        index += spacing;
    //    }
    //    list->PopClipRect();*/

    //   


    //}
    void DrawSoftShadowedBox(const ImVec4& boxColor, const ImVec2& position, const ImVec2& size, float shadowBlur, float shadowOffset)
    {
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();

        // Calculate shadow shape
        ImVec2 shadowPos = position + ImVec2(shadowOffset, shadowOffset);
        ImVec2 shadowSize = size + ImVec2(shadowBlur * 2, shadowBlur * 2);

        // Calculate the number of layers for the soft shadow
        int numLayers = static_cast<int>(shadowBlur) * 4; // Increase the multiplier to have more layers for softer shadow

        // Calculate the corner radius for the rounded shadow
        float cornerRadius = shadowBlur;

        // Draw the shadow layers
        for (int i = numLayers; i > 0; --i)
        {
            float alpha = static_cast<float>(i) / numLayers * 0.1f; // Adjust the multiplier to control the darkness of the shadow
            ImU32 shadowColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, alpha));
            ImVec2 offset = ImVec2(i, i);

            drawList->AddRectFilledMultiColor(
                shadowPos - offset, shadowPos + shadowSize + offset,
                shadowColor, shadowColor, shadowColor, shadowColor
            );
        }

        // Draw the box with rounded corners
        drawList->AddRectFilledMultiColor(
            position, position + size,
            ImGui::ColorConvertFloat4ToU32(boxColor), ImGui::ColorConvertFloat4ToU32(boxColor),
            ImGui::ColorConvertFloat4ToU32(boxColor), ImGui::ColorConvertFloat4ToU32(boxColor)
        );

        // Draw rounded corners for the shadow
        drawList->AddRectFilled(
            shadowPos - ImVec2(cornerRadius, cornerRadius),
            shadowPos + shadowSize + ImVec2(cornerRadius, cornerRadius),
            ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 0.0f)),
            cornerRadius,
            ImDrawCornerFlags_All
        );
    }
    
    //void onEvent(ImGUIRenderEvent* event)
    //{
    //    //static Vector2<float> prevMousePos = GuiInfo::MousePos.toFloat();
    //    //Vector2<float> currentMousePos = GuiInfo::MousePos.toFloat();
    //    //Vector2<float> mouseVelocity = currentMousePos - prevMousePos;
    //    //prevMousePos = currentMousePos;

    //    //float decayFactor = 0.2f;
    //    //mouseVelocity *= decayFactor;

    //    //Vector4<float> targetPos = Vector4<float>(Game::Core::ClientInstance->getGuiData()->WindowResolution2.x / 2 - 20, Game::Core::ClientInstance->getGuiData()->WindowResolution2.y / 2 - 20, Game::Core::ClientInstance->getGuiData()->WindowResolution2.x / 2 + 20, Game::Core::ClientInstance->getGuiData()->WindowResolution2.y / 2 + 20);
    //    //static Vector4<float> pos = targetPos;
    //    //pos = pos.lerp(targetPos, RenderUtil::getDeltaTime() * 8);

    //    //pos.x += mouseVelocity.x;
    //    //pos.z += mouseVelocity.x;
    //    //pos.y += mouseVelocity.y;
    //    //pos.w += mouseVelocity.y;

    //    //float fadeFactor = 0.2f;
    //    //static std::list<Vector4<float>> trailPositions; // List to store the trail positions
    //    //static const int maxTrailSize = 10;

    //    //trailPositions.push_front(pos);

    //    //// Remove excessive trail positions
    //    //while (trailPositions.size() > maxTrailSize)
    //    //    trailPositions.pop_back();

    //    //float opacityStep = 1.0f / trailPositions.size();

    //    //float sizeStep = 20.0f / trailPositions.size();
    //    //float currentSize = 20.0f;
    //    //float currentOpacity = 1.0f;

    //    //for (const auto& trailPos : trailPositions)
    //    //{
    //    //    Vector4<float> trailRect = Vector4<float>(trailPos.x - currentSize * 0.5f, trailPos.y - currentSize * 0.5f, trailPos.x + currentSize * 0.5f, trailPos.y + currentSize * 0.5f);
    //    //    ImRenderUtil::fillRectangle(trailRect, UIColor(255, 255, 255, static_cast<int>(currentOpacity * 255)), 0.5f, 10);
    //    //    currentSize -= sizeStep;
    //    //    currentOpacity -= opacityStep;
    //    //}

    //    //Vector4<float> currentRect = Vector4<float>(pos.x - 10.0f, pos.y - 10.0f, pos.x + 10.0f, pos.y + 10.0f);
    //    //ImRenderUtil::fillRectangle(currentRect, UIColor(255, 255, 255), 0.5f, 10);

    //    Vector4<float> buttonPos = Vector4<float>(200, 200, 350, 225);
    //    float stringGap = 60.0f;
    //    float totalWidth = 0.0f;

    //    // Draw the main rect
    //    ImRenderUtil::fillRectangle(buttonPos, UIColor(0, 0, 0), 0.8f, 8.f);
    //    ImRect clip_rect(buttonPos.x + 20, buttonPos.y, buttonPos.z - 20.f, buttonPos.w);

    //    ImDrawList* list = ImGui::GetBackgroundDrawList();
    //    //list->PushClipRect(clip_rect.Min, clip_rect.Max, true);

    //    // Left handle to press
    //    if (ImRenderUtil::isMouseOver(Vector4<float>(buttonPos.z - 20, buttonPos.y + 5.f, buttonPos.z - 5.f, buttonPos.w - 5.f)) && Util::leftClick) {
    //        onClickRightHandle();
    //        Util::leftClick = false;
    //    }
    //    ImRenderUtil::fillRectangle(Vector4<float>(buttonPos.z - 20, buttonPos.y + 5.f, buttonPos.z - 5.f, buttonPos.w - 5.f), UIColor(255, 255, 255), 0.8f, 8.f);

    //    // Right handle to press
    //    if (ImRenderUtil::isMouseOver(Vector4<float>(buttonPos.x + 5.f, buttonPos.y + 5.f, buttonPos.x + 20.f, buttonPos.w - 5.f)) && Util::leftClick) {
    //        onClickLeftHandle();
    //        Util::leftClick = false;
    //    }
    //    ImRenderUtil::fillRectangle(Vector4<float>(buttonPos.x + 5.f, buttonPos.y + 5.f, buttonPos.x + 20.f, buttonPos.w - 5.f), UIColor(255, 255, 255), 0.8f, 8.f);

    //    // Calculate the total width of all strings with gaps
    //    for (std::string& str : stringList) {
    //        totalWidth += ImRenderUtil::getTextWidth(&str, 1.2f) + stringGap;
    //    }

    //    float startX = buttonPos.x + buttonPos.getWidth() / 2 - totalWidth / 2;
    //    float selectedStringWidth = ImRenderUtil::getTextWidth(&stringList[currentIndex], 1.2f);
    //    float positionAdjustment = buttonPos.x + buttonPos.getWidth() / 2 - (startX + selectedStringWidth / 2);
    //    positionAdjustment -= currentIndex * (ImRenderUtil::getTextWidth(&stringList[0], 1.2f) + stringGap);

    //    // Animation variables
    //    static float offset = 0.0f;
    //    float targetOffset = positionAdjustment;
    //    static float animationSpeed = 10.0f;

    //    // Animate the offset
    //    offset = Math::lerp(offset, targetOffset, RenderUtil::getDeltaTime() * animationSpeed);

    //    // Loop through all the strings and render them with the adjusted position and fading effect
    //    float currentX = startX + offset;
    //    for (size_t i = 0; i < stringList.size(); i++) {
    //        std::string& str = stringList[i];
    //        // Calculate the target fade alpha based on the selection status
    //        float targetAlpha = (i == currentIndex) ? 1.0f : 0.0f;
    //        // Animation variables
    //        static float currentAlpha = targetAlpha;
    //        // Animate the alpha
    //        currentAlpha = Math::lerp(currentAlpha, targetAlpha, animationSpeed);
    //        // Render the text with adjusted position and fade alpha
    //        ImRenderUtil::drawText(Vector2<float>(currentX, buttonPos.y + buttonPos.getHeight() / 2 - ImRenderUtil::getTextHeight(1.2f) / 2), &str, UIColor(255, 255, 255, static_cast<int>(255 * currentAlpha)), 1.2f, currentAlpha, true);

    //        currentX += ImRenderUtil::getTextWidth(&str, 1.2f) + stringGap;
    //    }

    //    //list->PopClipRect();

    //}
    int currentIndex = 0;
    std::vector<std::string> stringList = { "str1", "str2", "str3" };

    // Click event handler for the right handle
    void onClickRightHandle()
    {
        currentIndex++;
        if (currentIndex >= stringList.size()) {
            currentIndex = 0;  // Wrap around to the first element
        }
    }

    // Click event handler for the left handle
    void onClickLeftHandle()
    {
        currentIndex--;
        if (currentIndex < 0) {
            currentIndex = stringList.size() - 1;  // Wrap around to the last element
        }
    }

    void onEnabled() override 
    {
        //NetworkUtil::openURL("https://www.pornhub.com/");
    }
};
