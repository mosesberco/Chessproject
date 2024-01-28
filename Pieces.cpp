#include "Pieces.h"
#include "Board.h"


Piece::Piece(Colors colors,Position Pos):color(colors),position(Pos)
{

}

Piece::~Piece()
{
}

void Piece::SetPosition(int i, int j)
{
	this->position.row = i;
	this->position.col = j;
}

Position Piece::GetPos()
{
	return position;
}

Colors Piece::Get_color()
{
	return this->color;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}
