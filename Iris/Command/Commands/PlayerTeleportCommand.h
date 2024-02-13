#pragma once

class PlayerTeleportCommand : public Command
{
public:
    PlayerTeleportCommand() : Command("playertp", "Teleport to something without OP", { "playerteleport", "ptp" })
    {}

    std::vector<std::string> _args = {};
    Vector3<float> pos = Vector3<float>(0, 0, 0); // target pos

    void findEntity(Player* ent)
    {
        if (!ent) return;

        AABBShapeComponent* shape = ent->try_get<AABBShapeComponent>();
        if (!shape || IsBadReadPtr(shape, sizeof(AABBShapeComponent))) return;

        Vector3<float> entLower = shape->r_Pos_Lower;

        Vector3<float> entDims = { shape->r_Hitbox.x, shape->r_Hitbox.y, shape->r_Hitbox.x };

        if (entDims.x != 0.6f || entDims.y != 1.8f)
            return;

        if (strcmp(ent->getNameTag()->getText(), _args[1].c_str()) == 0)
        {
            pos = ent->GetPosition();
        }
    }

    bool execute(std::vector<std::string> cmd) override
    {
        if (cmd.size() != 2)
        {
            if (cmd.size() == 1 && strcmp(cmd[0].c_str(), "list") == 0)
            {
                ChatUtil::sendMessage(combine("vanilla, list, lifeboat"));
            }

            ChatUtil::sendMessage("Invalid argument format. Usage: .playertp <type> <username> - .playertp list");
            return false;
        }

        if (!Game::GetLocalPlayer())
            return false;

        Player* player = Game::GetLocalPlayer();

        _args = cmd;

        auto callback = [this](Player* act) { findEntity(act); };
        getEntities(callback);

        _args = {};

        if (pos == Vector3<float>(0, 0, 0))
        {
            ChatUtil::sendMessage(combine(RED, "Player not in render distance!"));
            return false;
        }

        if (strcmp(cmd[0].c_str(), "vanilla") == 0)
        {
            player->TeleportTo(pos);
            ChatUtil::sendMessage(combine("Teleported to ", GRAY, pos.x, ", ", pos.y, ", ", pos.z, RESET, "!"));
        }

        if (strcmp(cmd[0].c_str(), "lifeboat") == 0)
        {
            if (lifeboatTpTarget == Vector3<float>(0, 0, 0))
            {
                lifeboatTpTarget = pos; // handled by LifeboatActionTick.h in misc modules
                Game::GetInstance()->getMinecraft()->setTimerSpeed(60);
                getModuleByName("LifeboatTickAction")->setEnabled(true);

                ChatUtil::sendMessage(combine("Teleported to ", GRAY, pos.x, ", ", pos.y, ", ", pos.z, RESET, "!"));
            }
            else
            {
                ChatUtil::sendMessage(combine(RED, "Teleport already in progress!"));
            }
        }

        return true;
    }
};
