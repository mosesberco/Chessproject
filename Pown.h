#pragma once
#include "Pieces.h"
class Pown :public Piece
{
public:
	Pown(Colors, Position);
	~Pown();
	virtual bool isvalid(Position newposition, Piece* [][8]);
	virtual void PrintSymbol();
	virtual string Get_type();
	sf::Sprite get_Sprite();
	void Print_move(sf::RenderWindow&);


};
