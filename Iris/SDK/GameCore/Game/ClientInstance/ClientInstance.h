#pragma once

#include "MinecraftGame.h"
#include "Minecraft.h"
#include "BlockSource/BlockSource.h"
#include "LevelRender.h"
#include "../../Struct/GLMatrix.h"

class ClientInstance
{
private:
	char pad_0x0000[0xA8]; //0x0000
public:
	MinecraftGame* mcGame; //0x00A8
private:
	char pad_0x00B0[0x250]; //0x00B0
public:
	GLMatrix Matrix1; //0x0300

public:
	Player* getLocalPlayer()
	{
		return CallVFunc<27, Player*>(this);
	}

	MoveInputHandler* getMoveInputHandler()
	{
		return *reinterpret_cast<MoveInputHandler**>((uintptr_t)this + 0xF8);
	}

	BlockSource* getBlockSource()
	{
		return CallVFunc<26, BlockSource*>(this);
	}

	LoopbackPacketSender* getPacketSender()
	{
		return *reinterpret_cast<LoopbackPacketSender**>((uintptr_t)this + 0xF0);
	}

	void grabCursor()
	{
		return CallVFunc<304, void>(this);
	}

	void releaseCursor()
	{
		return CallVFunc<305, void>(this);
	}

	void refocusCursor()
	{
		return CallVFunc<306, void>(this);
	}

	Minecraft* getMinecraft()
	{
		return *reinterpret_cast<Minecraft**>((uintptr_t)this + 0xD0);
	}

	GuiData* getGuiData()
	{
		return *reinterpret_cast<GuiData**>((uintptr_t)this + 0x510);
	}

	LevelRender* getLevelRender()
	{
		uintptr_t address = reinterpret_cast<uintptr_t>(this);
		return *reinterpret_cast<LevelRender**>(address + 0xE0);
	}

	float* getFovX()
	{
		return reinterpret_cast<float*>((uintptr_t)(this) + 0x6A0);
	};

	float* getFovY()
	{
		return reinterpret_cast<float*>((uintptr_t)(this) + 0x6B4);
	};

	Vector2<float> getFov()
	{
		return Vector2(*getFovX(), *getFovY());
	};

	GLMatrix* getMatrixCorrection()
	{
		GLMatrix toReturn = GLMatrix();

		for (int i = 0; i < 4; i++) {
			toReturn.matrix[i * 4 + 0] = Matrix1.matrix[0 + i];
			toReturn.matrix[i * 4 + 1] = Matrix1.matrix[4 + i];
			toReturn.matrix[i * 4 + 2] = Matrix1.matrix[8 + i];
			toReturn.matrix[i * 4 + 3] = Matrix1.matrix[12 + i];
		}

		return &toReturn;
	};

	__forceinline float transformx(const Vector3<float>& p)
	{
		auto matrix = getMatrixCorrection()->matrix;
		return p.x * matrix[0] + p.y * matrix[4] + p.z * matrix[8] + matrix[12];
	}

	__forceinline float transformy(const Vector3<float>& p)
	{
		auto matrix = getMatrixCorrection()->matrix;
		return p.x * matrix[1] + p.y * matrix[5] + p.z * matrix[9] + matrix[13];
	}

	__forceinline float transformz(const Vector3<float>& p)
	{
		auto matrix = getMatrixCorrection()->matrix;
		return p.x * matrix[2] + p.y * matrix[6] + p.z * matrix[10] + matrix[14];
	}

	inline bool WorldToScreen(Vector3<float> pos, Vector2<float>& screen)
	{ // pos = pos 2 w2s, screen = output screen coords
		if (!getGuiData()) {
			return false;
		}
		Vector2<float> displaySize = getGuiData()->WindowResolution2;
		LevelRender* lr = getLevelRender();
		Vector3<float> origin = lr->getOrigin();
		Vector2<float> fov = getFov();

		pos.x -= origin.x;
		pos.y -= origin.y;
		pos.z -= origin.z;

		float x = transformx(pos);
		float y = transformy(pos);
		float z = transformz(pos);

		if (z > 0) return false;

		float mX = (float)displaySize.x / 2.0F;
		float mY = (float)displaySize.y / 2.0F;

		screen.x = mX + (mX * x / -z * fov.x);
		screen.y = mY - (mY * y / -z * fov.y);

		return true;
	}
};