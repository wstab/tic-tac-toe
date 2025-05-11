# Tic-Tac-Toe

This program is a tic-tac-toe console game.

## Getting Started

### Installing

* Clone the repo
```
git clone https://github.com/wstab/tic-tac-toe.git
```

### Change Global Constants to configure to your needs

* Change player symbols:
```
const char symbol1 = 'X';     // player symbol option 1
const char symbol2 = 'O';     // player symbol option 2
```

* Change board size:
```
const int boardSize = 3;      // dimensions of board
```

* Change file to store board after exiting:
```
const string file = "board.txt"; // file to store board after each turn
```

### Executing program

* Run Program
* Choose how to proceed:
```
What would you like to do?
1. Play New Game
2. Display Stats
3. Quit
2
********************
Total games: 0
Draws: 0
X wins: 0
O wins: 0
********************
What would you like to do?
1. Play New Game
2. Display Stats
3. Quit
1
```
* Have player 1 choose their symbol (they will go first):
```
What symbol would you like to be? (X or O)
X
```
* Input the coordinates in which you want to place your symbol:
```
Current Board:
___
___
___
Player X, enter a row and column (0-2): 1 1
Current Board:
___
_X_
___
```
* Repeat until win or tie
