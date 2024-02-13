#pragma once

class ESP : public Module
{
public:
    ESP(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("ESP", "Visual", "Draw basic boxes around entities", keybind, enabled)
    {
        addEnum("Style", "Style of esp to use", { "Solid", "3D" }, &mode);
        addSlider("Thickness", "The thickness of each pixel", &thickness, 1, 10);
        addBool("OneCallRendering", "An optimized version of line rendering", &newLineRendering);
        //addSlider("EasingSpeed", "The speed at which it animates", &lerpSpeed, 5, 50);
    }

    float thickness = 1;
    float lerpSpeed = 1;
    bool newLineRendering = true;

    int mode = 1;

    void drawEntity(Player* entity)
    {
        switch (mode)
        {
        case 0:
        {
            if (!entity) return;

            if (entity->isLocalPlayer() || entity == Game::GetLocalPlayer()) return;

            Player* player = Game::GetLocalPlayer();
            if (!player) return;

            AABBShapeComponent* shape = entity->try_get<AABBShapeComponent>();
            if (!shape || IsBadReadPtr(shape, sizeof(AABBShapeComponent))) return;

            Vector3<float> entDims = { shape->r_Hitbox.x, shape->r_Hitbox.y, shape->r_Hitbox.x };

            if (entDims.x != 0.6f || entDims.y != 1.8f)
                return;

            if (player->isBot())
                return;

            Vector3<float> entLower = shape->r_Pos_Lower;
            Vector3<float> entUpper = shape->r_Pos_Upper;
            Vector3<float> entPos = entity->GetPosition();

            Vector3<float> origin = Game::GetInstance()->getLevelRender()->getOrigin();
            float dist = origin.distance(entPos);

            Vector2<float> output1, output2;
            if (!Game::GetInstance()->WorldToScreen(entLower, output1) || !Game::GetInstance()->WorldToScreen(entUpper, output2)) return;

            std::vector<Vector3<float>> aabbArr;
            for (float x : { entLower.x, entUpper.x })
            {
                for (float y : { entLower.y, entUpper.y })
                {
                    for (float z : { entLower.z, entUpper.z })
                    {
                        aabbArr.push_back({ x, y, z });
                    }
                }
            }

            std::vector<Vector2<float>> scrPoints;
            for (int i = 0; i < aabbArr.size(); i++)
            {
                Vector2<float> scrPoint;
                if (Game::GetInstance()->WorldToScreen(aabbArr[i], scrPoint))
                    scrPoints.push_back(scrPoint);
            }

            if (scrPoints.empty())
                return;

            Vector4<float> boundingRect = { scrPoints[0].x, scrPoints[0].y, scrPoints[0].x, scrPoints[0].y };
            for (const auto& point : scrPoints)
            {
                boundingRect.x = std::min(boundingRect.x, point.x);
                boundingRect.y = std::min(boundingRect.y, point.y);
                boundingRect.z = std::max(boundingRect.z, point.x);
                boundingRect.w = std::max(boundingRect.w, point.y);
            }

            float thickness = fmax(1.f, 1.f / std::max(1.f, origin.distance(entPos)));
            RenderUtil::renderImage(Util::getClientPath() + "Assets\\texel.png", boundingRect);
            RenderUtil::flushImage(UIColor(255, 255, 255), 0.5f);
        }
        break;

        case 1:
        {
            if (!entity) return;

            if (entity->isLocalPlayer() || entity == Game::GetLocalPlayer()) return;

            Player* player = Game::GetLocalPlayer();
            if (!player) return;

            AABBShapeComponent* shape = entity->try_get<AABBShapeComponent>();
            if (!shape || IsBadReadPtr(shape, sizeof(AABBShapeComponent))) return;

            if (player->isBot())
                return;

            Vector3<float> entLower = shape->r_Pos_Lower;

            Vector3<float> entDims = { shape->r_Hitbox.x, shape->r_Hitbox.y, shape->r_Hitbox.x };

            if (entDims.x != 0.6f || entDims.y != 1.8f)
                return;

            UIColor clientColour = ColorUtil::getClientColor(5, 1, 1, 1);

            ThreeUtil::DrawCube(entLower, clientColour, thickness, lerpSpeed, entDims, newLineRendering == true ? OneCall : Multi);
        }
        break;
        }
    }

    void onEvent(BeforeUpdateEvent* event) override
    {
        auto callback = [this](Player* act) { drawEntity(act); };
        getEntities(callback);
    }
};