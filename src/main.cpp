#include <iostream>

#include "uci.hpp"
#include "piecesbouns.hpp"

TranspositionTable tt;
ThreadPool Threads;

int main(void)
{
	piecesbouns::init_pieces_bouns();
	init_reductions();

	UCI Engine;
	Engine.Main_Loop();
}