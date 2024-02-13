#pragma once

class Killaura : public Module
{
public:
    Killaura(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Aura", "Combat", "Hit entities around you", keybind, enabled)
    {
        addEnum("Mode", "How many entities should be attacked", { "Multi", "Single"}, &switchMode);
        addSlider("Range", "The distance of attacking", &range, 3, 10);
        addSlider("APS", "How many times you attack in a second", &APS, 1, 30);
        addBool("Rotations", "Rotate Serversidedly", &rotations);

        ingameOnly = true;
        IngameOnly();
    }

    struct sortEntities 
    {
        bool operator()(Player* lhs, Player* rhs) 
        {
            return (lhs->GetPosition().distance(Game::GetLocalPlayer()->GetPosition()) < (rhs->GetPosition().distance(Game::GetLocalPlayer()->GetPosition())));
        }
    };

	void findEntity(Player* act) 
    {
		if (!act) return;
		if (act == Game::GetLocalPlayer()) return;
        if (getModuleByName("AntiBot")->isEnabled() && act->isBot()) return;
        if (act->IsBadPtr()) return;

		float distance = act->GetPosition().distance(Game::GetLocalPlayer()->GetPosition());
        if (distance > range) return;
		if (distance <= range) 
        {
			Game::TargetLists::auraList.push_back(act);
			sort(Game::TargetLists::auraList.begin(), Game::TargetLists::auraList.end(), sortEntities());
		}
	}

    int switchMode = 0;
    float range = 4;
    float APS = 10;
    bool rotations = true;

    void onEvent(UpdateEvent* event) override 
    {
        auto player = Game::GetLocalPlayer();
        if (!player) 
        {
            return;
        }

        Game::TargetLists::auraList.clear();
        auto callback = [this](Player* act) { findEntity(act); };
        getEntities(callback);

        GameMode* gm = player->getGameMode();

        if (!gm)
            return;

        if (!Game::TargetLists::auraList.empty())
        {
            Game::Iris::ShouldBlock = true;

            if (TimeUtil::hasTimeElapsed("kaTimer", 1000 / APS, true))
            {
                switch (switchMode)
                {
                case 1:
                    gm->attack(Game::TargetLists::auraList[0]);
                    break;
                case 0:
                    for (auto e : Game::TargetLists::auraList)
                    {
                        gm->attack(e);
                    }
                    break;
                }
                player->swing();
            }
        }
        else 
        {
            Game::Iris::ShouldBlock = false;
        }
    }

    void onEvent(PacketSendingEvent* event) override
    {
        if (!Game::GetLocalPlayer() ||!Game::GetInstance()->getPacketSender() || !rotations || Game::TargetLists::auraList.empty())
        {
            return;
        }

        if (event->Packet->instanceOf<PlayerAuthInputPacket>())
        {
            PlayerAuthInputPacket* pkt = reinterpret_cast<PlayerAuthInputPacket*>(event->Packet);
            Vector2 angle = CalcAngle(Game::GetLocalPlayer()->GetPosition(), Game::TargetLists::auraList[0]->GetPosition());

            pkt->yaw = angle.y;
            pkt->yawUnused = angle.y;
            pkt->pitch = angle.x;
        }

        if (event->Packet->instanceOf<MovePlayerPacket>())
        {
            MovePlayerPacket* pkt = reinterpret_cast<MovePlayerPacket*>(event->Packet);
            Vector2 angle = CalcAngle(Game::GetLocalPlayer()->GetPosition(), Game::TargetLists::auraList[0]->GetPosition());

            pkt->yaw = angle.y;
            pkt->headYaw = angle.y;
            pkt->pitch = angle.x;
        }
    }

    void onEnabled() 
    {
        Game::TargetLists::auraList.clear();
    }

    void onDisabled()
    {
        Game::Iris::ShouldBlock = false;
        Game::TargetLists::auraList.clear();
    }

    const static Vector2<float> CalcAngle(Vector3<float> ths, Vector3<float> dst)
    {
        Vector3 diff = dst.submissive(ths);

        diff.y = diff.y / diff.magnitude();
        Vector2<float> angles;
        angles.x = asinf(diff.y) * -DEG_RAD;
        angles.y = (float)-atan2f(diff.x, diff.z) * DEG_RAD;

        return angles;
    }
};