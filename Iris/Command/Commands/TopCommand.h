#pragma once

class TopCommand : public Command
{
public:

    TopCommand() : Command("top", "Teleport to the top block above you", {})
    {}

	bool execute(std::vector<std::string> cmd) override
	{
		BlockSource* blockSrc = Game::GetInstance()->getBlockSource();
		Player* lp = Game::GetLocalPlayer();

		bool groundAbove = false;
		Vector3<int> blockPos;

		for (int y = 0; y < 256 - lp->GetPosition().y; ++y)
		{
			if (blockSrc->getBlock(Vector3<int>(lp->GetPosition().x, lp->GetPosition().y + y, lp->GetPosition().z))->GetMaterialType() != MaterialType::Air)
			{
				groundAbove = true;
				blockPos = Vector3<int>(lp->GetPosition().x, lp->GetPosition().y + y, lp->GetPosition().z);
				break;
			}
		}

		if (groundAbove)
		{
			for (int y = 0; y < 256 - blockPos.y; ++y)
			{
				if ((blockSrc->getBlock(Vector3<int>(blockPos.x, blockPos.y + y, blockPos.z))->GetMaterialType() == MaterialType::Air) && (blockSrc->getBlock(Vector3<int>(blockPos.x, blockPos.y + y + 1, blockPos.z))->GetMaterialType() == MaterialType::Air))
				{
					lp->TeleportTo(Vector3<float>(blockPos.x, blockPos.y + y + 1, blockPos.z));
					ChatUtil::sendMessage(combine("Wooosh!"));
					return true;
				}
			}
		}
		else
		{
			ChatUtil::sendMessage(combine("No free spaces detected"));
		}

		return false;
	}
};
