#include <iostream>

#include <string>
#include <vector>
#include <tuple>
extern int totalGameTime;
using namespace std;

void displayPrologue() {
    // Prologue message
    string message =
        "\"Wandering...curiosity got the best of me.\n"
        "I entered Planet Lyrnth, but something's off.\n"
        "Ancient mazes guard the planet's core.\n"
        "IF I WANT TO ESCAPE, I HAVE TO FINISH THIS MAZE..\"\n";

    // Display prologue with typewriter effect
    cout << "+------------------+ PROLOGUE +------------------+" << endl;
    for (char c : message) {
        cout << c << flush;  // Output character and flush the buffer
        this_thread::sleep_for(chrono::milliseconds(20));  // Delay between characters
    }
    cout << endl;  // End the prologue

    // Display ending message
    cout << "                                       ~ Traveller" << endl;
    cout << "+--------------- [Enter to start] ---------------+" << endl;
}

void displayMenu(string displayGameMode, string displayDifficultyType, string displayNumOfLevels, string displayGameModeDiscription){
clearingScreen();
cout << "*********************** W E L C O M E   *  T R A V E L E R ***********************" << endl;
cout << endl;              
cout << "                  ========== The Planet Lyrnth Escape ==========                  " << endl;
cout << "**********************************************************************************" << endl;
cout << endl; 
cout << "          Why did I come here? Planet Lyrnth... it's a maze of secrets.           " << endl;
cout << "                           The only way out is through.                           " << endl;
cout << "                               Will I make it out?                                " << endl;
cout << endl;                            
cout << "                             > Select Your Next Move <                            " << endl;
cout << "**********************************************************************************" << endl;
cout << "              +----------------------------------------------------+              " << endl;
cout << "              |                  SELECT YOUR CHOICE                |              " << endl;
cout << "              +----------------------------------------------------+              " << endl;
cout << endl; 
cout << "        +---------------------------------------------------------------+         " << endl;
cout << "        |  [1] START GAME             |   [2] VIEW LEADERBOARD          |         " << endl;
cout << "        ------------------------------+----------------------------------         " << endl;
cout << "        |  [3] CUSTOMISE GAME         |   [4] LOAD GAME                 |         " << endl;
cout << "        -----------------------------------------------------------------         " << endl;
cout << "        |  [5] EXIT PLANET LYRNTH (Quit)                                |         " << endl;
cout << "        +---------------------------------------------------------------+         " << endl;
cout << endl; 
cout << "              +----------------------------------------------------+              " << endl;
cout << "              |                CURRENT GAME STATUS                 |              " << endl;
cout << "              +----------------------------------------------------+              " << endl;
cout << endl; 
cout << "              [Game Type]    : " << displayGameMode << '\n';
cout << "              [Difficulty]   : " << displayDifficultyType << '\n';
cout << "              [Levels]       : " << displayNumOfLevels << '\n';
cout << endl;
cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
cout << endl; 
cout << "        [" << displayGameMode << "]" << endl;
cout << "        " << displayGameModeDiscription << endl;
cout << endl; 
cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
}

void displayHelp(string displayGameMode, string displayGameModeDiscription){
clearingScreen();
cout << "+---------------------------------- HELP GUIDE ----------------------------------+" << endl;
cout << "+--------------------------[Enter 'Q' to return to game]-------------------------+" << endl;
cout << endl;
cout << "GAME MODE:                                                                        " << endl;
cout << endl; 
cout << "    ["<< displayGameMode << "]" << endl;
cout << "   " << displayGameModeDiscription << endl;
cout << endl; 
cout << " -------------------------------------------------------------------------------- " << endl;
cout << endl;
cout << " (P): PLAYER                                                                     " << endl;
cout << endl;                          
cout << " (X): GOAL" << endl; 
cout << endl;                          
cout << " (+): PUZZLE" << endl;
cout << "     - Finish Puzzle to continue on your path" << endl;  
cout << endl; 
cout << " (S): SWORD" << endl;
cout << "     - Collect sword to fight off Guardian." << endl;  
cout << "     - Only able to fight Guardian if Guardian is next to you" << endl;                                      
cout << endl;               
cout << " (G): GUARDIAN                                                                     " << endl;
cout << "     - Lose a life when guardian catches you                                       " << endl;
cout << endl; 
cout << " (K): KEY                                                                          " << endl;
cout << "     - Collect a key to unlock a Door                                              " << endl;
cout << endl; 
cout << " (D): DOOR                                                                         " << endl;
cout << "     - Unlock Doors with a key. It could give you a shortcut...                    " << endl;
cout << endl;  
cout << " (O): PORTAL GATE                                                                  " << endl; 
cout << "     - Spawn location if you use 'TELEPORT' to a random Portal Gate in maze        " << endl;
cout << endl;    
cout << " (?): CHEST                                                                        " << endl;
cout << "     - Contains either 'TELEPORT' , 'LIFE SHARD' or 'HAMMER                        " << endl;
cout << "       ( HAMMER ): Collect hammer to knock down walls                              " << endl;  
cout << "       ( TELEPORT ): Use it to teleport to a random PORTAL GATE                    " << endl;
cout << "       ( LIFE SHARD ): Gives you an extra life                                     " << endl;
cout << endl; 
cout << "+--------------------------[Enter 'Q' to return to game]-------------------------+" << endl;
}

void displayLeaderboardWithDetails(const vector<tuple<int, string, string, int, int>>& leaderboardGames) {\
clearingScreen();
cout << "                  ========== The Planet Lyrnth Escape ==========                  " << endl;         
cout << "================================[  LEADERBOARD  ]=================================" << endl;
cout << "==================================================================================" << endl;

    for (const auto& game : leaderboardGames) {
        int currentLevel = get<0>(game);
        string playerName = get<1>(game);
        string savedDateTime = get<2>(game);
        int totalTime = get<3>(game);

cout << "                              >>> Rank #" << get<4>(game) << " <<<" << endl;                                
cout << "----------------------------------------------------------------------------------" << endl;
cout << "   Player Name   : " << playerName << endl;
cout << "   Date          : " << savedDateTime << endl;
cout << "   Level         : " << currentLevel << endl;
cout << "   Time Taken    : "<< totalTime << " seconds" << endl;
cout << endl;
cout << "----------------------------------------------------------------------------------" << endl;
}
    
cout << "==================================================================================" << endl;
cout << "                    [Press 'Q' to return to the main dashboard]                   " << endl;  
cout << "==================================================================================" << endl;
}

void displayEmptyLeaderboard(){
clearingScreen();
cout << "                  ========== The Planet Lyrnth Escape ==========                  " << endl;      
cout << "================================[  LEADERBOARD  ]=================================" << endl;
cout << "==================================================================================" << endl;
cout << endl;  
cout << "           No games have been completed yet. The leaderboard is empty.            " << endl;
cout << "                  Begin your first mission to unlock your rank!                   " << endl;
cout << endl; 
cout << "            \"The galaxy is vast, and it's waiting for you to explore.\"            " << endl; 
cout << endl; 
cout << "==================================================================================" << endl;
cout << "                    [Press 'Q' to return to the main dashboard]                   " << endl;
cout << "==================================================================================" << endl;
}

void displayCustomGame1(){
clearingScreen();
cout << "                  ========== The Planet Lyrnth Escape ==========                  " << endl;    
cout << "                          [ MISSION CUSTOMIZATION MENU ]                          " << endl;
cout << "----------------------------------------------------------------------------------" << endl;
cout << "                        (Press 'Q' to return to main menu)                        " << endl;
}

void displayCustomGameGameMode(){
cout << endl;
cout << ">> Select your game mode:" << endl;
cout << "   [1] Default " << endl;
cout << "   [2] Puzzle Completion" << endl;
cout << "   [3] Guardian Elimination" << endl;
cout << "   [4] Speed Run Race (Leaderboard Competition)" << endl;
cout << "   [5] Countdown Challenge" << endl;
cout << "   Chosen Mode: ";
}

void displayCustomGameDifficulty(){
cout << endl;
cout << ">> Choose your difficulty level:" << endl;
cout << "   [1] Easy" << endl;
cout << "   [2] Medium" << endl;
cout << "   [3] Hard" << endl;
cout << "   Chosen Difficulty: ";
}

void displayCustomGameLevel(){
cout << endl;
cout << ">> Choose level type:" << endl;
cout << "   [1] Default" << endl;
cout << "   [2] Infinite" << endl;
cout << "   [3] Custom" << endl;
cout << "   Chosen Level Type: ";
}
void displayCustomGameInventory(){
cout << endl;
cout << ">> Keep your inventory between levels? (Y/N): ";
}
void displayCustomGamePuzzleOption(){
cout << endl;
cout << ">> Puzzle Options:" << endl;
cout << "   [1] Random Puzzles" << endl;
cout << "   [2] All Puzzles Available" << endl;
cout << "   Chosen Puzzle Mode: ";
}
void displayCustomGameEnemiesOption(){
cout << endl;
cout << ">> Include guardians in your journey? (Y/N): ";
}


void confirmCustomSettings(string choosenGameMode ,string choosenDifficulty ,string choosenLevels ,string choosenInventory ,string choosenPuzzleOptions ,string choosenIncludeEnemies){
clearingScreen();
cout << "                  ========== The Planet Lyrnth Escape ==========                  " << endl; 
cout << "----------------------------------------------------------------------------------" << endl;   
cout << "                           === CONFIRM GAME SETTINGS ===                          " << endl;
cout << "----------------------------------------------------------------------------------" << endl;
cout << endl;
cout << "  Game Mode:       " << choosenGameMode << endl;
cout << "  Difficulty:      " << choosenDifficulty << endl;
cout << "  Levels:          " << choosenLevels << endl;
cout << "  Inventory:       " << choosenInventory << endl;
cout << "  Puzzle Mode:     " << choosenPuzzleOptions << endl;
cout << "  Enemies:         " << choosenIncludeEnemies << endl;
cout << endl;
if(choosenGameMode == "SPEED RUN RACE"){cout << "  [Settings cannot be changed for this Game Mode*]" << endl;}
cout << "----------------------------------------------------------------------------------" << endl;
cout << endl;
cout << "               Are you sure you want to proceed with these settings?              " << endl;
cout << "                    (Y) Yes | (N) No, return back to dashboard                    " << endl;
cout << endl;
cout << "----------------------------------------------------------------------------------" << endl;
}

void displayingSavedGames(int gameCount, string savedDateTime, string playerName, int currentLevel, string numOfLevels, string displayGameMode, string displayDifficulty, bool puzzleOptions, bool includeEnemies){
cout << "=== Game Number:[" << gameCount << "]==============================================================" << endl;
cout << endl;
cout << "  Saved on: " << savedDateTime << endl;
cout << "  Player Name: " << playerName << endl;
cout << "  Current Level: " << currentLevel << endl;
cout << "  Game Mode: " << displayGameMode << endl;
cout << "  Difficulty: " << displayDifficulty << endl;
cout << "  Levels: " << numOfLevels << endl;
cout << "  Puzzle Enabled: " << (puzzleOptions ? "Yes" : "No") << endl;
cout << "  Enemies: " << (includeEnemies ? "Yes" : "No") << endl;
cout << endl;
cout << "----------------------------------------------------------------------------------" << endl;
}

void noSavedGamesDisplayed(){
cout << "==================================================================================" << endl; 
cout << "                          === AVAILABLE SAVED GAMES ===                           " << endl;
cout << "==================================================================================" << endl;
cout << "      Enter the number of the game you want to load (or 0 to return to menu)      " << endl;
cout << endl;
cout << "------------------------- No Saved Games. Come back soon. ------------------------" << endl;
cout << endl;
cout << "==================================================================================" << endl;
}

void topGameMenu(string displayGameMode, int currentLevel, string displayGameDifficulty, int totalTime, int levelTime, int countdownTimeRemaining){
cout << "============================ The Planet Lyrnth Escape ============================" << endl;
cout << "[MODE]: " << displayGameMode << " | [DIFFICULTY]: " << displayGameDifficulty << endl;
    if (displayGameMode == "COUNTDOWN CHALLENGE"){
       cout << "[TIME REMAINING]: " << countdownTimeRemaining  << " seconds" << endl;
    } else {
cout << "[LEVEL]: " << currentLevel << " | [TOTAL TIME]: " << totalTime << " seconds | [LEVEL TIME]: " << levelTime << " seconds\n";
    }
cout << "----------------------------------------------------------------------------------" << endl;
}

void bottomGameMenu(int displayPlayerLives, int displayPlayerInventoryCap, string displayInventory ,string displayPlayerMessage){
cout << "+--------------------------------------------------------------------------------+" << endl; 
cout << "[Lives]: " << displayPlayerLives << endl;
cout << "[Inventory (" << displayPlayerInventoryCap << ")]: " << displayInventory << endl;
cout << "+--------------------------------------------------------------------------------+" << endl;
cout << "(Q): Quit" << endl;
cout << "(H): Help" << endl;

if (displayInventory != "EMPTY"){
        cout << "(i): Access Inventory" << endl;
    }
cout << "Use WASD to move: " << endl;
    // Display the stored message (if any)
    if (!displayPlayerMessage.empty()) {
        cout << ">> " << displayPlayerMessage << endl;
    }
}


void gameCompleted(){
clearingScreen();
cout << "============================ The Planet Lyrnth Escape ============================" << endl;
cout << endl;  
cout << "                                    CONGRATS!                                     " << endl;
cout << "          You made it out of Planet Lyrnth! Till next time Traveller...           " << endl;
cout << "                             Total Time: " << totalGameTime << " seconds          " << endl;
cout << endl;                                                                                  
cout << "                          ('Q'/'q'): Back to Game Menu                            " << endl;
cout << endl;                                                                                  
cout << "+--------------------------------------------------------------------------------+" << endl;
cout << "+--------------------------------------------------------------------------------+" << endl;
}

void exitGame(){
cout << "*********************** G O O D B Y E   *  T R A V E L E R ***********************" << endl;            
cout << "                  ========== The Planet Lyrnth Escape ==========                  " << endl;
cout << endl; 
cout << "                                 Till next time...                                " << endl;
cout << endl;                            
cout << "**********************************************************************************" << endl;
}