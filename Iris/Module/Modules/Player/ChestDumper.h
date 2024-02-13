#pragma once

class ChestDumper : public Module
{
public:
    ChestDumper(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("ChestDumper", "Player", "Dumps inventory when you hold R", keybind, enabled)
    {
        addSlider("SPS", "How many items are moved a second", &SPS, 1, 60);
    }

    float SPS = 20;

    int item = 0;
    const int maxItem = 27;

    void onEvent(ContainerTickEvent* event) override
    {
        if (Game::Core::Keymap[Keyboard::R])
        {
            if (TimeUtil::hasTimeElapsed("Cd", 500, false))
                item = 0;

            ContainerScreenController* controller = event->Controller;

            if (!controller)
                return;

            if (SPS == 60)
            {
                for (int i = 0; i < 27; ++i)
                {
                    controller->shiftClickItems(Containers::Inventory, i);
                }

                return;
            }

            if (TimeUtil::hasTimeElapsed("Cd", 1000 / SPS, true))
            {
                controller->shiftClickItems(Containers::Inventory, item);

                if (item == maxItem)
                    item = -1;

                item++;
            }
        }
        else
        {
            item = -1;
        }
    }
};