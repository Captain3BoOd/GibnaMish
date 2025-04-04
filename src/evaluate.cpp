#include "evaluate.hpp"
#include "piecesbouns.hpp"

#define CHESS_NO_EXCEPTIONS
#include "chess.hpp"
#undef CHESS_NO_EXCEPTIONS

Score evaluate(const chess::Board& Board)
{
	int phase = 0;
	Score eval_mg = Board.psqt_mg_;
	Score eval_eg = Board.psqt_eg_;

	const chess::Bitboard wpawns_board = Board.pieces(chess::PieceType::PAWN, chess::Color::WHITE);
	const chess::Bitboard bpawns_board = Board.pieces(chess::PieceType::PAWN, chess::Color::BLACK);

	const int wpawns = wpawns_board.count();
	const int wknights = Board.pieces(chess::PieceType::KNIGHT, chess::Color::WHITE).count();
	const int wbishops = Board.pieces(chess::PieceType::BISHOP, chess::Color::WHITE).count();
	const int wrooks = Board.pieces(chess::PieceType::ROOK, chess::Color::WHITE).count();
	const int wqueens = Board.pieces(chess::PieceType::QUEEN, chess::Color::WHITE).count();

	const int bpawns = bpawns_board.count();
	const int bknights = Board.pieces(chess::PieceType::KNIGHT, chess::Color::BLACK).count();
	const int bbishops = Board.pieces(chess::PieceType::BISHOP, chess::Color::BLACK).count();
	const int brooks = Board.pieces(chess::PieceType::ROOK, chess::Color::BLACK).count();
	const int bqueens = Board.pieces(chess::PieceType::QUEEN, chess::Color::BLACK).count();

	phase += wknights + bknights;
	phase += wbishops + bbishops;
	phase += (wrooks + brooks) * 2;
	phase += (wqueens + bqueens) * 4;

	eval_mg +=
		((wpawns - bpawns) * PicesValues[MG][uint8_t(chess::PieceType::PAWN)]) +
		((wknights - bknights) * PicesValues[MG][uint8_t(chess::PieceType::KNIGHT)]) +
		((wbishops - bbishops) * PicesValues[MG][uint8_t(chess::PieceType::BISHOP)]) +
		((wrooks - brooks) * PicesValues[MG][uint8_t(chess::PieceType::ROOK)]) +
		((wqueens - bqueens) * PicesValues[MG][uint8_t(chess::PieceType::QUEEN)]);

	eval_eg +=
		((wpawns - bpawns) * PicesValues[EG][uint8_t(chess::PieceType::PAWN)]) +
		((wknights - bknights) * PicesValues[EG][uint8_t(chess::PieceType::KNIGHT)]) +
		((wbishops - bbishops) * PicesValues[EG][uint8_t(chess::PieceType::BISHOP)]) +
		((wrooks - brooks) * PicesValues[EG][uint8_t(chess::PieceType::ROOK)]) +
		((wqueens - bqueens) * PicesValues[EG][uint8_t(chess::PieceType::QUEEN)]);

	if (wpawns_board & uint8_t(chess::Rank::RANK_7))
	{
		eval_mg += 20;
		eval_eg += 30;
	}
	if (bpawns_board & uint8_t(chess::Rank::RANK_2))
	{
		eval_mg -= 20;
		eval_eg -= 30;
	}

	phase = 24 - phase;
	phase = (phase * 256 + (24 / 2)) / 24;

	return (((eval_mg * (256 - phase)) + (eval_eg * phase)) / 256) * (Board.sideToMove() * -2 + 1);
}
