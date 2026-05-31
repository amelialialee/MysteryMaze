#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <iomanip> 
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
#include <chrono>  
#include <thread>
#include <cstdlib> 
#include <fstream>
#include <ctime> 
#include "../src/puzzleList.cpp" 
#include "../src/text.cpp" 

using namespace std;
using namespace std::chrono;

const int WALL = 1;
const int PATH = 0;

//Symbol for elements
const char PLAYER = 'P';
const char ENEMY = 'G'; // 'Guardian'
const char PUZZLE = '+';
const char ITEM = '?'; // 'Chest'
const char GOAL = 'X';
const char PORTAL = 'O';
const char DOOR = 'D';  // Example value representing doors that require keys
const char KEY = 'K';
const char SWORD = 'S';

void clearScreen() {
    #ifdef _WIN32
        system("cls");  // Windows version
    #else
        system("clear");  // Linux/macOS version
    #endif
}

// Structure to represent the coordinates of a cell in the maze
struct Cell {
    int x, y; // x & y coordinates of the cell
    Cell(int _x, int _y) : x(_x), y(_y) {}
};

// Defining different game modes
enum GameMode {
    DEFAULT,
    PUZZLE_COMPLETION,
    GUARDIAN_ELIMINATION,
    SPEED_RUN_RACE,
    COUNTDOWN_CHALLENGE
};

// Defining difficulty levels
enum Difficulty { EASY, MEDIUM, HARD };

//Convert a string to the corresponding GameMode
GameMode stringToGameMode(const string& str) {
    if (str == "DEFAULT") return GameMode::DEFAULT;
    if (str == "PUZZLE COMPLETION") return GameMode::PUZZLE_COMPLETION;
    if (str == "GUARDIAN ELIMINATION") return GameMode::GUARDIAN_ELIMINATION;
    if (str == "SPEED RUN RACE") return GameMode::SPEED_RUN_RACE;
    if (str == "COUNTDOWN CHALLENGE") return GameMode::COUNTDOWN_CHALLENGE;
    return GameMode::DEFAULT; // Default to DEFAULT if the input is unrecognized
}

// Convert a string to the corresponding Difficulty enum
Difficulty stringToDifficulty(const string& str) {
    if (str == "MEDIUM") return Difficulty::MEDIUM;
    if (str == "HARD") return Difficulty::HARD;
    return Difficulty::EASY;  // Default to EASY if the input is unrecognized
}

// Convert Difficulty enum to its string representation
string difficultyToString(Difficulty difficulty) {
    switch (difficulty) {
        case EASY: return "EASY";
        case MEDIUM: return "MEDIUM";
        case HARD: return "HARD";
        default: return "UNKNOWN";
    }
}

//done
// Convert GameMode to its string representation
string gameModeToString(GameMode gameMode) {
    switch (gameMode) {
        case DEFAULT: return "DEFAULT";
        case PUZZLE_COMPLETION: return "PUZZLE COMPLETION" ;
        case GUARDIAN_ELIMINATION: return "GUARDIAN ELIMINATION";
        case SPEED_RUN_RACE: return "SPEED RUN RACE";
        case COUNTDOWN_CHALLENGE: return "COUNTDOWN CHALLENGE";
        default: return "DEFAULT"; // Return "DEFAULT" for any unrecognized value
    }
}

struct GameLevel {
    int width;
    int height;
    int playerLives;
    int inventoryCap;
    int numEnemies;
    int numSwords;
    int numDoors;
    int numKeys;
    int numPuzzles;
    int numPortals;
    int numItems;
};

// Represent the goal in the maze
struct Goal {
    int x, y; // Position (x, y) of the goal in the maze

    // Constructor to set a default position at the bottom-right corner
    Goal(int width, int height) : x(width - 2), y(height - 2) {}

    // Method to update the goal position to new coordinates
    void setGoal(int newX, int newY) {
        x = newX;
        y = newY;
    }
};

// Represent an item in the game
struct Item {
    int x, y; // Position of the item in the maze/grid
    string name; // Name of the item

    Item(int startX, int startY, const string& itemName) : x(startX), y(startY), name(itemName) {}
};

// Represent a portal in the maze
struct Portal {
    int x, y; // Position of the portal in the maze/
    // Constructor to initialize a portal at specific coordinates
    Portal(int _x, int _y) : x(_x), y(_y) {}
};

struct Door {
    int x, y;        // Position of the door
    bool isOpen;     // Whether the door is open or closed (true = open, false = closed)
    // Constructor to initialize the door at specific coordinates, and initially closed
    Door(int posX, int posY) : x(posX), y(posY), isOpen(false) {}
};

// Represent Key in the game
struct Key {
    int x, y; // Position (x, y) of the key in the maze
    string name;
    Key(int startX, int startY, const string& keyName = "KEY") : x(startX), y(startY), name(keyName) {}
};

// Represent a Sword in the game
struct Sword {
    int x, y; // Position (x, y) of the sword in the maze
    string name;
    Sword(int startX, int startY, const string& swordName = "SWORD") : x(startX), y(startY), name(swordName) {}
};

//done
// Represent the Player in the game
struct Player {
    int x, y;                 // Player's current position in the maze
    vector<string> inventory; // Player's inventory to store collected items
    int inventoryCap;         // Maximum capacity of the player's inventory
    string message = "";      // Stores messages such as "Inventory is full"
    int lives;                // Player's remaining lives
    string name;              // Name of the player

    // Constructor to initialize player at position (1, 1)
    Player() : x(1), y(1) {}
       
   // Method to set the player's position to a new (x, y) coordinate
    void setPlayerPoint(int newX, int newY) {
        x = newX;  // Update player's x position
        y = newY;  // Update player's y position
    }
    
    // Method to reduce the player's lives by 1
    void loseLife() {
        lives--; // Decrease the number of lives by 1
    }

    // Method to check if the player is still alive 
    bool isAlive() const {
        return lives > 0;
    }
    
    // Method to collect an item and add it to the player's inventory
    void collectItem(const Item& item) {
        if (inventory.size() < inventoryCap) { // Check if there is space in inventory
        inventory.push_back(item.name); // Add item to inventory
         //inventory.push_back(item); 
        message = "Collected: " + item.name; 
     } else {
        message = "Inventory is full! Cannot collect " + item.name + ".";
        }
    }

    // Method to collect a key and add it to the player's inventory
    void collectKey(const Key& key) {
        if (inventory.size() < inventoryCap) {  // Check if there is space in inventory
        inventory.push_back("KEY");  // Add the key to the inventory
        message = "Collected: Key ";
    }else {
        message = "Inventory is full! Cannot collect Key.";
        }
    }

    // Method to collect a sword and add it to the player's inventory
    void collectSword(const Sword& sword) {
        if (inventory.size() < inventoryCap) { // Check if there is space in inventory
        inventory.push_back("SWORD"); // Add the sword to the inventory
        message = "Collected: Sword "; 
    }else {
        message = "Inventory is full! Cannot collect Sword.";
        }
    }

    // Method to check if the player has a specific item in their inventory 
    bool hasItem(const string& itemName) const {
        // Method to check if the player has a specific item in inventory
        return find(inventory.begin(), inventory.end(), itemName) != inventory.end();
    } 
};

// Represent an Enemy in the game
struct Enemy {
    int x, y;  // Enemy's position
    bool skipNextMove = false; // Cooldown flag to determine if the enemy should skip the next move

    Enemy(int startX, int startY) : x(startX), y(startY) {
    }
};

// Reeresent a Puzzle in the game
struct Puzzle {
    int x, y; // Position (x, y) of the puzzle in the maze
    bool solved; // Boolean flag indicating if the puzzle has been solved

    Puzzle(int startX, int startY) : x(startX), y(startY), solved(false) {}
};

// Global variables
Player player;
vector<Enemy> enemies;
vector<Item> items;
vector<Puzzle> puzzles;
vector<Portal> portals;
vector<Door> doors;
vector<Key> keys;
vector<Sword> swords;
vector<vector<int>> maze;

// Game level configuration
GameLevel levelConfig; // Stores configuration for the current level (e.g., number of enemies, doors, etc.)

// Level and game tracking
int currentLevel = 1; // Tracks the current level in the game (default to level 1)
bool gameOver = true; // Flag to indicate if the game is over (default is true)
bool startGame = false; // Flag to determine when the game has started
bool showPrologue = false; // flag to ensure Prologue displays only once

// Game difficulty and mode settings
Difficulty difficulty = EASY;  // Default game difficulty (EASY)
GameMode gameMode = DEFAULT;   // Default game mode (DEFAULT)

// Level progression and customization
int maxLevels = 5;            // Default number of levels
// Game customization options
bool infiniteLevels = false;  // Default infinite levels flag
bool keepInventory = false;    // Flag to determine if the player keeps inventory across levels
bool puzzleOptions = false;    // Flag to enable/disable puzzle options
bool includeEnemies = true;    // Flag to include enemies in the game
int chaseDistanceThreshold = 5; // Distance threshold for enemy chasing behavior

// Timer-related variables
steady_clock::time_point gameStartTime, levelStartTime;  // Track start time of the game and level
string savedDateTime;  // Saved timestamp for game progress (if applicable)
int totalGameTime = 0; // Total time elapsed for the entire game
int levelTime = 0;     // Time taken for the current level
bool levelStarted = false; // Flag to track if the current level has started
bool gameStarted = false;  // Flag to track if the game has started
bool timerPaused = false;  // Global flag to check if the timer is paused

// Countdown and total game time tracking
int countdownTimeRemaining;// Time remaining for the countdown in the current level
int totalTime;

// Game indexing variables
int gameIndex = 0;
string gameIndexStr = "";

// Game state tracking
string currentDateTime; // Stores the current date and time for the game 
bool loadingGame = false;  // Flag to determine if the game is loading from a saved state

int width;  // Maze width 
int height; // Maze height 
Goal goal (0, 0); // Goal position (default at (0, 0)

int manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Function to pause the timer
void pauseTimer() {
    timerPaused = true;
}

// Function to resume the timer
void resumeTimer() {
    timerPaused = false;
}

// Function to start the game timer (total time for the game)
void startGameTimer() {
    if (!gameStarted) {
        gameStartTime = steady_clock::now();  // Record the start time of the game
        gameStarted = true;  // Mark the game as started
    }
}

// Function to start/reset the level timer
void startLevelTimer() {
    if (!levelStarted ) {
        levelStartTime = steady_clock::now();  // Record the start time of the level
        levelStarted = true;  // Mark the level as started
    }
}

int getLevelTimeInSeconds() {
    // Get the elapsed time for the current level
    if (levelStarted ) {
    auto currentTime = steady_clock::now();
    auto elapsed = duration_cast<seconds>(currentTime - levelStartTime);
    return elapsed.count();
    }
    return 0;
}

int getTotalTimeInSeconds() {
    if (gameStarted ) {
        auto currentTime = steady_clock::now();
        auto elapsed = duration_cast<seconds>(currentTime - gameStartTime);
        return elapsed.count();
    }
    return 0;
}

void stopTimers() { // Stop both timers (when the game ends)
    if (gameStarted) {
        totalGameTime = getTotalTimeInSeconds();  // Store total game time
        gameStarted = false;  // Mark game as stopped
    }
    if (levelStarted) {
        levelTime = getLevelTimeInSeconds();  // Store the final level time
        levelStarted = false;  // Mark level as stopped
    }
}

int getCountdownTimeRemaining() {
    const int countdownDuration = 30;  // Total time given per level 
    int elapsedTime = getTotalTimeInSeconds();  // Get the elapsed time since the level started
    
    int timeRemaining = countdownDuration - elapsedTime;
    return (timeRemaining > 0) ? timeRemaining : 0;  // Ensure no negative values
}

int getCurrentDateTimeAsIndex() {
    auto now = system_clock::now();
    auto time = system_clock::to_time_t(now);
    return static_cast<int>(time); // Use time_t as a unique index
}

string getCurrentDateTime() {
    auto now = system_clock::now();
    time_t now_time_t = system_clock::to_time_t(now);// Convert to time_t format
    string dateTime = ctime(&now_time_t); // Convert to string representation
    dateTime.pop_back(); // Remove the newline character at the end
    return dateTime;
}

string getPlayerName() {
    string playerName;
    // Initial prompt before entering the loop
    cout << "\nEnter your name to save the game: ";

    // Loop until a valid (non-empty) name is provided
    while (getline(cin, playerName), playerName.empty()) {
        cout << "\nName cannot be empty. Please enter a valid name: ";
    }
    return playerName;
}

string gameModeDiscription(string displayGameMode) {
    string gameDescription;

    // Check which game mode is selected and set the corresponding description
    if (displayGameMode == "DEFAULT") {
        gameDescription = "Finish the maze!";
    } else if (displayGameMode == "COUNTDOWN CHALLENGE") {
        gameDescription = "Finish as many mazes within the countdown... Let's see how far you can get";
    } else if (displayGameMode == "PUZZLE COMPLETION") {
        gameDescription = "Finish all puzzles to proceed to the next level";
    } else if (displayGameMode == "GUARDIAN ELIMINATION") {
        gameDescription = "Collect Swords & Fight off all guardians to proceed to the next level";
    } else if (displayGameMode == "SPEED RUN RACE") {
        gameDescription = "Finish as many mazes as fast as you can & see your rank on the leaderboard";
    } else {
        gameDescription = "Finish the maze!";
    }

    return gameDescription;// Return the game mode description
}

#endif // MAZE_H