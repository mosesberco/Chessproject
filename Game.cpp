#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
	sf::Texture White_king;
	/* {//sf::Font font;
	/*if (!font.loadFromFile("images\\saved_game.png")) {
		cout << "problem";
		exit(1);
	}
	sf::Text text;
	//text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(900, 300);
	text.setFillColor(sf::Color::White);
	sf::RectangleShape button(sf::Vector2f(100, 25));
	button.setPosition(900, 300);
	button.setFillColor(sf::Color::White);
	window.draw(button);
	}*/
	Colors turn = Colors::white, op_turn = Colors::black;//define the first turn

	/// <summary>
	/// /load all the pictures
	/// 
	/// </summary>
	if (!White_king.loadFromFile("images\\white_king.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture Black_king;
	if (!Black_king.loadFromFile("images\\black_king.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture White_rook;
	if (!White_rook.loadFromFile("images\\white_rook.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture Black_rook;
	if (!Black_rook.loadFromFile("images\\black_rook.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture White_knight;
	if (!White_knight.loadFromFile("images\\white_knight.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture Black_knight;
	if (!Black_knight.loadFromFile("images\\black_knight.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture White_bishop;
	if (!White_bishop.loadFromFile("images\\white_bishop.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture Black_bishop;
	if (!Black_bishop.loadFromFile("images\\black_bishop.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture White_queen;
	if (!White_queen.loadFromFile("images\\white_queen.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture Black_queen;
	if (!Black_queen.loadFromFile("images\\black_queen.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture White_pown;
	if (!White_pown.loadFromFile("images\\white_pown.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}
	sf::Texture Black_pown;
	if (!Black_pown.loadFromFile("images\\black_pown.png"))
	{
		cout << "Couldn't load the image.";
		return;
	}


	cout << "Would you like to open a new game?\n1-yes\n2-no\n";
	int choice;
	string game;
	cin >> choice;
	Board* board = nullptr;
	if (choice == 2) {
		cout << "What is the file name?";
		cin >> game;
		board = new Board(game);
	}
	else board = new Board();
	//Board board;//(game);
	
	Position from;
	bool isPieceSelected = false;
	Piece* piece = nullptr;
	int flag_check = 0;
	sf::RenderWindow window(sf::VideoMode(800, 800), "The Chess game");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			//// need to make a loop that check if there is a check in the game.

			sf::Vector2i mousefrom, mouseto;
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					isPieceSelected = true;
					//cout << "press" << endl;
					mousefrom = sf::Mouse::getPosition(window);
					from.col = mousefrom.x / 100;
					from.row = mousefrom.y / 100;
					//cout << "col " << from.col << endl << "row " << from.row << endl;
					/*if(board.board[col][row]!=nullptr)
					if(turn!=board.board[col][row]->Get_color())*/

					/*piece = board.getPiece(col, row);*/
					/*cout << "you choose " << piece->Get_type()<<endl;*/
					piece = board->getPiece(from.row, from.col);
					piece->Print_move(window);

				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					isPieceSelected = false;
					mouseto = sf::Mouse::getPosition(window);
					//if (button.getGlobalBounds().contains(sf::Vector2f(mouseto)))
					//cout << endl << "Release" << endl;
					//piece = board->getPiece(from.row, from.col);
					if (piece) {
						cout << "you choose " << piece->Get_type() << endl;
						//piece->Print_move(window);
						Position destiny;
						destiny.col = abs(mouseto.x / 100);
						destiny.row = abs(mouseto.y / 100);//איזה טור
						//cout << "col " << destiny.col << endl << "row " << destiny.row << endl;
						if (piece != nullptr)
							if (piece->isvalid(destiny, board->board) && turn == board->board[from.row][from.col]->Get_color())
								//check if the piece is the turn's colors
							{
								if (flag_check == 0)
								{
									piece->SetPosition(destiny.row, destiny.col);
									board->board[destiny.row][destiny.col] = piece;
									board->board[from.row][from.col] = nullptr;
									if (board->is_check(op_turn))
										flag_check = 1;
									if (turn == Colors::white)
									{
										turn = Colors::black;
										op_turn = Colors::white;
									}
									else {
										turn = Colors::white;
										op_turn = Colors::black;
									}

								}
								else if (board->avoid_check(from, destiny, turn) && flag_check == 1) {
									/*if (board.move_to_cancel_check(op_turn, from, destiny)) {*/
									piece->SetPosition(destiny.row, destiny.col);
									if (piece->Get_type() == "King" && abs(from.col - destiny.col) == 2)///// need to check
										board->move_rook_king(from, destiny, turn);
									board->board[destiny.row][destiny.col] = piece;
									board->board[from.row][from.col] = nullptr;

									if (flag_check == 1)
									{
										if (turn == Colors::white) {

											if (!board->is_check(Colors::white))
												flag_check = 0;


										}

										//check if there is an check
										else
										{
											if (!board->is_check(Colors::black))
												flag_check = 0;

										}
									}
									if (turn == Colors::white && flag_check == 0) {
										turn = Colors::black;
										op_turn = Colors::white;
										if (board->is_check(Colors::black)) {
											flag_check = 1;
										}
									}
									//check if there is an check
									else
									{
										if (flag_check == 0) {
											turn = Colors::white;
											op_turn = Colors::black;
											if (board->is_check(Colors::white))
												flag_check = 1;
										}

									}

									/*else {
										cout << endl << "checkmat\ncheckmat\ncheckmat\n";
										return;
									}*/
								}
								else if (board->End_game(turn))
								{
									if (turn == Colors::white)
										cout << "The Black win!";
									else cout << "The White win!";
									return;
								}

								

								else cout << "The move is invalid.";
							}
							else cout << "The move is invalid.";
					}
					else cout << "You didnt press any piece.";


				}//the picking piece
				else cout << "You didnt press any piece.";


			}
		}

		/// <summary>
		/// print all the board and the pieces
		/// </summary>
		window.clear();
		/// <summary>
		/// print the board
		/// </summary>
		for (int i = 0;i < 8;i++)
			for (int j = 0;j < 8;j++) {
				sf::RectangleShape squere(sf::Vector2f(100, 100));
				squere.setPosition(i * 100, j * 100);
				if ((i + j) % 2 == 0)
					squere.setFillColor(sf::Color::White);
				else squere.setFillColor(sf::Color(128, 128, 128));
				window.draw(squere);
			}
		//window.display();
		for (int i = 0;i < 8;i++)
			for (int j = 0;j < 8;j++)
			{
				Piece* piece = board->getPiece(i, j);
				if (piece) {
					sf::Sprite sprite;
					if (piece->Get_color() == Colors::white) {
						if (piece->Get_type() == "King")
							sprite.setTexture(White_king);
						else if (piece->Get_type() == "Bishop")
							sprite.setTexture(White_bishop);
						else if (piece->Get_type() == "Queen")
							sprite.setTexture(White_queen);
						else if (piece->Get_type() == "Rook")
							sprite.setTexture(White_rook);
						else if (piece->Get_type() == "Knight")
							sprite.setTexture(White_knight);
						else if (piece->Get_type() == "Pown")
							sprite.setTexture(White_pown);
					}
					else {
						if (piece->Get_type() == "King")
							sprite.setTexture(Black_king);
						else if (piece->Get_type() == "Bishop")
							sprite.setTexture(Black_bishop);
						else if (piece->Get_type() == "Queen")
							sprite.setTexture(Black_queen);
						else if (piece->Get_type() == "Rook")
							sprite.setTexture(Black_rook);
						else if (piece->Get_type() == "Knight")
							sprite.setTexture(Black_knight);
						else if (piece->Get_type() == "Pown")
							sprite.setTexture(Black_pown);
					}
					sprite.setPosition(j * 100, i * 100);
					window.draw(sprite);

				}
				//

			}
		window.display();
	}
	board->Save_game();
}




