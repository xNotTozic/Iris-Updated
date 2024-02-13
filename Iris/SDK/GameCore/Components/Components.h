#pragma once

struct RenderPositionComponent {
public:
	Vector3<float> renderPos;
};

struct RuntimeIDComponent {
public:
	int64_t runtimeID;
};

struct ActorHeadRotationComponent {
public:
	union {
		struct {
			float pitch;
			float yaw;
		};
		Vector2<float> rot;
	};
};

struct RenderRotationComponent {
public:
	Vector2<float> renderRot;
};
