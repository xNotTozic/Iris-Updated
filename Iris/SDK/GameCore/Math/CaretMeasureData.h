#pragma once

struct CaretMeasureData
{
	int Position;
	bool isSingleline;// false|insert

	CaretMeasureData()
	{
		CaretMeasureData(0xFFFFFFFF, true);
	};

	CaretMeasureData(int position, bool singlelines)
	{
		this->Position = position;
		this->isSingleline = singlelines;
	};
};