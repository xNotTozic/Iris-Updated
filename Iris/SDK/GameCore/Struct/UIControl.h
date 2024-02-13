#pragma once

class UIControl
{
private:
	char pad_0x0000[0x18]; //0x0000
public:
	char ControlName[16]; //0xBF6DE9C0 
private:
	char pad_0x0028[0x10]; //0x0028
public:
	Vector2<float> Offset; //0x0038 
	Vector2<float> Size; //0x0040 
private:
	char pad_0x0048[0x10]; //0x0048
public:
	float Opacity; //0x0058 
private:
	char pad_0x005C[0x1C]; //0x005C
public:
	Vector2<float> Position; //0x0078 
private:
	char pad_0x0080[0x10]; //0x0080
	UIControl* ChildrenRef; //0x0090 
public:
	UIControl* Parent;

public:
	UIControl* GetChild(int index)
	{
		return ChildrenRef + (0x150 * index);
	}

	const char* GetName() // bro this is so ANNOYING
	{
		/*bool extraChar = false;

		if (ControlName[0] != '\0')
		{
			for (int i = 0; i < 15; ++i)
			{
				if (ControlName[i] == '\0')
				{
					if (ControlName[i + 1] != '\0')
					{
						extraChar = true;
						break;
					}
				}
			}

			uintptr_t dyanmicStrPtr = *reinterpret_cast<uintptr_t*>(ControlName);

			if (extraChar)
			{
				return reinterpret_cast<const char*>(dyanmicStrPtr);
			}
		}*/

		return ControlName;
	}

	bool CmpName(const char* str)
	{
		const char* src = GetName();
		return strcmp(str, src) == 0;
	}
};

//class N00000000
//{
//public:
//private:
//	char pad_0x0000[0x18]; //0x0000
//public:
//	char ControlName[16]; //0xBF6DE9C0 
//private:
//	char pad_0x0028[0x10]; //0x0028
//public:
//	Vector2 Offset; //0x0038 
//	Vector2 Size; //0x0040 
//private:
//	char pad_0x0048[0x10]; //0x0048
//public:
//	float Opacity; //0x0058 
//private:
//	char pad_0x005C[0x1C]; //0x005C
//public:
//	Vector2 Position; //0x0078 
//private:
//	char pad_0x0080[0x10]; //0x0080
//public:
//	N0000010F* ChildrenRef; //0x0090 
//	N00000323* Parent; //0x0098 
//private:
//	char pad_0x00A0[0x7A0]; //0x00A0
//
//};