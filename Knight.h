#pragma once
#include "Pieces.h"
#include <SFML\Graphics.hpp>
class Knight:public Piece
{
public:
	Knight(Colors, Position);
	~Knight();
	bool isvalid(Position newposition, Piece* [][8]);
	void PrintSymbol();
	string Get_type();
	sf::Sprite get_Sprite();
	void Print_move(sf::RenderWindow&);//
};
