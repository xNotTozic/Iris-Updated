#pragma once
#include "ClickGUIManager.h"

class IrisGUI {
public:
    struct CategoryPosition {
        float x = 0.f, y = 0.f;
        bool isDragging = false, isExtended = true, wasExtended = false;
        float yOffset = 0;
        float scrollEase = 0;
        Vector2<float> dragVelocity = Vector2<float>();
        Vector2<float> dragAcceleration = Vector2<float>();
    };

    void render(float animation, float inScale, int& scrollDirection)
    {
        // Draw a faint background behind everything
        UIColor backColor = ColorUtil::getClientColor(5, 1, 1, 0);
        UIColor backColor2 = ColorUtil::getClientColor(5, 1, 1, 800);
        ImRenderUtil::fillRectangle(Vector4<float>(0, 0, ImRenderUtil::getScreenSize().x, ImRenderUtil::getScreenSize().y), UIColor(0, 0, 0), animation * 0.6f);
        ImRenderUtil::fillGradientOpaqueRectangle(Vector4<float>(0, 0, ImRenderUtil::getScreenSize().x, ImRenderUtil::getScreenSize().y), backColor, backColor2, animation * 0.5f, 0.f);

        bool isEnabled = getModuleByName("clickgui")->isEnabled();
        std::string tooltip = "";

        float textSize = inScale;
        float textHeight = ImRenderUtil::getTextHeight(textSize);

        if (catPositions.empty() && isEnabled)
        {
            float centerX = ImRenderUtil::getScreenSize().x / 2.f;
            float xPos = centerX - (categories.size() * (catWidth + catGap) / 2);
            for (std::string& category : categories)
            {
                CategoryPosition pos;
                pos.x = xPos;
                pos.y = catGap * 2;
                xPos += catWidth + catGap;
                catPositions.push_back(pos);
            }
        }

        if (!catPositions.empty())
        {
            for (size_t i = 0; i < categories.size(); i++)
            {
                // Mod math stuff
                const float modWidth = catWidth;
                const float modHeight = catHeight;
                float moduleY = -catPositions[i].yOffset;

                // Get all the modules and populate our vector
                const auto& modsInCategory = ClickGUIManager::getModulesInCategory(categories[i], modules);

                // Calculate the catRect pos
                Vector4<float> catRect = Vector4<float>(catPositions[i].x, catPositions[i].y, catPositions[i].x + catWidth, catPositions[i].y + catHeight)
                    .scaleToPoint(Vector4<float>(ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2, ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2), inScale);

                /* Calculate the height of the catWindow including the settings */
                float settingsHeight = 0;

                for (const auto& mod : modsInCategory) {
                    if (mod->cAnim < 0.01f || !mod->exists)
                        continue;

                    for (const auto& setting : mod->getSettings()) {
                        switch (setting->getType())
                        {
                        case SettingType::BOOL: {
                            settingsHeight = Math::lerp(settingsHeight, settingsHeight + modHeight, mod->cAnim);
                            break;
                        }
                        case SettingType::ENUM: {
                            std::vector<std::string> enumValues = setting->getEnumValues();
                            int numValues = static_cast<int>(enumValues.size());

                            settingsHeight = Math::lerp(settingsHeight, settingsHeight + modHeight, mod->cAnim);
                            if (setting->enumSlide > 0.01)
                            {
                                for (int j = 0; j < numValues; j++)
                                    settingsHeight = Math::lerp(settingsHeight, settingsHeight + modHeight, setting->enumSlide);
                            }
                            break;
                        }
                        case SettingType::SLIDER: {
                            settingsHeight = Math::lerp(settingsHeight, settingsHeight + modHeight, mod->cAnim);
                            break;
                        }
                        }
                    }
                }

                float catWindowHeight = catHeight + modHeight * modsInCategory.size() + settingsHeight;
                Vector4<float> catWindow = Vector4<float>(catPositions[i].x, catPositions[i].y, catPositions[i].x + catWidth, catPositions[i].y + moduleY + catWindowHeight)
                    .scaleToPoint(Vector4<float>(ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2, ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2), inScale);
                ImRenderUtil::fillShadowRectangle(catWindow, UIColor(0, 0, 0), animation * 0.8f, 100, 0);
                UIColor rgb = ColorUtil::getClientColor(5, 1, 1, i * 20);
                
                //ImRenderUtil::fillShadowRectangle(catWindow.scale(0), rgb, 555.F, 200, Vector2<float>(0.f, 0.f), 0);
                
                // Can we scroll?
                if (ImRenderUtil::isMouseOver(catWindow) && catPositions[i].isExtended) {
                    if (scrollDirection > 0) {
                        catPositions[i].scrollEase += scrollDirection * catHeight;
                        if (catPositions[i].scrollEase > catWindowHeight - modHeight * 2)
                            catPositions[i].scrollEase = catWindowHeight - modHeight * 2;
                    }
                    else if (scrollDirection < 0) {
                        catPositions[i].scrollEase += scrollDirection * catHeight;
                        if (catPositions[i].scrollEase < 0)
                            catPositions[i].scrollEase = 0;
                    }
                    scrollDirection = 0;
                }

                // Lerp the category extending
                if (!catPositions[i].isExtended) {
                    catPositions[i].scrollEase = catWindowHeight - catHeight;
                    catPositions[i].wasExtended = false;
                }
                else if (!catPositions[i].wasExtended) {
                    catPositions[i].scrollEase = 0;
                    catPositions[i].wasExtended = true;
                }

                // Lerp the scrolling cuz smooth
                catPositions[i].yOffset = Math::animate(catPositions[i].scrollEase, catPositions[i].yOffset, ImRenderUtil::getDeltaTime() * 10.5);

                for (const auto& mod : modsInCategory) {
                    if (!mod->exists) {
                        continue;
                    }

                    UIColor rgb = ColorUtil::getClientColor(5, 1, 1, moduleY * 2);

                    // If the mod belongs to the category
                    if (mod->getCategory() == categories[i]) {
                        // Calculate the modRect pos
                        Vector4<float> modRect = Vector4<float>(catPositions[i].x, catPositions[i].y + catHeight + moduleY, catPositions[i].x + modWidth, catPositions[i].y + catHeight + moduleY + modHeight)
                            .scaleToPoint(Vector4<float>(ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2, ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2), inScale);

                        // Animate the setting animation percentage
                        float targetAnim = mod->showSettings ? 1.f : 0.f;
                        mod->cAnim = Math::animate(targetAnim, mod->cAnim, ImRenderUtil::getDeltaTime() * 10);
                        mod->cAnim = Math::clamp(mod->cAnim, 0.f, 1.f);

                        // Settings
                        if (mod->cAnim > 0.001) {
                            for (const auto& setting : mod->getSettings()) {
                                if (!setting->render) {
                                    continue;
                                }

                                UIColor rgb = ColorUtil::getClientColor(5, 1, 1, moduleY * 2);

                                switch (setting->getType()) {
                                case SettingType::BOOL: {
                                    moduleY = Math::lerp(moduleY, moduleY + modHeight, mod->cAnim);

                                    Vector4<float> rect = Vector4<float>(modRect.x, catPositions[i].y + catHeight + moduleY, modRect.z, catPositions[i].y + catHeight + moduleY + modHeight)
                                        .scaleToPoint(Vector4<float>(modRect.x, ImRenderUtil::getScreenSize().y / 2, modRect.z, ImRenderUtil::getScreenSize().y / 2), inScale);

                                    if (rect.y > catRect.y + 0.5f) {
                                        std::string setName = setting->getName();
                                        ImRenderUtil::fillRectangle(rect, UIColor(25, 25, 25), animation);

                                        if (ImRenderUtil::isMouseOver(rect) && isEnabled) {
                                            tooltip = setting->getDescription();
                                            if (Util::leftDown) {
                                                *(bool*)setting->getValue() = !*(bool*)setting->getValue();
                                                Util::leftDown = false;
                                            }
                                        }

                                        setting->boolScale = Math::animate(*(bool*)setting->getValue() ? 1 : 0, setting->boolScale, ImRenderUtil::getDeltaTime() * 10);

                                        float scaledWidth = rect.getWidth() * setting->boolScale;
                                        float scaledHeight = rect.getHeight() * setting->boolScale;
                                        Vector2<float> center = Vector2<float>(rect.x + rect.getWidth() / 2.f, rect.y + rect.getHeight() / 2.f);
                                        Vector4<float> scaledRect = Vector4<float>(center.x - scaledWidth / 2.f, center.y - scaledHeight / 2.f, center.x + scaledWidth / 2.f, center.y + scaledHeight / 2.f);

                                        ImRenderUtil::fillRectangle(scaledRect, rgb, animation * (setting->boolScale));

                                        float cSetRectCentreX = rect.x + ((rect.z - rect.x) - ImRenderUtil::getTextWidth(&setName, textSize)) / 2;
                                        float cSetRectCentreY = rect.y + ((rect.w - rect.y) - textHeight) / 2;
                                        ImRenderUtil::drawText(Vector2(rect.x + 5.f, cSetRectCentreY), &setName, *(bool*)setting->getValue() ? UIColor(255, 255, 255) : UIColor(180, 180, 180), textSize, animation, true);
                                    }
                                    break;
                                }
                                case SettingType::ENUM: {
                                    std::string setName = setting->getName();
                                    std::vector<std::string> enumValues = setting->getEnumValues();
                                    int* iterator = setting->getIterator();
                                    int numValues = static_cast<int>(enumValues.size());

                                    // Increment the yOffset
                                    moduleY = Math::lerp(moduleY, moduleY + modHeight, mod->cAnim);

                                    Vector4<float> rect = Vector4<float>(modRect.x, catPositions[i].y + catHeight + moduleY, modRect.z, catPositions[i].y + catHeight + moduleY + modHeight)
                                        .scaleToPoint(Vector4<float>(modRect.x, ImRenderUtil::getScreenSize().y / 2, modRect.z, ImRenderUtil::getScreenSize().y / 2), inScale);

                                    // Animate the setting animation percentage
                                    float targetAnim = setting->enumExtended && mod->showSettings ? 1.f : 0.f;
                                    setting->enumSlide = Math::animate(targetAnim, setting->enumSlide, ImRenderUtil::getDeltaTime() * 10);
                                    setting->enumSlide = Math::clamp(setting->enumSlide, 0.f, 1.f);

                                    if (setting->enumSlide > 0.001)
                                    {
                                        for (int j = 0; j < numValues; j++)
                                        {
                                            std::string enumValue = enumValues[j];

                                            // Calculate current position using easing function
                                            moduleY = Math::lerp(moduleY, moduleY + modHeight, setting->enumSlide);

                                            Vector4<float> rect2 = Vector4<float>(modRect.x, catPositions[i].y + catHeight + moduleY, modRect.z, catPositions[i].y + catHeight + moduleY + modHeight)
                                                .scaleToPoint(Vector4<float>(modRect.x, ImRenderUtil::getScreenSize().y / 2, modRect.z, ImRenderUtil::getScreenSize().y / 2), inScale);

                                            if (rect2.y > catRect.y + 0.5f)
                                            {
                                                float cSetRectCentreY = rect2.y + ((rect2.w - rect2.y) - textHeight) / 2;

                                                ImRenderUtil::fillRectangle(rect2, UIColor(20, 20, 20), animation);

                                                if (*iterator == j)
                                                    ImRenderUtil::fillRectangle(Vector4<float>(rect2.x, rect2.y, rect2.x + 1.5f, rect2.w), rgb, animation);

                                                if (ImRenderUtil::isMouseOver(rect2) && Util::leftDown && isEnabled) {
                                                    *iterator = j;
                                                    Util::leftDown = false;
                                                }

                                                ImRenderUtil::drawText(Vector2<float>(rect2.x + 5.f, cSetRectCentreY), &enumValue, UIColor(255, 255, 255), textSize, animation, true);
                                            }
                                        }
                                    }

                                    if (rect.y > catRect.y + 0.5f) {
                                        ImRenderUtil::fillRectangle(rect, UIColor(25, 25, 25), animation);

                                        if (ImRenderUtil::isMouseOver(rect) && isEnabled) {
                                            tooltip = setting->getDescription();
                                            if (Util::leftDown) {
                                                *iterator = (*iterator + 1) % enumValues.size();
                                            }
                                            else if (Util::rightDown && mod->showSettings) {
                                                setting->enumExtended = !setting->enumExtended;
                                            }
                                        }

                                        float cSetRectCentreY = rect.y + ((rect.w - rect.y) - textHeight) / 2;

                                        std::string enumValue = enumValues[*iterator];
                                        std::string settingString = setName + ": " + enumValue;

                                        ImRenderUtil::drawText(Vector2<float>(rect.x + 5.f, cSetRectCentreY), &settingString, UIColor(255, 255, 255), textSize, animation, true);
                                    }
                                    if (rect.y > catRect.y - modHeight) {
                                        ImRenderUtil::fillGradientOpaqueRectangle(Vector4<float>(rect.x, rect.w, rect.z, rect.w + 10.f * setting->enumSlide * animation), UIColor(0, 0, 0), UIColor(0, 0, 0), 0.F * animation, 0.55F * animation);
                                    }
                                    break;
                                }
                                case SettingType::SLIDER: {
                                    const float value = *(float*)setting->getValue();
                                    const float min = setting->getMin();
                                    const float max = setting->getMax();

                                    char str[10];
                                    sprintf_s(str, 10, "%.2f", value);
                                    std::string rVal = str;

                                    std::string setName = setting->getName() + " " + rVal;

                                    moduleY = Math::lerp(moduleY, moduleY + modHeight, mod->cAnim);

                                    Vector4<float> rect = Vector4<float>(modRect.x, catPositions[i].y + catHeight + moduleY, modRect.z, catPositions[i].y + catHeight + moduleY + modHeight)
                                        .scaleToPoint(Vector4<float>(modRect.x, ImRenderUtil::getScreenSize().y / 2, modRect.z, ImRenderUtil::getScreenSize().y / 2), inScale);

                                    if (rect.y > catRect.y + 0.5f)
                                    {
                                        ImRenderUtil::fillRectangle(rect, UIColor(25, 25, 25), animation);

                                        const float sliderPos = (value - min) / (max - min) * (rect.z - rect.x);

                                        setting->sliderEase = Math::animate(sliderPos, setting->sliderEase, ImRenderUtil::getDeltaTime() * 10);
                                        setting->sliderEase = std::clamp(setting->sliderEase, 0.f, rect.getWidth());

                                        if (ImRenderUtil::isMouseOver(rect) && isEnabled) {
                                            tooltip = setting->getDescription();
                                            if (Util::leftDown) {
                                                setting->isDragging = true;
                                            }
                                        }

                                        if (Util::leftClick && setting->isDragging && isEnabled) {
                                            const float newValue = std::max(std::min((ImRenderUtil::getMousePos().x - rect.x) / (rect.z - rect.x) * (max - min) + min, max), min);
                                            *(float*)setting->getValue() = newValue;
                                        }
                                        else {
                                            setting->isDragging = false;
                                        }

                                        ImRenderUtil::fillRectangle(Vector4<float>(rect.x, rect.y, rect.x + setting->sliderEase, rect.w), rgb, animation);

                                        ImRenderUtil::drawText(Vector2<float>(rect.x + 5.f, rect.y + 2.5f), &setName, UIColor(255, 255, 255), textSize, animation, true);
                                    }
                                    break;
                                }
                                }
                            }
                        }

                        if (modRect.y > catRect.y + 0.5f)
                        {
                            // Draw the rect
                            if (mod->cScale <= 1) ImRenderUtil::fillRectangle(modRect, UIColor(35, 35, 35), animation);

                            std::string modName = (mod == lastMod && ClickGUIManager::isBinding) ? "Binding..." : mod->getName();

                            // Calculate the centre of the rect
                            Vector2<float> center = Vector2<float>(modRect.x + modRect.getWidth() / 2.f, modRect.y + modRect.getHeight() / 2.f);

                            mod->cScale = Math::animate(mod->isEnabled() ? 1 : 0, mod->cScale, ImRenderUtil::getDeltaTime() * 10);

                            // Calculate scaled size based on cScale
                            float scaledWidth = modRect.getWidth() * mod->cScale;
                            float scaledHeight = modRect.getHeight() * mod->cScale;

                            // Calculate new rectangle based on scaled size and center point
                            Vector4<float> scaledRect = Vector4<float>(center.x - scaledWidth / 2.f, center.y - scaledHeight / 2.f, center.x + scaledWidth / 2.f, center.y + scaledHeight / 2.f);

                            // Interpolate between original rectangle and scaled rectangle
                            if (mod->cScale > 0) ImRenderUtil::fillRectangle(scaledRect, rgb, animation * mod->cScale);

                            float cRectCentreX = modRect.x + ((modRect.z - modRect.x) - ImRenderUtil::getTextWidth(&modName, textSize)) / 2;
                            float cRectCentreY = modRect.y + ((modRect.w - modRect.y) - textHeight) / 2;

                            Vector2<float> modPosLerped = Vector2<float>(cRectCentreX, cRectCentreY).lerp(Vector2<float>(modRect.x + 5, cRectCentreY), mod->cAnim);

                            // Draw the string
                            ImRenderUtil::drawText(modPosLerped, &modName, UIColor(mod->isEnabled() ? UIColor(255, 255, 255) : UIColor(180, 180, 180)).lerp(UIColor(100, 100, 100), mod->cAnim), textSize, animation, true);

                            if (ImRenderUtil::isMouseOver(modRect) && catPositions[i].isExtended && isEnabled)
                            {
                                if (ImRenderUtil::isMouseOver(catWindow) && catPositions[i].isExtended) {
                                    tooltip = mod->getDescription();
                                }
                                if (Util::leftDown)
                                {
                                    mod->toggle();
                                    Util::leftDown = false;
                                    //particleMgr.addParticles(5, GuiInfo::MousePos.x, GuiInfo::MousePos.y, 80, 2.f);
                                }
                                else if (Util::rightClick)
                                {
                                    mod->showSettings = !mod->showSettings;
                                    Util::rightClick = false;
                                }
                                else if (Util::middleClick) {
                                    lastMod = mod;
                                    ClickGUIManager::isBinding = true;
                                    Util::middleClick = false;
                                }
                            }
                        }
                        if (modRect.y > catRect.y - modHeight) {
                            // Render a slight glow effect
                            ImRenderUtil::fillGradientOpaqueRectangle(Vector4<float>(modRect.x, modRect.w, modRect.z, modRect.w + 10.f * mod->cAnim * animation), UIColor(0, 0, 0), UIColor(0, 0, 0), 0.F * animation, 0.55F * animation);
                        }
                        moduleY += modHeight;
                    }
                }

                if (ClickGUIManager::isBinding) {
                    tooltip = combine("Currently binding ", lastMod->getName(), "...", " Press ESC to unbind.");
                    for (const auto& key : Game::Core::Keymap) {
                        if (key.second && lastMod) {
                            lastMod->setKeybind(key.first == Keyboard::ESC ? 0 : key.first);
                            ClickGUIManager::isBinding = false;
                        }
                    }
                }

                std::string catName = categories[i];

                if (ImRenderUtil::isMouseOver(catRect) && Util::rightDown)
                    catPositions[i].isExtended = !catPositions[i].isExtended;

                ImRenderUtil::fillRectangle(catRect, UIColor(20, 20, 20), animation);

                // Calculate the centre of the rect
                float cRectCentreX = catRect.x + ((catRect.z - catRect.x) - ImRenderUtil::getTextWidth(&catName, textSize)) / 2;
                float cRectCentreY = catRect.y + ((catRect.w - catRect.y) - textHeight) / 2;

                // Draw the string
                ImRenderUtil::drawText(Vector2(cRectCentreX, cRectCentreY), &catName, UIColor(255, 255, 255), textSize, animation, true);

                catPositions[i].x = std::clamp(catPositions[i].x, 0.f, ImRenderUtil::getScreenSize().x - catWidth);
                catPositions[i].y = std::clamp(catPositions[i].y, 0.f, ImRenderUtil::getScreenSize().y - catHeight);

#pragma region DraggingLogic
                static bool dragging = false;
                static Vector2<float> dragOffset;
                if (catPositions[i].isDragging)
                {
                    if (Util::leftClick)
                    {
                        if (!dragging)
                        {
                            dragOffset = ImRenderUtil::getMousePos() - Vector2<float>(catRect.x, catRect.y);
                            dragging = true;
                        }
                        Vector2<float> newPosition = ImRenderUtil::getMousePos() - dragOffset;
                        newPosition.x = std::clamp(newPosition.toFloat().x, 0.f, ImRenderUtil::getScreenSize().x - catWidth);
                        newPosition.y = std::clamp(newPosition.toFloat().y, 0.f, ImRenderUtil::getScreenSize().y - catHeight);
                        catPositions[i].x = newPosition.x;
                        catPositions[i].y = newPosition.y;
                    }
                    else
                    {
                        catPositions[i].isDragging = false;
                        dragging = false;
                    }
                }
                else if (ImRenderUtil::isMouseOver(catRect) && Util::leftDown && isEnabled)
                {
                    Util::leftDown = false;
                    catPositions[i].isDragging = true;
                    dragOffset = ImRenderUtil::getMousePos() - Vector2<float>(catRect.x, catRect.y);
                }
#pragma endregion
                ImRenderUtil::drawRoundRect(catWindow.scale(-1), ImDrawFlags_RoundCornersMask_, 5, UIColor(35, 35, 35), animation, 2.f); Vector2 mousePos(ImRenderUtil::getMousePos());
            }

            if (!tooltip.empty()) {
                float textWidth = ImRenderUtil::getTextWidth(&tooltip, textSize * 0.8f);
                float textHeight = ImRenderUtil::getTextHeight(textSize * 0.8f);
                float padding = 2.5f;
                float offset = 8.f;

                Vector4<float> tooltipRect = Vector4<float>(
                    ImRenderUtil::getMousePos().x + offset - padding,
                    ImRenderUtil::getMousePos().y + textHeight / 2 - textHeight - padding,
                    ImRenderUtil::getMousePos().x + offset + textWidth + padding * 2,
                    ImRenderUtil::getMousePos().y + textHeight / 2 + padding
                ).scaleToPoint(Vector4<float>(
                    ImRenderUtil::getScreenSize().x / 2,
                    ImRenderUtil::getScreenSize().y / 2,
                    ImRenderUtil::getScreenSize().x / 2,
                    ImRenderUtil::getScreenSize().y / 2
                ), inScale);

                ImRenderUtil::fillShadowRectangle(tooltipRect, UIColor(0, 0, 0), animation * 0.5f, 30, 0);
                ImRenderUtil::fillRectangle(tooltipRect, UIColor(20, 20, 20), animation, 5.f);
                ImRenderUtil::drawText(Vector2(tooltipRect.x + padding, tooltipRect.y + padding), &tooltip, UIColor(255, 255, 255), textSize * 0.8f, animation, true);
            }

            if (isEnabled) {
                Util::leftDown = false;
                Util::rightDown = false;
                Util::rightClick = false;
                Game::GetInstance()->releaseCursor();
                scrollDirection = 0;
            }
        }
    }

    const float catWidth = 150.f;
    const float catHeight = 25.f;

    const float catGap = 40;
    int lastDragged = -1;
    std::vector<CategoryPosition> catPositions;
    Module* lastMod = nullptr;
};
