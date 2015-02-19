# include <iostream>

using namespace std;

// Constants for whose turn it is
const int PLAYER_HUMAN = 0;
const int PLAYER_COMPUTER = 1;

class Game {
  int numStones, currentPlayer;

public:
  Game(int player);
  void startGame();
  int userMove();
  int getUserInput();
  int computerMove();
  bool gameWinner();
  void displayWinner();
  void endGame();

  int getCurrentPlayer();
  void switchPlayer();
  int getNumStones();
};

// Ends the game
void Game::endGame() {
  displayWinner();
}

// Prints out a welcome message for the game
void Game::startGame() {

  cout << "Welcome to 21 stone pickup" << endl;
}

// Constructor for game
Game::Game(int player) {
  currentPlayer = player;
  numStones = 21;
}

// Returns the number of stones left in the pile
int Game::getNumStones() {
  return numStones;
}

// Switchs the current player
void Game::switchPlayer() {
  if (currentPlayer == PLAYER_COMPUTER)
    currentPlayer = PLAYER_HUMAN;
  else
    currentPlayer = PLAYER_COMPUTER;
}

// Returns who the current player is
int Game::getCurrentPlayer() {
  return currentPlayer;
}

// Asks the user what move they want to make, which must be between 1 and 3
int Game::getUserInput() {
    int stones;

    do {
        cout << "How many stones did you want to take (1 - 3)? ";
        cin >> stones;
    } while (stones < 1 || stones > 3);

    return stones;
}

// Asks the user for their move and removes the stones from the pile
int Game::userMove() {
    int stones = getUserInput();
    numStones -= stones;
    cout << "User picked up " << stones << " stone(s)" << endl;

    return stones;
}

// Returns whether there the game is over
bool Game::gameWinner() {
    return numStones == 0;
}

// Displays who the winner is
void Game::displayWinner() {
  // At the end of the last move, the players are switched one extra time
  // so we need to switch them back
  switchPlayer();

  if (currentPlayer == PLAYER_HUMAN)
      cout << "You win!" << endl;
  else
      cout << "The computer has won" << endl;
}

int Game::computerMove(){
  int computer_move;

  // If there are <= 3 stones, the computer picks them up
  if (numStones <= 3)
    computer_move = numStones;
  else {
    // Otherwise, try to get the number of stones to a multiple of 4
    computer_move = numStones % 4;

    // If computer_move is 0, that means the number of stones in the pile
    // is already a multiple of 4. But, we can't take 0 stones, so forcibly
    // take one stone.
    if(computer_move == 0)
      computer_move = 1;
  }

  numStones -= computer_move;
  cout << "Computer's move: " << computer_move << " stone(s)" << endl;

  return numStones;
}


int main()
{
  bool quit = false;

  do {
    char c;
    int first_player;

    // Ask the user if they'd like to go first
    do {
      cout << "Would you like to go first <y/n>? ";
      cin >> c;
    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');

    if (c == 'y' || c == 'Y')
      first_player = PLAYER_HUMAN;
    else
      first_player = PLAYER_COMPUTER;

    // Create a game object
    Game game(first_player);

    game.startGame();

    while (!game.gameWinner()){
      int player = game.getCurrentPlayer();

      if (player == PLAYER_HUMAN) {
        // Human's move
        game.userMove();
      }
      else {
        // Computer's move
        game.computerMove();
      }

      cout << "Stones left in the pile: " << game.getNumStones() << endl << endl;

      // Switch to the next player
      game.switchPlayer();
    }

    // Display the winner of the game
    game.endGame();

    // Ask the user if they'd like to play again
    do{
      cout << "Would you like to play again <y/n>? ";
      cin >> c;
    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');

    if(c == 'n' || c == 'N')
      quit = true;

  } while(!quit);
}
