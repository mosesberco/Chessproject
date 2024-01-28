#include "Rook.h"
Rook::Rook(Colors colors, Position Pos) :Piece(colors, Pos)
{
	/*if(colors==Colors::white)
		texture.loadFromFile("images\\white_rook.jpg");
	else 	texture.loadFromFile("images\\black_rook.png");

	this->sprite_piece.setTexture(texture);*/
}
Rook::~Rook()
{
}

bool Rook::isvalid(Position newposition, Piece* Board[][8])//done
{
	if (position.col == newposition.col || position.row == newposition.row) {
		//need to add method to check if there is Piece in the road
		if (position.col == newposition.col)
		{
			if (position.row > newposition.row) {
				for (int i = newposition.row;i < position.row;i++)
					if (Board[i][position.col] != nullptr)
						return false;
			}
			else for (int i = position.row;i < newposition.row;i++)
				if (Board[i][position.col] != nullptr)
					return false;

		}
		if (position.row == newposition.row)
		{
			if (position.col > newposition.col) {
				for (int i = newposition.col;i < position.col;i++)
					if (Board[position.row][i] != nullptr)
						return false;
			}
			else for (int i = position.col;i < newposition.col;i++)
				if (Board[position.row][i] != nullptr)
					return false;
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

void Rook::PrintSymbol()
{
	if (this->color == Colors::white)
		cout << " WR ";
	else cout << " BR ";
}

string Rook::Get_type()
{
	return "Rook";
}

sf::Sprite Rook::get_Sprite()
{
	return this->sprite_piece;
}

void Rook::Print_move(sf::RenderWindow& window)
{
	for(int i=0;i<8;i++)
		for (int j = 0;j < 8;j++)
		{
			if (position.col == j || position.row == i)
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
