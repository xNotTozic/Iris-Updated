#pragma once

class TestCommand : public Command
{
public:
	TestCommand() : Command("test", "Debugging command for the developers", {})
	{}

	bool execute(std::vector<std::string> cmd) override
	{
		BlockSource* blockSrc = Game::GetInstance()->getBlockSource();
		Player* lp = Game::GetLocalPlayer();

		Block* block = blockSrc->getBlock(lp->try_get<AABBShapeComponent>()->r_Pos_Lower.ToInt() - Vector3<int>(0, 1, 0));

		ChatUtil::sendMessage(
			combine(
				GREEN,
				"TileID: ",
				block->GetTileName()->getText(),
				" \\ MaterialType: ",
				block->GetMaterialType()
			)
		);

		return false;
	}
};
