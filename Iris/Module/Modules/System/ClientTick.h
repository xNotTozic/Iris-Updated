#pragma once

class ClientTick : public Module
{
public:
    ClientTick(int keybind = Keyboard::NONE, bool enabled = true) :
        Module("ClientTick", "Misc", "You shouldnt be able to see this", keybind, enabled)
    {
        visible_ = false;
        exists = false;
        showNotifications = false;
    }

    void onEvent(PacketSendingEvent* event) override
    {
        if (event->Packet->instanceOf<MovePlayerPacket>())
        {
            MovePlayerPacket* packet = reinterpret_cast<MovePlayerPacket*>(event->Packet);

            lastRunId = packet->runtimeId;
        }
    };

    void onEvent(LayerUpdateEvent* event) override
    {
        if (UILayer::Is(event->GuiLayer, UILayer::Ingame_ChatScreen))
            Game::Core::InChat = true;

        if (UILayer::Is(event->GuiLayer, {
                UILayer::Ingame_InventoryScreen,
                UILayer::Ingame_CanMoveScreen
            }))
        {
            Game::Core::InChat = false;
        }
    }

    void onEvent(ImGUIRenderEvent* event) override
    {
        //    if (!g_debugMode)
        //        return;

        //    if (ImGui::Begin("Field Debugger"))
        //    {
        //        ImGui::BeginTabBar("TabStrip");

        //        if (ImGui::BeginTabItem("ImGui"))
        //        {
        //            ImGuiIO& io = ImGui::GetIO();

        //            ImGui::InputFloat("Framerate", &io.Framerate);
        //            ImGui::InputFloat("DeltaTime", &io.DeltaTime);
        //            ImGui::Checkbox("WantCaptureKeyboard", &io.WantCaptureKeyboard);
        //            ImGui::Checkbox("WantCaptureMouse", &io.WantCaptureMouse);

        //            ImGui::EndTabItem();
        //        }

        //        if (ImGui::BeginTabItem("GuiInfo"))
        //        {
        //            ImGui::InputFloat("DeltaTime", &GuiInfo::DeltaTime);
        //            ImGui::InputFloat("GuiScale", &GuiInfo::GuiScale);

        //            ImGui::EndTabItem();
        //        }

        //        if (ImGui::BeginTabItem("Game"))
        //        {
        //            ImGui::InputInt("gameFps", &Game::gameFps);
        //            ImGui::InputInt("frameCount", &Game::frameCount);

        //            if (ImGui::CollapsingHeader("Game::Core"))
        //            {
        //                ImGui::Checkbox("ApplyField", &Game::Core::ApplyField);
        //                ImGui::SliderFloat("FieldMultiplier", &Game::Core::FieldMultiplier, 0, 2);
        //                ImGui::SliderFloat("HotbarSpeed", &Game::Core::HotbarSpeed, 0, 60);
        //                ImGui::Checkbox("InChat", &Game::Core::InChat);
        //                ImGui::SliderFloat("SwingSpeed", &Game::Core::SwingSpeed, 0, 60);
        //            }

        //            if (ImGui::CollapsingHeader("Game::Iris"))
        //            {
        //                ImGui::InputInt("ClientColor", &Game::Iris::ClientColor);
        //                ImGui::Checkbox("ShouldBlock", &Game::Iris::ShouldBlock);
        //                ImGui::InputText("ClientName", &Game::Iris::ClientName[0], 32);
        //                ImGui::InputText("ClientVersion", &Game::Iris::ClientVersion[0], 32);
        //            }

        //            ImGui::EndTabItem();
        //        }

        //        if (Game::GetLocalPlayer() != nullptr)
        //        {
        //            Player* player = Game::GetLocalPlayer();

        //            // theres alot to cover here so I'll do it later
        //            if (ImGui::BeginTabItem("LocalPlayer"))
        //            {
        //                StateVectorComponent* state = player->try_get<StateVectorComponent>();
        //                MovementInterpolatorComponent* movement = player->try_get<MovementInterpolatorComponent>();
        //                AABBShapeComponent* shape = player->try_get<AABBShapeComponent>();

        //                Level* level = player->GetLevel();

        //                if (ImGui::TreeNode("Class Methods"))
        //                {
        //                    if (ImGui::TreeNode("SetPos"))
        //                    {
        //                        static Vector3<float> pos{};
        //                        ImGui::InputFloat("X", &pos.x);
        //                        ImGui::InputFloat("Y", &pos.y);
        //                        ImGui::InputFloat("Z", &pos.z);

        //                        if (ImGui::Button("Call Method"))
        //                        {
        //                            player->SetPos(pos);
        //                        }

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("TeleportTo"))
        //                    {
        //                        static Vector3<float> pos{};
        //                        ImGui::InputFloat("X", &pos.x);
        //                        ImGui::InputFloat("Y", &pos.y);
        //                        ImGui::InputFloat("Z", &pos.z);

        //                        if (ImGui::Button("Call Method"))
        //                        {
        //                            player->TeleportTo(pos);
        //                        }

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("DisplayClientMessage"))
        //                    {
        //                        static std::string msg = "Test message here";
        //                        ImGui::InputText("Message", &msg[0], msg.size());

        //                        if (ImGui::Button("Call Method"))
        //                        {
        //                            player->DisplayClientMessage(msg.c_str());
        //                        }

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("getHorizontalSpeed"))
        //                    {
        //                        float output = 0;
        //                        if (ImGui::Button("Call Method"))
        //                        {
        //                            output = player->getHorizontalSpeed();
        //                        }

        //                        ImGui::Text("Output(s)");
        //                        ImGui::InputFloat("HorizontalSpeed", &output);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("getVerticalSpeed"))
        //                    {
        //                        float output = 0;
        //                        if (ImGui::Button("Call Method"))
        //                        {
        //                            output = player->getVerticalSpeed();
        //                        }

        //                        ImGui::Text("Output(s)");
        //                        ImGui::InputFloat("VerticalSpeed", &output);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("OpenInventory"))
        //                    {
        //                        if (ImGui::Button("Call Method"))
        //                        {
        //                            player->OpenInventory();
        //                        }

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("OpenPorti"))
        //                    {
        //                        if (ImGui::Button("Call Method"))
        //                        {
        //                            player->OpenPorti();
        //                        }

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("jumpFromDaGround"))
        //                    {
        //                        if (ImGui::Button("Call Method"))
        //                        {
        //                            player->jumpFromDaGround();
        //                        }

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("Respawn"))
        //                    {
        //                        if (ImGui::Button("Call Method"))
        //                        {
        //                            player->Respawn();
        //                        }

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("Swing"))
        //                    {
        //                        if (ImGui::Button("Call Method"))
        //                        {
        //                            player->Swing();
        //                        }

        //                        ImGui::TreePop();
        //                    }

        //                    ImGui::TreePop();
        //                }

        //                if (level && ImGui::CollapsingHeader("Properties"))
        //                {
        //                    if (ImGui::TreeNode("Position"))
        //                    {
        //                        Vector3<float> pos = player->GetPosition();
        //                        ImGui::InputFloat("X", &pos.x);
        //                        ImGui::InputFloat("Y", &pos.y);
        //                        ImGui::InputFloat("Z", &pos.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("Position.TPReady"))
        //                    {
        //                        Vector3<float> pos = player->GetPosition(true);
        //                        ImGui::InputFloat("X", &pos.x);
        //                        ImGui::InputFloat("Y", &pos.y);
        //                        ImGui::InputFloat("Z", &pos.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("BlockPosition"))
        //                    {
        //                        Vector3<int> pos = player->GetBlockPosition();
        //                        ImGui::InputInt("X", &pos.x);
        //                        ImGui::InputInt("Y", &pos.y);
        //                        ImGui::InputInt("Z", &pos.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("LookingVector"))
        //                    {
        //                        Vector3<float> pos = player->getLookingVector();
        //                        ImGui::InputFloat("X", &pos.x);
        //                        ImGui::InputFloat("Y", &pos.y);
        //                        ImGui::InputFloat("Z", &pos.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("MoveVec"))
        //                    {
        //                        Vector2<int> pos = player->GetMoveVec();
        //                        ImGui::InputInt("X", &pos.x);
        //                        ImGui::InputInt("Y", &pos.y);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("StandingBlock"))
        //                    {
        //                        ImGui::Text("Use Debugger!");

        //                        ImGui::TreePop();
        //                    }
        //                }

        //                if (state && ImGui::CollapsingHeader("StateVectorComponent"))
        //                {
        //                    if (ImGui::TreeNode("Position"))
        //                    {
        //                        ImGui::InputFloat("X", &state->Position.x);
        //                        ImGui::InputFloat("Y", &state->Position.y);
        //                        ImGui::InputFloat("Z", &state->Position.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("PrevPosition"))
        //                    {
        //                        ImGui::InputFloat("X", &state->PrevPosition.x);
        //                        ImGui::InputFloat("Y", &state->PrevPosition.y);
        //                        ImGui::InputFloat("Z", &state->PrevPosition.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("r_Velocity"))
        //                    {
        //                        ImGui::InputFloat("X", &state->r_Velocity.x);
        //                        ImGui::InputFloat("Y", &state->r_Velocity.y);
        //                        ImGui::InputFloat("Z", &state->r_Velocity.z);

        //                        ImGui::TreePop();
        //                    }
        //                }

        //                if (movement && ImGui::CollapsingHeader("MovementInterpolatorComponent"))
        //                {
        //                    if (ImGui::TreeNode("Rotations"))
        //                    {
        //                        ImGui::InputFloat("X", &movement->Rotations.x);
        //                        ImGui::InputFloat("Y", &movement->Rotations.y);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("PrevRotations"))
        //                    {
        //                        ImGui::InputFloat("X", &movement->PrevRotations.x);
        //                        ImGui::InputFloat("Y", &movement->PrevRotations.y);

        //                        ImGui::TreePop();
        //                    }
        //                }

        //                if (shape && ImGui::CollapsingHeader("AABBShapeComponent"))
        //                {
        //                    if (ImGui::TreeNode("r_Pos_Lower"))
        //                    {
        //                        ImGui::InputFloat("X", &shape->r_Pos_Lower.x);
        //                        ImGui::InputFloat("Y", &shape->r_Pos_Lower.y);
        //                        ImGui::InputFloat("Z", &shape->r_Pos_Lower.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("r_Pos_Upper"))
        //                    {
        //                        ImGui::InputFloat("X", &shape->r_Pos_Upper.x);
        //                        ImGui::InputFloat("Y", &shape->r_Pos_Upper.y);
        //                        ImGui::InputFloat("Z", &shape->r_Pos_Upper.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("r_Hitbox"))
        //                    {
        //                        ImGui::InputFloat("X", &shape->r_Hitbox.x);
        //                        ImGui::InputFloat("Y", &shape->r_Hitbox.y);

        //                        ImGui::TreePop();
        //                    }
        //                }

        //                if (level && ImGui::CollapsingHeader("Level"))
        //                {
        //                    ImGui::InputInt("BlockFace", &level->BlockFace);
        //                    ImGui::InputInt("HitType", &level->HitType);

        //                    int seed = level->GetSeed();
        //                    ImGui::InputInt("WorldSeed", &seed);

        //                    int time = level->GetTime();
        //                    ImGui::InputInt("WorldTime", &time);

        //                    if (ImGui::TreeNode("AbsoluteHitPos"))
        //                    {
        //                        ImGui::InputFloat("X", &level->AbsoluteHitPos.x);
        //                        ImGui::InputFloat("Y", &level->AbsoluteHitPos.y);
        //                        ImGui::InputFloat("Z", &level->AbsoluteHitPos.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("IBlockPos"))
        //                    {
        //                        ImGui::InputInt("X", &level->IBlockPos.x);
        //                        ImGui::InputInt("Y", &level->IBlockPos.y);
        //                        ImGui::InputInt("Z", &level->IBlockPos.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("Origin"))
        //                    {
        //                        ImGui::InputFloat("X", &level->Origin.x);
        //                        ImGui::InputFloat("Y", &level->Origin.y);
        //                        ImGui::InputFloat("Z", &level->Origin.z);

        //                        ImGui::TreePop();
        //                    }

        //                    if (ImGui::TreeNode("RelativeRayEnd"))
        //                    {
        //                        ImGui::InputFloat("X", &level->RelativeRayEnd.x);
        //                        ImGui::InputFloat("Y", &level->RelativeRayEnd.y);
        //                        ImGui::InputFloat("Z", &level->RelativeRayEnd.z);

        //                        ImGui::TreePop();
        //                    }
        //                }

        //                if (level && ImGui::CollapsingHeader("EntityContext"))
        //                {
        //                    EntityContext* entCtx = player->GetEntityContext();

        //                    ImGui::InputInt("EntityId.Id", &entCtx->entityId.id);

        //                    /*std::stringstream ss;
        //                    ss << "0x" << std::hex << entCtx->registry;

        //                    std::string str = ss.str();*/

        //                    std::string str = "Use Debugger!";

        //                    ImGui::InputText("RegistryAddr", &str[0], str.size());
        //                }

        //                ImGui::EndTabItem();
        //            }
        //        }

        //        if (ImGui::BeginTabItem("ClientInstance"))
        //        {
        //            ClientInstance* instance = Game::GetInstance();

        //            ImGui::InputFloat("FovX", instance->getFovX());
        //            ImGui::InputFloat("FovY", instance->getFovY());

        //            if (instance->getGuiData() && ImGui::CollapsingHeader("GuiData"))
        //            {
        //                GuiData* data = instance->getGuiData();

        //                ImGui::InputFloat("GuiScale", &data->GuiScale);

        //                if (ImGui::TreeNode("MousePos"))
        //                {
        //                    int realFlrX = data->MousePos.x, realFlrY = data->MousePos.x;
        //                    ImGui::InputInt("X", &realFlrX);
        //                    ImGui::InputInt("Y", &realFlrY);

        //                    ImGui::TreePop();
        //                }

        //                if (ImGui::TreeNode("ScaledResolution"))
        //                {
        //                    ImGui::InputFloat("X", &data->ScaledResolution.x);
        //                    ImGui::InputFloat("Y", &data->ScaledResolution.y);

        //                    ImGui::TreePop();
        //                }

        //                if (ImGui::TreeNode("WindowResolution"))
        //                {
        //                    ImGui::InputFloat("X", &data->WindowResolution.x);
        //                    ImGui::InputFloat("Y", &data->WindowResolution.y);

        //                    ImGui::TreePop();
        //                }

        //                if (ImGui::TreeNode("WindowResolution2"))
        //                {
        //                    ImGui::InputFloat("X", &data->WindowResolution2.x);
        //                    ImGui::InputFloat("Y", &data->WindowResolution2.y);

        //                    ImGui::TreePop();
        //                }
        //            }

        //            if (instance->getLevelRender() && ImGui::CollapsingHeader("LevelRender"))
        //            {
        //                LevelRender* levelrndr = instance->getLevelRender();

        //                if (ImGui::TreeNode("Origin"))
        //                {
        //                    Vector3<float> origin = levelrndr->getOrigin();
        //                    ImGui::InputFloat("X", &origin.x);
        //                    ImGui::InputFloat("Y", &origin.y);
        //                    ImGui::InputFloat("Z", &origin.z);

        //                    ImGui::TreePop();
        //                }
        //            }

        //            if (instance->mcGame && ImGui::CollapsingHeader("MinecraftGame"))
        //            {
        //                bool canusemovekeys = instance->mcGame->canUseMoveKeys();
        //                ImGui::Checkbox("canUseMoveKeys", &canusemovekeys);
        //            }

        //            if (instance->getMinecraft() && ImGui::CollapsingHeader("Minecraft"))
        //            {
        //                Minecraft* mc = instance->getMinecraft();

        //                ImGui::InputFloat("timer", mc->timer);
        //                ImGui::InputFloat("renderTimer", mc->renderTimer);
        //            }

        //            ImGui::EndTabItem();
        //        }

        //        /*if (ImGui::BeginTabItem("Template Tab"))
        //        {
        //            if (ImGui::CollapsingHeader("Template Header"))
        //            {
        //                int tmp = 0;
        //                ImGui::InputInt("Template Int", &tmp);
        //            }

        //            ImGui::EndTabItem();
        //        }*/

        //        ImGui::EndTabBar();

        //        ImGui::End();
        //    }

        //    if (ImGui::Begin("Debugging Utils"))
        //    {
        //        ImGui::Checkbox("AllInspect", Game::GetInspecter()->GetAllInspect());
        //        ImGui::Checkbox("FocusInspect", Game::GetInspecter()->GetFocusInspect());

        //        ImGui::End();
        //    }
        //}
    }
};