#pragma once
class MaterialPtr;
class LevelRendererPlayer
{
public:
	BUILD_ACCESS(this, MaterialPtr*, shadowBack, 0x238);
	BUILD_ACCESS(this, MaterialPtr*, shadowFront, 0x248);
	BUILD_ACCESS(this, MaterialPtr*, shadowOverlay, 0x258);
	BUILD_ACCESS(this, MaterialPtr*, stars, 0x268);
	BUILD_ACCESS(this, MaterialPtr*, skyplane, 0x278);
	BUILD_ACCESS(this, MaterialPtr*, sunMoon, 0x288);
	BUILD_ACCESS(this, MaterialPtr*, endSky, 0x298);
	BUILD_ACCESS(this, MaterialPtr*, clouds, 0x2A8);
	BUILD_ACCESS(this, MaterialPtr*, wireframe, 0x2B8);
	BUILD_ACCESS(this, MaterialPtr*, cubemap, 0x2C8);

	// Oeigin
	// 0x514 in 1.20.0.1
	BUILD_ACCESS(this, Vector3<float>, cameraPos, 0x5E4); // Updated to 1.20.51
};

class LevelRender {
public:
	LevelRendererPlayer* getLevelRendererPlayer()
	{
		return *reinterpret_cast<LevelRendererPlayer**>((uintptr_t)(this) + 0x308); // Updated to 1.20.51
		//return *reinterpret_cast<LevelRendererPlayer**>((uintptr_t)(this) + 0x2F8); 1.20.0.1
	};

	Vector3<float> getOrigin()
	{
		return getLevelRendererPlayer()->cameraPos;
	};
};