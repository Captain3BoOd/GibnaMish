#include "types.hpp"

int is_mate_score(const Score score)
{
	int result = 0;

	if (score > VALUE_MATE_IN_PLY) { result = VALUE_MATE - score; }
	else if (score < VALUE_MATED_IN_PLY) { result = -VALUE_MATE - score; }
	if (result % 2 != 0) { result++; }

	return result / 2;
}
