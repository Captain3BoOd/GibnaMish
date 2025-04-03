#pragma once
#ifndef _EVALUATE_HPP_
#define _EVALUATE_HPP_

#define CHESS_NO_EXCEPTIONS
#include "chesslib/chess.hpp"
#undef CHESS_NO_EXCEPTIONS

#include "types.hpp"

class Evaluate
{
public:
	static Score evaluate(const chess::Board&);
private:
	using MG_EG = std::pair<int, int>;
	using Indexes = std::vector<int>;
	using PieceType = chess::PieceType;
	using Color = chess::Color;

	static MG_EG Calc_adjustment(const chess::Board&);
};

#endif // !_EVALUATE_HPP_