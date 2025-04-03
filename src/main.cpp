#include <iostream>

#include "uci.hpp"
#include "piecesbouns.hpp"

TranspositionTable tt;
ThreadPool Threads;

int main(void)
{
	init_reductions();

	UCI Engine;
	Engine.Main_Loop();
}