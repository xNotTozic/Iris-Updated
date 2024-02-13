#pragma once

class ChronosGUI {
public:
    struct CategoryPosition {
        float x = 0.f, y = 0.f;
        bool isDragging = false, isExtended = true, wasExtended = false;
        float yOffset = 0, scrollEase = 0;
        float rotationAngle = 0;
    };
    const float catWidth = 165.f;
    const float catHeight = 24.f;

    const float catGap = 5;
    Module* lastMod = nullptr;
    std::vector<CategoryPosition> catPositions;

    void render(float animation, float inScale, int& scrollDirection)
    {
        bool isEnabled = getModuleByName("clickgui")->isEnabled();
        static std::string tooltip = "";

        float textSize = inScale * 1.2f;
        float textHeight = ImRenderUtil::getTextHeight(textSize);
        ImRenderUtil::fillRectangle(Vector4<float>(0, 0, ImRenderUtil::getScreenSize().x, ImRenderUtil::getScreenSize().y), UIColor(0, 0, 0), animation * 0.4f);
        if (catPositions.empty() && isEnabled) {
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

        ClickGUIManager::ImRotateStart();
        for (int i = 0; i < categories.size(); i++) {
            const float modWidth = catWidth;
            const float modHeight = 22;
            int moduleY = -catPositions[i].yOffset;
            int gapOffset = 2;
            UIColor chronos = UIColor(30, 106, 127); //idk

            // Calculate the catRect position
            Vector4<float> catRect = Vector4<float>(catPositions[i].x, catPositions[i].y, catPositions[i].x + catWidth, catPositions[i].y + catHeight)
                .scaleToPoint(Vector4<float>(ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2, ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2), inScale);

            // Get all the modules and populate our vector
            const auto& modsInCategory = ClickGUIManager::getModulesInCategory(categories[i], modules);
            float settingsHeight = 0;

            for (const auto& mod : modsInCategory) {
                if (!mod->exists)
                    continue;
                settingsHeight += modHeight + gapOffset;
            }

            float catWindowHeight = settingsHeight + 2;
            Vector4<int> catWindow = Vector4<int>(catPositions[i].x + 2, catPositions[i].y + catHeight, catPositions[i].x + catWidth - 2, catPositions[i].y + catHeight + catWindowHeight)
                .scaleToPoint(Vector4<int>(ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2, ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2), inScale);
            
            if (catPositions[i].isExtended) {
                ImRenderUtil::fillRectangle(catWindow, UIColor(0, 0, 0), animation * 0.2f);
            }
            bool isMouseOverModule = false; // Flag to track if mouse is over any module
            static float aalpha = 0;
            for (const auto& mod : modsInCategory) {
                if (!mod->exists || mod->getCategory() != categories[i] || !catPositions[i].isExtended)
                    continue;

                std::string modName = (mod == lastMod && ClickGUIManager::isBinding) ? "Binding..." : mod->getName();

                Vector4<float> modRect = Vector4<float>(catPositions[i].x + 4, catPositions[i].y + catHeight + moduleY + 2, catPositions[i].x + modWidth - 4, catPositions[i].y + catHeight + moduleY + modHeight + 2.f)
                    .scaleToPoint(Vector4<float>(ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2, ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2), inScale);
                
                ImRenderUtil::fillRectangle(modRect, mod->isEnabled() ? chronos : UIColor(0, 0, 0), animation * (mod->isEnabled() ? 0.9f : 0.2f));

                ImRenderUtil::drawText(Vector2<float>(modRect.x + 4, modRect.y + ((modRect.w - modRect.y) - textHeight) / 2), &modName, mod->isEnabled() ? UIColor(255, 255, 255) : UIColor(180, 180, 180), textSize, animation * 1, false);

                if (ImRenderUtil::isMouseOver(modRect) && catPositions[i].isExtended && isEnabled) {
                    isMouseOverModule = true;
                    if (Util::leftClick) {
                        mod->toggle();
                        Util::leftClick = false;
                    }
                    else if (Util::rightClick) {
                        mod->showSettings = !mod->showSettings;
                        Util::rightClick = false;
                    }
                    else if (Util::middleClick) {
                        lastMod = mod;
                        ClickGUIManager::isBinding = !ClickGUIManager::isBinding;
                        Util::middleClick = false;
                    }
                }
                moduleY += modHeight + gapOffset;
            }

            if (ClickGUIManager::isBinding) {
                for (const auto& key : Game::Core::Keymap) {
                    if (key.second && lastMod) {
                        lastMod->setKeybind(key.first == Keyboard::ESC ? 0 : key.first);
                        ClickGUIManager::isBinding = false;
                    }
                }
            }

            if (isMouseOverModule) {
                aalpha = Math::animate(aalpha, 1.f, RenderUtil::getDeltaTime() * 0.0002f * modsInCategory.size());
            }
            else {
                aalpha = Math::lerp(aalpha, 0.0f, RenderUtil::getDeltaTime() * 3);
            }
            std::string catName = categories[i];

            if (ImRenderUtil::isMouseOver(catRect) && Util::rightClick) {
                catPositions[i].isExtended = !catPositions[i].isExtended;
                Util::rightClick = false;
            }

            ImRenderUtil::fillRectangle(catRect, chronos, animation * 0.9f);
            ImRenderUtil::drawText(Vector2(catRect.x + 4, catRect.y + (catRect.getHeight() - textHeight) / 2), &catName, UIColor(255, 255, 255), textSize, animation, false);
            handleCategoryDragging(catRect, i, catWidth, catHeight, catPositions, isEnabled);

            if (isEnabled) {
                Game::GetInstance()->releaseCursor();
            }
            ClickGUIManager::ImRotateEnd(catPositions[i].rotationAngle);
        }
    }

    void handleCategoryDragging(Vector4<float> catRect, int i, float catWidth, float catHeight, std::vector<CategoryPosition>& catPositions, bool isEnabled)
    {
        catPositions[i].x = std::clamp(catPositions[i].x, 0.f, ImRenderUtil::getScreenSize().x - catWidth);
        catPositions[i].y = std::clamp(catPositions[i].y, 0.f, ImRenderUtil::getScreenSize().y - catHeight);

        static bool dragging = false;
        static Vector2<float> dragOffset;

        if (catPositions[i].isDragging)
        {
            if (Util::leftDown)
            {
                static ImVec2 prevMousePos = ImGui::GetIO().MousePos;
                ImVec2 currentMousePos = ImGui::GetIO().MousePos;
                ImVec2 mouseVelocity = currentMousePos - prevMousePos;
                prevMousePos = currentMousePos;

                float lerpSpeed = 0.075f; // Adjust this value to control the lerping speed
                ImVec2 targetCenter = currentMousePos;
                static ImVec2 center = targetCenter;
                center = ImLerp(center, targetCenter, lerpSpeed);

                // Lerping for rotation
                float rotationSpeed = 0.075f; // Adjust this value to control the rotation speed
                float targetRotationAngle = -mouseVelocity.x * rotationSpeed;
                catPositions[i].rotationAngle = ImLerp(catPositions[i].rotationAngle, targetRotationAngle, lerpSpeed);

                if (!dragging)
                {
                    dragOffset = ImRenderUtil::getMousePos() - Vector2<float>(catRect.x, catRect.y);
                    dragging = true;
                }

                Vector2<float> targetPosition = ImRenderUtil::getMousePos() - dragOffset;
                static Vector2<float> currentPosition = targetPosition;
                currentPosition = ImLerp(currentPosition, targetPosition, lerpSpeed);

                catPositions[i].x = std::clamp(currentPosition.toFloat().x, 0.f, ImRenderUtil::getScreenSize().x - catWidth);
                catPositions[i].y = std::clamp(currentPosition.toFloat().y, 0.f, ImRenderUtil::getScreenSize().y - catHeight);
            }
            else
            {
                catPositions[i].isDragging = false;
                dragging = false;
            }
        }
        else if (ImRenderUtil::isMouseOver(catRect) && Util::leftClick && isEnabled)
        {
            Util::leftClick = false;
            catPositions[i].isDragging = true;
            dragOffset = ImRenderUtil::getMousePos() - Vector2<float>(catRect.x, catRect.y);
        }
    }

    
    void HandleMiddleClickBinding(Module& mod, Module*& lastMod) {
        if (Util::middleClick) {
            lastMod = &mod;
            ClickGUIManager::isBinding = true;
            Util::middleClick = false;
        }

        if (ClickGUIManager::isBinding) {
            for (const auto& key : Game::Core::Keymap) {
                if (key.second && lastMod) {
                    lastMod->setKeybind(key.first);
                    ClickGUIManager::isBinding = false;
                    break;
                }
            }
        }
    }

};
