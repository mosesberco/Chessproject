#include "Queen.h"
Queen::Queen(Colors colors, Position Pos) :Piece(colors, Pos)
{
	/*if(colors==Colors::white)
		this->texture.loadFromFile("images\\white_queen.jpg");
	else 	this->texture.loadFromFile("images\\black_queen.jpg");
	this->sprite_piece.setTexture(texture);*/
}

Queen::~Queen()
{
}

bool Queen::isvalid(Position newposition, Piece* Board[][8])//done
{
	if (position.col == newposition.col || position.row == newposition.row) {
		//need to add method to check if there is Piece in the road
		if(Board[newposition.row][newposition.col]!=nullptr)
			if (Board[newposition.row][newposition.col]->Get_color() == this->color)
				return false;
		if (position.col == newposition.col)
		{
			if (position.row > newposition.row) {
				for (int i = newposition.row + 1;i < position.row;i++)
					if (Board[i][position.col] != nullptr) {
						//continue;
					//else
						return false;
					}
			}
			else for (int i = position.row + 1;i < newposition.row;i++)
				if (Board[i][position.col] != nullptr) {
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
		if (position.row == newposition.row)
		{
			if (position.col > newposition.col) {
				for (int i = newposition.col+1;i < position.col;i++)
					if (Board[position.row][i] != nullptr)
						return false;
			}
			else for (int i = position.col+1;i < newposition.col;i++)
				if (Board[position.row][i] != nullptr)
					return false;
			if (Board[newposition.row][newposition.col] != nullptr) {
				if (Board[newposition.row][newposition.col]->Get_color() == this->color)
					return false;
				return true;
			}
			if (Board[newposition.row][newposition.col] == nullptr)
				return true;
		}
	}
		///check if the move is diagonal
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

void Queen::PrintSymbol()
{
	if (this->color == Colors::white)
		cout << " WQ ";
	else cout << " BQ ";
}

string Queen::Get_type()
{
	return "Queen";
}

sf::Sprite Queen::get_Sprite()
{
	return this->sprite_piece;
}

void Queen::Print_move(sf::RenderWindow& window)
{
	Position x;
	for(int i=0;i<8;i++)
		for (int j = 0;j < 8;j++)
		{
			if (position.col == j || position.row == i)
			{
				x.row = i;
				x.col = j;
				//if(this->isvalid(x,))
				sf::RectangleShape squere(sf::Vector2f(100, 100));
				squere.setPosition(i * 100, j * 100);
				if ((i + j) % 2 == 0)
					squere.setFillColor(sf::Color::Red);
				else squere.setFillColor(sf::Color(128, 128, 128));
				window.draw(squere);
			}
			if (abs(position.col - i) == abs(position.row - j))
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
