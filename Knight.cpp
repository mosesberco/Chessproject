#include "Knight.h"
Knight::Knight(Colors colors, Position Pos) :Piece(colors, Pos)
{
	/*if(colors==Colors::white)
		texture.loadFromFile("images\\white_knight.png");
	else 	texture.loadFromFile("images\\black_knight.png");
	this->sprite_piece.setTexture(texture);*/
}
Knight::~Knight()
{
}

bool Knight::isvalid(Position newposition, Piece* Board[][8])//done
{
	int rankrow = abs(this->position.row - newposition.row);
	int rankcol = abs(this->position.col - newposition.col);
	if (rankcol == 1 && rankrow == 2 || rankcol == 2 && rankrow == 1)
	{
		if (Board[newposition.row][newposition.col] != nullptr) {
			if (Board[newposition.row][newposition.col]->Get_color() == this->color)
				return false;
			return true;
		}
		if(Board[newposition.row][newposition.col]==nullptr)
		return true;
	}
	return false;
}
void Knight::PrintSymbol()
{
	if (this->color == Colors::white)
		cout << " WKn ";
	else cout << " BKn ";
}
string Knight::Get_type()
{
	return "Knight";
}

sf::Sprite Knight::get_Sprite()
{
	return this->sprite_piece;
}

void Knight::Print_move(sf::RenderWindow& window)
{
	for (int i = 0;i < 8;i++)
		for (int j = 0;j < 8;j++) {
			int rankrow = abs(this->position.row - i);
			int rankcol = abs(this->position.col - j);
			if (rankcol == 1 && rankrow == 2 || rankcol == 2 && rankrow == 1)
			{
				sf::RectangleShape squere(sf::Vector2f(100, 100));
				squere.setPosition(i * 100, j * 100);
				if ((i + j) % 2 == 0)
					squere.setFillColor(sf::Color::Red);
				else squere.setFillColor(sf::Color::Red);
				window.draw(squere);
				
			}
		}
	window.display();
}
