#pragma once
#ifndef _GLOBAL_HPP_
#define _GLOBAL_HPP_

#include <cstdint>
#include <corecrt.h>

using Score = int32_t;
using Depth = int32_t;

inline constexpr int lmpM[4] = { 0, 8, 12, 24 };

enum : Score
{
	MAX_DEPTH = 100,
	MAX_PLY = 120,
	VALUE_MATE = 32000,
	VALUE_INFINITE = 32001,
	VALUE_NONE = 32002,

	VALUE_MATE_IN_PLY = VALUE_MATE - MAX_PLY,
	VALUE_MATED_IN_PLY = -VALUE_MATE_IN_PLY,

	VALUE_TB_WIN = VALUE_MATE_IN_PLY,
	VALUE_TB_LOSS = -VALUE_TB_WIN,
	VALUE_TB_WIN_IN_MAX_PLY = VALUE_TB_WIN - MAX_PLY,
	VALUE_TB_LOSS_IN_MAX_PLY = -VALUE_TB_WIN_IN_MAX_PLY
};

struct Limits
{
	time_t time;
	uint64_t nodes = 0;
	Depth depth = MAX_PLY - 1;
	bool infinite = false;
};

#endif // !_GLOBAL_HPP_