#pragma once

class ToCommand : public Command
{
public:

    ToCommand() : Command("to", "Teleport to something", { "t" })
    {}

    bool execute(std::vector<std::string> cmd) override // I'll actually put effort into this after I finish oresense commands
    {
        if (cmd.size() == 0)
            return false;

        //.to lifeboat <tile.ore>
        if (cmd[0] == "vanilla")
        {
            Vector3<float> nextTile = GetNextTile(cmd[1]);

            if (nextTile != Vector3<float>(0, 0, 0))
            {
                Game::GetLocalPlayer()->TeleportTo(nextTile);
                return true;
            }
            else
            {
                ChatUtil::sendMessage(combine(RED, "No tiles found"));
            }
        }

        //.to lifeboat <tile.ore>
        if (cmd[0] == "lifeboat")
        {
            Vector3<float> nextTile = GetNextTile(cmd[1]);

            if (nextTile != Vector3<float>(0, 0, 0))
            {
                lifeboatTpTarget = nextTile; // pass to lifeboat tick handler
                Game::GetInstance()->getMinecraft()->setTimerSpeed(60);
                return true;
            }
            else
            {
                ChatUtil::sendMessage(combine(RED, "No tiles found"));
            }
        }

        return false;
    }

    Vector3<float> GetNextTile(std::string tile, int radius = 32)
    {
        for (int x = -radius; x <= radius; ++x)
        {
            for (int y = -radius; y <= radius; ++y)
            {
                for (int z = -radius; z <= radius; ++z)
                {
                    Vector3<int> blockPos = Game::GetLocalPlayer()->GetPosition().ToInt() + Vector3<int>(x, y, z);

                    if (blockPos.y <= 3)
                        continue;

                    BlockSource* source = Game::GetInstance()->getBlockSource();

                    if (!source)
                        return false;

                    Block* block = source->getBlock(blockPos);

                    if (tile == block->GetTileName()->getText())
                    {
                        return blockPos.ToFloat();
                    }
                }
            }
        }

        return Vector3<float>(0, 0, 0);
    }
};