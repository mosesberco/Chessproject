#pragma once
#include "Pieces.h"
class Rook :public Piece
{
public:
	Rook(Colors, Position);
	~Rook();
	bool isvalid(Position newposition, Piece* [][8]);
	void PrintSymbol();
	string Get_type();
	sf::Sprite get_Sprite();
	void Print_move(sf::RenderWindow&);
};
