#include "include/MysteryMaze.h"
#include "include/json.hpp"
using json = nlohmann::json;

// Template function to get a value from a JSON object, with a fallback to a default value
template<typename T>
T getValueOrDefault(const json& j, const string& key, const T& defaultValue) {
    if (j.contains(key) && !j[key].is_null()) { // Check if the key exists and is not null
        return j[key].get<T>(); // Return the value associated with the key
    }
    return defaultValue; // Return the default value if key doesn't exist or is null
}

//done
void clearGame(){
    cout << "                            [ENTER to go back to menu]" << endl;  
    cin.ignore();  // Ignore any remaining input in the input buffer
    cin.get(); 
    gameIndexStr = "";  // Reset the game index string (clearing the current game data)
    gameIndex = 0;  // Reset the game index to 0
    player.name = "";
}
//done
// Function to clear or reset the Player and game data
void clearGameData() {
    // Reset Player data
    player.x = 1;
    player.y = 1;
    player.name = "";
    player.inventory.clear(); // Clear inventory
    player.inventoryCap = 0;
    player.lives = 0;
    player.message = "";

    // Reset game state data
    infiniteLevels = false;
    gameMode = GameMode::DEFAULT;  // Default game mode
    difficulty = Difficulty::EASY;  // Default difficulty
    maxLevels = 10;
    puzzleOptions = false;
    includeEnemies = true;

    currentLevel = 1;
    startGame = false;
    levelStarted = false;
    gameStarted = false;
    gameOver = false;

    // Reset level data
    levelConfig.width = 10;
    levelConfig.height = 10;
    levelConfig.playerLives = 3;
    levelConfig.numEnemies = 1;
    levelConfig.numSwords = 1;
    levelConfig.numDoors = 1;
    levelConfig.numKeys = 1;
    levelConfig.numPuzzles = 1;
    levelConfig.numPortals = 1;
    levelConfig.numItems = 1;
    levelConfig.inventoryCap = 3;

    goal.x = levelConfig.width -2 ;
    goal.y = levelConfig.height -2;

    // Clear game elements (maze, items, doors, keys, enemies, etc.)
    maze.clear();
    items.clear();
    portals.clear();
    doors.clear();
    keys.clear();
    swords.clear();
    enemies.clear();
    puzzles.clear();

}
//done
// Function to set up level progression based on difficulty
GameLevel setLevel(int level, Difficulty difficulty) {
    GameLevel config;

    // Base values for the starting level
    int baseWidth = 10, baseHeight = 10, baseEnemies = 1, baseDoors = 1, basePuzzles = 1, basePortal = 1;
    config.inventoryCap = 3; // Starting inventory capacity

    switch (difficulty) {
        case EASY:
            config.width = baseWidth + (level - 1);  // Gradual increase in maze size
            config.height = baseHeight + (level - 1);
            config.playerLives = 3;  // Player always has 3 lives
            config.numEnemies = baseEnemies + (level / 3);  // Enemies increase every 3 levels
            config.numSwords = config.numEnemies;  // Same number of swords as enemies
            config.numDoors = baseDoors + (level / 2);  // Doors/Keys increase every 2 levels
            config.numKeys = config.numDoors;  // Equal doors and keys
            config.numPuzzles = basePuzzles + (level / 4);  // Puzzles increase every 4 levels
            config.numPortals = basePortal + (level % 5 == 0) ? 1 : 0;  // Add portals every 5 levels
            config.numItems = level / 2;  // Gradual increase in items
            chaseDistanceThreshold = 6;
            break;

        case MEDIUM:
            config.width = baseWidth + 2 + (level - 1);  // Faster increase in maze size
            config.height = baseHeight + 2 + (level - 1);
            config.playerLives = 3;  // Player always has 3 lives
            config.numEnemies = baseEnemies + (level / 2);  // Enemies increase every 2 levels
            config.numSwords = config.numEnemies;  // Same number of swords as enemies
            config.numDoors = baseDoors + (level / 1.5);  // Doors/Keys increase every 1.5 levels
            config.numKeys = config.numDoors;  // Equal doors and keys
            config.numPuzzles = basePuzzles + (level / 3);  // Puzzles increase every 3 levels
            config.numPortals = basePortal + (level % 4 == 0) ? 1 : 0;  // Add portals every 4 levels
            config.numItems = level / 1.5;  // Faster increase in items
            chaseDistanceThreshold = 5;

            break;

        case HARD:
            config.width = baseWidth + 4 + (level - 1);  // Larger maze from the start
            config.height = baseHeight + 4 + (level - 1);
            config.playerLives = 3;  // Player always has 3 lives
            config.numEnemies = baseEnemies + level;  // Enemies increase every level
            config.numSwords = config.numEnemies;  // Same number of swords as enemies
            config.numDoors = baseDoors + level;  // Doors/Keys increase every level
            config.numKeys = config.numDoors;  // Equal doors and keys
            config.numPuzzles = basePuzzles + (level / 2);  // Puzzles increase every 2 levels
            config.numPortals = basePortal + (level % 3 == 0) ? 1 : 0;  // Add portals every 3 levels
            config.numItems = level;  // Items increase rapidly
            chaseDistanceThreshold = 4;

            break;

        default: //EASY
            config.width = baseWidth + (level - 1);  // Gradual increase in maze size
            config.height = baseHeight + (level - 1);
            config.playerLives = 3;  // Player always has 3 lives
            config.numEnemies = baseEnemies + (level / 3);  // Enemies increase every 3 levels
            config.numSwords = config.numEnemies;  // Same number of swords as enemies
            config.numDoors = baseDoors + (level / 2);  // Doors/Keys increase every 2 levels
            config.numKeys = config.numDoors;  // Equal doors and keys
            config.numPuzzles = basePuzzles + (level / 4);  // Puzzles increase every 4 levels
            config.numPortals = (level % 5 == 0) ? 1 : 0;  // Add portals every 5 levels
            config.numItems = level / 2;  // Gradual increase in items
            chaseDistanceThreshold = 6;

            break;
    }

    // Ensure inventoryCap is capped at 8
    if (config.inventoryCap > 8) {
        config.inventoryCap = 8;
    }

    // Ensure width and height are always odd
    if (config.width % 2 == 0) {
        config.width++;  // Make width odd if even
    }
    if (config.height % 2 == 0) {
        config.height++;  // Make height odd if even
    }
    
    return config;
}

//DONE


void customGame(){

    displayCustomGame1();  // Display the initial custom game setup screen

    // Ask the player to choose a game mode
    char gameModeInput;
    GameMode tempGameMode = DEFAULT;  // Default game mode is set to DEFAULT

    // Loop to get a valid game mode input
    while (true) {
        displayCustomGameGameMode();  // Display game mode options
        cin >> gameModeInput;

        // Check if the player wants to quit
        if (gameModeInput == 'Q' || gameModeInput == 'q') {
            cout << "Returning to menu..." << endl;
            return;  // Exit the function and return to the menu
        }

        // Set the game mode based on player input
        switch (gameModeInput) {
            case '1': tempGameMode = DEFAULT; break;
            case '2': tempGameMode = PUZZLE_COMPLETION; break;
            case '3': tempGameMode = GUARDIAN_ELIMINATION; break;
            case '4': tempGameMode = SPEED_RUN_RACE; break;
            case '5': tempGameMode = COUNTDOWN_CHALLENGE; break;
            default:
                cout << "Invalid choice. ";  // Inform the player of invalid input
                continue;  // Loop again until valid input is given
        }
        break;  // Exit the loop if a valid game mode is chosen
    }

   // Set the difficulty level
    char difficultyInput;
    Difficulty tempDifficulty;

    // Default difficulty for SPEED_RUN_RACE mode
    if (tempGameMode == SPEED_RUN_RACE) {
        tempDifficulty = MEDIUM;
    } else {
        // Loop to get a valid difficulty input
        while (true) {
            displayCustomGameDifficulty();  // Display difficulty options
            cin >> difficultyInput;

            // Check if the player wants to quit
            if (difficultyInput == 'Q' || difficultyInput == 'q') {
                cout << "Returning to menu..." << endl;
                return;  // Exit the function and return to the menu
            }

            // Set the difficulty based on player input
            switch (difficultyInput) {
                case '1': tempDifficulty = EASY; break;
                case '2': tempDifficulty = MEDIUM; break;
                case '3': tempDifficulty = HARD; break;
                default:
                    tempDifficulty = EASY;  // Default to EASY if invalid input
                    cout << "Invalid input. ";
                    continue;  // Loop again until valid input is given
            }
            break;  // Exit the loop once a valid difficulty is chosen
        }
    }

    // Ask the player if they want infinite levels
    bool tempInfiniteLevels = false;  // Default to finite levels
    int tempLevels;
    int defaultLevels = 5;  // Default to 5 levels
    char levelType;

    // Automatically set infinite levels for specific game modes (Speed Run Race & Countdown Challenge)
    if (tempGameMode == SPEED_RUN_RACE || tempGameMode == COUNTDOWN_CHALLENGE) {
        tempInfiniteLevels = true;
    } else {
        // Loop to get valid input for level selection
        while (true) {
            displayCustomGameLevel();  // Display level selection options
            cin >> levelType;

            // Check if the player wants to quit
            if (levelType == 'q' || levelType == 'Q') {
                cout << "Returning to menu..." << endl;
                return;  // Exit the function and return to the menu
            }

            // Set the number of levels or infinite levels based on player input
            switch (levelType) {
                case '1': tempLevels = defaultLevels; break;  // Default levels
                case '2': tempInfiniteLevels = true; break;  // Infinite levels
                case '3':  // Ask the player for a custom number of levels
                    cout << "Enter number of levels: ";
                    while (true) {
                        cin >> tempLevels;
                        if (tempLevels > 0) {
                            break;  // Valid input, exit the loop
                        } else {
                            cout << "Please enter a valid number of levels (>= 0): ";
                        }
                    }
                    break;
                default:
                    cout << "Invalid input. ";
                    continue; // Loop again until valid input is given
            }
            break; // Exit the loop once valid input is received
        }
    }

    // Ask the player if they want to keep inventory between levels
    char keepInventoryInput;
    bool tempKeepInventory = false;  // Default to not keeping inventory

    // Automatically set no inventory for SPEED_RUN_RACE mode
    if (tempGameMode == SPEED_RUN_RACE) {
        tempKeepInventory = false;
    } else {
        // Loop to get valid input for keeping inventory
        while (true) {
            displayCustomGameInventory();  // Display inventory options
            cin >> keepInventoryInput;

            // Check if the player wants to quit
            if (keepInventoryInput == 'Q' || keepInventoryInput == 'q') {
                cout << "Returning to menu..." << endl;
                return;  // Exit the function and return to the menu
            } else if (keepInventoryInput == 'Y' || keepInventoryInput == 'y') {
                tempKeepInventory = true;  // Keep inventory
                break;  // Exit the loop
            } else if (keepInventoryInput == 'N' || keepInventoryInput == 'n') {
                tempKeepInventory = false;  // Don't keep inventory
                break;  // Exit the loop
            } else {
                cout << "Invalid input. ";  // Inform the player of invalid input
                continue;  // Loop again until valid input is given
            }
        }
    }

    // Ask the player to choose puzzle options
    char puzzleInput;
    bool tempPuzzleOptions;

    // Automatically set no puzzle options for SPEED_RUN_RACE mode
    if (tempGameMode == SPEED_RUN_RACE) {
        tempPuzzleOptions = false;
    } else {
        // Loop to get valid input for puzzle options
        while (true) {
            displayCustomGamePuzzleOption();  // Display puzzle options
            cin >> puzzleInput;

            // Check if the player wants to quit
            if (puzzleInput == 'Q' || puzzleInput == 'q') {
                cout << "Returning to menu..." << endl;
                return;  // Exit the function and return to the menu
            } else if (puzzleInput == '1') {
                tempPuzzleOptions = false;  // Random puzzles
                break;
            } else if (puzzleInput == '2') {
                tempPuzzleOptions = true;  // All puzzles
                break;
            } else {
                cout << "Invalid input. ";
                continue; // Loop again until valid input is given
            }
        }
    }

    // Set default value for including enemies
    bool tempincludeEnemies = true; // Default: include enemies

    // Automatically include enemies for certain game modes
    if (tempGameMode == GUARDIAN_ELIMINATION || tempGameMode == SPEED_RUN_RACE) {
        tempincludeEnemies = true;  // Automatically include enemies for GUARDIAN_ELIMINATION and SPEED_RUN_RACE
    } else {
        // Ask the player if they want to include enemies in other game modes
        char enemyInput;
        while (true) {
            displayCustomGameEnemiesOption(); // Display the option to include enemies
            cin >> enemyInput;

            // Return to menu if the user chooses to quit
            if (enemyInput == 'Q' || enemyInput == 'q') {
                cout << "Returning to menu..." << endl;
                return;  // Exit the function and return to the menu
            } else if (enemyInput == 'Y' || enemyInput == 'y') {
                tempincludeEnemies = true;  // Include enemies
                break; // Exit the loop as valid input was given
            } else if (enemyInput == 'N' || enemyInput == 'n') {
                tempincludeEnemies = false; // Do not include enemies
                break; // Exit the loop as valid input was given
            } else {
                cout << "Invalid input. ";
                continue;  // Loop again until valid input is provided
           }
        }
    }

    // Display the summary of custom game settings for confirmation
    clearScreen();  // Clear the screen before displaying confirmation
    //char confirmInput;

    string choosenGameMode = gameModeToString(tempGameMode);
    string choosenDifficulty = (tempDifficulty == EASY ? "Easy" : (tempDifficulty == MEDIUM ? "Medium" : "Hard"));
    string choosenLevels = (tempInfiniteLevels ? "Infinite" : (tempLevels == defaultLevels ? to_string(tempLevels) + " (Default)" : to_string(tempLevels)));
    string choosenInventory = (tempKeepInventory ? "Yes(Carry Items to Next Level)" : "No");
    string choosenPuzzleOptions = (tempPuzzleOptions ? "All" : "Random");
    string choosenIncludeEnemies= (tempincludeEnemies ? "Yes" : "No");

    // Display the confirmation prompt with the selected settings
    confirmCustomSettings(choosenGameMode,choosenDifficulty, choosenLevels, choosenInventory, choosenPuzzleOptions, choosenIncludeEnemies);
    char confirmInput = _getch();
    //cin >> confirmInput;  // Get user input to confirm or reject the settings

    // If the user confirms the settings
    if (confirmInput == 'Y' || confirmInput == 'y') {
        // Apply the confirmed settings to the game
        gameMode = tempGameMode;
        difficulty = tempDifficulty;
        maxLevels = tempLevels;
        infiniteLevels = tempInfiniteLevels;
        keepInventory = tempKeepInventory;
        puzzleOptions = tempPuzzleOptions;
        includeEnemies = tempincludeEnemies;

        this_thread::sleep_for(seconds(1)); 
        cout << "Settings updated. Returning to menu..." << endl;

    } else {
         // If the user does not confirm, no settings are changed
        this_thread::sleep_for(seconds(1)); 
        cout << "Settings remain unchanged. Returning to menu..." << endl;
    }
}

//DONE
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
//DONE
void printMaze(const vector<vector<int>>& maze, const Player& player, const Goal& goal,
               const vector<Enemy>& enemies, const vector<Puzzle>& puzzles,
               const vector<Item>& items, const vector<Portal>& portals,
               const vector<Door>& doors, const vector<Key>& keys, const vector<Sword>& swords) {
 
    // Loop through each row (y-coordinate) of the maze
    for (int y = 0; y < maze.size(); y++) {
        // Loop through each column (x-coordinate) of the maze
        for (int x = 0; x < maze[y].size(); x++) {
            bool printed = false;  // Track if an object has already been printed in the current cell
            bool adjacentToObject = false;  // Track if there are objects adjacent to this cell

            // Check if the current cell is adjacent to any other object
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue; // Skip the current cell

                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < maze[y].size() && ny >= 0 && ny < maze.size()) {
                        // Check for any adjacent objects
                        if (maze[ny][nx] != PATH && maze[ny][nx] != WALL) {
                            adjacentToObject = true;
                            break;
                        }
                    }
                }
                if (adjacentToObject) break;
            }

            // If the cell is adjacent to an object, don't print anything here
            if (adjacentToObject) continue;

            // Check if the goal is at the current position
            if (x == goal.x && y == goal.y) {
                cout << GOAL;  // Display goal as 'G'
                printed = true; // Mark that something has been printed
            }

            if (!printed) {
                // Check if an enemy is at the current position (Enemy overrides player)
                for (const auto& enemy : enemies) {
                    if (x == enemy.x && y == enemy.y) {
                        cout << ENEMY;
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed) {
                // Check if the player is at the current position (only if not printed by enemy)
                if (x == player.x && y == player.y) {
                    cout << PLAYER;
                    printed = true;
                }
            }

            if (!printed) {
                // Check if a puzzle is at the current position
                for (const auto& puzzle : puzzles) {
                    if (x == puzzle.x && y == puzzle.y) {
                        printed = true;

                        // If the puzzle is solved, print a space
                        if (puzzle.solved) {
                            if (player.x == puzzle.x && player.y == puzzle.y) {
                                cout << PLAYER; // Print player if they are on the puzzle
                            } else {
                                cout << ' '; // Player not on solved puzzle
                            }
                        } else {
                            cout << PUZZLE;  // Print puzzle if player is not there
                        }
                        break;
                    }
                }
            }

            if (!printed) {
                // Check if an item is at the current position
                for (const auto& item : items) {
                    if (x == item.x && y == item.y) {
                        cout << ITEM;
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed) {
                // Check if a portal is at the current position
                for (const auto& portal : portals) {
                    if (x == portal.x && y == portal.y) {
                        cout << PORTAL;
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed) {
                // Check if a door is at the current position
                for (const auto& door : doors) {
                    if (x == door.x && y == door.y) {
                        if (!adjacentToObject) {
                            printed = true;
                            // If the door is locked, print an empty space
                            if (door.isOpen) {
                                if (player.x == door.x && player.y == door.y) {
                                    cout << PLAYER; // Print player if they are on the lockec door
                                } else {
                                    cout << ' '; // Print empty space for locked door
                                }
                            } else {
                                cout << DOOR; // Print locked door
                            }
                        }
                        break;
                    }
                }
            }

            if (!printed) {
                // Check if a key is at the current position
                for (const auto& key : keys) {
                    if (x == key.x && y == key.y) {
                        cout << KEY;
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed) {
                // Check if a sword is at the current position
                for (const auto& sword : swords) {
                    if (x == sword.x && y == sword.y) {
                        cout << SWORD;  // Display sword as 'S'
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed) {
                // If nothing was printed, check if the player is at the current position
                if (x == player.x && y == player.y) {
                    cout << PLAYER;  // Display player
                } else {
                    // Otherwise, print the maze structure (wall as '#' or path as ' ')
                    cout << (maze[y][x] == WALL ? '#' : ' ');
                }
            }
        }
        cout << endl; // Print a new line at the end of each row
    }
}
//DONE
void generateMaze(int width, int height, vector<vector<int>>& maze) {
    // Ensure odd width and height for proper wall placement
    if (width % 2 == 0) width++;
    if (height % 2 == 0) height++;

    // Initialize the maze with all walls
    maze.assign(height, vector<int>(width, WALL));

    // Random starting point
    srand(time(0)); // Seed for random number generation
    int startX = (rand() % (width / 2)) * 2 + 1;
    int startY = (rand() % (height / 2)) * 2 + 1;

    // Mark the starting cell as a path
    maze[startY][startX] = PATH;

    // List of walls (pairs of cells)
    vector<Cell> walls;
    walls.push_back(Cell(startX, startY)); // Initialize with the starting cell

    // Process walls to build the maze using Prim's algorithm
    while (!walls.empty()) {
        // Pick a random wall from the list of walls
        int randIndex = rand() % walls.size();
        Cell wall = walls[randIndex];

        // Get the neighbors of the current cell
        vector<Cell> neighbors = getNeighbors(wall.x, wall.y, maze);

        if (!neighbors.empty()) {
            // Pick a random neighboring cell to connect to
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

//DONE
bool isValidMove(int x, int y, const vector<vector<int>>& maze, vector<Puzzle>& puzzles, const vector<Portal>& portals, const vector<Door>& doors) {
   // Check if the move is within bounds
    if (x >= 0 && x < maze[0].size() && y >= 0 && y < maze.size()) {  // Ensure the move is within the maze's boundaries

        // Check if the position is a wall
        if (maze[y][x] == WALL) {
            // If the position is a wall, check if there is a door at this position
            for (const auto& door : doors) {
                if (x == door.x && y == door.y && door.isOpen) {
                    return true;  // Allow movement if there's an open door at this position
                }
            }
            return false;  // Block movement if it's a wall and no door or the door is closed
        }

        // Check if the position contains an unsolved puzzle
        for (const auto& puzzle : puzzles) {
            if (x == puzzle.x && y == puzzle.y && !puzzle.solved) {
                // Block movement if the puzzle is unsolved
                return false;
            }
        }

        return true;  // Allow movement if it's a valid path and no unsolved puzzles are blocking
    } else {
        // Return false if the move is out of bounds or not on a valid path
        return false;
    }
}
//DONE
bool isValidMoveForEnemy(int x, int y, const vector<vector<int>>& maze, vector<Puzzle>& puzzles, const vector<Portal>& portals, const vector<Door>& doors, const vector<Enemy>& enemies) {
    // Check if the move is within bounds and the position is a valid path
    if (x >= 0 && x < maze[0].size() && y >= 0 && y < maze.size() && maze[y][x] == PATH) {

        // Prevent enemy from moving to the goal position
        if (x == goal.x && y == goal.y) {
            return false;  // Enemies cannot move to the goal location
        }

        // Check if the position is an unsolved puzzle
        for (const auto& puzzle : puzzles) {
            if (x == puzzle.x && y == puzzle.y && !puzzle.solved) {
                return false;  // Block movement if the puzzle is unsolved
            }
        }

        // Prevent enemy from moving to a portal location
        for (const auto& portal : portals) {
            if (x == portal.x && y == portal.y) {
                return false;  // Block movement if the position is a portal
            }
        }

        // Prevent enemy from moving to a door that is closed
        for (const auto& door : doors) {
            if (x == door.x && y == door.y && !door.isOpen) {
                return false;  // Block movement if the door is closed
            }
        }

        // Prevent enemy from moving to a cell already occupied by another enemy
        for (const auto& enemy : enemies) {
            if (enemy.x == x && enemy.y == y) {
                return false;  // Block movement if the position is occupied by another enemy
            }
        }

        return true;  // Allow movement if all checks pass
    }
    // Return false if the position is out of bounds or not a valid path
    return false;
}

//DONE
bool checkAndSolvePuzzle(Player& player, vector<Puzzle>& puzzles, vector<vector<int>>& maze, int newX, int newY ) { 
    
    // Iterate through all puzzles in the maze
    for (auto& puzzle : puzzles) {
        
        // Check if the player has encountered an unsolved puzzle at the target position
        if (newX == puzzle.x && newY == puzzle.y && !puzzle.solved) {
            
            // Prompt the player that they have encountered a puzzle
            player.message = "You've encountered a puzzle! Solve it to proceed.";

            // Call the solvePuzzle function to allow the player to attempt solving the puzzle
            bool puzzleSolved = solvePuzzle(difficulty, puzzleOptions);
            
            // If the puzzle is solved, mark it as solved and allow the player to proceed
            if (puzzleSolved == true) {
                puzzle.solved = true;  // Mark the puzzle as solved
                player.message = "You solved the puzzle! You can now proceed.";
                return true;  // Allow movement forward since the puzzle is solved
            } else {
                // If the player fails, display a message and leave the puzzle unsolved
                player.message = "Exiting...The puzzle remains locked.";
            }
            
            return false;  // Exit after handling the puzzle at this position (whether solved or not)
        }
    }
    
    return false;  // Return false if no puzzle is encountered or if the puzzle was already solved
}

//DONE
void openDoorWithKey(Player& player, vector<vector<int>>& maze, int newX, int newY, vector<Door>& doors){   
    // Loop through all doors in the maze to check if one is at the target position (newX, newY)
    for (auto& door : doors) {
        // Check if the player has encountered a closed door at the given position
        if (newX == door.x && newY == door.y && !door.isOpen) {
            
            // Check if the player has a key in their inventory
            if (player.hasItem("KEY")) {
                // Prompt the player if they want to use the key to open the door
                cout << "You found a door! Do you want to use a key to open it? (Y/N): ";
                char choice = _getch();  // Get the player's input (Y or N)
                
                if (choice == 'Y' || choice == 'y') {
                    // Remove the key from the player's inventory
                    player.inventory.erase(remove(player.inventory.begin(), player.inventory.end(), "KEY"), player.inventory.end());

                    // Open the door (set the door's status to open)
                    door.isOpen = true;

                    // Update player message to inform them the door is opened
                    player.message = "Door opened!";
                }
                else {
                    // If the player chooses not to open the door, display this message
                    player.message = "You decided not to use the key.";
                }
            } else {
                // If the player doesn't have a key, inform them that the door is locked
                player.message = "The door is locked. You need a key!";
            }  
            return;  // Exit the function once the door interaction is handled
        }   
    }
}

//DONE
void handlePlayerMovement(Player& player, char input, vector<vector<int>>& maze, vector<Puzzle>& puzzles, const vector<Portal>& portals, vector<Door>& doors) {

    // Store the player's current position
    int newX = player.x, newY = player.y;

    // Determine the direction based on input
    if (input == 'w' || input == 'W') newY--;  // Move up
    else if (input == 's' || input == 'S') newY++;  // Move down
    else if (input == 'a' || input == 'A') newX--;  // Move left
    else if (input == 'd' || input == 'D') newX++;  // Move right

    // Check if the new position is valid (not a wall, within bounds)
    if (isValidMove(newX, newY, maze, puzzles, portals, doors)) { 
        // Update the player's position if the move is valid
        player.x = newX; // newX after increment
        player.y = newY;
    } else {
        bool foundUnsolvedPuzzle = false;
        bool puzzleSolved = false;

        // Check if the player encountered an unsolved puzzle at the new position
        for (const auto& puzzle : puzzles) {
            if (newX == puzzle.x && newY == puzzle.y && !puzzle.solved) {
                foundUnsolvedPuzzle = true;
                // Attempt to solve the puzzle if it's unsolved
                puzzleSolved = checkAndSolvePuzzle(player, puzzles, maze, newX, newY);
                break;  // Exit the loop after attempting to solve the puzzles
            }
        } 

        // If the puzzle is solved, update the player's position
        if (puzzleSolved) {
            player.x = newX;  // Set the player's new X position
            player.y = newY;  // Set the player's new Y position
        } 
       
        // Check if the new position corresponds to a door that is not open
        bool foundUnopenedDoor = false;
        for (auto& door : doors) {
            if (newX == door.x && newY == door.y && !door.isOpen) {
                foundUnopenedDoor = true;
                // Attempt to open the door with a key if the door is closed
                openDoorWithKey(player, maze, newX, newY, doors);
                break;  // Exit the loop after trying to open the door
            }
        }

        // If no valid move (no puzzle solved or door opened), display an invalid move message
        if (!foundUnsolvedPuzzle && !foundUnopenedDoor) {
            player.message = "Invalid move. Try a different direction.\n";
        }
    }
}

// Function for random enemy movement
void moveEnemyRandom(Enemy& enemy, const vector<vector<int>>& maze, 
                     vector<Puzzle>& puzzles, const vector<Portal>& portals, 
                     const vector<Door>& doors,const vector<Enemy>& enemies) {

    // Skip the move if enemy is set to skip the next move
    if (enemy.skipNextMove) {
        enemy.skipNextMove = false;  // Reset the flag for the next turn
        return;  // Skip this turn
    }

    int direction;
    int newX = enemy.x, newY = enemy.y;
    
    do {
        // Randomly choose a direction for movement: 0 = up, 1 = down, 2 = left, 3 = right
        direction = rand() % 4;
        newX = enemy.x;
        newY = enemy.y;

        // Check if the enemy can move in the chosen direction; if so, move
        if (direction == 0 && isValidMoveForEnemy(newX, newY - 1, maze, puzzles, portals, doors, enemies)) {
            newY--;
        }
        else if (direction == 1 && isValidMoveForEnemy(newX, newY + 1, maze, puzzles, portals, doors, enemies)) {
            newY++;
        }
        else if (direction == 2 && isValidMoveForEnemy(newX - 1, newY, maze, puzzles, portals, doors, enemies)) {
            newX--;
        }
        else if (direction == 3 && isValidMoveForEnemy(newX + 1, newY, maze, puzzles, portals, doors, enemies)) {
            newX++;
        }
    // Repeat the process until the enemy actually moves
    } while (newX == enemy.x && newY == enemy.y);
    // Update the enemy's position after a valid move is found
    enemy.x = newX;
    enemy.y = newY;
}

//DONE
//'AI to move enemy towards the player'
void moveEnemyTowardsPlayer(Enemy& enemy, const Player& player, const vector<vector<int>>& maze, vector<Puzzle>& puzzles, const vector<Portal>& portals, const vector<Door>& doors, const vector<Enemy>& enemies) {
    // Skip the move if enemy is set to skip the next move
    if (enemy.skipNextMove) {
        enemy.skipNextMove = false;  // Reset the flag for the next turn
        return;  // Skip this turn
    }
    
    int newX = enemy.x, newY = enemy.y;

    // Check if the enemy should move left, right, up, down towards the player
    if (player.x < enemy.x && isValidMoveForEnemy(enemy.x - 1, enemy.y, maze, puzzles, portals, doors, enemies)) newX--;
    else if (player.x > enemy.x && isValidMoveForEnemy(enemy.x + 1, enemy.y, maze, puzzles, portals, doors, enemies)) newX++;
    if (player.y < enemy.y && isValidMoveForEnemy(enemy.x, enemy.y - 1, maze, puzzles, portals, doors, enemies)) newY--;
    else if (player.y > enemy.y && isValidMoveForEnemy(enemy.x, enemy.y + 1, maze, puzzles, portals, doors, enemies)) newY++;

    // Update the enemy's position to the new coordinates
    enemy.x = newX;
    enemy.y = newY;
}

//DONE
// Function to check if any enemy has caught the player
bool checkEnemyCatchPlayer(Player& player, vector<Enemy>& enemies) {
    
    // Iterate through all enemies in the game
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        // Check if the current enemy is at the same position as the player
        if (it->x == player.x && it->y == player.y) {
            player.message = "A Guardian has caught you!"; 

            // If the player has a sword, they can defeat the enemy
            if (player.hasItem("SWORD")) {
                player.message = "You have killed a guardian with your Sword!";
                it = enemies.erase(it);  // Remove the enemy from the vector as it has been defeated
                // Remove the sword from the player's inventory after use
                player.inventory.erase(remove(player.inventory.begin(), player.inventory.end(), "SWORD"), player.inventory.end());
                return false; 
            } else {
                // If the player doesn't have a sword, they lose a life
                player.loseLife();  // Decrease player's life count

                // Check if the player is still alive after losing a life
                if (!player.isAlive()) {
                    // If the player has an extra life item ("LIFE SHARD"), they can use it to revive
                    if (player.hasItem("LIFE SHARD")) {
                        // Remove the "LIFE SHARD" from the player's inventory and restore one life
                        player.inventory.erase(remove(player.inventory.begin(), player.inventory.end(), "LIFE SHARD"), player.inventory.end());
                        player.message = "You used an extra life!"; 
                        return false; 
                    } else {
                        // If the player has no extra life items, the game is over
                        player.message = "Game Over! You had no lives left ~";  // Set game over message
                        return true;  // Return true to indicate the game is over
                    }
                }
                // If the player is still alive after being caught by the enemy, mark the enemy to skip its next move
                it->skipNextMove = true;
            }
            return false;  // The player was caught by the enemy but is still alive, the game continues
        }
    }
    return false;  // No enemy has caught the player, the game continues as normal
}

//DONE
// Add Item Collection Mechanism
void checkItemCollection(Player& player, vector<Item>& items, vector<Key>& keys, vector<Sword>& swords) {
    // Loop through all items in the maze
    for (int i = 0; i < items.size(); i++) {
        // Check if the player's position matches the item's position
        if (player.x == items[i].x && player.y == items[i].y) {
            // Check if the player's inventory has space for more items
            if (player.inventory.size() < player.inventoryCap) {
                player.collectItem(items[i]);  // Collect the item and add it to the player's inventory
                items.erase(items.begin() + i); // Remove the item from the maze after it's collected
            i--;  // Adjust index after erasing to avoid skipping the next item
            } else {
                player.message = "Inventory is full! Cannot collect " + items[i].name + ".";
            }
        }
    }

    // Loop through all keys in the maze
    for (int i = 0; i < keys.size(); i++) {
        // If player's position matches the key's position
        if (player.x == keys[i].x && player.y == keys[i].y) {
            // Only collect the key if there is space in the inventory
            if (player.inventory.size() < player.inventoryCap) {
                player.collectKey(keys[i]); // Collect the key and add it to the player's inventory
                // Remove the collected key from the list
                keys.erase(keys.begin() + i); // Remove the key from the list after it's collected
                i--;  // Adjust index after erasing to avoid skipping the next key
            } else {
                // Store the message that the inventory is full
                player.message = "Inventory is full! Cannot collect key.";
            }
        }
    }

    // Loop through all swords in the maze
    for (int i = 0; i < swords.size(); i++) {
        // If player's position matches the sword's position
        if (player.x == swords[i].x && player.y == swords[i].y) {
            // Only collect the sword if there is space in the inventory
            if (player.inventory.size() < player.inventoryCap) {
                player.collectSword(swords[i]); // Collect the sword and add it to the player's inventory
                swords.erase(swords.begin() + i); // Remove the collected sword from the list
                i--;  // Adjust index after erasing to avoid skipping the next sword
            } else {
                player.message = "Inventory is full! Cannot collect sword.";
            }
        }
    }
}

//DONE
void keyFunction(Player& player, vector<vector<int>>& maze, vector<Door>& doors) {
 bool doorFound = false;  // Flag to check if a door is found in neighboring cells
    
    // Check neighboring cells (left, right, up, down)
    for (auto& door : doors) {
        if ((player.x - 1 == door.x && player.y == door.y) ||  // Left
            (player.x + 1 == door.x && player.y == door.y) ||  // Right
            (player.x == door.x && player.y - 1 == door.y) ||  // Up
            (player.x == door.x && player.y + 1 == door.y)) {  // Down
            // If the door is closed, open it using a key from the player's inventory
            if (!door.isOpen) {
                player.inventory.erase(remove(player.inventory.begin(), player.inventory.end(), "KEY"), player.inventory.end());
                door.isOpen = true;  // Set the door status to open
                doorFound = true;  // Set flag if door is found and opened
                player.message = "Door opened!";
                break; // Exit the loop once the door is opened
            }
        }
    }
    // If no door was found in the neighboring cells
    if (!doorFound) {
        player.message = "There is no door here!";
    }
}

//DONE
void teleportPlayer(Player& player, const vector<Portal>& portals) {
     // If there are no portals in the maze
    if (portals.empty()) {
        player.message = "No portals to teleport to!";
        return;
    }
    // Randomly selects a portal
    const Portal& portal = portals[rand() % portals.size()];
    player.x = portal.x;  // Set the player's x-coordinate to the portal's x-coordinate
    player.y = portal.y;  // Set the player's y-coordinate to the portal's y-coordinate
    player.message = "Teleported to a portal!";
}

//DONE
// When using 'LIFE SHARD'
void xtraLife(Player& player) {
    player.lives += 1;  // Add one extra life to the player's current lives
    player.message = "Extra life added!";
}

//DOME
void hammerFunction(Player& player, vector<vector<int>>& maze) {
    char direction;  // Variable to store the player's input for the direction
    cout << "\nWhich wall do you want to break? (W: Up, S: Down, A: Left, D: Right): ";  // Prompt player for direction
    
    // Infinite loop to keep asking the player for valid input
    while (true) {
        direction= _getch(); // Capture the player's input (W, A, S, or D)
        
        int newX = player.x, newY = player.y;  // Set initial position

        if (direction == 'w'|| direction == 'W') newY--;  // Up
        else if (direction == 's' || direction == 'A') newY++;  // Down
        else if (direction == 'a' || direction == 'S') newX--;  // Left
        else if (direction == 'd' || direction == 'D') newX++;  // Right
        else {
            player.message = "\nInvalid input! Please enter W/A/S/D: ";
            continue;  // Ask again if input is invalid
        }

        // Check if the new position is within bounds
        if (newX >= 0 && newX < maze[0].size() && newY >= 0 && newY < maze.size()) {
            // Check if the wall is on the border
            if (newX == 0 || newX == maze[0].size() - 1 || newY == 0 || newY == maze.size() - 1) {
                player.message = "You cannot break border walls!";
                break;  // Exit the loop without breaking the wall
            } 
            // If it's a wall
            else if (maze[newY][newX] == WALL) {  
                maze[newY][newX] = PATH;  // Break the wall (turn it into a path)
                player.inventory.erase(remove(player.inventory.begin(), player.inventory.end(), "HAMMER"), player.inventory.end());  // Remove hammer from inventory after use
                player.message = "Wall broken!";
                break;  // Exit the loop
            } else {
                player.message = "There is no wall to break!"; // Notify if the target is not a wall
                break;
            }
        } else {
            // target is out of bounds
            break;
        }
    }
}

//DONE
void swordFunction(Player& player, vector<vector<int>>& maze, vector<Enemy>& enemies) {
    // Check neighboring cells for enemies(Guardian)
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        // Check if the enemy is in a neighboring cell (up, down, left, right)
        if ((it->x == player.x - 1 && it->y == player.y) ||  // Left
            (it->x == player.x + 1 && it->y == player.y) ||  // Right
            (it->x == player.x && it->y == player.y - 1) ||  // Up
            (it->x == player.x && it->y == player.y + 1)) {  // Down
            
            // Enemy (Guardian) found in neighboring cell, "kill" it
            player.message = "You have killed an enemy!";
            
            // Remove the enemy (Guardian) from the enemies vector
            enemies.erase(it);  // Erase the enemy(Guardian) at the iterator position
            player.inventory.erase(remove(player.inventory.begin(), player.inventory.end(), "SWORD"), player.inventory.end());
            return;  // Exit the function after killing the enemy
        }
    }

    // If no enemy was found in the neighboring cells
    player.message = "There is no guardians beside you!";
}

//DONE
// Function to use an item based on its name
void useItemByName(Player& player, const string& itemName, vector<vector<int>>& maze, const Goal& goal, const vector<Portal>& portals, vector<Door>& doors, vector<Enemy>& enemies) {

    // Check the item name and call the corresponding function for that item
    if (itemName == "KEY") {
        keyFunction(player, maze, doors);  
    } else if (itemName == "TELEPORT") {
       teleportPlayer(player, portals);  
    } else if (itemName == "LIFE SHARD") {
       xtraLife(player); 
    }  else if (itemName == "HAMMER") {
       hammerFunction(player, maze);  
    } else if (itemName == "SWORD") {
        swordFunction(player, maze, enemies);
    } else { // Error if the item is not recognized
        player.message = "Unknown item: " + itemName;
    }
}

//done
void chooseInventory(Player& player, vector<vector<int>>& maze, Goal& goal, vector<Portal>& portals, vector<Door>& doors, vector<Enemy>& enemies, vector<Puzzle>& puzzles, vector<Item>& items, vector<Key>& keys, vector<Sword>& swords) {
 // Clear the screen and display the maze again
    clearScreen();  // Clear console screen
    printMaze(maze, player, goal, enemies, puzzles, items, portals, doors, keys, swords);

    // Display player's inventory
    if (player.inventory.empty()) {
        cout << "Inventory: Empty" << endl;
    } else {
        cout << "Inventory: ";
        int i = 1;  // Start the index at 1
        for (const auto& item : player.inventory) {
            cout << "(" << i << ") " << item << " ";  // Display item with corresponding index
            i++;
        }
        cout << endl;
    }

    // Loop for player to select an item to use or discard
    while (true) {
        cout << "\nInput number to use or discard item (Enter 'Q' to go back to maze): ";
        char playerInput = _getch();  // Get input 

        // Check if the player wants to go back to the maze
        if (playerInput == 'q' || playerInput == 'Q') {
            return;  // Exit the inventory menu
        }

        // Convert input to an inventory index
        int itemIndex = playerInput - '1'; // Convert input
        if (itemIndex < 0 || itemIndex >= player.inventory.size()) { // Handle invalid item selection
            cout <<  "\nInvalid item number, please try again.";
            this_thread::sleep_for(seconds(1)); // Pause for a second before clearing the screen
            clearScreen(); 
            printMaze(maze, player, goal, enemies, puzzles, items, portals, doors, keys, swords);

            // Redisplay the inventory with updated content
            cout << "Inventory: ";
            for (int i = 1; i <= player.inventory.size(); ++i) {
                cout << "(" << i << ") " << player.inventory[i - 1] << " ";
            }
            continue;  // Prompt again for valid input
        }


        // If valid input, ask the player if they want to discard the item
        string itemName = player.inventory[itemIndex];
        cout << "\nYou selected " << itemName << ". Do you want to use (U) or discard (D) it? ";
        char actionInput = _getch();  // Get input without requiring Enter

        // Check if the player wants to discard the item
        if (actionInput == 'd' || actionInput == 'D') {
            cout << "\nDiscarding " << itemName << "...";
            player.inventory.erase(player.inventory.begin() + itemIndex); // Remove item from inventory
            this_thread::sleep_for(seconds(1));  // Pause before exiting inventory menu
            return;  // Exit the inventory menu after discarding
        }

        // If they choose to use the item
        if (actionInput == 'u' || actionInput == 'U') {
            useItemByName(player, itemName, maze, goal, portals, doors, enemies);// Use the item based on its name

            // Remove the item from inventory if it is not Key, Hammer or Sword
            if (itemName != "KEY" && itemName != "HAMMER" && itemName != "SWORD") {
                player.inventory.erase(player.inventory.begin() + itemIndex);
            }    
            break;  // Exit the loop after using the item
        }
        // If invalid action input, re-prompt
        cout << "\nInvalid action. Please select U to use or D to discard.";
    }
}
//done
bool updateGameProgress(Player& player, vector<Enemy>& enemies, vector<Puzzle>& puzzles, GameMode gameMode) {
    bool gameModeConditionMet = false; // Variable to track if the game mode condition is met

    // Switch statement to handle different game modes and their respective win conditions
    switch (gameMode) {
        case DEFAULT:
                // Default win condition: Progress automatically when reaching the goal
                gameModeConditionMet = true;
            break;

        case PUZZLE_COMPLETION:
            // Win condition: All puzzles must be solved
            for (const auto& puzzle : puzzles) {
                if (puzzle.solved) {
                gameModeConditionMet = true; // Mark as true if puzzle is solved
                } else {
                    // If a puzzle remains unsolved
                    player.message = "Complete all puzzles to proceed to the next level";
                }
            }
            break;

        case GUARDIAN_ELIMINATION:
            // Win condition: All enemies(Guardians) must be killed
            if (enemies.empty()) {
                gameModeConditionMet = true;  // Mark as true if no enemies(Guardians) remain
            } else {
                // If enemies (Guardian) remain
            player.message = "Kill all Guardians to proceed to the next level";
            }
            break;

        default:
            //Progress automatically when reaching the goal
            gameModeConditionMet = true;
            break;

    }
    return gameModeConditionMet;
}

//DONE
void updateGameElements(const GameLevel& levelConfig, 
                        int width, int height, 
                        vector<vector<int>>& maze, 
                        Player& player, 
                        Goal& goal, 
                        vector<Enemy>& enemies, 
                        vector<Puzzle>& puzzles, 
                        vector<Item>& items, 
                        vector<Portal>& portals, 
                        vector<Door>& doors, 
                        vector<Key>& keys, 
                        vector<Sword>& swords) {

    // Minimum distance constants to ensure game elements are not too close to each other
    int minDistanceFromPlayer = 3; 
    int minDistanceFromGoal = 3;
    int minDistanceBetweenEnemies = 4; // Minimum distance between enemies
  
    // Set the goal's position to the bottom-right corner of the maze
    goal.x = levelConfig.width - 2;
    goal.y = levelConfig.height - 2;

    // Clear the existing enemies list and then generate new enemy positions
    enemies.clear();
    for (int i = 0; i < levelConfig.numEnemies; i++) {
        int enemyX, enemyY;
        bool validPosition;

        // Keep trying to place the enemy until a valid position is found
        do {
          validPosition = true;
          // Generate random enemy coordinates
          enemyX = (rand() % (width - 2)) + 1;
          enemyY = (rand() % (height - 2)) + 1;

          // Check if the position is valid (not on the player, too close to the player, or too close to the goal)
          if (maze[enemyY][enemyX] != PATH || 
              (enemyX == player.x && enemyY == player.y) ||
              manhattanDistance(enemyX, enemyY, player.x, player.y) < minDistanceFromPlayer ||
              manhattanDistance(enemyX, enemyY, goal.x, goal.y) < minDistanceFromGoal) {
              validPosition = false;
          } else {
              // Ensure the enemy is not too close to other enemies
              for (const auto& existingEnemy : enemies) {
                  if (manhattanDistance(enemyX, enemyY, existingEnemy.x, existingEnemy.y) < minDistanceBetweenEnemies) {
                      validPosition = false;
                      break;
                  }
              }
          }
      } while (!validPosition); // Keep trying until a valid position is found
      enemies.push_back(Enemy(enemyX, enemyY)); // Add the enemy to the enemies list
    }

    // Clear and generate new puzzle positions
    puzzles.clear();
    for (int i = 0; i < levelConfig.numPuzzles; i++) {
        int puzzleX, puzzleY;
        do {
            puzzleX = (rand() % (width - 2)) + 1;
            puzzleY = (rand() % (height - 2)) + 1;
        } while (maze[puzzleY][puzzleX] != PATH || (puzzleX == player.x && puzzleY == player.y)|| // Avoid player position
            manhattanDistance(puzzleX, puzzleY, player.x, player.y) < minDistanceFromPlayer||  
            manhattanDistance(puzzleX, puzzleY, goal.x, goal.y) < minDistanceFromGoal);
        puzzles.push_back(Puzzle(puzzleX, puzzleY)); // Add the puzzle to the puzzles list
    }
    
  // Clear and generate new item positions
    items.clear();
    vector<string> itemNames = {"HAMMER", "TELEPORT", "LIFE SHARD"}; // List of item names
    //loop generates random coordinates (itemX, itemY) for the item inside the maz
    for (int i = 0; i < levelConfig.numItems; i++) {
        string itemName = itemNames[rand() % itemNames.size()]; // Randomly select an item name
        int itemX, itemY;
        do {
            itemX = (rand() % (width - 2)) + 1;
            itemY = (rand() % (height - 2)) + 1;
        } while (maze[itemY][itemX] != PATH || (itemX == player.x && itemY == player.y)); // Avoid player position
        items.push_back(Item(itemX, itemY, itemName)); // Add the item to the items list
    }
    // Clear and generate new portal positions
    portals.clear();
    for (int i = 0; i < levelConfig.numPortals; i++) {
        int portalX, portalY;
        do {
            portalX = (rand() % (width - 2)) + 1;
            portalY = (rand() % (height - 2)) + 1;
        } while (maze[portalY][portalX] != PATH || (portalX == player.x && portalY == player.y)||  
            manhattanDistance(portalX, portalY, goal.x, goal.y) < minDistanceFromGoal);
        portals.push_back(Portal(portalX, portalY)); // Add the portal to the portals list
    }

    // Clear and generate new door positions
    doors.clear();
    for (int i = 0; i < levelConfig.numDoors; i++) {
        int doorX, doorY;
        do {
            doorX = (rand() % (width - 2)) + 1;
            doorY = (rand() % (height - 2)) + 1;
        } while (maze[doorY][doorX] != WALL || (doorX == player.x && doorY == player.y)|| // Avoid player position
            manhattanDistance(doorX, doorY, player.x, player.y) < minDistanceFromPlayer);  // Place doors on walls
        doors.push_back(Door(doorX, doorY)); // Add the door to the doors list
    }
    // Clear and generate new key positions
    keys.clear();
    for (int i = 0; i < levelConfig.numKeys; i++) {
        int keyX, keyY;
        do {
            keyX = (rand() % (width - 2)) + 1;
            keyY = (rand() % (height - 2)) + 1;
        } while (maze[keyY][keyX] != PATH || (keyX == player.x && keyY == player.y)); // Avoid player position
        keys.push_back(Key(keyX, keyY));// Add the key to the keys list
    }

    // Clear and generate new sword positions
    swords.clear();
    for (int i = 0; i < levelConfig.numSwords; i++) {
        int swordX, swordY;
        do {
            swordX = (rand() % (width - 2)) + 1;
            swordY = (rand() % (height - 2)) + 1;
        } while (maze[swordY][swordX] != PATH || (swordX == player.x && swordY == player.y)|| // Avoid player position
            manhattanDistance(swordX, swordY, player.x, player.y) < minDistanceFromPlayer); // Ensure swords are not too close to the playerplayer's starting position
        swords.push_back(Sword(swordX, swordY)); // Add the sword to the swords list
    }
}

//done
void saveGame(const string& gameIndexStr) {
                
    // Load existing game saves (if any)
    ifstream loadFile("savegame.json");
    json allGamesData;
    
    // Check if the file exists and can be opened
    if (loadFile) {
        try {
            // If the file is open, try to read the contents into allGamesData
            loadFile >> allGamesData;
            loadFile.close();
        } catch (const json::parse_error& e) {
            // If there's an error in parsing, log it and proceed with an empty json object
            cerr << "Error parsing JSON: " << e.what() << endl;
            allGamesData = json::object(); // Initialize with empty object in case of error
        }
    } else {
        // If the file doesn't exist, create a new empty game save
        cerr << "savegame.json not found, creating a new save." << endl;
        allGamesData = json::object();
    }

    // New json object for the current game's data
    json gameData;

    // Initialize the maze 2D array in JSON format
    gameData["maze"] = json::array();
    for (int y = 0; y < maze.size(); ++y) {
        json row = json::array();  // Create a new row for the maze
        for (int x = 0; x < maze[y].size(); ++x) {
            row.push_back(maze[y][x]);  // Add each cell to the row
        }
        gameData["maze"].push_back(row);  // Add the row to the maze array
    }

    // Store player data in gameData
    gameData["Player"] = {
        {"x", player.x},
        {"y", player.y},
        {"name", player.name},
        {"inventory", player.inventory},
        {"inventorycap", player.inventoryCap},
        {"lives", player.lives},
        {"message", player.message}
    };

    // Store custom game settings
    gameData["CustomGame"] = {
        {"GameMode", gameMode},
        {"Infinitelevels", infiniteLevels},
        {"NumOfLevels", maxLevels},
        {"Difficulty", difficulty},
        {"Puzzle", puzzleOptions},
        {"Enemies", includeEnemies}
    };

    // Store the current game state
    gameData["CurrentGame"] = {
        {"CurrentLevel", currentLevel},
        {"StartGame", startGame},
        {"levelTime", levelTime},
        {"totalTime", totalTime},
        {"levelStarted", levelStarted},
        {"gameStarted", gameStarted},
        {"savedDateTime", savedDateTime},
        {"gameOver", gameOver},
    };
    // Store level configuration
    gameData["CurrentGame"]["GameLevel"] = {
        {"width", levelConfig.width},
        {"height", levelConfig.height}
    };
    // Store goal data (position of the goal)
    gameData["CurrentGame"]["GameLevel"]["goal"] = {
        {"goalX", goal.x},
        {"goalY", goal.y}
    };
    // Store items data (positions and names of items)
    for (const auto& item : items) {
        gameData["Items"].push_back({
            {"x", item.x},
            {"y", item.y},
            {"name", item.name}
        });
    }
    // Store portal data (positions of portals)
    for (const auto& portal : portals) {
        gameData["Portals"].push_back({
            {"x", portal.x},
            {"y", portal.y}
        });
    }
    // Store door data (positions and open status of doors)
    for (const auto& door : doors) {
        gameData["Doors"].push_back({
            {"x", door.x},
            {"y", door.y},
            {"isOpen", door.isOpen}
        });
    }
    // Store key data (positions and names of keys)
    for (const auto& key : keys) {
        gameData["Keys"].push_back({
            {"x", key.x},
            {"y", key.y},
            {"name", key.name}
        });
    }
    // Store sword data (positions and names of swords)
    for (const auto& sword : swords) {
        gameData["Swords"].push_back({
            {"x", sword.x},
            {"y", sword.y},
            {"name", sword.name}
        });
    }
    // Store enemy data (positions and state of enemies)
    for (const auto& enemy : enemies) {
        gameData["Enemies"].push_back({
            {"x", enemy.x},
            {"y", enemy.y},
            {"skipNextMove", enemy.skipNextMove}
        });
    }
    // Store puzzle data (positions and solved status of puzzles)
    for (const auto& puzzle : puzzles) {
        gameData["Puzzles"].push_back({
            {"x", puzzle.x},
            {"y", puzzle.y},
            {"solved", puzzle.solved}
        });
    }

    // Update or add the current game data to allGamesData
    if (allGamesData.contains(gameIndexStr)) {
        // If the game already exists, update it
        allGamesData[gameIndexStr] = gameData;
    } else {
        // If this is a new game, add it
        allGamesData[gameIndexStr] = gameData;
    }

    // Save the updated game data to the save file
    ofstream file("savegame.json");
    file << allGamesData.dump(4); // Pretty print with indentation
    file.close();
}

//DONE
void loadGame(const string& gameIndexStrParam) {
    clearGameData();  // Clear existing game data before loading the saved game

    ifstream inputFile("savegame.json");  // Open the saved game file
    if (!inputFile.is_open()) {
        cerr << "Failed to open save file.\n";  // Handle failure to open the file
        return;
    }

    json saveData;  // Declare a variable to hold the parsed JSON data
    inputFile >> saveData;  // Read the contents of the file into saveData
    inputFile.close();  // Close the file after reading

    // Check if the provided game index exists in the loaded save data
    if (!saveData.contains(gameIndexStrParam)) {
        cerr << "Save data for gameIndex " << gameIndex << " not found.\n";
        return;
    }

    // Extract the data for the specific game index
    json gameData = saveData[gameIndexStrParam];

    // Load player data from the saved game
    player.x = getValueOrDefault<int>(gameData["Player"], "x", 1);
    player.y = getValueOrDefault<int>(gameData["Player"], "y", 1);
    player.name = getValueOrDefault<string>(gameData["Player"], "name", "Nil");
    player.inventory = getValueOrDefault<vector<string>>(gameData["Player"], "inventory", vector<string>());
    player.inventoryCap = getValueOrDefault<int>(gameData["Player"], "inventorycap", 0);
    player.lives = getValueOrDefault<int>(gameData["Player"], "lives", 0);
    player.message = getValueOrDefault<string>(gameData["Player"], "message", "");

    // Load Custom Game data
    gameMode = static_cast<GameMode>(getValueOrDefault<int>(gameData["CustomGame"], "GameMode", 0)); // Default to 0 (EASY)
    infiniteLevels = getValueOrDefault<bool>(gameData["CustomGame"], "Infinitelevels", false);
    maxLevels = getValueOrDefault<int>(gameData["CustomGame"], "NumOfLevels", 10);
    difficulty = static_cast<Difficulty>(getValueOrDefault<int>(gameData["CustomGame"], "Difficulty", 0)); // Default to 0 (EASY)
    puzzleOptions = getValueOrDefault<bool>(gameData["CustomGame"], "Puzzle", false);
    includeEnemies = getValueOrDefault<bool>(gameData["CustomGame"], "Enemies", true);

    // Load Current Game data
    currentLevel = getValueOrDefault<int>(gameData["CurrentGame"], "CurrentLevel", 1);
    startGame = getValueOrDefault<bool>(gameData["CurrentGame"], "StartGame", false);//
    levelTime = getValueOrDefault<int>(gameData["CurrentGame"], "levelTime", 0);
    totalTime = getValueOrDefault<int>(gameData["CurrentGame"], "totalTime", 0);
    levelStarted = getValueOrDefault<bool>(gameData["CurrentGame"], "levelStarted", false);// for timer
    gameStarted = getValueOrDefault<bool>(gameData["CurrentGame"], "gameStarted", false); //for timer
    savedDateTime = getValueOrDefault<string>(gameData["CurrentGame"], "savedDateTime", "");
    gameOver = getValueOrDefault<bool>(gameData["CurrentGame"], "gameOver", true); //

    // Load Game Level data
    levelConfig.width = getValueOrDefault<int>(gameData["CurrentGame"]["GameLevel"], "width", 10);
    levelConfig.height = getValueOrDefault<int>(gameData["CurrentGame"]["GameLevel"], "height", 10);
    goal.x = getValueOrDefault<int>(gameData["CurrentGame"]["GameLevel"]["goal"], "goalX", levelConfig.width - 2);
    goal.y = getValueOrDefault<int>(gameData["CurrentGame"]["GameLevel"]["goal"], "goalY", levelConfig.height  -2);
    
    // Load the maze data and resize the maze to match the level's dimensions
    maze.clear();
    maze.resize(levelConfig.height, vector<int>(levelConfig.width));

    // Load the maze data from the gameData
    if (gameData["maze"].is_array()) {
        for (int y = 0; y < levelConfig.height; ++y) {
            if (gameData["maze"][y].is_array()) {
                for (int x = 0; x <levelConfig.width; ++x) {
                    if (gameData["maze"][y][x].is_number()) {
                        maze[y][x] = gameData["maze"][y][x].get<int>(); // Load each maze cell
                    }
                }
            }
        }
    }

    items.clear();  // Clear the existing items
    if (gameData.contains("Items") && gameData["Items"].is_array() && !gameData["Items"].empty()) {
        for (const auto& itemInfo : gameData["Items"]) {
            Item item(itemInfo["x"], itemInfo["y"], itemInfo["name"]);
            items.push_back(item); // Add each item to the game
        }
    } else {
        cerr << "'Items' is missing or empty!" << endl;
    }

    // Load portals from the saved game
    portals.clear();  
    if (gameData.contains("Portals") && gameData["Portals"].is_array() && !gameData["Portals"].empty()) {
        for (const auto& portalInfo : gameData["Portals"]) {
            Portal portal(portalInfo["x"], portalInfo["y"]);
            portals.push_back(portal); // Add each portal to the game
        }
    } else {
        cerr << "'Portals' is missing or empty!" << endl;
    }

    // Load doors from the saved game
    doors.clear();
    if (gameData.contains("Doors") && gameData["Doors"].is_array() && !gameData["Doors"].empty()) {
        for (const auto& doorInfo : gameData["Doors"]) {
            Door door(doorInfo["x"], doorInfo["y"]);
            door.isOpen = doorInfo["isOpen"]; // Set the door's open/closed state
            doors.push_back(door);  // Add each door to the game
        }
    } else {
        cerr << "'Doors' is missing or empty!" << endl; // Handle missing or empty doors data
    }
    
    // Load keys from the saved game
    keys.clear();
    if (gameData.contains("Keys") && gameData["Keys"].is_array() && !gameData["Keys"].empty()) {
        for (const auto& keyInfo : gameData["Keys"]) {
            Key key(keyInfo["x"], keyInfo["y"], keyInfo["name"]);
            keys.push_back(key); // Add each key to the game
        }
    } else {
            cerr << "'Keys' is missing or empty!" << endl;
    }

     // Load swords from the saved game
    swords.clear();
    if (gameData.contains("Swords") && gameData["Swords"].is_array() && !gameData["Swords"].empty()) {
        for (const auto& swordInfo : gameData["Swords"]) {
            Sword sword(swordInfo["x"], swordInfo["y"], swordInfo["name"]);
            swords.push_back(sword);  // Add each sword to the game
        }
    } else {
        cerr << "'Swords' is missing or empty!" << endl;
    }
    // Load enemies (guardians) from the saved game
    enemies.clear();
    if (gameData.contains("Enemies") && gameData["Enemies"].is_array() && !gameData["Enemies"].empty()) {
        for (const auto& enemyInfo : gameData["Enemies"]) {
            Enemy enemy(enemyInfo["x"], enemyInfo["y"]);
            enemy.skipNextMove = enemyInfo["skipNextMove"]; // Set whether the enemy skips its next move
            enemies.push_back(enemy); // Add each enemy (guardians) to the game
        }
    } else {
        cerr << "'Enemies' is missing or empty!" << endl; // Handle missing or empty enemies data
    }

    // Load puzzles from the saved game
    puzzles.clear();
    if (gameData.contains("Puzzles") && gameData["Puzzles"].is_array() && !gameData["Puzzles"].empty()) {
        for (const auto& puzzleInfo : gameData["Puzzles"]) {
            Puzzle puzzle(puzzleInfo["x"], puzzleInfo["y"]);
            puzzle.solved = puzzleInfo["solved"];  // Set whether the puzzle is solved
            puzzles.push_back(puzzle); // Add each puzzle to the game
        }
    } else {
        cerr << "'Puzzles' is missing or empty!" << endl;
    }

    gameIndexStr = gameIndexStrParam; // Set the game index string for the loaded game
    loadingGame = true;  // Set flag to indicate that the game is currently being loaded
}

//DONE
void printGame(Player& player, int currentLevel, const vector<vector<int>>& maze, 
               const vector<Enemy>& enemies, const vector<Item>& items, 
               const vector<Puzzle>& puzzles, const Goal& goal, 
               const vector<Portal>& portals, const vector<Door>& doors, 
               const vector<Key>& keys, const vector<Sword>& swords, 
               Difficulty difficulty, GameMode gameMode) {
    clearScreen();  // Clear the console screen

    // Check the current game mode to display appropriate time info   
    if (gameMode == COUNTDOWN_CHALLENGE){
        // For COUNTDOWN_CHALLENGE, display remaining time for the level
        countdownTimeRemaining = getCountdownTimeRemaining();
    } else {
        // For other game modes, display level time and total time
        levelTime = getLevelTimeInSeconds();
        totalTime = getTotalTimeInSeconds();
    }
    
    // Convert the game mode and difficulty to strings for display
    string displayGameMode = gameModeToString(gameMode);
    string displayGameDifficulty = difficultyToString(difficulty);
     
    // Display the top game menu with mode, level, and time information
    topGameMenu(displayGameMode, currentLevel, displayGameDifficulty, totalTime , levelTime, countdownTimeRemaining);

    // Print the maze, player, enemies, etc.
    printMaze(maze, player, goal, enemies, puzzles, items, portals, doors, keys, swords);
    
    int displayPlayerLives = player.lives;
    int displayPlayerInventoryCap = player.inventoryCap;

    // Setup the player's inventory display
    string displayInventory;
    if (player.inventory.empty()) {
        displayInventory = "EMPTY";
    } else {
        for (const auto& item : player.inventory) {
            displayInventory += " " + item + " |"; 
        }
    }

    // Display player's message (if any)
    string displayPlayerMessage = player.message;

    // Call function to display the bottom game menu with player status
    bottomGameMenu(displayPlayerLives, displayPlayerInventoryCap, displayInventory, displayPlayerMessage);
    // Clear the player's message after displaying it
    player.message.clear();
}

//DONE
void displayLeaderboard() {
    json allGamesData; // Variable to hold the entire game save data

    // Load existing game saves (if any)
    ifstream file("savegame.json");

    // Check if the file is empty (no games data)
    if (file.peek() == ifstream::traits_type::eof()) {
        cout << "No available leaderboard data! Press Enter to go back to menu.";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    // If the file is not empty, load the game data from the file
    if (file) {
        file >> allGamesData;  // Parse JSON data from the file
        file.close();  // Close the file after reading
    } else {
        cerr << "Error: Could not open savegame.json for loading!" << endl;  // Display error if file opening fails
        return;  // Exit the function if file couldn't be opened
    }

    // Create a vector to store the games that match the criteria (tuple foprmat)
    vector<tuple<int, string, string, int, int>> leaderboardGames;

    // Loop through all saved games and collect relevant information
    for (auto& gameIndex : allGamesData.items()) {
        json gameData = gameIndex.value();

        // Extract relevant game data
        bool gameOver = getValueOrDefault<bool>(gameData["CurrentGame"], "gameOver", false);
        int gameMode = getValueOrDefault<int>(gameData["CustomGame"], "GameMode", 0); // Default to 0

        // If the game is over and the game mode is 3 (SPEED RUN RACE), add the game to the leaderboard
        if (gameOver && gameMode == 3) { 
            string playerName = getValueOrDefault<string>(gameData["Player"], "name", "Nil");
            string savedDateTime = getValueOrDefault<string>(gameData["CurrentGame"], "savedDateTime", "");
            int currentLevel = getValueOrDefault<int>(gameData["CurrentGame"], "CurrentLevel", 1);
            int totalTime = getValueOrDefault<int>(gameData["CurrentGame"], "totalTime", 0);  // Get total time

            // Add game to leaderboard vector
            leaderboardGames.push_back(make_tuple(currentLevel, playerName, savedDateTime, totalTime, leaderboardGames.size() + 1));
        }
    }

    // If no games to displayed
    if (leaderboardGames.empty()) {
        displayEmptyLeaderboard();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return ;
    }

    // Sort leaderboardGames by level first, and by total time if levels are the same
    sort(leaderboardGames.begin(), leaderboardGames.end(), [](const auto& a, const auto& b) {
        if (get<0>(a) != get<0>(b)) {
            return get<0>(a) > get<0>(b);  // Sort by level (descending)
        }
        return get<3>(a) < get<3>(b);  // If levels are equal, sort by total time (ascending)
    });

    // Assign ranks after sorting
    for (int i = 0; i < leaderboardGames.size(); ++i) {
        get<4>(leaderboardGames[i]) = i + 1;  // Assign rank based on sorted order
    }

    // Display the leaderboard with all collected game data
    displayLeaderboardWithDetails(leaderboardGames);

    // Player can only input 'Q' to go back to the menu
    char userInput;
    while (true) {
        cout << "Press 'Q' to go back to menu: ";
        cin >> userInput;

        // Check if the user input is 'Q' or 'q' to exit to the menu
        if (userInput == 'Q' || userInput == 'q') {
            return ;  // Exit to menu
        } else {
            cout << "Invalid input! Please press 'Q' to go back to the menu.\n";
        }
    }
}

//DONE
bool displaySavedGames() {
    json allGamesData;

    // Load existing game saves (if any)
    ifstream file("savegame.json");
    
    // Check if the file is empty (no saved game data available)
    if (file.peek() == ifstream::traits_type::eof()) {
        // If the file is empty
        noSavedGamesDisplayed();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore any leftover input
        cin.get();  // Wait for user input before returning to the menu
        return false; 
    }

    // If file is successfully opened, load the data from the JSON file
    if (file) {
        file >> allGamesData;  // Parse JSON data from the file
        file.close();  // Close the file after reading
    } else {
        cerr << "Error: Could not open savegame.json for loading!" << endl;  // Display error if file opening fails
        return false; 
    }

    // Display the header for the saved games list
    cout << "==================================================================================" << endl;
    cout << "                          === AVAILABLE SAVED GAMES ===                           " << endl;
    cout << "==================================================================================" << endl;
    cout << "      Enter the number of the game you want to load (or 0 to return to menu)      " << endl;

    int gameCount = 1;  // Counter to keep track of game number
    vector<string> gameKeys;  // Vector to store keys (indexes) of the saved games
    bool gameDisplayed = false;  // Flag to check if any valid game was displayed

    // Loop through all saved games and display relevant information for each
    for (auto& gameIndex : allGamesData.items()) {
        json gameData = gameIndex.value();  // Get data for the current game
        //gameKeys.push_back(gameIndex.key());  // Store the game key (index)

        // Extract relevant game data
        bool gameStarted = getValueOrDefault<bool>(gameData["CurrentGame"], "gameStarted", false);  // Check if the game has started
        bool gameOver = getValueOrDefault<bool>(gameData["CurrentGame"], "gameOver", true);  // Check if the game is over
       
        // Display game if it's started and not over   
        if (gameStarted && !gameOver) {
            gameKeys.push_back(gameIndex.key());  // Store the game key (index)
            gameDisplayed = true; // Flag indicating at least one game was displayed
            // Extract relevant game data
            string gameIndexStr = gameIndex.key();  // Get the index (key) of the current game
            int currentLevel = getValueOrDefault<int>(gameData["CurrentGame"], "CurrentLevel", 1);
            string playerName = getValueOrDefault<string>(gameData["Player"], "name", "Nil");
            GameMode gameMode = static_cast<GameMode>(getValueOrDefault<int>(gameData["CustomGame"], "GameMode", 0)); // Default to 0 (DEFAULT)
            string displayGameMode = gameModeToString(gameMode);
            bool infiniteLevels = getValueOrDefault<bool>(gameData["CustomGame"], "Infinitelevels", false);
            int maxLevels = getValueOrDefault<int>(gameData["CustomGame"], "NumOfLevels", 10);
            string numOfLevels = (infiniteLevels ? "Infinite" : to_string(maxLevels));
            Difficulty difficulty = static_cast<Difficulty>(getValueOrDefault<int>(gameData["CustomGame"], "Difficulty", 0)); // Default to 0 (EASY)
            string displayDifficulty = difficultyToString(difficulty);
            bool puzzleOptions = getValueOrDefault<bool>(gameData["CustomGame"], "Puzzle", false);
            bool includeEnemies = getValueOrDefault<bool>(gameData["CustomGame"], "Enemies", true);
            string savedDateTime = getValueOrDefault<string>(gameData["CurrentGame"], "savedDateTime", "");
        
            // Display the saved game details
            displayingSavedGames(gameCount, savedDateTime, playerName, currentLevel, numOfLevels, displayGameMode, displayDifficulty, puzzleOptions, includeEnemies);
            gameCount++; // Increment the game count for next game
        }
    }
    // Display footer for the saved games list
    cout << "==================================================================================" << endl;
    
    int choice = -1;

    // Loop until a valid choice is made or 0 is entered to return to the menu
    while (true) {
        cin >> choice;  // Get user's choice

        // Check if the input is valid
        if (cin.fail()) {
            cin.clear();  // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore any bad input
            continue;  // Ask for input again
        }

        // If choice is 0, return to the menu
        if (choice == 0) {
            return false;  // Exit the function and return to the menu
        }

        // Check if the choice is valid (within the range of saved games)
        if (choice > 0 && choice <= gameCount - 1) {
            string selectedGameKey = gameKeys[choice - 1];  // Get the key for the selected game

            // Confirm with the user if they want to load the selected game
            char confirm;
            while (true) {
                cout << "> Are you sure you want to load this game? (Y/N): ";
                cin >> confirm;

                // If confirmation is 'Y' or 'y', load the game
                if (confirm == 'Y' || confirm == 'y') {
                    loadGame(selectedGameKey);  // Load the selected game
                    return true;  // Return true to indicate successful game load
                } 
                // If confirmation is 'N' or 'n', break the loop to choose another game
                else if (confirm == 'N' || confirm == 'n') {
                    break;  // Break and return to game selection
                } 
                // If input is invalid, ask again for confirmation
                else {
                    cout << "> Invalid input. Please enter 'Y' or 'N'.\n";
                }
            }
        } else {
            // If the choice is invalid, prompt the user again
            cout << "> Invalid choice! (Enter a number between 1 - " << gameCount - 1 << ")";
            cin.clear();  // Clear any error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore remaining input
            continue;  // Stay in the function until valid input is given
        }
    }
    return false;  // Return false if no valid game is selected or loaded
}

//done
bool showMenu() {
    char selection;  // Variable to store the user's menu choice

    while (true) { // Loop indefinitely until a valid selection is made
        
        // Prepare strings to display current game settings in the menu
        string displayGameMode = gameModeToString(gameMode);
        string displayDifficultyType = difficultyToString(difficulty);
        string displayNumOfLevels = (infiniteLevels ? "Infinite" : to_string(maxLevels));
        string displayGameModeDiscription = gameModeDiscription(displayGameMode);
        
        // Display the menu to the user with the current settings
        displayMenu(displayGameMode, displayDifficultyType, displayNumOfLevels, displayGameModeDiscription);

        selection = _getch();  // Get user input for menu selection 
        
        // Handle the user's menu selection
        switch (selection) {
            case '1':
                return true;  // Start the game
                break;
            case '2':
                clearScreen();
                displayLeaderboard();  // Display the leaderboard
                break;
            case '3': 
               clearScreen();
               customGame(); // Start the custom game setup
               break;
            case '4':
                clearScreen();
                if (displaySavedGames()) { 
                    return true;  // Start the loaded game
                }
                break;       
            case '5':
                clearScreen();
                exitGame();
                exit(0);  // Exit the program
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }
    return false;
}

//DONE
//FUCNTION FOR 1ST LEVEL & GENERATE NEW LEVEL (added during trip(29Dec))
void setUpForLevel(){

    // Retrieve level configuration based on the current level and difficulty
    levelConfig = setLevel(currentLevel, difficulty);  
    width = levelConfig.width;  // Get the width of the maze 
    height = levelConfig.height; // Get the height of the maze
    
    player.setPlayerPoint(1, 1);  // Set the player's initial position at the top-left corner
    player.lives = levelConfig.playerLives;  // Set the player's number of lives based on level config
    player.inventoryCap = levelConfig.inventoryCap;  // Set the player's inventory capacity for the level

    // Generate the maze based on the configured width and height
    generateMaze(width, height, maze); 
    // Update the game elements
    updateGameElements(levelConfig, width, height, maze, player, goal, 
                       enemies, puzzles, items, portals, doors, keys, swords);  
}

//DONE
int main() {

    while (true) {  // Start program: Main loop to return to the menu after the game ends
        
        if (!showPrologue){
            clearScreen();  // Clear the console screen
            displayPrologue(); // Display Prologue
            cin.get();// Wait for user input to continue
            showPrologue = true;
        }

        clearScreen(); 
        startGame = showMenu(); // Wait for user input to continue

        if (startGame) { // Start the Maze Game
            if (!loadingGame) { // If its first game (not loading a saved game)
                if (gameIndexStr == "") {
                    // Initialize game index and date/time when starting a new game
                    gameIndex = getCurrentDateTimeAsIndex();  // Generate a unique index
                    gameIndexStr = to_string(gameIndex);  // Convert to string for saving
                    currentDateTime = getCurrentDateTime();  // Get the current date and time
                }
                
                currentLevel = 1; // Start from the first level
                setUpForLevel(); // Initialize game settings for the current level

                gameOver = false;  // Ensure the game is not over
                gameStarted = false;  // Mark game as not started yet
                
                if (gameMode == SPEED_RUN_RACE) { 
                    savedDateTime = getCurrentDateTime();  // Save the start time for speed run mode
                }

                startGameTimer(); // Start the game timer
            }

            // Main game loop: Runs as long as the game is not over
            while (!gameOver) { 

                if (infiniteLevels) { //Set levels if game has infinite levels
                    maxLevels = currentLevel + 1;  // Allow one additional level for infinite levels
                }

                if (!includeEnemies) {  // Clear enemies and swords if they are not included
                    enemies.clear();
                    swords.clear();
                }

                // Print the current game state (maze, player, etc.)
                printGame(player, currentLevel, maze, enemies, items, puzzles, goal, portals, doors, keys, swords, difficulty, gameMode);

                startLevelTimer(); // Start the level timer

                char input = _getch(); // Read player input for movement and actions

                // Display Help Screen
                if (input == 'h' || input == 'H') {
                    while (true) {
                        pauseTimer(); // Pause the game timer while showing help
                        string displayGameMode = gameModeToString(gameMode);
                        string displayGameModeDiscription = gameModeDiscription(displayGameMode);
                        displayHelp(displayGameMode, displayGameModeDiscription); // Show the help screen
                    
                        char exitHelp = _getch();

                        if (exitHelp == 'q' || exitHelp == 'Q') {
                            resumeTimer();  // Resume the game timer
                            break;
                        }
                    }
                }

                // Quit game option
                if (input == 'q' || input == 'Q') {
                    char confirmInput;
                    char saveInput;

                    while (true) {
                        clearScreen(); // Clear the screen
                        pauseTimer(); // Pause the game timer
                        cout << "Are you sure you want to quit? (Y/N): ";
                        confirmInput = _getch(); // Get confirmation input

                        if (confirmInput == 'Y' || confirmInput == 'y') {
                            cout << "\nDo you want to save the game before quitting? (Y/N): ";
                            saveInput = _getch();
                            
                            // Loop until the user enters 'Y' or 'N'
                            while (saveInput != 'Y' && saveInput != 'y' && saveInput != 'N' && saveInput != 'n') {
                            cout << "\nInvalid input. Please enter 'Y' to save or 'N' to quit without saving." << endl;
                            saveInput = _getch();  // Read new input
                            }  

                            if (saveInput == 'Y' || saveInput == 'y') {
                                savedDateTime = getCurrentDateTime(); // Save the current date/time
                                // If the player's name is empty, ask for it
                                if (player.name.empty()) {player.name = getPlayerName();}
                                saveGame(gameIndexStr);  // Save the game
                            }

                            clearGameData(); // Clear game data 
                            loadingGame = false; // Reset loading state
                            gameIndexStr = ""; // Reset game index
                            gameIndex = 0;

                            gameOver = true; // End the game
                            startGame = false;  // Stop the game 
                            this_thread::sleep_for(seconds(1));
                            break;

                        } else if (confirmInput == 'N' || confirmInput == 'n') {
                            resumeTimer();
                            break;  // If no, continue with the game
                        } else {
                            // Invalid input, prompt again
                            cout << "\nInvalid input. Please enter 'Y' to confirm or 'N' to cancel." << endl;
                        }
                    }
                }

                // Inventory handling
                if (!player.inventory.empty()) {
                    if (input == 'i' || input == 'I') {
                        chooseInventory(player, maze, goal, portals, doors, enemies, puzzles, items, keys, swords);
                    }
                }

                // Handle player movement
                handlePlayerMovement(player, input, maze, puzzles, portals, doors);
                // Check if the player collects any items
                checkItemCollection(player, items, keys, swords);

                // Enemy (Guardian) Movement
                for (auto& enemy : enemies) {
                    int distance = manhattanDistance(enemy.x, enemy.y, player.x, player.y);
                    if (distance <= chaseDistanceThreshold) {
                        // Enemy (guardian) starts chasing player if within the threshold distance
                        moveEnemyTowardsPlayer(enemy, player, maze, puzzles, portals, doors, enemies);  // AI movement towards player
                    } else {
                        // Enemy moves randomly
                        moveEnemyRandom(enemy, maze, puzzles, portals, doors, enemies);  // Random movement
                    }
                }

                // Check if any enemy catches the player and update the game state
                bool caught = checkEnemyCatchPlayer(player, enemies);

                // Game Over: Player caught by enemy
                if (caught) {
                    stopTimers(); // Stop the game timer
                    cout << "\n>> ---------------------------------------------------------------------------- <<" << endl;
                    cout << "                    GAME OVER! You were killed by a Guardian!" << endl;         
                    cout << "                    [TOTAL TIME]: " << totalGameTime << " seconds" << endl;                           
                    cout << ">> ---------------------------------------------------------------------------- <<" << endl;
                    gameOver = true;  // End the game
                    loadingGame = false;

                    // If game mode is Speed Run Race, get name to display on leaderboard
                    if (gameMode == 3) {
                        // If the player's name is empty, ask for it
                        if (player.name.empty()) {player.name = getPlayerName();}
                        saveGame(gameIndexStr);
                    }
                    clearGame();  // Clear game data after game over
                    break;
                }

                // Game Over: Countdown challenge failed
                countdownTimeRemaining = getCountdownTimeRemaining();
                if (gameMode == COUNTDOWN_CHALLENGE && countdownTimeRemaining == 0) {
                    cout << "\nTime's up! You failed to complete the level." << endl;
                    gameOver = true; // End the game
                    loadingGame = false; // Clear game data
                    clearGame();
                    break;
                }

                // Check if the player reaches the goal
                if (player.x == goal.x && player.y == goal.y && updateGameProgress(player, enemies, puzzles, gameMode)) {
                    printGame(player, currentLevel, maze, enemies, items, puzzles, goal, portals, doors, keys, swords, difficulty, gameMode);

                    if (currentLevel >= maxLevels) { // Check if it's the last level
                        stopTimers();  // Stop timers when the game is completed
                        gameCompleted();
                        gameOver = true;  // End the game 

                        // If game mode is Speed Run Race, get name to display on leaderboard
                        if (gameMode == 3) {
                            // If the player's name is empty, ask for it
                            if (player.name.empty()) {player.name = getPlayerName();}
                            saveGame(gameIndexStr);  // Save game progress
                        }
                        clearGame();  // Clear game data after completion
                        clearGameData();  // Reset game data
                    } else {
                        // If level is completed, move to the next level
                        cout << "Level " << currentLevel << " Completed! Next level generating..." << endl; 
                        this_thread::sleep_for(seconds(1));  // Add a delay
                        currentLevel++; // Increment the current level
                        setUpForLevel(); // Set up the next level
                        levelStarted = false; // Reset level timer
                        if (!keepInventory) {
                            player.inventory.clear();  // Clear inventory if player chose not to keep it
                        }
                        loadingGame = false;  // Proceed to the next level
                    }
                }
            }
        }
    }
    return 0;
}
