#pragma once

class RootUIControl
{
public:
	std::string GetName()
	{
		const char* ptr = reinterpret_cast<const char*>(this);

		if (ptr == nullptr || reinterpret_cast<uintptr_t>(ptr) >= range_start)
			return std::string("UnknownLayer");

		std::string result;
		while (*ptr != '\0')
		{
			result += *ptr;
			ptr++;
		}
		return result;
	}
};