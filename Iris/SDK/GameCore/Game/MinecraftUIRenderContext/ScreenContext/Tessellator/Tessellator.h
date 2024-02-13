#pragma once

#include "VertextFormat.h"
#include "MaterialPtr.h"

class ScreenContext;

class Tessellator
{
private:
	char pad_0000[0x184]; // Updated to 1.20.51
	Vector3<float> transformOffset; // 0x184
	// 0x128 old transfromOffset offset

public:
	void addPostTransformOffset(int x, int y, int z)
	{
		addPostTransformOffset((float)x, (float)y, (float)z);
	}
	void addPostTransformOffset(float x, float y, float z)
	{
		this->transformOffset = this->transformOffset + Vector3<float>(x, y, z);
	};

	inline void begin(VertextFormat format, int reservedVerticies = 0)
	{
		using tess_begin_t = void(__fastcall*)(Tessellator*, VertextFormat, bool);
		static tess_begin_t tess_begin = reinterpret_cast<tess_begin_t>(findSig("48 89 5C 24 ? 56 48 83 EC ? 80 B9 ? ? ? ? ? 45 0F B6")); // Updated to 1.20.51
		// 48 89 5c 24 ? 55 48 83 ec ? 80 b9 ? ? ? ? ? 45 0f b6 d1 in 1.20.0.1
		tess_begin(this, format, reservedVerticies);
	}
	inline void vertex(float x, float y, float z)
	{
		using tess_vertex_t = void(__fastcall*)(Tessellator*, float, float, float);
		static tess_vertex_t tess_vertex = reinterpret_cast<tess_vertex_t>(findSig("40 57 48 81 EC ? ? ? ? 0F 29 7C ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 8B 81")); // Updated to 1.20.51
		// 40 57 48 81 ec ? ? ? ? 0f 29 7C 24 in 1.20.0.1
		tess_vertex(this, x, y, z);
	}
	inline void color(float r, float g, float b, float a)
	{
		using tess_color_t = void(__fastcall*)(Tessellator*, float, float, float, float);
		static tess_color_t tess_color = reinterpret_cast<tess_color_t>(findSig("80 b9 ? ? ? ? ? 4c 8b c1 75")); // Updated to 1.20.51
		// The same sig in 1.20.0.1
		tess_color(this, r, g, b, a);
	}
	inline void setRotation(float angle, Vector3<float> pivot)
	{
		using tess_setRotation_t = void(__fastcall*)(Tessellator*, float, Vector3<float>);
		static tess_setRotation_t tess_setRotation = reinterpret_cast<tess_setRotation_t>(findSig("48 89 5C 24 ? 57 48 81 EC ? ? ? ? F3 41 0F 10")); // Updated to 1.20.51
		// 40 53 48 81 ec ? ? ? ? f3 41 0f 10 ? in 1.20.0.1
		tess_setRotation(this, angle, pivot);
	}
	inline void resetTransform(bool a1)
	{
		using tess_resetTransform_t = void(__fastcall*)(Tessellator*, bool);
		static tess_resetTransform_t tess_resetTransform = reinterpret_cast<tess_resetTransform_t>(findSig("40 53 48 81 ec ? ? ? ? c6 81 ? ? ? ? ? 48 8b d9 84 d2")); // Updated to 1.20.51
		// The same sig in 1.20.0.1
		tess_resetTransform(this, a1);
	}
	inline void renderMeshImmediately(ScreenContext* ctx, MaterialPtr* material)
	{
		using meshHelper_renderImm_t = void(__fastcall*)(ScreenContext*, Tessellator*, MaterialPtr*);
		// Updated to 1.20.51
		static meshHelper_renderImm_t meshHelper_renderImm = reinterpret_cast<meshHelper_renderImm_t>(findSig("48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 49 8B F8 48 8B DA 48 8B F1 80 BA ? ? ? ? ? 0F 85 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 44 24 ? 48 C7 44 24 ? ? ? ? ? 0F 28 44 24 ? 66 0F 7F 44 24 ?")); // Updated to 1.20.51
		// 40 55 53 56 57 41 56 48 8d ac 24 ? ? ? ? 48 81 ec ? ? ? ? 49 8b f0 in 1.20.0.1 
		meshHelper_renderImm(ctx, this, material);
	}
};
