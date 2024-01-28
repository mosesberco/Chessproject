#include "King.h"
King::King(Colors colors, Position Pos) :Piece(colors, Pos)
{
	/*if(colors==Colors::white)
		texture.loadFromFile("images\\white_king.png");
	else 	texture.loadFromFile("images\\black_king.png");
	this->sprite_piece.setTexture(texture);*/
}

King::~King()
{
}

bool King::isvalid(Position newposition, Piece* Board[][8])//done
{

	int delta_col = abs(position.col - newposition.col);
	int delta_row = abs(position.row - newposition.row);
	if (delta_row == 1&&delta_col==1||delta_row==0&&delta_col==1||delta_row==1&&delta_col==0)
	{
		if (Board[newposition.row][newposition.col] != nullptr) {
			if (Board[newposition.row][newposition.col]->Get_color() == this->color)
				return false;
			return true;
		}
		if (Board[newposition.row][newposition.col] == nullptr)
			return true;
	}
	if(delta_row==0&&delta_col==2)

	return false;
}
void King::PrintSymbol()
{
	if (this->color == Colors::white)
		cout << " WK ";
	else cout << " BK ";
}
string King::Get_type()
{
	return "King";
}

sf::Sprite King::get_Sprite()
{
	return this->sprite_piece;
}

void King::Print_move(sf::RenderWindow& window)
{
	for(int i=0;i<8;i++)
		for (int j=0;j<  8;j++)
		{
			int delta_col = abs(position.col - i);
			int delta_row = abs(position.row - j);
			if (delta_row == 1 && delta_col == 1 || delta_row == 0 &&delta_col == 1 || delta_row == 1 && delta_col ==0)
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
