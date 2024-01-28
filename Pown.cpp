#include "Pown.h"
Pown::Pown(Colors colors, Position Pos) :Piece(colors, Pos)
{
	/*if(colors==Colors::white)
		texture.loadFromFile("images\\white_pown.png");
	else 	texture.loadFromFile("images\\black_pown.png");
	this->sprite_piece.setTexture(texture);*/

}

Pown::~Pown()
{
}

bool Pown::isvalid(Position newposition, Piece* Board[][8])
{
	if (this->color == Colors::white)//can move only one way
	{
		if (newposition.row > position.row)
			return false;
	}
	else if (newposition.row < position.row)
		return false;
	
	Colors other_color;
	if (this->Get_color() == Colors::white)
		other_color = Colors::black;
	else other_color = Colors::white;
	if (abs(newposition.row - this->position.row) == 2&& newposition.col - this->position.col == 0)
		if (this->position.row == 1 || this->position.row == 6) {
			if (Board[newposition.row][newposition.col] != nullptr)
				return false;
			return true;
		}
	if (abs(newposition.row - this->position.row) == 1 && newposition.col - this->position.col == 0)
		return true;
	else if (abs(newposition.row - this->position.row) == 1 && abs(newposition.col - this->position.col) == 1)//eat diagonal
	{
		if (Board[newposition.row][newposition.col] != nullptr) {
			if (Board[newposition.row][newposition.col]->Get_color() == other_color)
				return true;
			else return false;
			if (newposition.row == 3 && position.row == 4 || newposition.row == 6 && position.row == 5)
				return true;
		}
		if (Board[newposition.row][newposition.col] == nullptr)
			if (newposition.row == 3 && position.row == 4 || newposition.row == 6 && position.row == 5)
				return true;
	}
	//לבדוק מה קורה אם הרגלי אוכל חייל
	return false;
}

void Pown::PrintSymbol()
{
	if (this->color == Colors::white)
		cout << " WP ";
	else cout << " BP ";
}

string Pown::Get_type()
{
	return "Pown";
}

sf::Sprite Pown::get_Sprite()
{
	return this->sprite_piece;
}

void Pown::Print_move(sf::RenderWindow&)
{
	
}
