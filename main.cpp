#include <iostream>
#include <string>
#include <fstream>
using namespace std;


const char symbol1 = 'X';        // player symbol option 1
const char symbol2 = 'O';        // player symbol option 2
const int boardSize = 3;         // dimensions of board
const string file = "board.txt"; // file to store board after each turn


/*
  Name: playGame
  PreCondition: None
  PostCondition: Manages the main game loop
*/
void playGame(char board[boardSize][boardSize]);

/*
  Name: clearBoard
  PreCondition: number of rows in board is equal to boardSize; number of columns in board is equal to boardSize
  PostCondition: Replaces the board with an empty 2D array full of placeholder characters
*/
void clearBoard(char board[boardSize][boardSize]);

/*
  Name: displayBoard
  PreCondition: number of rows in board is equal to boardSize; number of columns in board is equal to boardSize
  PostCondition: Outputs the current board
*/
void displayBoard(char board[boardSize][boardSize]);

/*
  Name: chooseSymbol
  PreCondition: None
  PostCondition: Returns the player one's symbol choice
*/
char chooseSymbol();

/*
  Name: makeMove
  PreCondition: number of rows in board is equal to boardSize; number of columns in board is equal to boardSize; player one and two have been initialized t\
o variables equivalent to their chosen character
  PostCondition: Sets player symbol equal to the element in the array with the row and column specified by user input
*/
void makeMove(char board[boardSize][boardSize], char player);

/*
  Name: checkWin
  PreCondition: number of rows in board is equal to boardSize; number of columns in board is equal to boardSize; player one and two have been initialized t\
o variables equivalent to their chosen character
  PostCondition: Returns true if there has been a win or tie and false if neither
*/
bool checkWin(char board[boardSize][boardSize], char player);

/*
  Name: saveFile
  PreCondition: number of rows in board is equal to boardSize; number of columns in board is equal to boardSize
  PostCondition: Saves board to the file proj1_data.txt
*/
void saveFile(char board[boardSize][boardSize]);

/*
  Name: calcStats
  PreCondition: gameResult must be equal to one of the symbols or 'D'; length of stats must be equal to 4 and each element must be greater than or equal to\
 0
  PostCondition: Increments the stats[0] by 1 for total games, stats[1] for Draws, stats[2] for symbol1 wins, stats[3] for symbol2 wins
*/
void calcStats(int stats[4], char gameResult);

/*
  Name: displayStats
  PreCondition: length of stats must be equal to 4 and each element must exist
  PostCondition: outputs the number of games, draws, symbol1 wins, and symbol2 wins
*/
void displayStats(int stats[4]);

int main () {
  int startChoice = 0;                   // start game, display stats, or end loop
  int stats[4] = {0,0,0,0};              // game stats from this session
  char board[boardSize][boardSize];      // main Tic-Tac-Toe board

  // make sure user selects valid option
  do {
  cout << "What would you like to do?\n1. Play New Game\n2. Display Stats\n3. Quit" << endl;
  cin >> startChoice;
  }
  while (startChoice != 1 and startChoice != 2 and startChoice != 3);

  // start main game loop as long as user doesn't choose to quit
  while (startChoice != 3) {
    if (startChoice == 1) {
      playGame(board);

      // increments elements in stats based on game outcome
      if (checkWin(board, symbol1))
        calcStats(stats, symbol1);
      else if (checkWin(board, symbol2))
        calcStats(stats, symbol2);
      else
        calcStats(stats, 'D');

      cout << "Thank you for playing Tic-Tac-Toe" << endl;
    } else {
      displayStats(stats);
    }
    // make sure user selects valid option
    do {
    cout << "What would you like to do?\n1. Play New Game\n2. Display Stats\n3. Quit" << endl;
    cin >> startChoice;
    }
    while (startChoice != 1 and startChoice != 2 and startChoice != 3);
  }

  cout << "Thank you for playing Tic-Tac-Toe" << endl;
  return 0;
}


// chooseSymbol
// Given user input, returns player symbol choice
char chooseSymbol() {
  char playerChoice;     // character for player symbol

  // filter out user input that isn't equivalent to the two symbols
  do {
    cout << "What symbol would you like to be? (" << symbol1
         << " or " << symbol2 << ")" << endl;
    cin >> playerChoice;
  }
  while (playerChoice != symbol1 and playerChoice != symbol2);

  return playerChoice;
}


// playGame
// Manages main gameplay loop
void playGame (char board[boardSize][boardSize]) {
  char player1;                     // player symbol for player1
  char player2;                     // player symbol for player2
  bool win = false;                 // should main gameplay loop end
  int moves = 0;                    // total moves of both players

  // player1 is the symbol given by user input; player2 is the other symbol
  switch (chooseSymbol()) {
    case symbol1:
      player1 = symbol1;
      player2 = symbol2;
      break;

    case symbol2:
      player1 = symbol2;
      player2 = symbol1;
      break;
  }

  // clear board and initialize each element to '_'
  clearBoard(board);
  saveFile(board);
  // loop until win
  do {
    // player1 moves
    displayBoard(board);
    makeMove(board, player1);
    saveFile(board);
    moves++;
    win = checkWin(board, player1);

    // player2 moves
    if (!win and moves != boardSize*boardSize) {
      displayBoard(board);
      makeMove(board, player2);
      saveFile(board);
      moves++;
      win = checkWin(board, player2);
    }

    // there must be a draw if the board is full and there is no win
    if (moves == boardSize * boardSize and !win) {
      displayBoard(board);
      cout << "Draw!" << endl;

      win = true;
    }
  }
  while (!win);

  // save final board after win
  saveFile(board);
}


// displayBoard
// Given the board, outputs the board for the user
void displayBoard(char board[boardSize][boardSize]) {
  cout << "Current Board:" << endl;

  // output every element in board
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++)
      cout << board[i][j];

    cout << endl;
  }
}


// makeMove
// Given the board and current player turn, sets the array element given by user to player symbol
void makeMove(char board[boardSize][boardSize], char player) {
  int yCoordinate;     // index of row that needs to be accessed
  int xCoordinate;     // index of element within row that needs to be accessed

  cout << "Player " << player << ", enter a row and column (0-" << boardSize - 1 << "): ";
  cin >> yCoordinate;
  cin >> xCoordinate;

  // handle invalid user input, where coordinates are out of bounds or space is full
  while (board[yCoordinate][xCoordinate] != '_'
         or xCoordinate < 0 or xCoordinate >= boardSize
         or yCoordinate < 0 or yCoordinate >= boardSize) {
    cout << "Invalid move. Try again." << endl;
    displayBoard(board);

    cout << "Player " << player
         << ", enter a row and column (0-" << boardSize - 1 << "): ";

    cin >> yCoordinate;
    cin >> xCoordinate;
  }

  // set element at chosen position to player symbol
  board[yCoordinate][xCoordinate] = player;
}


// checkWin
// Given the board, current player turn, and number of moves, returns true or false if there is a win or not, respectively
bool checkWin(char board[boardSize][boardSize], char player) {
  int diagonal1 = 0;     // num of consecutive player symbols in the positive diagonal direction
  int diagonal2 = 0;     // num of consecutive player symbols in the negative diagonal direction
  int horizontal;        // num of consecutive player symbols horizontally
  int vertical;          // num of consecutive player symbols vertically

  // check every array in 2D array
  for (int i = 0; i < boardSize; i++) {
    // reset consecutive player symbol count for horizontal and vertical
    horizontal = 0;
    vertical = 0;

    // check every element in array
    for (int x = 0; x < boardSize; x++){
      // add one to corresponding count for every consecutive player symbol horizontally or vertically
      if (board[i][x] == player)
        horizontal++;
      if (board[x][i] == player)
        vertical++;

      // win for sufficient num of consecutive player symbols
      if (horizontal == boardSize or vertical == boardSize) {
        displayBoard(board);
        cout << "Player " << player << " wins!" << endl;

        return true;
      }
    }

    // add one to corresponding counter for every consecutive player symbol for both diagonal directions
    if (board[boardSize-1-i][i] == player)
      diagonal1++;
    if (board[i][i] == player)
      diagonal2++;

    // win for sufficient num of consecutive player symbols
    if (diagonal1 == boardSize or diagonal2 == boardSize) {
      displayBoard(board);
      cout << "Player " << player << " wins!" << endl;

      return true;
    }
  }

  return false;
}


// saveFile
// Given the board, saves it to the proj1_data.txt file
void saveFile (char board[boardSize][boardSize]) {
  ofstream inputStream;
  inputStream.open(file);

  // writes every element of the board to the file
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++)
      inputStream << board[i][j];

    inputStream << endl;
  }

  inputStream.close();
}


// calcStats
// Given stats populated with ints and gameResult, increments element of stats with corresponding game result
void calcStats (int stats[4], char gameResult) {
  // adds one to number of games
  stats[0]++;
  switch(gameResult) {
    case 'D':
      // adds one to number of draws
      stats[1]++;
      break;
    case symbol1:
      // adds one to number of symbol1 wins
      stats[2]++;
      break;
    case symbol2:
      // adds one to number of symbol2 wins
      stats[3]++;
      break;
  }
}


// displayStats
// Given a stats, outputs the total games, draws, symbol1 wins, and symbol2 wins
void displayStats (int stats[4]) {
  cout << "********************" << endl;
  cout << "Total games: " << stats[0] << endl;
  cout << "Draws: " << stats[1] << endl;
  cout << symbol1 << " wins: " << stats[2] << endl;
  cout << symbol2 << " wins: " << stats[3] << endl;
  cout << "********************" << endl;
}
