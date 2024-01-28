#pragma once
#include "Pieces.h"
class Queen :public Piece
{
public:
	Queen(Colors, Position);
	~Queen();
	bool isvalid(Position newposition, Piece* [][8]);
	void PrintSymbol();
	string Get_type();
	sf::Sprite get_Sprite();
	void Print_move(sf::RenderWindow&);
};
