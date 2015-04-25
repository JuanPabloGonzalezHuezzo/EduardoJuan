// Solving Problems with Programming
// Professor Ken Bauer
//
// Sudoku

// Jesús Eduardo Tostado Nieto
// A01224505
// and
// Juan Abdiel Mercado 
// A0*******

// Standard libraries
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int BOARDSIZE = 9;
const int EMPTY = 0;

bool checkrange(int number){
  if(number<0 || number>BOARDSIZE)
    {return false;}
  else{return true;}
}

//Esta función checa que el número que quiere introducir el usuario no esté repetido en la fila que eligió
bool checkrow(int number, int row, vector< vector<int> >& board){
int r=row-1;
int column;
int n=0;
bool v;

while (n<BOARDSIZE)
{
  column=board[r][n];
  if(column==number)
    {v=false;}else{v=true;}
		if(v==false){
	n=BOARDSIZE;
	}else{
		n++;
		}
}
return v;

//if(column!=number)
//{return true;}
}

//Esta función checa que el número que quiere introducir el usuario no esté repetido en la columna que eligió
bool checkcolumn(int number, int column, vector< vector<int> >& board){
int c=column-1;
int row;
int n=0;
bool v;

while (n<BOARDSIZE)
{
  row=board[n][c];
  if(row==number)
    {v=false;}else{v=true;}
	if(v==false){
	n=BOARDSIZE;
	}else{
		n++;
		}
}
return v;

//if(row!=number)
//{return true;}
}

//Codigo del writeBoard que es para poder modificar el tablero
int writeBoard(int row, int column, int n, vector< vector<int> >& board){
	int r=row-1;
	int c=column-1;
	if(board[r][c]<=EMPTY){
	board[r][c]=n;
	}else{
	cout<<"That was not a valid move. You cannot write a number in that space. Try again."<<endl;
	}
}

//Codigo del eraseBroad que es para volver la tabla a la normalidad
int eraseBoard(int row, int column, vector< vector<int> >& board_original, vector< vector<int> >& board){
	int r=row-1;
	int c=column-1;
	if(board[r][c]==board_original[r][c]){
	cout<<"That was not a valid move, try again."<<endl;
	}else{
	board[r][c]=0;
	}	
}

/*
 * creates a board filed with zeroes (empty spaces)
 * we will do this, then populate it from a file with
 * another function below
 */
void createZeroBoard(vector< vector<int> >& board){
  for(int r = 0; r < BOARDSIZE ; r++){
    // grab a full line from the file
    for(int c = 0; c < BOARDSIZE ; c++){
      board[r][c] = EMPTY;
    }
  }
}

/*
 * Populates the board from the contents of the file
 * The file must contain 9 lines with 9 values each line
 * The values must be either zero (0) for empty or values between 1 and 9
 */
void populateBoardFromFile(vector< vector<int> >& board, string filename){
  ifstream infile(filename.c_str()); // the c_str() is to convert from string to char*
  int cell;
  string line;
  if(infile.good()){
    for(int r = 0; r < BOARDSIZE ; r++){
      // grab a full line from the file
      for(int c = 0; c < BOARDSIZE ; c++){
	infile >> cell;
	board[r][c] = cell;
      }
    }
  } else {
    cout << "Something is wrong with the input file" << endl;
  }
}

/*
 * The function prints the board.
 * Each cell is a zero (for empty) or the value 1 to 9
 * Each cell is separated by a space
 * NO SPACE at end of row.
 */
void printBoard(vector< vector<int> >& board){
  // nothing for now, you will implement this for Partial 2 project delivery
  for(int r = 0; r < BOARDSIZE ; r++)
  {
    for(int c = 0; c < BOARDSIZE ; c++)
      { if(c > 0)
        { cout << " ";}
      cout << board[r][c]<<"|";
      }
    cout << endl;
    cout<<"--------------------------"<<endl;
  }
}
/*

 * Your main program goes here.
 * first get the parameters, check if parameter size is 2
 * first parameter is always the program name in C/C++
 * second parameter is the filename to read in this program
 * any other number of parameters is illegal
 */
int main(int argc, char* argv[]) {
  string filename;

  vector< vector<int> > theBoard(BOARDSIZE,vector<int>(BOARDSIZE));
  vector< vector<int> > theBoard_original(BOARDSIZE,vector<int>(BOARDSIZE));

  switch(argc)
    {
    case 1:
      cout << "Please provide the parameters to the program, you must enter a filename to initiate the Sudoku." << endl;
      exit(1);
    case 2:
      filename = argv[1];
      break;
    default:
      cout << "Please provide the parameters to the program, you must enter a filename to initiate the Sudoku." << endl;
      exit(1);
    }

  createZeroBoard(theBoard);
  populateBoardFromFile(theBoard,filename);
  theBoard_original=theBoard;

  cout << "Welcome to the Game of Sudoku" << endl;
  // Here you provide a menu to the user to do what they want
  // The options are:
  //    print (call the printBoard function)
  //    write (ask user what number they want to add and where), must accept only legal values
  //    erase (ask user which position they want to erase), must not erase original values
  //    quit (quit the program)
  string userChoice = "";
  do{
    cout << "What would you like to do (print, write, erase, quit): ";
    cin >> userChoice;
    if(userChoice == "print"){
      printBoard(theBoard);
      continue;
    }
    if(userChoice == "write"){
      // ask user for position (row,column) and number
      // check if valid (legal) and modify the board or notify that the move is invalid
  int row, column, number;
	cout<<"Give me the number of the row"<<endl;
	cin>>row;
  while(row<0 || row>=10)
    {
    cout<<"This row does not exist. Try again."<<endl;
    cout<<"Give me the number of row: "<<endl;
    cin>>row;
    }

	cout<<"Give me the number of the column"<<endl;
	cin>>column;
   while(column<0 || column>=10)
    {
    cout<<"This column does not exist. Try again."<<endl;
    cout<<"Give me the number of column: "<<endl;
    cin>>column;
    }

	cout<<"Give me the number to enter"<<endl;
	cin>>number;

  if(checkrange(number)==false)
    {cout<<"Not valid. Your number must be greater than 0 and smaller than 9."<<endl;} 
 
  else {

    if(checkrow(number, row, theBoard)==false)
    //(number, row, theBoard)==false)
     {cout<<"You can´t write that number there. There is already a "<<number<<" in this row."<<endl;}else{//writeBoard(row,column,number,theBoard);}

    //checkcolumn(number, column, theBoard);

    if(checkcolumn(number, column, theBoard)==false)
    //(number, column, theBoard)==false)
    {cout<<"You can´t write that number there. There is already a "<<number<<" in this column."<<endl;}else{writeBoard(row,column,number,theBoard);}
      }
    }
    

  //else{writeBoard(row,column,number,theBoard);}

      continue;
    }
    if(userChoice == "erase"){
      // ask user for position (row,column) to erase
      // check if valid (legal) and modify the board or notify that the move is invalid
	int row, column;
	cout<<"Give me the number of the row"<<endl;
	cin>>row;
	cout<<"Give me the number of the column"<<endl;
	cin>>column;
	eraseBoard(row,column,theBoard_original,theBoard);
	
      continue;
    }
    if(userChoice == "quit"){
      cout << "Thanks for playing our game, have a great day!" << endl;
      continue;
    }
    cout << "That was not a valid choice, try again." << endl;
  } while (userChoice != "quit");
  return 0;
}
