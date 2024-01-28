#include "Board.h"

Board::Board()
{
	Position x;
	for(int i=0;i<8;i++)
		for (int j = 0;j < 8;j++)
		{
			if (i == 1) {
				x.row = i;
				x.col = j;
				board[i][j] = new Pown(Colors::black, x);
			}
			else if (i == 6)
			{
				x.row = i;
				x.col = j;
				board[i][j] = new Pown(Colors::white, x);
			}
			else if (i == 0) {
				if (j == 0 || j == 7)
				{
					x.row = i;
					x.col = j;
					board[i][j] = new Rook(Colors::black, x);
				}
				else if (j == 1 || j == 6)
				{
					x.row = i;
					x.col = j;
					board[i][j] = new Knight(Colors::black, x);
				}
				else if (j == 2 || j == 5)
				{
					x.row = i;
					x.col = j;
					board[i][j] = new Bishop(Colors::black, x);
				}
				else if (j == 3)
				{
					x.row = i;
					x.col = j;
					board[i][j] = new Queen(Colors::black, x);
				}
				else if (j == 4)
				{
					x.row = i;
					x.col = j;
					board[i][j] = new King(Colors::black, x);
				}
			}
			else if (i == 7)
			{
				if (j == 0 || j == 7)
				{
					x.row = i;
					x.col = j;
					board[i][j] = new Rook(Colors::white, x);
				}
				else if (j == 1 || j == 6)
				{
					x.row = i;
					x.col = j;
					board[i][j] = new Knight(Colors::white, x);
				}
				else if (j == 2 || j == 5)
				{
					x.row = i;
					x.col = j;
					board[i][j] = new Bishop(Colors::white, x);
				}
				else if (j == 3)
				{
					x.row = i;
					x.col = j;
					board[i][j] = new Queen(Colors::white, x);
				}
				else if (j == 4)
				{
					x.row = i;
					x.col = j;
					board[i][j] = new King(Colors::white, x);
				}
			}
			else board[i][j] = nullptr;
		}
}

/*Board::Board(const Board& other)
{
	for (int i = 0;i < 8;i++)
		for (int j = 0;j < 8;j++)
			board[i][j] = other.board[i][j];
}*/

Board::~Board()
{
	for (int i = 0;i < 8;i++)
		for (int j = 0;j < 8;j++)
			if (board[i][j] != nullptr)
				delete board[i][j];
}

Piece* Board::getPiece(int i, int j)
{
	return board[i][j];
}

bool Board::SetPiece(Piece* piece, int i, int j)
{
	if (board[i ][j ] == nullptr) {
		Position pos = { i,j };
		if (piece->isvalid(pos,board)) {
			Position last_pos = piece->GetPos();
			board[i ][j ] = piece;
			board[i][j]->SetPosition(i, j);
			board[last_pos.row][last_pos.col] = nullptr;
		}
	}
	else return false;
	return true;
}

void Board::PrintBoard(sf::RenderWindow& window)
{
	for (int i = 0;i < 8;i++)
		for (int j = 0;j < 8;j++)
			window.draw(board[i][j]->get_Sprite());
			
}

bool Board::is_check(Colors col)//check if there is a 'check' on the color 'col' king
{
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 8;j++)
			if (board[i][j] != nullptr) {
				if (board[i][j]->Get_type() == "King" && board[i][j]->Get_color() == col)
				{
					Position posKing = { i,j };
					Colors oponent_color;
					if (col == Colors::white)
						oponent_color = Colors::black;
					else oponent_color = Colors::white;
					for (int m = 0;m < 8;m++)
						for (int n = 0;n < 8;n++) {
							if (board[m][n] != nullptr) {
								Piece* piece = board[m][n];
								if (piece->Get_color() == oponent_color)
									if (piece->isvalid(posKing, board) && piece->Get_type() != "King") {
										cout << "\nCheck from " << piece->Get_type();
										return true;
									}
							}

						}
				}
			}
	}
	return false;



}

bool Board::move_to_cancel_check(Colors oponnent,Position before,Position after)//there is a move to canceled check
{

	if (!this->is_check(oponnent))//if there is no check, return true
		return true;
	Board temp;
	temp = *this;
	temp.getPiece(before.col, before.row)->SetPosition(after.col, after.row);
	if (this->is_check(oponnent))
		return false;


	Position from, to;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if (temp.board[i][j] != nullptr)
			{
				Piece* temp_piece = temp.board[i][j];
				from = temp.board[i][j]->GetPos();
				for (int m = 0;m < 8;m++)
					for (int n = 0;n < 8;n++) {
						to.row = m;
						to.col = n;
						if (temp_piece->isvalid(to, temp.board))
						{
							temp_piece->SetPosition(m, n);
							temp.board[i][j] = nullptr;
							temp.board[m][n] = temp_piece;
							if (temp.is_check(oponnent))
							{
								temp_piece->SetPosition(from.row, from.col);
								temp.board[i][j] = temp_piece;
								temp.board[m][n] = nullptr;
							}
							else return true;
						}
					}

			}
	return false;
}

void Board::operator=(const Board& other)
{
	for (int i = 0;i < 8;i++)
		for (int j = 0;j < 8;j++)
			if (board[i][j])
				delete board[i][j];
	Position x;
	for (int i = 0;i < 8;i++)
		for (int j = 0;j < 8;j++)
		{
			/*if (other.board[i][j] != nullptr) {
				if (other.board[i][j]->Get_color() == Colors::white) {
					if (other.board[i][j]->Get_type() == "King") {
						x.row = i;
						x.col = j;
						board[i][j] = new King(Colors::white, x);
					}
					if (other.board[i][j]->Get_type() == "Queen") {
						x.row = i;
						x.col = j;
						board[i][j] = new Queen(Colors::white, x);
					}
					if (other.board[i][j]->Get_type() == "Bishop") {
						x.row = i;
						x.col = j;
						board[i][j] = new Bishop(Colors::white, x);
					}
					if (other.board[i][j]->Get_type() == "Rook") {
						x.row = i;
						x.col = j;
						board[i][j] = new Rook(Colors::white, x);
					}
					if (other.board[i][j]->Get_type() == "Knight") {
						x.row = i;
						x.col = j;
						board[i][j] = new Knight(Colors::white, x);
					}
					if (other.board[i][j]->Get_type() == "Pown") {
						x.row = i;
						x.col = j;
						board[i][j] = new Pown(Colors::white, x);
					}
				}
				if (other.board[i][j]->Get_color() == Colors::black) {
					if (other.board[i][j]->Get_type() == "King") {
						x.row = i;
						x.col = j;
						board[i][j] = new King(Colors::black, x);
					}
					if (other.board[i][j]->Get_type() == "Queen") {
						x.row = i;
						x.col = j;
						board[i][j] = new Queen(Colors::black, x);
					}
					if (other.board[i][j]->Get_type() == "Bishop") {
						x.row = i;
						x.col = j;
						board[i][j] = new Bishop(Colors::black, x);
					}
					if (other.board[i][j]->Get_type() == "Rook") {
						x.row = i;
						x.col = j;
						board[i][j] = new Rook(Colors::black, x);
					}
					if (other.board[i][j]->Get_type() == "Knight") {
						x.row = i;
						x.col = j;
						board[i][j] = new Knight(Colors::black, x);
					}
					if (other.board[i][j]->Get_type() == "Pown") {
						x.row = i;
						x.col = j;
						board[i][j] = new Pown(Colors::black, x);
					}
				}
			}*/
			board[i][j] = other.board[i][j];
			//else board[i][j] = nullptr;
		}
				
		
}

bool Board::avoid_check(Position before, Position after, Colors color)
{
	if (!this->is_check(color))
		return true;
	Board temp(*this);
	//temp = *this;
	Position temp_pos;
	temp.getPiece(before.row, before.col)->SetPosition(after.row, after.col);
	temp.board[after.row][after.col] = temp.getPiece(before.row, before.col);
	temp.board[before.row][before.col] = nullptr;
	if (!temp.is_check(color))
		return true;
	else return false;
	return (!temp.is_check(color));
}

void Board::move_rook_king(Position from, Position to,Colors col)
{
	if (from.col == 4 && to.col == 6)
	{
		if (board[from.row][7]->Get_type()=="Rook"&& board[from.row][7]->Get_color()==col)
		{
			board[from.row][7]->SetPosition(from.row, 5);
			board[from.row][5] = board[from.row][7];
			board[from.row][7] = nullptr;
		}
	}
	if (from.col == 4 && to.col == 2)
	{
		if (board[from.row][7]->Get_type() == "Rook" && board[from.row][0]->Get_color() == col)
		{
			board[from.row][0]->SetPosition(from.row, 3);
			board[from.row][3] = board[from.row][0];
			board[from.row][0] = nullptr;
		}
	}
}

void Board::Save_game()
{
	string name;
	cout << "save game?" << endl;
	cin >> name;
	if (name == "yes") {
		cout << "Enter the name to save the game: ";
		cin >> name;
		name += ".txt";
		ofstream savedgame(name);
		if (!savedgame.is_open()) {
			cout << "Failed to create the file." << endl;
			exit(2);
		}
		for (int i = 0;i < 8;i++)
			for (int j = 0;j < 8;j++)
			{
				if (board[i][j]) {
					savedgame << board[i][j]->Get_type() << endl;
					if (board[i][j]->Get_color() == Colors::white)
						savedgame << "white";
					else savedgame << "black";
					savedgame << endl;
				}
				else savedgame << "NULL" << endl;
			}
		savedgame.close();
	}
	else cout << "Bay Bay." << endl;
}

bool Board::End_game(Colors col)
{
	Position KingPos, y, After;
	for(int i=0;i<8;i++)
		for (int j = 0;j < 8;j++) {

			if (board[i][j]&&board[i][j]->Get_type() == "King" && board[i][j]->Get_color() == col)
			{
				KingPos.row = i;
				KingPos.col = j;
				break;
			}
		}
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			y.row = i;
			y.col = j;
			if (board[i][j]&&board[i][j]->Get_color()==col)
			{
				for(int n=0;n<8;n++)
					for (int m = 0;m < 8;m++)
					{
						After.row = n;
						After.col = m;
						if (board[i][j]->isvalid(After, board) && avoid_check(y,After,col))
							return false;
							
					}
			}
		}
	}
	return true;
			
}





 Board::Board(string game)
{
	/*cout << "enter game: ";
	cin >> game;*/
	game += ".txt";
	ifstream openfile(game);
	if (!openfile.is_open())
	{
		cout << "problem with loading game";
		exit(2);
	}
	//openfile.open(game,ios::in);
	string Line1,Line2;
	for(int i=0;i<8;i++)
		for (int j = 0;j < 8;j++) {
			Position x = { i,j };
			if(openfile >> Line1) {
				if (Line1 == "Rook") {
					openfile >> Line2;
					if (Line2 == "white")
						board[i][j] = new Rook(Colors::white, x);
					else board[i][j] = new Rook(Colors::black, x);
				}
				if (Line1 == "Knight")
				{
					openfile >> Line2;
					if (Line2 == "white")
						board[i][j] = new Knight(Colors::white, x);
					else board[i][j] = new Knight(Colors::black, x);
				}
				if (Line1 == "King")
				{
					openfile >> Line2;
					if (Line2 == "white")
						board[i][j] = new King(Colors::white, x);
					else board[i][j] = new King(Colors::black, x);
				}
				if (Line1 == "Queen")
				{
					openfile >> Line2;
					if (Line2 == "white")
						board[i][j] = new Queen(Colors::white, x);
					else board[i][j] = new Queen(Colors::black, x);
				}
				if (Line1 == "Bishop")
				{
					openfile >> Line2;
					if (Line2 == "white")
						board[i][j] = new Bishop(Colors::white, x);
					else board[i][j] = new Bishop(Colors::black, x);
				}
				if (Line1 == "Pown")
				{
					openfile >> Line2;
					if (Line2 == "white")
						board[i][j] = new Pown(Colors::white, x);
					else board[i][j] = new Pown(Colors::black, x);
				}
				if (Line1 == "NULL")
					board[i][j] = nullptr;
			}

		}
	openfile.close();
}

 Board::Board(const Board& other)
 {
	 Position x;
	 for(int i=0;i<8;i++)
		 for (int j = 0;j < 8;j++)
		 {
			 if (other.board[i][j] != nullptr) {
				 if (other.board[i][j]->Get_color() == Colors::white) {
					 if (other.board[i][j]->Get_type() == "King") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new King(Colors::white, x);
					 }
					 if (other.board[i][j]->Get_type() == "Queen") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new Queen(Colors::white, x);
					 }
					 if (other.board[i][j]->Get_type() == "Bishop") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new Bishop(Colors::white, x);
					 }
					 if (other.board[i][j]->Get_type() == "Rook") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new Rook(Colors::white, x);
					 }
					 if (other.board[i][j]->Get_type() == "Knight") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new Knight(Colors::white, x);
					 }
					 if (other.board[i][j]->Get_type() == "Pown") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new Pown(Colors::white, x);
					 }
				 }
				 if (other.board[i][j]->Get_color() == Colors::black) {
					 if (other.board[i][j]->Get_type() == "King") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new King(Colors::black, x);
					 }
					 if (other.board[i][j]->Get_type() == "Queen") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new Queen(Colors::black, x);
					 }
					 if (other.board[i][j]->Get_type() == "Bishop") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new Bishop(Colors::black, x);
					 }
					 if (other.board[i][j]->Get_type() == "Rook") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new Rook(Colors::black, x);
					 }
					 if (other.board[i][j]->Get_type() == "Knight") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new Knight(Colors::black, x);
					 }
					 if (other.board[i][j]->Get_type() == "Pown") {
						 x.row = i;
						 x.col = j;
						 board[i][j] = new Pown(Colors::black, x);
					 }
				 }
			 }
			 else board[i][j] = nullptr;
		 }
 }

