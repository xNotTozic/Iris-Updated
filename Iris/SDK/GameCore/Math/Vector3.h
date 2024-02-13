#pragma once

static constexpr float DEG_RAD = 180.0f / 3.1415927f;

template <typename T>
struct Vector3
{
	union
	{
		struct
		{
			T x, y, z;
		};
		T arr[3];
	};

	static Vector3<T> Zero;

	Vector3(T x = 0, T y = 0, T z = 0)
	{
		this->x = x; this->y = y; this->z = z;
	};

	bool empty()
	{
		return x == 0 && y == 0 && z == 0;
	}

	Vector3<T> Normalize() const {
		T length = std::sqrt(x * x + y * y + z * z);
		if (length != 0) {
			return Vector3<T>(x / length, y / length, z / length);
		}
		else {
			return Vector3<T>(0, 0, 0);
		}
	}

	Vector3<T> floor() const
	{
		return Vector3<T>(std::floor(x), std::floor(y), std::floor(z));
	}

	Vector3<T> Add(float ammount) const
	{
		return Vector3<T>(this->x + ammount, this->y + ammount, this->z + ammount);
	}

	Vector3<T> add(Vector3<T> o) const {
		return Vector3<T>(x + o.x, y + o.y, z + o.z);
	}

	bool operator == (Vector3 v)
	{
		return v.x == x && v.y == y && v.z == z;
	};

	bool operator != (Vector3 v)
	{
		return v.x != x || v.y != y || v.z != z;
	};

	Vector3 operator *= (Vector3 v)
	{
		return Vector3(v.x * x, v.y * y, v.z * z);
	};

	Vector3 operator + (Vector3 v)
	{
		return Vector3(v.x + x, v.y + y, v.z + z);
	};

	Vector3 operator + (Vector2<T> v)
	{
		return Vector3(v.x + x, v.y + y, v.x + z);
	};

	Vector3 operator / (Vector3 v)
	{
		return Vector3(v.x / x, v.y / y, v.z / z);
	};

	Vector3 operator * (Vector3 v)
	{
		return Vector3(v.x * x, v.y * y, v.z * z);
	};

	Vector3<T> Div(float v)
	{
		return Vector3<T>(x / v, y / v, z / v);
	}

	Vector3<float> ToFloat()
	{
		return Vector3<float>((float)x, (float)y, (float)z);
	}

	Vector3<int> ToInt()
	{
		return Vector3<int>((int)x, (int)y, (int)z);
	}

	Vector3<T> Invert()
	{
		return Vector3<T>(-x, -y, -z);
	}

	Vector3 operator - (Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	};

	Vector3 operator * (float v)
	{
		return Vector3(v * x, v * y, v * z);
	};

	Vector3 submissive(const Vector3& o) const
	{
		return Vector3(x - o.x, y - o.y, z - o.z);
	}

	T squaredlen() const
	{
		return x * x + y * y;
	}

	T magnitude() const
	{
		return sqrtf(squaredlen());
	}

	T magnitudexy() const
	{
		return sqrtf(x * x + y * y);
	}

	Vector3<T> Project(const Vector3<T>& vector, const Vector3<T>& onto) {
		float scalar = (vector.dot(onto) / onto.magnitudeSquared());
		return onto * scalar;
	}

	T magnitudexz() const
	{
		return sqrtf(x * x + z * z);
	} // Totally not skidded

	Vector3 lerp(const Vector3& pos, T x1, T y1, T z1)
	{
		Vector3 This;
		This.x = x + x1 * (pos.x - x);
		This.y = y + y1 * (pos.y - y);
		This.z = z + z1 * (pos.z - z);
		return This;
	}

	T distance(Vector3 v)
	{
		T dX = x - v.x;
		T dY = y - v.y;
		T dZ = z - v.z;
		return std::sqrt(dX * dX + dY * dY + dZ * dZ);
	}
};