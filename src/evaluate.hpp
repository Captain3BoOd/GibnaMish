#pragma once
#ifndef _EVALUATE_HPP_
#define _EVALUATE_HPP_

#include "types.hpp"
namespace chess {
	class Board;
}

Score evaluate(const chess::Board& Board);

#endif // !_EVALUATE_HPP_