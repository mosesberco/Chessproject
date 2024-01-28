#pragma once
#include <SFML\Graphics.hpp>
using namespace std;
#include <iostream>
//using namespace sf;

#include <iostream>
#include <locale>
#include <io.h>
#include <fcntl.h>
#include <SFML\Graphics.hpp>
struct Position {
	int row;
	int col;
};
enum class Colors {
	white,black
};
class Piece
{
protected:
	Colors color;
	Position position;
	sf::Texture texture;
	sf::Sprite sprite_piece;
public:
	Piece(Colors,Position);
	~Piece();
	virtual bool isvalid(Position newposition, Piece* [][8]) = 0;
	virtual sf::Sprite get_Sprite()=0;
	void SetPosition(int, int);
	Position GetPos();
	virtual void PrintSymbol() = 0;
	virtual string Get_type() = 0;
	virtual void Print_move(sf::RenderWindow&) = 0;
	Colors Get_color();
	friend int min(int,int);
	friend int max(int, int);
	//friend class Board;
	//virtual void drow(RenderWindow& window)=0;

};









