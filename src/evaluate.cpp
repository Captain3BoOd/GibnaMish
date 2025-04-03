#include "evaluate.hpp"
#include "piecesbouns.hpp"

Score Evaluate::evaluate(const chess::Board& Board)
{
	using PHASE = piecesbouns::PHASE;
	using Punderlying = piecesbouns::Punderlying;

	int eval_eg = 0;
	int eval_mg = 0;
	int phase = 0;

	const chess::Bitboard wpawns_board = Board.pieces(chess::PieceType::PAWN, Color::WHITE);
	const chess::Bitboard bpawns_board = Board.pieces(chess::PieceType::PAWN, Color::BLACK);

	const int wpawns = wpawns_board.count();
	const int wknights = Board.pieces(chess::PieceType::KNIGHT, Color::WHITE).count();
	const int wbishops = Board.pieces(chess::PieceType::BISHOP, Color::WHITE).count();
	const int wrooks = Board.pieces(chess::PieceType::ROOK, Color::WHITE).count();
	const int wqueens = Board.pieces(chess::PieceType::QUEEN, Color::WHITE).count();

	const int bpawns = bpawns_board.count();
	const int bknights = Board.pieces(chess::PieceType::KNIGHT, Color::BLACK).count();
	const int bbishops = Board.pieces(chess::PieceType::BISHOP, Color::BLACK).count();
	const int brooks = Board.pieces(chess::PieceType::ROOK, Color::BLACK).count();
	const int bqueens = Board.pieces(chess::PieceType::QUEEN, Color::BLACK).count();

	phase += wknights + bknights;
	phase += wbishops + bbishops;
	phase += (wrooks + brooks) * 2;
	phase += (wqueens + bqueens) * 4;

	eval_mg +=
		((wpawns - bpawns) * piecesbouns::PicesValues[uint8_t(PHASE::MG)][uint8_t(Punderlying::PAWN)]) +
		((wknights - bknights) * piecesbouns::PicesValues[uint8_t(PHASE::MG)][uint8_t(Punderlying::KNIGHT)]) +
		((wbishops - bbishops) * piecesbouns::PicesValues[uint8_t(PHASE::MG)][uint8_t(Punderlying::BISHOP)]) +
		((wrooks - brooks) * piecesbouns::PicesValues[uint8_t(PHASE::MG)][uint8_t(Punderlying::ROOK)]) +
		((wqueens - bqueens) * piecesbouns::PicesValues[uint8_t(PHASE::MG)][uint8_t(Punderlying::QUEEN)]);

	eval_eg +=
		((wpawns - bpawns) * piecesbouns::PicesValues[uint8_t(PHASE::EG)][uint8_t(Punderlying::PAWN)]) +
		((wknights - bknights) * piecesbouns::PicesValues[uint8_t(PHASE::EG)][uint8_t(Punderlying::KNIGHT)]) +
		((wbishops - bbishops) * piecesbouns::PicesValues[uint8_t(PHASE::EG)][uint8_t(Punderlying::BISHOP)]) +
		((wrooks - brooks) * piecesbouns::PicesValues[uint8_t(PHASE::EG)][uint8_t(Punderlying::ROOK)]) +
		((wqueens - bqueens) * piecesbouns::PicesValues[uint8_t(PHASE::EG)][uint8_t(Punderlying::QUEEN)]);

	const MG_EG mg_eg = Calc_adjustment(Board);
	eval_mg += mg_eg.first;
	eval_eg += mg_eg.second;

	if (wpawns_board & uint8_t(chess::Rank::underlying::RANK_7))
	{
		eval_mg += 20;
		eval_eg += 30;
	}
	if (bpawns_board & uint8_t(chess::Rank::underlying::RANK_2))
	{
		eval_mg -= 20;
		eval_eg -= 30;
	}

	phase = 24 - phase;
	phase = (phase * 256 + (24 / 2)) / 24;

	return (((eval_mg * (256 - phase)) + (eval_eg * phase)) / 256) * (Board.sideToMove() * -2 + 1);
}

Evaluate::MG_EG Evaluate::Calc_adjustment(const chess::Board& Board)
{
	static constexpr uint8_t MG = uint8_t(piecesbouns::PHASE::MG);
	static constexpr uint8_t EG = uint8_t(piecesbouns::PHASE::EG);

	chess::Bitboard white_pieces = Board.us(Color::WHITE);
	chess::Bitboard black_pieces = Board.us(Color::BLACK);

	int eval_mg = 0;
	int eval_eg = 0;

	while (white_pieces)
	{
		const uint8_t square = white_pieces.pop();
		const chess::Piece piece = Board.at(square);

		eval_mg += piecesbouns::pieceSquareScore[MG][piece % 6][square ^ 56];
		eval_eg += piecesbouns::pieceSquareScore[EG][piece % 6][square ^ 56];
	}

	while (black_pieces)
	{
		const uint8_t square = black_pieces.pop();
		const chess::Piece piece = Board.at(square);

		eval_mg -= piecesbouns::pieceSquareScore[MG][piece % 6][square];
		eval_eg -= piecesbouns::pieceSquareScore[EG][piece % 6][square];
	}

	return { eval_mg, eval_eg };
}
