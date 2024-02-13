template <typename T>
struct Vector4
{
	union
	{
		struct
		{
			T x, y, z, w;
		};
		T arr[4];
	};

	Vector4(T x = 0, T y = 0, T z = 0, T w = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	};

	Vector4(Vector2<float> position, Vector2<float> size)
	{
		this->x = position.x;
		this->y = position.x + size.x;
		this->z = position.y;
		this->w = position.y + size.y;
	};

	__forceinline Vector4<T> lerp(Vector4<T> target, float pct) {
		return Vector4<T>((this->x + (target.x - this->x) * pct), (this->y + (target.y - this->y) * pct), (this->z + (target.z - this->z) * pct), (this->w + (target.w - this->w) * pct));
	}

	__forceinline Vector4<T> scale(float amount) {
		return Vector4<T>(this->x + amount, this->y + amount, this->z - amount, this->w - amount);
	}

	__forceinline Vector4<T> getCenter() const {
		float centerX = (x + z) / 2.0f;
		float centerY = (y + w) / 2.0f;
		return Vector4<T>(centerX, centerY, centerX, centerY);
	}

	__forceinline Vector4<T> scaleToCenter(float scaleFactor) {
		float centerX = (this->x + this->z) / 2.0f;
		float centerY = (this->y + this->w) / 2.0f;

		float width = this->getWidth();
		float height = this->getHeight();

		float scaledWidth = width * scaleFactor;
		float scaledHeight = height * scaleFactor;

		float newX = centerX - scaledWidth / 2.0f;
		float newY = centerY - scaledHeight / 2.0f;
		float newZ = newX + scaledWidth;
		float newW = newY + scaledHeight;

		return Vector4<T>(newX, newY, newZ, newW);
	}

	Vector2<T> xy() const
	{
		return Vector2<T>(x, y);
	}

	Vector2<T> xz() const
	{
		return Vector2<T>(x, z);
	}

	__forceinline float getWidth() {
		return abs(this->z - this->x);
	}

	__forceinline float getHeight() {
		return abs(this->w - this->y);
	}

	__forceinline Vector4<T> scaleToPoint(const Vector4<T>& point, float amount) {
		return Vector4<T>(point.x + (this->x - point.x) * amount, point.y + (this->y - point.y) * amount,
			point.z + (this->z - point.z) * amount, point.w + (this->w - point.w) * amount);
	}

	bool operator == (Vector4 v)
	{
		return v.x == x && v.y == y && v.z == z && v.w == w;
	};

	bool operator != (Vector4 v)
	{
		return v.x != x || v.y != y || v.z != z || v.w != w;
	};

	bool operator * (float v)
	{
		return { x * v , y * v , z * v , w * v };
	};


};
