#include "types.hpp"

int is_mate_score(const Score score)
{
	int result = 0;

	if (score > VALUE_MATE_IN_PLY) { result = VALUE_MATE - score; }
	else if (score < VALUE_MATED_IN_PLY) { result = -VALUE_MATE - score; }
	if (result % 2 != 0) { result++; }

	return result / 2;
}

bool NonPawnMaterial(const chess::Board& Board, const chess::Color color)
{
	const uint64_t Queens = Board.pieces(chess::PieceType::QUEEN, color).getBits();
	const uint64_t Rooks = Board.pieces(chess::PieceType::ROOK, color).getBits();
	const uint64_t Bishops = Board.pieces(chess::PieceType::BISHOP, color).getBits();
	const uint64_t Knights = Board.pieces(chess::PieceType::KNIGHT, color).getBits();
	const uint64_t NonPawnMaterials = Queens | Rooks | Bishops | Knights;
	return NonPawnMaterials;
}
