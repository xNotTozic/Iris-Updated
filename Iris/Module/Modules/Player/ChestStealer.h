#pragma once

class ChestStealer : public Module
{
public:
    ChestStealer(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("ChestStealer", "Player", "Steal items out of chests", keybind, enabled)
    {
        addSlider("SPS", "How many items are moved a second", &SPS, 1, 60);
        addBool("AutoClose", "Automatically close the container", &close);
    }

    float SPS = 20;
    bool close = false;

    int item = 0;
    int maxItem = 56;

    bool inChest = false;

    void onEvent(LayerUpdateEvent* event) override
    {
        if (UILayer::Is(event->GuiLayer, {
                UILayer::Ingame_LargeChestScreen,
                UILayer::Ingame_SmallChestScreen,
                UILayer::Ingame_ShulkerBoxScreen,
                UILayer::Ingame_BarrelScreen,
            }))
        {
            inChest = true;

            if (UILayer::Is(event->GuiLayer, UILayer::Ingame_LargeChestScreen))
            {
                maxItem = 54;
            }

            if (UILayer::Is(event->GuiLayer, {
                    UILayer::Ingame_SmallChestScreen,
                    UILayer::Ingame_ShulkerBoxScreen,
                    UILayer::Ingame_BarrelScreen
                }))
            {
                maxItem = 27;
            }
        }

        if (UILayer::Is(event->GuiLayer, {
                UILayer::Ingame_InventoryScreen,
                UILayer::Ingame_CanMoveScreen
            }))
        {
            inChest = false;
        }
    }

    void onEvent(ContainerTickEvent* event) override
    {
        if (getModuleByName("ChestDumper")->isEnabled() && Game::Core::Keymap[Keyboard::R])
            return; // dumping items

        if (!inChest)
            return;

        if (TimeUtil::hasTimeElapsed("Cs", 500, false))
            item = 0;

        ContainerScreenController* controller = event->Controller;

        if (!controller)
            return;

        if (SPS == 60)
        {
            for (int i = 0; i < 56; ++i)
            {
                controller->shiftClickItems(Containers::Container, i);
            }

            if (close)
                controller->closeContainer();

            return;
        }

        if (TimeUtil::hasTimeElapsed("Cs", 1000 / SPS, true))
        {
            controller->shiftClickItems(Containers::Container, item);

            if (item == maxItem)
            {
                item = -1;

                if (close)
                    controller->closeContainer();
            }

            item++;
        }
    }
};