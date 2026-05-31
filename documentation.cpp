
// MAZE GENERATION

Level sensitivity:
   bool shouldChasePlayer = true;  // You can set this flag based on the game conditions
    int chaseDistanceThreshold = 5; // Distance threshold for chasing player
 
// General  -------------------------------------------------------------------------------------------------------
int main() {
    int width = 21;  // Maze width (must be odd)
    int height = 21; // Maze height (must be odd)
    vector<vector<int>> maze;

    generateMaze(width, height, maze);

    // Player's starting position (top-left corner of the maze)
    Player player(1, 1);

    // Mark the player's starting position as a path if not already
    if (maze[player.y][player.x] == WALL) maze[player.y][player.x] = PATH;

    // Randomly place enemies
    vector<Enemy> enemies;

       char input;
    while (true) {
        system("cls");  // Clear the console (Windows-specific)
        printMaze(maze, player, enemies);

        cout << "Use WASD to move. Press 'Q' to quit.\n";
        input = _getch();  // Read input without needing to press Enter

        if (input == 'q' || input == 'Q') break; // Quit the game

        // Process player movement based on WASD keys
        int newX = player.x, newY = player.y;
        if (input == 'w' || input == 'W') newY--;  // Move up
        else if (input == 's' || input == 'S') newY++;  // Move down
        else if (input == 'a' || input == 'A') newX--;  // Move left
        else if (input == 'd' || input == 'D') newX++;  // Move right

        // Check if the move is valid (i.e., not into a wall)
        if (isValidMove(newX, newY, maze)) {
            player.x = newX;
            player.y = newY;
        }
    }
  return 0;
}
//OTHERS 
input = _getch();  // Read input without needing to press Enter

// MG1 ------------------------------------------------------------------------------------------------------------------------
//(Maze generation using PRIM)
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WALL = 1;
const int PATH = 0;

struct Cell {
    int x, y;
    Cell(int _x, int _y) : x(_x), y(_y) {}
};

vector<Cell> getNeighbors(int x, int y, const vector<vector<int>>& maze) {
    vector<Cell> neighbors;
    int height = maze.size();
    int width = maze[0].size();

    // Check in 4 directions (top, bottom, left, right)
    if (x > 1 && maze[y][x - 2] == WALL) neighbors.push_back(Cell(x - 2, y)); // Left
    if (x < width - 2 && maze[y][x + 2] == WALL) neighbors.push_back(Cell(x + 2, y)); // Right
    if (y > 1 && maze[y - 2][x] == WALL) neighbors.push_back(Cell(x, y - 2)); // Up
    if (y < height - 2 && maze[y + 2][x] == WALL) neighbors.push_back(Cell(x, y + 2)); // Down

    return neighbors;
}

void generateMaze(int width, int height) {
    // Ensure odd width and height for proper wall placement
    if (width % 2 == 0) width++;
    if (height % 2 == 0) height++;

    // Initialize the maze with all walls
    vector<vector<int>> maze(height, vector<int>(width, WALL));

    // Random starting point
    srand(time(0));
    int startX = (rand() % (width / 2)) * 2 + 1;
    int startY = (rand() % (height / 2)) * 2 + 1;

    // Mark the starting cell as a path
    maze[startY][startX] = PATH;

    // List of walls (pairs of cells)
    vector<Cell> walls;
    walls.push_back(Cell(startX, startY));

    // Process walls
    while (!walls.empty()) {
        // Pick a random wall
        int randIndex = rand() % walls.size();
        Cell wall = walls[randIndex];

        // Get the neighbors of the current cell
        vector<Cell> neighbors = getNeighbors(wall.x, wall.y, maze);

        if (!neighbors.empty()) {
            // Pick a random neighboring cell
            Cell neighbor = neighbors[rand() % neighbors.size()];

            // Remove the wall between the current cell and the neighbor
            int midX = (wall.x + neighbor.x) / 2;
            int midY = (wall.y + neighbor.y) / 2;

            maze[midY][midX] = PATH;   // Remove wall between
            maze[neighbor.y][neighbor.x] = PATH;  // Make the neighbor a path

            // Add the neighboring cell's walls to the list
            walls.push_back(neighbor);
        } else {
            // If no neighbors, remove the wall from the list
            walls.erase(walls.begin() + randIndex);
        }
    }

    // Print the maze
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cout << (maze[y][x] == WALL ? "#" : " ");
        }
        cout << endl;
    }
}

int main() {
    int width = 21;  // Maze width (must be odd)
    int height = 21; // Maze height (must be odd)

    generateMaze(width, height);

    return 0;
}
//------------------------------------------------------------------------------------------------------------------------
//ADD PLAYER
//AP1
//(Add player, Takes Player movement  (do not need to press enter), Press 'Q' to quit)

#include <conio.h>  // For _getch() to read player input (Windows only)

//1) Adding a Player Struct
struct Player {
    int x, y;  // Player's position

    Player(int startX, int startY) : x(startX), y(startY) {}
};

//2) Player Initialization
// Player's starting position (top-left corner of the maze)
Player player(1, 1);
// Mark the player's starting position as a path if not already
if (maze[player.y][player.x] == WALL) maze[player.y][player.x] = PATH;

//3) Player Movement Logic using WASD:
void handlePlayerMovement(Player& player, char input, const vector<vector<int>>& maze) {
    // Store the player's current position
    int newX = player.x, newY = player.y;

    // Determine the direction based on input
    if (input == 'w' || input == 'W') newY--;  // Move up
    else if (input == 's' || input == 'S') newY++;  // Move down
    else if (input == 'a' || input == 'A') newX--;  // Move left
    else if (input == 'd' || input == 'D') newX++;  // Move right

    // Check if the new position is valid (not a wall, within bounds)
    if (isValidMove(newX, newY, maze)) {
        // Update the player's position if the move is valid
        player.x = newX;
        player.y = newY;
    } else {
        cout << "Invalid move. Try a different direction.\n";
    }
}

char input;
while (true) {
    system("cls");  // Clear the console (Windows-specific)
    printMaze(maze, player);

    cout << "Use WASD to move. Press 'Q' to quit.\n";
    input = _getch();  // Read input without needing to press Enter

    if (input == 'q' || input == 'Q') break; // Quit the game

   // Handle player movement using the abstracted function
        handlePlayerMovement(player, input, maze);

}

//4) Modified printMaze Function - to show the player's position:
void printMaze(const vector<vector<int>>& maze, const Player& player) {
    for (int y = 0; y < maze.size(); y++) {
        for (int x = 0; x < maze[y].size(); x++) {
            if (x == player.x && y == player.y) {
                cout << PLAYER;  // Display player
            } else {
                cout << (maze[y][x] == WALL ? '#' : ' ');
            }
        }
        cout << endl;
    }
}

//5) Function to check if the player can move to a new position:
bool isValidMove(int x, int y, const vector<vector<int>>& maze) {
    return x >= 0 && x < maze[0].size() && y >= 0 && y < maze.size() && maze[y][x] == PATH;
}
//------------------------------------------------------------------------------------------------------------------------
//ADD ENEMY
//AE1 (Add enemy(struct), custom number of enemy, display enemy, enemy movement, AI-chase player , add into maze)

#include <conio.h>  // For _getch() to read player input (Windows only)

//1) New Struct for Enemy:
struct Enemy {
    int x, y;  // Enemy's position
    static int numEnemies;  // Static variable to track number of enemies
    Enemy(int startX, int startY) : x(startX), y(startY) {}
};
int Enemy::numEnemies = 1;  // Initialize the static member outside the class, default 1 enemy

//2) Changes to printMaze to Display Enemies:
void printMaze(const vector<vector<int>>& maze, const Player& player, const vector<Enemy>& enemies) {
    for (int y = 0; y < maze.size(); y++) {
        for (int x = 0; x < maze[y].size(); x++) {
            bool isEnemyHere = false;
            for (const auto& enemy : enemies) {
                if (x == enemy.x && y == enemy.y) {
                    cout << ENEMY;
                    isEnemyHere = true;
                    break;
                }
            }
            if (!isEnemyHere) {
                if (x == player.x && y == player.y) {
                    cout << PLAYER;  // Display player
                } else {
                    cout << (maze[y][x] == WALL ? '#' : ' ');
                }
            }
        }
        cout << endl;
    }
}

//3) Functions to Handle Enemy Movement - Random Enemy Movement:
void moveEnemyRandom(Enemy& enemy, const vector<vector<int>>& maze) {
    int direction = rand() % 4; // 0 = up, 1 = down, 2 = left, 3 = right
    int newX = enemy.x, newY = enemy.y;

    if (direction == 0 && isValidMove(enemy.x, enemy.y - 1, maze)) newY--;
    else if (direction == 1 && isValidMove(enemy.x, enemy.y + 1, maze)) newY++;
    else if (direction == 2 && isValidMove(enemy.x - 1, enemy.y, maze)) newX--;
    else if (direction == 3 && isValidMove(enemy.x + 1, enemy.y, maze)) newX++;

    enemy.x = newX;
    enemy.y = newY;
}

//4) AI Movement to Chase Player:
void moveEnemyTowardsPlayer(Enemy& enemy, const Player& player, const vector<vector<int>>& maze) {
    int newX = enemy.x, newY = enemy.y;

    if (player.x < enemy.x && isValidMove(enemy.x - 1, enemy.y, maze)) newX--;
    else if (player.x > enemy.x && isValidMove(enemy.x + 1, enemy.y, maze)) newX++;
    if (player.y < enemy.y && isValidMove(enemy.x, enemy.y - 1, maze)) newY--;
    else if (player.y > enemy.y && isValidMove(enemy.x, enemy.y + 1, maze)) newY++;

    enemy.x = newX;
    enemy.y = newY;
}

//5) Adding Enemies and Moving Them in the Game Loop:
// Randomly place enemies
vector<Enemy> enemies;
for (int i = 0; i < Enemy::numEnemie; i++) {
    int enemyX, enemyY;
    do {
        enemyX = (rand() % (width - 2)) + 1;
        enemyY = (rand() % (height - 2)) + 1;
    } while (maze[enemyY][enemyX] != PATH || (enemyX == player.x && enemyY == player.y));

    enemies.push_back(Enemy(enemyX, enemyY));
}
// Move enemies (random or AI)
for (auto& enemy : enemies) {
    // You can toggle between random and AI movement for enemies
    // moveEnemyRandom(enemy, maze);  // Random movement
    moveEnemyTowardsPlayer(enemy, player, maze);  // AI movement towards player
}

//PUZZLE --------------------------------------------------------------------
//PZ1
//1) Puzzle struct
const char PUZZLE = 'Q';
struct Puzzle {
    int x, y;
    bool solved;
    Puzzle(int startX, int startY) : x(startX), y(startY), solved(false) {}
};

//2)Print puzzle to maze : "Q"= unsolved puzzle, solved & player = P, solved & no player = " "
void printMaze(const vector<vector<int>>& maze, const Player& player, const vector<Enemy>& enemies, const vector<Puzzle>& puzzles) {    
    for (int y = 0; y < maze.size(); y++) {
        for (int x = 0; x < maze[y].size(); x++) {
            bool isEnemyHere = false;
            bool isPuzzleHere = false;

            // Check if an enemy is at the current position
            for (const auto& enemy : enemies) {
                if (x == enemy.x && y == enemy.y) {
                    cout << ENEMY;
                    isEnemyHere = true;
                    break;
                }
            }

            // Check if a puzzle is at the current position
            for (const auto& puzzle : puzzles) {
                if (x == puzzle.x && y == puzzle.y) {
                    isPuzzleHere = true;

                // If the puzzle is solved, print a space
                if (puzzle.solved) {         
                    // Player on solved puzzle
                    if (player.x == puzzle.x && player.y == puzzle.y) {
                        cout << PLAYER;
                    // Player not on solved puzzle
                    } else {
                        cout << ' ';
                    }
                    //puzzle.solved == false
                } else {
                        cout << PUZZLE;  // Print puzzle if player is not there
                    }
                    break;
                }
            }

            // If no enemy or puzzle is here, check if the player is here
            if (!isEnemyHere && !isPuzzleHere) {
                if (x == player.x && y == player.y) {
                    cout << PLAYER;  // Display player
                } else {
                    cout << (maze[y][x] == WALL ? '#' : ' ');  // Wall or empty space
                }
            }
        }
        cout << endl;
    }
}

//3) Update isValidMove : So enemies & player cannot move when puzzle is not solved
bool isValidMove(int x, int y, const vector<vector<int>>& maze, vector<Puzzle>& puzzles) {
// Check if the move is within bounds and the position is a path
if (x >= 0 && x < maze[0].size() && y >= 0 && y < maze.size() && maze[y][x] == PATH){

    // Check if the move is within bounds and the position is a path or an unsolved puzzle
    for (const auto& puzzle : puzzles) {
        if (x == puzzle.x && y == puzzle.y){
            // If the puzzle is unsolved, block the move
            if (!puzzle.solved) {
                return false;
            } else { 
                return true;
            } 
        }
    } 
    // If no puzzle is at this position, return true since it's a valid path
    return true;
 } 
    // Return false if the position is out of bounds or not a valid path
    return false;
}
//4) Update Enemy movement: Consider unsolved puzzle in movement
void moveEnemyRandom(Enemy& enemy, const vector<vector<int>>& maze, vector<Puzzle>& puzzles) {
    //...
    //if (direction == 0 && isValidMove(enemy.x, enemy.y - 1, maze, puzzles)
   // ...
}
void moveEnemyTowardsPlayer(Enemy& enemy, const Player& player, const vector<vector<int>>& maze, vector<Puzzle>& puzzles) {
   //...
   if (player.x < enemy.x && isValidMove(enemy.x - 1, enemy.y, maze, puzzles)) newX--;
   //...
}

//5) When player attempt to enter Puzzle cell, Puzzle game is call and puzzle solved status is updated accordingly
void checkAndSolvePuzzle(Player& player, vector<Puzzle>& puzzles, vector<vector<int>>& maze, int newX, int newY ) { 
    
   for (auto& puzzle : puzzles) {
        // If the puzzle is unsolved, prompt the player to solve it
        if (newX == puzzle.x && newY == puzzle.y && !puzzle.solved) {
            cout << "2You've encountered a puzzle! Solve it to proceed.\n";
            bool puzzleSolved = solvePuzzle();  // Call the solvePuzzle function from puzzleList.cpp

            if (puzzleSolved == true) {
                puzzle.solved = true;
                cout << "You solved the puzzle! You can now proceed.\n";
            } else {
                // Restore the player's previous position if they fail
                cout << "You failed to solve the puzzle. The puzzle remains locked." << endl;
            }
            return;  // Exit after handling the puzzle at this position
        }
   }
}

//6) Do not let player move into unsloved Puzzle cell and call check & slove Puzzle function 
void handlePlayerMovement(Player& player, char input, vector<vector<int>>& maze, vector<Puzzle>& puzzles, bool& validMove) {

    // Store the player's current position
    int newX = player.x, newY = player.y;

    // Determine the direction based on input
    if (input == 'w' || input == 'W') newY--;  // Move up
    else if (input == 's' || input == 'S') newY++;  // Move down
    else if (input == 'a' || input == 'A') newX--;  // Move left
    else if (input == 'd' || input == 'D') newX++;  // Move right

    // Check if the new position is valid (not a wall, within bounds)
    if (isValidMove(newX, newY, maze, puzzles)) { 
        // Update the player's position if the move is valid
        player.x = newX; // newX after increment
        player.y = newY;
        validMove = true;
    } else {
        bool foundUnsolvedPuzzle = false;
        for (const auto& puzzle : puzzles) {
            if (newX == puzzle.x && newY == puzzle.y && !puzzle.solved) {
                foundUnsolvedPuzzle = true;
                cout << "There's an unsolved puzzle here. Solve it first!\n";
                // Check if the player encounters a puzzle
                checkAndSolvePuzzle(player, puzzles, maze, newX, newY);
                break;  // Exit the loop after attempting to solve the puzzles
            }
        } 
        // If no valid move was made, display an invalid move message
        if (!foundUnsolvedPuzzle) {
            validMove = false;
            cout << "Invalid move. Try a different direction.\n";
        }
   }
}

// 7) Update main function
int main() {
    //...

    // Randomly place puzzles
    vector<Puzzle> puzzles;
    int numPuzzles = 10;
    for (int i = 0; i < numPuzzles; i++) {
        int puzzleX, puzzleY;
        do {
            puzzleX = (rand() % (width - 2)) + 1;
            puzzleY = (rand() % (height - 2)) + 1;
        } while (maze[puzzleY][puzzleX] != PATH || (puzzleX == player.x && puzzleY == player.y));

        puzzles.push_back(Puzzle(puzzleX, puzzleY));
    }

    char input;
    bool gameOver = false;
    bool validMove = true;
    while (!gameOver) {

        system("cls");  // Clear the console (Windows-specific)
        printMaze(maze, player, enemies, puzzles);
        cout << "Use WASD to move. Press 'Q' to quit.\n";

        if (!validMove){ // if previous was an invalid move add on this line
        cout << "Invalid move. Try a different direction.\n";
        }
        
        input = _getch();  // Read input without needing to press Enter

        if (input == 'q' || input == 'Q') break; // Quit the game

        // Handle player movement using the abstracted function
        handlePlayerMovement(player, input, maze, puzzles, validMove);

        // Check if player encounters a puzzle
        //checkAndSolvePuzzle(player, puzzles, maze, player.x, player.y);
        
        // Move enemies (random or AI)
        for (auto& enemy : enemies) {
            // You can toggle between random and AI movement for enemies
            moveEnemyRandom(enemy, maze, puzzles);  // Random movement
            moveEnemyTowardsPlayer(enemy, player, maze, puzzles);  // AI movement towards player
        }
    }
    return 0;
}

//PZ2 Version 1 of Puzzle for Backup
 // Simple puzzle solving function (example: word puzzle)
 bool solveWordPuzzle() {
    string answer;
    cout << "Solve the puzzle: What is the capital of France? ";
    cin >> answer;
    return answer == "Paris";
 }
 // Check if the player is on a puzzle and solve it
 void checkAndSolvePuzzle(Player& player, vector<Puzzle>& puzzles, vector<vector<int>>& maze) {
    for (auto& puzzle : puzzles) {
        if (player.x == puzzle.x && player.y == puzzle.y && !puzzle.solved) {
            cout << "You've encountered a puzzle! Solve it to proceed.\n";

            if (solveWordPuzzle()) {
                cout << "Puzzle solved! Path unlocked.\n";
                puzzle.solved = true;
                maze[puzzle.y][puzzle.x] = PATH;  // Unlock the path
            } else {
                cout << "Wrong answer. Try again later.\n";
            }
        }
    }
 }

 //4) Update Main
 vector<Puzzle> puzzles;
    int numPuzzles = 2;
    for (int i = 0; i < numPuzzles; i++) {
        int puzzleX, puzzleY;
        do {
            puzzleX = (rand() % (width - 2)) + 1;
            puzzleY = (rand() % (height - 2)) + 1;
        } while (maze[puzzleY][puzzleX] != PATH || (puzzleX == player.x && puzzleY == player.y));

        puzzles.push_back(Puzzle(puzzleX, puzzleY));
    }

    char input;
    bool gameOver = false;
    while (!gameOver) {
        system("cls");  // Clear the console (Windows-specific)
        printMaze(maze, player, enemies, puzzles);
 //...
}

/* With puzzle: base code diff
 #include <iostream>
 #include <vector>
 #include <cstdlib>
 #include <ctime>
 using namespace std;

 // Constants for maze representation
 const int WALL = 1;
 const int PATH = 0;

 // Player struct
 struct Player {
    int x, y;
    Player(int startX, int startY) : x(startX), y(startY) {}
 };

 // Enemy struct
 struct Enemy {
    int x, y;
    static int numEnemies;  // Static variable for number of enemies
    Enemy(int startX, int startY) : x(startX), y(startY) {}
 };
 
 // Define static variable for number of enemies
 int Enemy::numEnemies = 1;  // Default 1 enemy

 // Puzzle struct
 struct Puzzle {
    int x, y;
    bool solved;
    Puzzle(int startX, int startY) : x(startX), y(startY), solved(false) {}
 };

 // Function to generate the maze using Prim's algorithm (simplified version)
 void generateMaze(int width, int height, vector<vector<int>>& maze) {
    maze.resize(height, vector<int>(width, WALL));
    for (int y = 1; y < height - 1; y += 2) {
        for (int x = 1; x < width - 1; x += 2) {
            maze[y][x] = PATH;
            if (rand() % 2 == 0 && x + 1 < width - 1) maze[y][x + 1] = PATH;
            else if (y + 1 < height - 1) maze[y + 1][x] = PATH;
        }
    }
 }

 // Function to print the maze
 void printMaze(const vector<vector<int>>& maze, const Player& player, const vector<Enemy>& enemies, const vector<Puzzle>& puzzles) {
    for (int y = 0; y < maze.size(); y++) {
        for (int x = 0; x < maze[y].size(); x++) {
            bool isEnemyHere = false;
            bool isPuzzleHere = false;

            // Check if an enemy is in the current position
            for (const auto& enemy : enemies) {
                if (x == enemy.x && y == enemy.y) {
                    cout << 'E';  // Display enemy
                    isEnemyHere = true;
                    break;
                }
            }

            // Check if a puzzle is in the current position
            for (const auto& puzzle : puzzles) {
                if (x == puzzle.x && y == puzzle.y) {
                    if (!puzzle.solved)
                        cout << 'Q';  // Display puzzle if not solved
                    else
                        cout << ' ';  // Empty space if solved
                    isPuzzleHere = true;
                    break;
                }
            }

            if (!isEnemyHere && !isPuzzleHere) {
                if (x == player.x && y == player.y) {
                    cout << 'P';  // Display player
                } else {
                    cout << (maze[y][x] == WALL ? '#' : ' ');
                }
            }
        }
        cout << endl;
    }
 }

 // Function to move the player using WASD
 void movePlayer(Player& player, const vector<vector<int>>& maze) {
    char input;
    cout << "Move (WASD): ";
    cin >> input;
    //input = _getch();  // Read input without needing to press Enter

    int newX = player.x;
    int newY = player.y;

    if (input == 'W' || input == 'w') newY--;
    else if (input == 'A' || input == 'a') newX--;
    else if (input == 'S' || input == 's') newY++;
    else if (input == 'D' || input == 'd') newX++;

    if (maze[newY][newX] == PATH) {  // Move if the new position is a path
        player.x = newX;
        player.y = newY;
    }
 }

 // Simple puzzle solving function (example: word puzzle)
 bool solveWordPuzzle() {
    string answer;
    cout << "Solve the puzzle: What is the capital of France? ";
    cin >> answer;
    return answer == "Paris";
 }

 // Check if the player is on a puzzle and solve it
 void checkAndSolvePuzzle(Player& player, vector<Puzzle>& puzzles, vector<vector<int>>& maze) {
    for (auto& puzzle : puzzles) {
        if (player.x == puzzle.x && player.y == puzzle.y && !puzzle.solved) {
            cout << "You've encountered a puzzle! Solve it to proceed.\n";

            if (solveWordPuzzle()) {
                cout << "Puzzle solved! Path unlocked.\n";
                puzzle.solved = true;
                maze[puzzle.y][puzzle.x] = PATH;  // Unlock the path
            } else {
                cout << "Wrong answer. Try again later.\n";
            }
        }
    }
 }

 // Function to move the enemy randomly or towards the player
 void moveEnemy(Enemy& enemy, const Player& player, const vector<vector<int>>& maze) {
    int dx = player.x - enemy.x;
    int dy = player.y - enemy.y;

    if (abs(dx) + abs(dy) < 5) {  // If the player is close, use simple chasing
        if (abs(dx) > abs(dy)) {
            enemy.x += (dx > 0) ? 1 : -1;
        } else {
            enemy.y += (dy > 0) ? 1 : -1;
        }
    } else {  // Otherwise, move randomly
        int dir = rand() % 4;
        int newX = enemy.x;
        int newY = enemy.y;

        if (dir == 0) newY--;
        else if (dir == 1) newY++;
        else if (dir == 2) newX--;
        else newX++;

        if (maze[newY][newX] == PATH) {  // Move only if the new position is a path
            enemy.x = newX;
            enemy.y = newY;
        }
    }
 } 

 // Main function
 int main() {
    srand(time(0));

    // Set up maze dimensions
    int width = 15, height = 10;

    // Generate maze
    vector<vector<int>> maze;
    generateMaze(width, height, maze);

    // Create player and randomly place enemies
    Player player(1, 1);
    Enemy::numEnemies = 3;  // Adjust number of enemies based on the level
    vector<Enemy> enemies;
    for (int i = 0; i < Enemy::numEnemies; i++) {
        int enemyX, enemyY;
        do {
            enemyX = (rand() % (width - 2)) + 1;
            enemyY = (rand() % (height - 2)) + 1;
        } while (maze[enemyY][enemyX] != PATH || (enemyX == player.x && enemyY == player.y));

        enemies.push_back(Enemy(enemyX, enemyY));
    }

    // Randomly place puzzles
    vector<Puzzle> puzzles;
    int numPuzzles = 2;
    for (int i = 0; i < numPuzzles; i++) {
        int puzzleX, puzzleY;
        do {
            puzzleX = (rand() % (width - 2)) + 1;
            puzzleY = (rand() % (height - 2)) + 1;
        } while (maze[puzzleY][puzzleX] != PATH || (puzzleX == player.x && puzzleY == player.y));

        puzzles.push_back(Puzzle(puzzleX, puzzleY));
    }

    // Game loop
    bool gameOver = false;
    while (!gameOver) {
         system("cls");  // Clear the console (Windows-specific)
        // Print the maze
        printMaze(maze, player, enemies, puzzles);

        // Move the player
        movePlayer(player, maze);

        // Check if player encounters a puzzle
        checkAndSolvePuzzle(player, puzzles, maze);

        // Move enemies
        for (auto& enemy : enemies) {
            moveEnemy(enemy, player, maze);
        }

        // Check game over conditions, etc.
    }

    return 0;
 }
 //*/

/* BASE CODE

 #include <iostream>
 #include <vector>
 #include <cstdlib>
 #include <ctime>
 #include <conio.h>  // For _getch() to read player input (Windows only)

 using namespace std;

 const int WALL = 1;
 const int PATH = 0;
 const char PLAYER = 'P';
 const char ENEMY = 'E';

 struct Cell {
    int x, y;
    Cell(int _x, int _y) : x(_x), y(_y) {}
 };

 struct Player {
    int x, y;  // Player's position

    Player(int startX, int startY) : x(startX), y(startY) {}
 };

 struct Enemy {
    int x, y;  // Enemy's position
    static int numEnemies;  // Static variable to track number of enemies

    Enemy(int startX, int startY) : x(startX), y(startY) {
    }
 };

 int Enemy::numEnemies = 1;  // Initialize the static member outside the class, Deafult 1 enemy


 vector<Cell> getNeighbors(int x, int y, const vector<vector<int>>& maze) {
    vector<Cell> neighbors;
    int height = maze.size();
    int width = maze[0].size();

    // Check in 4 directions (top, bottom, left, right)
    if (x > 1 && maze[y][x - 2] == WALL) neighbors.push_back(Cell(x - 2, y)); // Left
    if (x < width - 2 && maze[y][x + 2] == WALL) neighbors.push_back(Cell(x + 2, y)); // Right
    if (y > 1 && maze[y - 2][x] == WALL) neighbors.push_back(Cell(x, y - 2)); // Up
    if (y < height - 2 && maze[y + 2][x] == WALL) neighbors.push_back(Cell(x, y + 2)); // Down

    return neighbors;
 }

 void printMaze(const vector<vector<int>>& maze, const Player& player, const vector<Enemy>& enemies) {
    for (int y = 0; y < maze.size(); y++) {
        for (int x = 0; x < maze[y].size(); x++) {
            bool isEnemyHere = false;
            for (const auto& enemy : enemies) {
                if (x == enemy.x && y == enemy.y) {
                    cout << ENEMY;
                    isEnemyHere = true;
                    break;
                }
            }
            if (!isEnemyHere) {
                if (x == player.x && y == player.y) {
                    cout << PLAYER;  // Display player
                } else {
                    cout << (maze[y][x] == WALL ? '#' : ' ');
                }
            }
        }
        cout << endl;
    }
 }

 void generateMaze(int width, int height, vector<vector<int>>& maze) {
    // Ensure odd width and height for proper wall placement
    if (width % 2 == 0) width++;
    if (height % 2 == 0) height++;

    // Initialize the maze with all walls
    maze.assign(height, vector<int>(width, WALL));

    // Random starting point
    srand(time(0));
    int startX = (rand() % (width / 2)) * 2 + 1;
    int startY = (rand() % (height / 2)) * 2 + 1;

    // Mark the starting cell as a path
    maze[startY][startX] = PATH;

    // List of walls (pairs of cells)
    vector<Cell> walls;
    walls.push_back(Cell(startX, startY));

    // Process walls
    while (!walls.empty()) {
        // Pick a random wall
        int randIndex = rand() % walls.size();
        Cell wall = walls[randIndex];

        // Get the neighbors of the current cell
        vector<Cell> neighbors = getNeighbors(wall.x, wall.y, maze);

        if (!neighbors.empty()) {
            // Pick a random neighboring cell
            Cell neighbor = neighbors[rand() % neighbors.size()];

            // Remove the wall between the current cell and the neighbor
            int midX = (wall.x + neighbor.x) / 2;
            int midY = (wall.y + neighbor.y) / 2;

            maze[midY][midX] = PATH;   // Remove wall between
            maze[neighbor.y][neighbor.x] = PATH;  // Make the neighbor a path

            // Add the neighboring cell's walls to the list
            walls.push_back(neighbor);
        } else {
            // If no neighbors, remove the wall from the list
            walls.erase(walls.begin() + randIndex);
        }
    }
 }

 bool isValidMove(int x, int y, const vector<vector<int>>& maze) {
    return x >= 0 && x < maze[0].size() && y >= 0 && y < maze.size() && maze[y][x] == PATH;
 } 

 // Function for random enemy movement
 void moveEnemyRandom(Enemy& enemy, const vector<vector<int>>& maze) {
    int direction = rand() % 4; // 0 = up, 1 = down, 2 = left, 3 = right
    int newX = enemy.x, newY = enemy.y;

    if (direction == 0 && isValidMove(enemy.x, enemy.y - 1, maze)) newY--;
    else if (direction == 1 && isValidMove(enemy.x, enemy.y + 1, maze)) newY++;
    else if (direction == 2 && isValidMove(enemy.x - 1, enemy.y, maze)) newX--;
    else if (direction == 3 && isValidMove(enemy.x + 1, enemy.y, maze)) newX++;

    enemy.x = newX;
    enemy.y = newY;
 }

 // Simple AI to move enemy towards the player
 void moveEnemyTowardsPlayer(Enemy& enemy, const Player& player, const vector<vector<int>>& maze) {
    int newX = enemy.x, newY = enemy.y;

    if (player.x < enemy.x && isValidMove(enemy.x - 1, enemy.y, maze)) newX--;
    else if (player.x > enemy.x && isValidMove(enemy.x + 1, enemy.y, maze)) newX++;
    if (player.y < enemy.y && isValidMove(enemy.x, enemy.y - 1, maze)) newY--;
    else if (player.y > enemy.y && isValidMove(enemy.x, enemy.y + 1, maze)) newY++;

    enemy.x = newX;
    enemy.y = newY;
 }

 int main() {
    int width = 21;  // Maze width (must be odd)
    int height = 21; // Maze height (must be odd)
    vector<vector<int>> maze;

    generateMaze(width, height, maze);

    // Player's starting position (top-left corner of the maze)
    Player player(1, 1);

    // Mark the player's starting position as a path if not already
    if (maze[player.y][player.x] == WALL) maze[player.y][player.x] = PATH;

    // Randomly place enemies
    vector<Enemy> enemies;
    
    for (int i = 0; i < Enemy::numEnemies; i++) {
        int enemyX, enemyY;
        do {
            enemyX = (rand() % (width - 2)) + 1;
            enemyY = (rand() % (height - 2)) + 1;
        } while (maze[enemyY][enemyX] != PATH || (enemyX == player.x && enemyY == player.y));

        enemies.push_back(Enemy(enemyX, enemyY));
    }

    char input;
    while (true) {
        system("cls");  // Clear the console (Windows-specific)
        printMaze(maze, player, enemies);

        cout << "Use WASD to move. Press 'Q' to quit.\n";
        input = _getch();  // Read input without needing to press Enter

        if (input == 'q' || input == 'Q') break; // Quit the game

        // Process player movement based on WASD keys
        int newX = player.x, newY = player.y;
        if (input == 'w' || input == 'W') newY--;  // Move up
        else if (input == 's' || input == 'S') newY++;  // Move down
        else if (input == 'a' || input == 'A') newX--;  // Move left
        else if (input == 'd' || input == 'D') newX++;  // Move right

        // Check if the move is valid (i.e., not into a wall)
        if (isValidMove(newX, newY, maze)) {
            player.x = newX;
            player.y = newY;
        }

        // Move enemies (random or AI)
        for (auto& enemy : enemies) {
            // You can toggle between random and AI movement for enemies
            // moveEnemyRandom(enemy, maze);  // Random movement
            moveEnemyTowardsPlayer(enemy, player, maze);  // AI movement towards player
        }
    }

    return 0;
 }

*/

//FINALISED


 /*
  #include <iostream>
 #include <vector>
 #include <cstdlib>
 #include <ctime>
 #include <conio.h>  // For _getch() to read player input (Windows only)
 #include "puzzleList.cpp"  // Include puzzle menu and functions

 using namespace std;

 const int WALL = 1;
 const int PATH = 0;
 const char PLAYER = 'P';
 const char ENEMY = 'E';
 const char PUZZLE = 'Q';
 const char ITEM = 'X';

 struct Cell {
    int x, y;
    Cell(int _x, int _y) : x(_x), y(_y) {}
 };

 struct Player {
    int x, y;  // Player's position

    Player(int startX, int startY) : x(startX), y(startY) {}
 };

 struct Enemy {
    int x, y;  // Enemy's position
    static int numEnemies;  // Static variable to track number of enemies

    Enemy(int startX, int startY) : x(startX), y(startY) {
    }
 };

 struct Puzzle {
    int x, y;
    bool solved;
    Puzzle(int startX, int startY) : x(startX), y(startY), solved(false) {}
 };

 struct Item {
    int x, y;
    string name;

    Item(int startX, int startY, const string& itemName) : x(startX), y(startY), name(itemName) {}
 };


 int Enemy::numEnemies = 1;  // Initialize the static member outside the class, Deafult 1 enemy

 vector<Cell> getNeighbors(int x, int y, const vector<vector<int>>& maze) {
    vector<Cell> neighbors;
    int height = maze.size();
    int width = maze[0].size();

    // Check in 4 directions (top, bottom, left, right)
    if (x > 1 && maze[y][x - 2] == WALL) neighbors.push_back(Cell(x - 2, y)); // Left
    if (x < width - 2 && maze[y][x + 2] == WALL) neighbors.push_back(Cell(x + 2, y)); // Right
    if (y > 1 && maze[y - 2][x] == WALL) neighbors.push_back(Cell(x, y - 2)); // Up
    if (y < height - 2 && maze[y + 2][x] == WALL) neighbors.push_back(Cell(x, y + 2)); // Down

    return neighbors;
 }
 /* OLD
 void printMaze(const vector<vector<int>>& maze, const Player& player, const vector<Enemy>& enemies, const vector<Puzzle>& puzzles) {
    for (int y = 0; y < maze.size(); y++) {
        for (int x = 0; x < maze[y].size(); x++) {
            bool isEnemyHere = false;
            bool isPuzzleHere = false;

            // Check if an enemy is at the current position
            for (const auto& enemy : enemies) {
                if (x == enemy.x && y == enemy.y) {
                    cout << ENEMY;
                    isEnemyHere = true;
                    break;
                }
            }

            // Check if a puzzle is at the current position
            for (const auto& puzzle : puzzles) {
                if (x == puzzle.x && y == puzzle.y) {
                    if (!puzzle.solved) {
                        if (x == player.x && y == player.y) {
                            // If the player is at the puzzle position, don't overwrite the player
                            cout << PLAYER;
                        } else {
                            // Display the puzzle if not solved
                            cout << PUZZLE;
                        }
                    } else {
                        // Empty space if puzzle is solved and no player is here
                        if (x == player.x && y == player.y) {
                            cout << PLAYER;
                        } else {
                            cout << ' ';
                        }
                    }
                    isPuzzleHere = true;
                    break;
                }
            }
            

            // If no enemy or puzzle is at the position, print the player or wall
            if (!isEnemyHere && !isPuzzleHere) {
                if (x == player.x && y == player.y) {
                    cout << PLAYER;  // Display player
                } else {
                    cout << (maze[y][x] == WALL ? '#' : ' ');  // Wall or empty space
                }
            }
        }
        cout << endl;
    }
 }
 */
 void printMaze(const vector<vector<int>>& maze, const Player& player, const vector<Enemy>& enemies, const vector<Puzzle>& puzzles) {
    for (int y = 0; y < maze.size(); y++) {
        for (int x = 0; x < maze[y].size(); x++) {
            bool isEnemyHere = false;
            bool isPuzzleHere = false;

            // Check if an enemy is at the current position
            for (const auto& enemy : enemies) {
                if (x == enemy.x && y == enemy.y) {
                    cout << ENEMY;
                    isEnemyHere = true;
                    break;
                }
            }

            // Check if a puzzle is at the current position
            for (const auto& puzzle : puzzles) {
                if (x == puzzle.x && y == puzzle.y) {
                    isPuzzleHere = true;

                // If the puzzle is solved, print a space
                if (puzzle.solved) {         
                    // Player on solved puzzle
                    if (player.x == puzzle.x && player.y == puzzle.y) {
                        cout << PLAYER;
                    // Player not on solved puzzle
                    } else {
                        cout << ' ';
                    }
                    //puzzle.solved == false
                } else {
                        cout << PUZZLE;  // Print puzzle if player is not there
                    }
                    break;
                }
            }

            // If no enemy or puzzle is here, check if the player is here
            if (!isEnemyHere && !isPuzzleHere) {
                if (x == player.x && y == player.y) {
                    cout << PLAYER;  // Display player
                } else {
                    cout << (maze[y][x] == WALL ? '#' : ' ');  // Wall or empty space
                }
            }
        }
        cout << endl;
    }
 }

 void generateMaze(int width, int height, vector<vector<int>>& maze) {
    // Ensure odd width and height for proper wall placement
    if (width % 2 == 0) width++;
    if (height % 2 == 0) height++;

    // Initialize the maze with all walls
    maze.assign(height, vector<int>(width, WALL));

    // Random starting point
    srand(time(0));
    int startX = (rand() % (width / 2)) * 2 + 1;
    int startY = (rand() % (height / 2)) * 2 + 1;

    // Mark the starting cell as a path
    maze[startY][startX] = PATH;

    // List of walls (pairs of cells)
    vector<Cell> walls;
    walls.push_back(Cell(startX, startY));

    // Process walls
    while (!walls.empty()) {
        // Pick a random wall
        int randIndex = rand() % walls.size();
        Cell wall = walls[randIndex];

        // Get the neighbors of the current cell
        vector<Cell> neighbors = getNeighbors(wall.x, wall.y, maze);

        if (!neighbors.empty()) {
            // Pick a random neighboring cell
            Cell neighbor = neighbors[rand() % neighbors.size()];

            // Remove the wall between the current cell and the neighbor
            int midX = (wall.x + neighbor.x) / 2;
            int midY = (wall.y + neighbor.y) / 2;

            maze[midY][midX] = PATH;   // Remove wall between
            maze[neighbor.y][neighbor.x] = PATH;  // Make the neighbor a path

            // Add the neighboring cell's walls to the list
            walls.push_back(neighbor);
        } else {
            // If no neighbors, remove the wall from the list
            walls.erase(walls.begin() + randIndex);
        }
    }
 }

 bool isValidMove(int x, int y, const vector<vector<int>>& maze, vector<Puzzle>& puzzles) {
 // Check if the move is within bounds and the position is a path
 if (x >= 0 && x < maze[0].size() && y >= 0 && y < maze.size() && maze[y][x] == PATH){

    // Check if the move is within bounds and the position is a path or an unsolved puzzle
    for (const auto& puzzle : puzzles) {
        if (x == puzzle.x && y == puzzle.y){
            // If the puzzle is unsolved, block the move
            if (!puzzle.solved) {
                return false;
            } else { 
                return true;
            } 
        }
    } 
    // If no puzzle is at this position, return true since it's a valid path
    return true;
 } 
    // Return false if the position is out of bounds or not a valid path
    return false;
 }

 // Function for random enemy movement
 void moveEnemyRandom(Enemy& enemy, const vector<vector<int>>& maze, vector<Puzzle>& puzzles) {
    int direction = rand() % 4; // 0 = up, 1 = down, 2 = left, 3 = right
    int newX = enemy.x, newY = enemy.y;

    if (direction == 0 && isValidMove(enemy.x, enemy.y - 1, maze, puzzles)) newY--;
    else if (direction == 1 && isValidMove(enemy.x, enemy.y + 1, maze, puzzles)) newY++;
    else if (direction == 2 && isValidMove(enemy.x - 1, enemy.y, maze, puzzles)) newX--;
    else if (direction == 3 && isValidMove(enemy.x + 1, enemy.y, maze, puzzles)) newX++;

    enemy.x = newX;
    enemy.y = newY;
 }

 void checkAndSolvePuzzle(Player& player, vector<Puzzle>& puzzles, vector<vector<int>>& maze, int newX, int newY ) { 
    
   for (auto& puzzle : puzzles) {
        // If the puzzle is unsolved, prompt the player to solve it
        if (newX == puzzle.x && newY == puzzle.y && !puzzle.solved) {
            cout << "2You've encountered a puzzle! Solve it to proceed.\n";
            bool puzzleSolved = solvePuzzle();  // Call the solvePuzzle function from puzzleList.cpp

            if (puzzleSolved == true) {
                puzzle.solved = true;
              //  maze[puzzle.y][puzzle.x] = " ";  // Unlock the path
                cout << "You solved the puzzle! You can now proceed.\n";
            } else {
                // Restore the player's previous position if they fail
               // maze[puzzle.y][puzzle.x] = PUZZLE;  // lock the path
                cout << "You failed to solve the puzzle. The puzzle remains locked." << endl;
            }
            return;  // Exit after handling the puzzle at this position
        }
   }
 }

 void handlePlayerMovement(Player& player, char input, vector<vector<int>>& maze, vector<Puzzle>& puzzles, bool& validMove) {

    // Store the player's current position
    int newX = player.x, newY = player.y;

    // Determine the direction based on input
    if (input == 'w' || input == 'W') newY--;  // Move up
    else if (input == 's' || input == 'S') newY++;  // Move down
    else if (input == 'a' || input == 'A') newX--;  // Move left
    else if (input == 'd' || input == 'D') newX++;  // Move right

    // Check if the new position is valid (not a wall, within bounds)
    if (isValidMove(newX, newY, maze, puzzles)) { 
        // Update the player's position if the move is valid
        player.x = newX; // newX after increment
        player.y = newY;
        validMove = true;
    } else {
        bool foundUnsolvedPuzzle = false;
        for (const auto& puzzle : puzzles) {
            if (newX == puzzle.x && newY == puzzle.y && !puzzle.solved) {
                foundUnsolvedPuzzle = true;
                cout << "There's an unsolved puzzle here. Solve it first!\n";
                // Check if the player encounters a puzzle
                checkAndSolvePuzzle(player, puzzles, maze, newX, newY);
                break;  // Exit the loop after attempting to solve the puzzles
            }
        } 
        // If no valid move was made, display an invalid move message
        if (!foundUnsolvedPuzzle) {
            validMove = false;
            cout << "Invalid move. Try a different direction.\n";
        }
   }
 }

 /* OLD
 // Check if the player is on a puzzle and solve it
 void checkAndSolvePuzzle(Player& player, vector<Puzzle>& puzzles, vector<vector<int>>& maze) {
    for (auto& puzzle : puzzles) {
        if (player.x == puzzle.x && player.y == puzzle.y && !puzzle.solved) {
            cout << "You've encountered a puzzle! Solve it to proceed.\n";

            if (solveWordPuzzle()) {
                cout << "Puzzle solved! Path unlocked.\n";
                puzzle.solved = true;
                maze[puzzle.y][puzzle.x] = PATH;  // Unlock the path
            } else {
                cout << "Wrong answer. Try again later.\n";
            }
        }
    }
 } */
 /*NEW - updated
 void checkAndSolvePuzzle(Player& player, vector<Puzzle>& puzzles, vector<vector<int>>& maze) { 
    
    for (auto& puzzle : puzzles) {
        if (player.x == puzzle.x && player.y == puzzle.y && !puzzle.solved) {
            cout << "You've encountered a puzzle! Solve it to proceed.\n";

            bool puzzleSolved = solvePuzzle();  // Call the solvePuzzle function from puzzleList.cpp
            if (puzzleSolved == true) {
                puzzle.solved = true;
                maze[puzzle.y][puzzle.x] = PATH;  // Unlock the path
                cout << "You solved the puzzle! You can now proceed.\n";
            } else {
                cout << "You failed to solve the puzzle. The puzzle remains locked." << endl;
                puzzle.solved = false;
                // Restore the player's previous position if they fail
                maze[puzzle.y][puzzle.x] = PUZZLE;  // lock the path
            
            }
        }
    }
 }
 */
 // Simple AI to move enemy towards the player
 void moveEnemyTowardsPlayer(Enemy& enemy, const Player& player, const vector<vector<int>>& maze, vector<Puzzle>& puzzles) {
    int newX = enemy.x, newY = enemy.y;

    if (player.x < enemy.x && isValidMove(enemy.x - 1, enemy.y, maze, puzzles)) newX--;
    else if (player.x > enemy.x && isValidMove(enemy.x + 1, enemy.y, maze, puzzles)) newX++;
    if (player.y < enemy.y && isValidMove(enemy.x, enemy.y - 1, maze, puzzles)) newY--;
    else if (player.y > enemy.y && isValidMove(enemy.x, enemy.y + 1, maze, puzzles)) newY++;

    enemy.x = newX;
    enemy.y = newY;
 }

 int main() {
    int width = 21;  // Maze width (must be odd)
    int height = 21; // Maze height (must be odd)
    vector<vector<int>> maze;

    generateMaze(width, height, maze);

    // Player's starting position (top-left corner of the maze)
    Player player(1, 1);

    // Mark the player's starting position as a path if not already
    if (maze[player.y][player.x] == WALL) maze[player.y][player.x] = PATH;

    // Randomly place enemies
    vector<Enemy> enemies;
    for (int i = 0; i < Enemy::numEnemies; i++) {
        int enemyX, enemyY;
        do {
            enemyX = (rand() % (width - 2)) + 1;
            enemyY = (rand() % (height - 2)) + 1;
        } while (maze[enemyY][enemyX] != PATH || (enemyX == player.x && enemyY == player.y));

        enemies.push_back(Enemy(enemyX, enemyY));
    }

    // Randomly place puzzles
    vector<Puzzle> puzzles;
    int numPuzzles = 10;
    for (int i = 0; i < numPuzzles; i++) {
        int puzzleX, puzzleY;
        do {
            puzzleX = (rand() % (width - 2)) + 1;
            puzzleY = (rand() % (height - 2)) + 1;
        } while (maze[puzzleY][puzzleX] != PATH || (puzzleX == player.x && puzzleY == player.y));

        puzzles.push_back(Puzzle(puzzleX, puzzleY));
    }

    char input;
    bool gameOver = false;
    bool validMove = true;
    while (!gameOver) {

        system("cls");  // Clear the console (Windows-specific)
        printMaze(maze, player, enemies, puzzles);
        cout << "Use WASD to move. Press 'Q' to quit.\n";

        if (!validMove){
        cout << "Invalid move. Try a different direction.\n";
        }
        
        input = _getch();  // Read input without needing to press Enter

        if (input == 'q' || input == 'Q') break; // Quit the game

        // Handle player movement using the abstracted function
        handlePlayerMovement(player, input, maze, puzzles, validMove);

        // Check if player encounters a puzzle
        //checkAndSolvePuzzle(player, puzzles, maze, player.x, player.y);
        
        // Move enemies (random or AI)
        for (auto& enemy : enemies) {
            // You can toggle between random and AI movement for enemies
            moveEnemyRandom(enemy, maze, puzzles);  // Random movement
            moveEnemyTowardsPlayer(enemy, player, maze, puzzles);  // AI movement towards player
        }

    }

    return 0;
 }
*/

//RESCOURCES --------------------------------------------------------------------

// 1) ADD ITEM STRUCT

struct Item {
    int x, y;
    string name;

    Item(int startX, int startY, const string& itemName) : x(startX), y(startY), name(itemName) {}
};

//2) ADD TO PRINT MAZE (print if there is an item there)
//,const vector<Item>& items)
            bool isItemHere = false;

            // Check if an item is at the current position
            for (const auto& item : items) {
                if (x == item.x && y == item.y) {
                    cout << ITEM;  // Symbol for the item
                    isItemHere = true;
                    break;
                }
            }
            //...
            // If no enemy or puzzle is here, check if the player is here
            if (!isEnemyHere && !isPuzzleHere && !isItemHere) {
                if (x == player.x && y == player.y) {
                    cout << PLAYER;  // Display player
                } else {
                    cout << (maze[y][x] == WALL ? '#' : ' ');  // Wall or empty space
                }
            }

//3) Add Item Collection Mechanis: add item to 'inventory when player is on item's cell & delete item from the list of item

void checkItemCollection(Player& player, vector<Item>& items) {
    // Loop through all items in the maze
    for (int i = 0; i < items.size(); i++) {
        // If player's position matches the item's position
        if (player.x == items[i].x && player.y == items[i].y) {
            // Player collects the item
            player.collectItem(items[i]);
            // Remove the collected item from the list & Item is not printed when maze is rerendered
            items.erase(items.begin() + i); 
            i--;  // Adjust index after erasing to avoid skipping the next item
        }
    }
}

//4) Printing of inventory 
void showInventory(const Player& player) {
    cout << "Inventory: ";
    if (player.inventory.empty()) {
        cout << "Empty" << endl;
    } else {
        for (const auto& item : player.inventory) {
            cout << item << " ";
        }
        cout << endl;
    }
}
 

//5) Update main

    //Randomly Place Items in the Maze (First generation)
    vector<Item> items;
    int numItems = 20;  // Number of items to place in the maze

    vector<string> itemNames = { "Key", "Potion", "Power-Up", "Teleport", "ITEM2" ,"ITEM4" ,"ITEM3","ITEM6" ,"ITEM7"  };
    
    //loop generates random coordinates (itemX, itemY) for the item inside the maz
    for (int i = 0; i < numItems; i++) {
        // Randomly select an item name
        string itemName = itemNames[rand() % itemNames.size()];
        int itemX, itemY;
        do {
            itemX = (rand() % (width - 2)) + 1;
            itemY = (rand() % (height - 2)) + 1;
        } while (maze[itemY][itemX] != PATH || (itemX == player.x && itemY == player.y)); //empty spot & isn't placed on the player's starting position
        items.push_back(Item(itemX, itemY, itemName)); //new Item is created & added to the items vector
    }
    // Game loop
    while (!gameOver) {

        system("cls");  // Clear the console (Windows-specific)
        printMaze(maze, player, enemies, puzzles, items);
        // Show player inventory
        showInventory(player);
        cout << "Use WASD to move. Press 'Q' to quit.\n";

// ...
        checkItemCollection(player, items);
    
    return 0;
}



//SET GOAL -------------------------------------------------------------------

//1) STRUCT
struct Goal {
    int x, y;

    // Constructor to set a default position at the bottom-right corner
    Goal(int width, int height) : x(width - 2), y(height - 2) {}

    // Method to update the goal position
    void setGoal(int newX, int newY) {
        x = newX;
        y = newY;
    }
};

//2) UPDATE MAIN
int width = 21;
int height = 21;
Goal goal(width, height);  // The goal will be set to (width - 2, height - 2)

//3)TO change the goal's position
goal.setGoal(newX, newY);

----------------------------------
//OLD 13DEC
       /*
        // Move enemies (random or AI)
        for (auto& enemy : enemies) {
            // You can toggle between random and AI movement for enemies
            moveEnemyRandom(enemy, maze, puzzles, portals, doors);  // Random movement
           moveEnemyTowardsPlayer(enemy, player, maze, puzzles, portals, doors);  // AI movement towards player
        }   */
/*
    // Randomly place enemies
    vector<Enemy> enemies;
  //  int numEnemies = 1;
    for (int i = 0; i < levelConfig.numEnemies; i++) {
        int enemyX, enemyY;
        do {
            enemyX = (rand() % (width - 2)) + 1;
            enemyY = (rand() % (height - 2)) + 1;
        } while (maze[enemyY][enemyX] != PATH || (enemyX == player.x && enemyY == player.y)|| // Avoid player position
            manhattanDistance(enemyX, enemyY, player.x, player.y) < minDistanceFromPlayer ||  // Too close to the player
            manhattanDistance(enemyX, enemyY, goal.x, goal.y) < minDistanceFromGoal); // Too close to the goal);

        enemies.push_back(Enemy(enemyX, enemyY));
    }

    // Randomly place puzzles
    vector<Puzzle> puzzles;
   // int numPuzzles = 0;
    for (int i = 0; i < levelConfig.numPuzzles; i++) {
        int puzzleX, puzzleY;
        do {
            puzzleX = (rand() % (width - 2)) + 1;
            puzzleY = (rand() % (height - 2)) + 1;
        } while (maze[puzzleY][puzzleX] != PATH || (puzzleX == player.x && puzzleY == player.y)|| // Avoid player position
            manhattanDistance(puzzleX, puzzleY, player.x, player.y) < minDistanceFromPlayer||  
             manhattanDistance(puzzleX, puzzleY, goal.x, goal.y) < minDistanceFromGoal);

        puzzles.push_back(Puzzle(puzzleX, puzzleY));
    }

    //Randomly Place Items in the Maze (First generation)
    vector<Item> items;
   // int numItems = 0;  // Number of items to place in the maze
    vector<string> itemNames = {"poition", "Teleport", "xtraLife", "Hammer"};
    //loop generates random coordinates (itemX, itemY) for the item inside the maz
    for (int i = 0; i < levelConfig.numItems; i++) {
     // Randomly select an item name
       string itemName = itemNames[rand() % itemNames.size()];
        int itemX, itemY;
        do {
            itemX = (rand() % (width - 2)) + 1;
            itemY = (rand() % (height - 2)) + 1;
        } while (maze[itemY][itemX] != PATH || (itemX == player.x && itemY == player.y)); //empty spot & isn't placed on the player's starting position
        items.push_back(Item(itemX, itemY, itemName)); //new Item is created & added to the items vector
    }

    vector<Portal> portals;  // Vector to hold portal positions
   // int numPortals = 3;  // Set the number of portals
    for (int i = 0; i < levelConfig.numPortals; i++) {
     int portalX, portalY;
     do {
        portalX = (rand() % (width - 2)) + 1;
        portalY = (rand() % (height - 2)) + 1;
     } while (maze[portalY][portalX] != PATH || (portalX == player.x && portalY == player.y)||  
             manhattanDistance(portalX, portalY, goal.x, goal.y) < minDistanceFromGoal);
    
     portals.push_back(Portal(portalX, portalY));
     //maze[portalY][portalX] = 'T';  // Mark the portal on the maze as 'T'
}

    //Randomly Place doors in the Maze (First generation)
    vector<Door> doors;
    // Randomly place doors in the maze
   // int numDoors = 0;  // Number of doors to place in the maze
    for (int i = 0; i < levelConfig.numDoors; i++) {
        int doorX, doorY;
        do {
            doorX = (rand() % (width - 2)) + 1;
            doorY = (rand() % (height - 2)) + 1;
        } while (maze[doorY][doorX] != WALL || (doorX == player.x && doorY == player.y)|| // Avoid player position
            manhattanDistance(doorX, doorY, player.x, player.y) < minDistanceFromPlayer);  // Place doors on walls
        doors.push_back(Door(doorX, doorY));
    }

    //Randomly Place keys in the Maze (First generation)
    vector<Key> keys;
   // int numKeys = 0;  // Number of items to place in the maze
    //loop generates random coordinates (itemX, itemY) for the item inside the maz
    for (int i = 0; i < levelConfig.numKeys; i++) {
        int keyX, keyY;
        do {
            keyX = (rand() % (width - 2)) + 1;
            keyY = (rand() % (height - 2)) + 1;
        } while (maze[keyY][keyX] != PATH || (keyX == player.x && keyY == player.y)); //empty spot & isn't placed on the player's starting position
        keys.push_back(Key(keyX, keyY, "Key")); //new Item is created & added to the items vector
    }

    //Randomly Place sword in the Maze (First generation)
    vector<Sword> swords;
   // int numSwords = 20;  // Number of items to place in the maze
    //loop generates random coordinates (itemX, itemY) for the item inside the maz
    for (int i = 0; i < levelConfig.numSwords; i++) {
        int swordX, swordY;
        do {
            swordX = (rand() % (width - 2)) + 1;
            swordY = (rand() % (height - 2)) + 1;
        } while (maze[swordY][swordX] != PATH || (swordX == player.x && swordY == player.y)|| // Avoid player position
            manhattanDistance(swordX, swordY, player.x, player.y) < minDistanceFromPlayer); //empty spot & isn't placed on the player's starting position
        swords.push_back(Sword(swordX, swordY, "Sword")); //new Item is created & added to the items vector
    }
*/

/* OLD
bool checkEnemyCatchPlayer(Player& player, const vector<Enemy>& enemies) { 

    for (const auto& enemy : enemies) {
        if (enemy.x == player.x && enemy.y == player.y) {
            player.message = "Enemy has caught you!";
            player.loseLife(); // Player loses a life
            if (!player.isAlive()) {
                // Check if the player has an extra life item
                if (player.hasItem("xtraLife")) { // display seperately as 'H'?
                    // Use the extra life item and restore 1 life
                    player.inventory.erase(remove(player.inventory.begin(), player.inventory.end(), "xtraLife"), player.inventory.end());
                   // player.lives += 1;  // Restore 1 life
                    player.message = "You used an extra life!";
                    return false;  // Player is revived, game continuesd
                } else {
                player.message = "Game Over! You had no lives left ~";
                return true;  // Return true if the game is over
                }
            }
            return false;  // Player caught by an enemy, but still alive
        }
    }
    return false;  // No enemy caught the player
 }
*/

/* OLD
// Function for random enemy movement
void moveEnemyRandom(Enemy& enemy, const vector<vector<int>>& maze, vector<Puzzle>& puzzles, const vector<Portal>& portals, const vector<Door>& doors, Player& player) {
    int direction = rand() % 4; // 0 = up, 1 = down, 2 = left, 3 = right
    int newX = enemy.x, newY = enemy.y;

    if (direction == 0 && isValidMoveForEnemy(enemy.x, enemy.y - 1, maze, puzzles, portals, doors)) newY--;
    else if (direction == 1 && isValidMoveForEnemy(enemy.x, enemy.y + 1, maze, puzzles, portals, doors)) newY++;
    else if (direction == 2 && isValidMoveForEnemy(enemy.x - 1, enemy.y, maze, puzzles, portals, doors)) newX--;
    else if (direction == 3 && isValidMoveForEnemy(enemy.x + 1, enemy.y, maze, puzzles, portals, doors)) newX++;

    enemy.x = newX;
    enemy.y = newY;
}*/

/* OLD
void printMaze(const vector<vector<int>>& maze, const Player& player, const vector<Enemy>& enemies, const vector<Puzzle>& puzzles, const vector<Item>& items) {
    for (int y = 0; y < maze.size(); y++) {
        for (int x = 0; x < maze[y].size(); x++) {
            bool isEnemyHere = false;
            bool isPuzzleHere = false;
            bool isItemHere = false;

            // Check if an enemy is at the current position
            for (const auto& enemy : enemies) {
                if (x == enemy.x && y == enemy.y) {
                    cout << ENEMY;
                    isEnemyHere = true;
                    break;
                }
            }

            // Check if a puzzle is at the current position
            for (const auto& puzzle : puzzles) {
                if (x == puzzle.x && y == puzzle.y) {
                    isPuzzleHere = true;

                // If the puzzle is solved, print a space
                if (puzzle.solved) {         
                    // Player on solved puzzle
                    if (player.x == puzzle.x && player.y == puzzle.y) {
                        cout << PLAYER;
                    // Player not on solved puzzle
                    } else {
                        cout << ' ';
                    }
                    //puzzle.solved == false
                } else {
                        cout << PUZZLE;  // Print puzzle if player is not there
                    }
                    break;
                }
            }

            // Check if an item is at the current position
            for (const auto& item : items) {
                if (x == item.x && y == item.y) {
                    cout << ITEM;  // Symbol for the item
                    isItemHere = true;
                    break;
                }
            }

            // If no enemy or puzzle is here, check if the player is here
            if (!isEnemyHere && !isPuzzleHere && !isItemHere) {
                if (x == player.x && y == player.y) {
                    cout << PLAYER;  // Display player
                } else {
                    cout << (maze[y][x] == WALL ? '#' : ' ');  // Wall or empty space
                }
            }
        }
        cout << endl;
    }
}
*/