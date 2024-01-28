#include "Bishop.h"
Bishop::Bishop(Colors colors, Position Pos) :Piece(colors, Pos) {
	/*if(colors==Colors::white)
		texture.loadFromFile("images\\white_bishop.jpg");
	else 	texture.loadFromFile("images\\black_bishop.png");
	this->sprite_piece.setTexture(texture);*/

}

Bishop::~Bishop()
{
}

bool Bishop::isvalid(Position newposition, Piece* Board[][8])//done
{
	if (abs(position.col - newposition.col) == abs(position.row - newposition.row)) {
		int delta_i, delta_j;
		if (position.col > newposition.col)
			delta_j = -1;
		else delta_j = 1;
		if (position.row > newposition.row)
			delta_i = -1;
		else delta_i = 1;
		int i = position.row + delta_i;
		int j = position.col + delta_j;
		while (i != newposition.row && j != newposition.col)//check if there is a pieces on the way
		{
			if (Board[i][j] != nullptr)
				return false;
			i += delta_i;
			j += delta_j;
		}
		if (Board[newposition.row][newposition.col] != nullptr) {
			if (Board[newposition.row][newposition.col]->Get_color() == this->color)
				return false;
			return true;
		}
		if (Board[newposition.row][newposition.col] == nullptr)
			return true;
	}
	return false;
}

void Bishop::PrintSymbol()
{
	if (this->color == Colors::white)
		wcout << L"♖";
	else wcout << L"♖";
}

string Bishop::Get_type()
{
	return "Bishop";
}

sf::Sprite Bishop::get_Sprite()
{
	return this->sprite_piece;
}

void Bishop::Print_move(sf::RenderWindow& window)
{
	for (int i = 0;i < 8;i++)
		for (int j = 0;j < 8;j++)
		{
			if (abs(position.col - j) == abs(position.row - i)) 
			{
				sf::RectangleShape squere(sf::Vector2f(100, 100));
				squere.setPosition(i * 100, j * 100);
				if ((i + j) % 2 == 0)
					squere.setFillColor(sf::Color::Red);
				else squere.setFillColor(sf::Color(128, 128, 128));
				window.draw(squere);
			}
		}
	window.display();
}
