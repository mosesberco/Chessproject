#pragma once
#include "Pieces.h"

class Bishop :public Piece
{
public:
	Bishop(Colors, Position);
	~Bishop();
	bool isvalid(Position newposition, Piece*[][8]);
	void PrintSymbol();
	string Get_type();
	sf::Sprite get_Sprite();
	void Print_move(sf::RenderWindow&);
	//void drow(RenderWindow& window);
};