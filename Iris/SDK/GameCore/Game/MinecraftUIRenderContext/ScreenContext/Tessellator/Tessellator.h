#pragma once

#include "VertextFormat.h"
#include "MaterialPtr.h"

class ScreenContext;

class Tessellator 
{
private:
	char pad_0000[0x128];
	Vector3<float> transformOffset; // 0x128

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
		static tess_begin_t tess_begin = reinterpret_cast<tess_begin_t>(Addresses::Render::tess_Begin);
		tess_begin(this, format, reservedVerticies);
	}
	inline void vertex(float x, float y, float z) 
	{
		using tess_vertex_t = void(__fastcall*)(Tessellator*, float, float, float);
		static tess_vertex_t tess_vertex = reinterpret_cast<tess_vertex_t>(Addresses::Render::tess_Vertex);
		tess_vertex(this, x, y, z);
	}
	inline void color(float r, float g, float b, float a) 
	{
		using tess_color_t = void(__fastcall*)(Tessellator*, float, float, float, float);
		static tess_color_t tess_color = reinterpret_cast<tess_color_t>(findSig("80 b9 ? ? ? ? ? 4c 8b c1 75"));
		tess_color(this, r, g, b, a);
	}
	inline void setRotation(float angle, Vector3<float> pivot) 
	{
		using tess_setRotation_t = void(__fastcall*)(Tessellator*, float, Vector3<float>);
		static tess_setRotation_t tess_setRotation = reinterpret_cast<tess_setRotation_t>(findSig("40 53 48 81 ec ? ? ? ? f3 41 0f 10 ?"));
		tess_setRotation(this, angle, pivot);
	}
	inline void resetTransform(bool a1) 
	{
		using tess_resetTransform_t = void(__fastcall*)(Tessellator*, bool);
		static tess_resetTransform_t tess_resetTransform = reinterpret_cast<tess_resetTransform_t>(findSig("40 53 48 81 ec ? ? ? ? c6 81 ? ? ? ? ? 48 8b d9 84 d2"));
		tess_resetTransform(this, a1);
	}
	inline void renderMeshImmediately(ScreenContext* ctx, MaterialPtr* material) 
	{
		using meshHelper_renderImm_t = void(__fastcall*)(ScreenContext*, Tessellator*, MaterialPtr*);
		static meshHelper_renderImm_t meshHelper_renderImm = reinterpret_cast<meshHelper_renderImm_t>(Addresses::Render::renderMesh);
		meshHelper_renderImm(ctx, this, material);
	}
};
