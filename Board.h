#pragma once
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Pown.h"
#include "Knight.h"
#include <cstdlib>
#include <fstream>
#include <string.h>

class Board
{
public:
	Board();
	Board(string);
	Board(const Board&);
	~Board();
	Piece* getPiece(int,int);
	bool SetPiece(Piece*,int,int);
	void PrintBoard(sf::RenderWindow&);
	bool is_check(Colors);
	friend class Game;
	bool move_to_cancel_check(Colors, Position, Position);
	void operator=(const Board&);
	bool avoid_check(Position, Position, Colors);
	void move_rook_king(Position, Position, Colors);
	void Save_game();
	bool End_game(Colors);

private:
	Piece* board[8][8];
};

