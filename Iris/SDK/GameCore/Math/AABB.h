#pragma once

template<typename T>
struct AABB
{
	union
	{
		struct {
			Vector3<T> lower, upper;
		};
		Vector3<T> arr[2]{};
	};

	AABB(Vector3<T> position, Vector3<T> size)
	{
		this->upper.x = position.x;
		this->lower.x = position.x + size.x;
		this->upper.y = position.y;
		this->lower.y = position.y + size.y;
		this->upper.z = position.z;
		this->lower.z = position.z + size.z;
	};
	
#pragma region Utils from BDS
	Vector3<float> getCenter()
	{
		Vector3<float> result;
		Vector3<float> point1 = this->lower;
		Vector3<float> point2 = this->upper;
		Vector3<float> diff = point1 - point2;
		Vector3<float> scaled = diff * 0.5f;
		Vector3<float> offset = point2 + scaled;
		result = offset;
		return result;
	}

	AABB<T> isValid()
	{
		if (*((float*)this + 3) < *(float*)this)
			return 0;
		if (*((float*)this + 4) >= *((float*)this + 1))
			return *((float*)this + 5) >= *((float*)this + 2);
		return 0;
	}
#pragma endregion
};