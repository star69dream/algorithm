#include<iostream>
#include<string>
#include<bits/stdc++.h>
 
using namespace std;



 class Board{
 private :
	 string **board;

 public:
	 Board()
	 {
		 board = new string*[3];
		 for (int i = 0; i < 3; i++)
			board[i] = new string[3];
		 board[2][0] = "BP"; board[2][1] = "BP"; board[2][2] = "BP";
		 board[1][0] = "  "; board[1][1] = "  "; board[1][2] = "  ";
		 board[0][0] = "WP"; board[0][1] = "WP"; board[0][2] = "WP";
	 }

	 Board(const Board &b)
	 {
		 board = new string*[3];
		 for (int i = 0; i < 3; i++)
			board[i] = new string[3];
		 board[2][0] = "BP"; board[2][1] = "BP"; board[2][2] = "BP";
		 board[1][0] = "  "; board[1][1] = "  "; board[1][2] = "  ";
		 board[0][0] = "WP"; board[0][1] = "WP"; board[0][2] = "WP";
	 }

	 ~Board()
	 {
		 for (int i = 0; i < 3; i++)
  		 {
  			 delete[]board[i];
  		 }
		 delete[]board;
	 }

	 // getter and setter methods
	 string** getBoard()
	 {
		 return board;
	 }


	 void printBoard()
	 {
		 cout<<"   ___ ___ ___"<<endl;
		 cout<<"1 |"<<board[0][0]<<" |"<<board[0][1]<<" |"<<board[0][2]<<" |"<<endl;
		 cout<<"   ___ ___ ___"<<endl;
		 cout<<"2 |"<<board[1][0]<<" |"<<board[1][1]<<" |"<<board[1][2]<<" |"<<endl;
		 cout<<"   ___ ___ ___"<<endl;
		 cout<<"3 |"<<board[2][0]<<" |"<<board[2][1]<<" |"<<board[2][2]<<" |"<<endl;
		 cout<<"  ___ ___ ___"<<endl;
		 cout<<"   A   B   C"<<endl;
	 }

	 bool checkWin()
	 {
		 if(board[2][0] == "WP" || board[2][1] == "WP" || board[2][2] == "WP")
			 return true;
		 if(board[2][0] != "WP" && board[2][1] != "WP" && board[2][2] != "WP" && board[1][0] != "WP" && board[1][1] != "WP" && board[1][2] != "WP"
			 && board[0][0] != "WP" && board[0][1] != "WP" && board[0][2] != "WP")
			 return true;           
		 bool flag = true;
		 for(int i = 0; i < 3; i++)
			 for(int j = 0; j < 3; j++)
				 if(board[i][j] == "WP")
				 {
					 int numberOfMoves = 0;
					 if(i + 1 < 4 &&  board[i+1][j] == "  ")
						 numberOfMoves++;
					 if(i + 1 < 4 && j - 1 >= 0 && board[i+1][j - 1] == "BP")
						 numberOfMoves++;
					 if(i + 1 < 4 && j + 1 < 3 && board[i+1][j + 1] == "BP")
						 numberOfMoves++;
					 if(numberOfMoves > 0)
							 flag = false;
				 }
		 return flag;
	 }

	 char getWinner()
	 {
		 if(board[2][0] == "WP" || board[2][1] == "WP" || board[2][2] == "WP")
			 return 'W';
		 return 'B';
	 }
 };

 /******************************************************************************************************/

 class Player{
 private :
	 char playerType;
	 char playerColor;
 public :
	 Player() // default constructor
	 {
		 playerType = 'C';
		 playerColor = 'W';
	 }

	 Player(const Player &p)  // copy constructor
	 {
		 playerType = p.playerType;
		 playerColor = p.playerColor;
	 }

	 Player(char type , char color)  // parameterized constructor
	 {
		 playerType = type;
		 playerColor = color;
	 }

	 ~Player(){} // destructor
	  

	 /* getter and setter method */
	 int getPlayerType()
	 {
		 return playerType;
	 }

	 void setPlayerType(char type)
	 {
		 playerType = type;
	 }

	 int getPlayerColor()
	 {
		 return playerColor;
	 }

	 void setPlayerColor(char color)
	 {
		 playerColor = color;
	 }

	 void play(Board &b);
 };


 /******************************************************************************************************/
//////////
 class Human : public Player{

 public :
	 Human() : Player(){} // default constructor
	 
	 Human(const Player &p) : Player(p){}  // copy constructor
	 

	 Human(char color) : Player('H' , color) {}  // parameterized constructor


	 ~Human(){}  // destructor

	 void play(Board &b)
	 {
		 while(true)
		 {
			 char x;
			 int y;
			 cout<<"enter x and y for the your pawn you will move : ";
			 cin >> x;
			 cin >> y;
			 x = tolower(x);
			 if(getPlayerColor() == 'W')
				if(y - 1 >= 0 && y < 4 && ((int)x - (int)'a') >= 0 && ((int)x - (int)'a') < 3 && b.getBoard()[y-1][((int)x - (int)'a')] == "WP")
				{
					char newX;
					int newY;
					cout<<"enter x and y for the new location of your pawn you will move : ";
					cin >> newX;
					cin >> newY;
					newX = tolower(newX);
					if(newY < y)
						cout<<"wrong move"<<endl;
					else
					{
						if(newY - 1 >= 0 && newY < 4 && ((int)newX - (int)'a') >= 0 && ((int)newX - (int)'a') < 3 && (b.getBoard()[newY - 1][((int)newX - (int)'a')] == "  " || b.getBoard()[newY - 1][((int)newX - (int)'a')] == "BP"))
						{
							if(x != newX && b.getBoard()[newY-1][((int)newX - (int)'a')] == "  ")
								cout<<"wrong location"<<endl;
							else
							{
								b.getBoard()[newY-1][((int)newX - (int)'a')] = "WP";
								b.getBoard()[y-1][((int)x - (int)'a')] = "  ";
								break;
							}
						}
						else
							cout<<"wrong location"<<endl;
					}
				}
				else
					cout<<"wrong piece"<<endl;
			 else
				if(y - 1 >= 0 && y < 4 && ((int)x - (int)'a') >= 0 && ((int)x - (int)'a') < 3 && b.getBoard()[y-1][((int)x - (int)'a')] == "BP")
				{
					char newX;
					int newY;
					cout<<"enter x and y for the new location of your pawn you will move : ";
					cin >> newX;
					cin >> newY;
					newX = tolower(newX);
					if(newY > y)
						cout<<"wrong move"<<endl;
					else
					{
						if(newY - 1 >= 0 && newY < 4 && ((int)newX - (int)'a') >= 0 && ((int)newX - (int)'a') < 3 && (b.getBoard()[newY - 1][((int)newX - (int)'a')] == "  " || b.getBoard()[newY - 1][((int)newX - (int)'a')] == "WP"))
						{
							if(x != newX && b.getBoard()[newY-1][((int)newX - (int)'a')] == "  ")
								cout<<"wrong location"<<endl;
							else
							{
								b.getBoard()[newY-1][((int)newX - (int)'a')] = "BP";
								b.getBoard()[y-1][((int)x - (int)'a')] = "  ";
								break;
							}
						}
						else
							cout<<"wrong location"<<endl;
					}
				}
				else
					cout<<"wrong piece"<<endl;
		 }
	 }
 };

 /******************************************************************************************************/

 class CPU : public Player{
 public :
	 CPU() : Player(){} // default constructor
	 
	 CPU(const Player &p) : Player(p){}  // copy constructor
	 

	 CPU(char color) : Player('C' , color) {}  // parameterized constructor


	 ~CPU(){}  // destructor

	 void play(Board &b)
	 {
		 if(getPlayerColor() == 'B')
		 {
			 for(int i = 0; i < 3; i++)
				 for(int j = 0; j < 3; j++)
					 if(b.getBoard()[i][j] == "BP")
					 {
							 int numberOfMoves = 0;
							 if(i - 1 >= 0 &&  b.getBoard()[i-1][j] == "  ")
								 numberOfMoves++;
							 if(i - 1 >= 0 && j - 1 >= 0 && b.getBoard()[i-1][j - 1] == "WP")
								 numberOfMoves++;
							 if(i + 1 < 3 && j - 1 >= 0 && b.getBoard()[i-1][j + 1] == "WP")
								 numberOfMoves++;
							 int num = 1 + int(numberOfMoves * (rand() / (RAND_MAX + 1.0)));
							 if(num == 1)
							 {
								 if(i - 1 >= 0 &&  b.getBoard()[i-1][j] == "  ")
									 b.getBoard()[i-1][j] = "BP";
								 else if(i - 1 >= 0 && j - 1 >= 0 && b.getBoard()[i-1][j - 1] == "WP")
									 b.getBoard()[i-1][j - 1] = "BP";
								 else if(i + 1 < 3 && j - 1 >= 0 && b.getBoard()[i-1][j + 1] == "WP")
									 b.getBoard()[i-1][j + 1] = "BP";
								 b.getBoard()[i][j] = "  ";
								 return;
							 }
							 else if(num == 2)
							 {
								 if(i - 1 >= 0 && j - 1 >= 0 && b.getBoard()[i-1][j - 1] == "WP")
									 b.getBoard()[i-1][j - 1] = "BP";
								 else if(i + 1 < 3 && j - 1 >= 0 && b.getBoard()[i-1][j + 1] == "WP")
									 b.getBoard()[i-1][j + 1] = "BP";
								 b.getBoard()[i][j] = "  ";
								 return;
							 }
							 else
							 {
								 b.getBoard()[i-1][j + 1] = "BP";
								 b.getBoard()[i][j] = "  ";
								 return;
							 }

						 }
		 }
		 else
		 {
			 for(int i = 0; i < 3; i++)
				 for(int j = 0; j < 3; j++)
					 if(b.getBoard()[i][j] == "WP")
					 {
							 int numberOfMoves = 0;
							 if(i + 1 < 4 &&  b.getBoard()[i+1][j] == "  ")
								 numberOfMoves++;
							 if(i + 1 < 4 && j - 1 >= 0 && b.getBoard()[i+1][j - 1] == "BP")
								 numberOfMoves++;
							 if(i + 1 < 4 && j + 1 < 3 && b.getBoard()[i+1][j + 1] == "BP")
								 numberOfMoves++;
							 int num = 1 + int(numberOfMoves * (rand() / (RAND_MAX + 1.0)));
							 if(num == 1)
							 {
								 if(i + 1 < 4 &&  b.getBoard()[i+1][j] == "  ")
									 b.getBoard()[i+1][j] = "WP";
								 else if(i + 1 < 4 && j - 1 >= 0 && b.getBoard()[i+1][j - 1] == "BP")
									 b.getBoard()[i+1][j - 1] = "WP";
								 else if(i + 1 < 4 && j + 1 < 4 && b.getBoard()[i+1][j + 1] == "BP")
									 b.getBoard()[i+1][j + 1] = "WP";
								 b.getBoard()[i][j] = "  ";
								 return;
							 }
							 else if(num == 2)
							 {
								 if(i + 1 < 4 && j - 1 >= 0 && b.getBoard()[i+1][j - 1] == "BP")
									 b.getBoard()[i+1][j - 1] = "WP";
								 else if(i + 1 < 4 && j + 1 < 4 && b.getBoard()[i+1][j + 1] == "BP")
									 b.getBoard()[i+1][j + 1] = "WP";
								 b.getBoard()[i][j] = "  ";
								 return;
							 }
							 else
							 {
								 b.getBoard()[i+1][j + 1] = "WP";
								 b.getBoard()[i][j] = "  ";
								 return;
							 }
						 }
		 }
	 }
 };

 /******************************************************************************************************/


 int main()
 {
	 char choice;
	 cout <<"do you want to play with white ?(Y/N) : ";
	 cin>>choice;
	 choice = tolower(choice);
	 Human hPlayer;
	 CPU cpuPlayer;
	 Player currentPlayer;
	 if(choice == 'y')
	 {
		 hPlayer = Human('W');
		 cpuPlayer = CPU('B');
		 currentPlayer = hPlayer;
	 }
	 else
	 {
		 hPlayer = Human('B');
		 cpuPlayer = CPU('W');
		 currentPlayer = cpuPlayer;
	 }
	 Board b;
	 while(!b.checkWin())
	 {
		b.printBoard();
		if(currentPlayer.getPlayerType() == 'H')
		{
			hPlayer.play(b);
			currentPlayer = cpuPlayer;
		}
		else
		{
			cpuPlayer.play(b);
			currentPlayer = hPlayer;
		}
	 }
	 b.printBoard();
	 char winner = b.getWinner();
	 printf("---winner----    %c", winner);
	 if(winner == 'W' && hPlayer.getPlayerColor() == 'W')
		 cout<<"You Won"<<endl;
	 else if(winner == 'W' && hPlayer.getPlayerColor() == 'B')
		 cout<<"CPU won"<<endl;
	 else if(winner == 'B' && hPlayer.getPlayerColor() == 'B')
		 cout<<"You won"<<endl;
	 else if(winner == 'B' && hPlayer.getPlayerColor() == 'W')
		 cout<<"CPU won"<<endl;

	 return 0;
 }
