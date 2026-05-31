
#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include <map>
#include <unordered_map>
#include <limits>
#include <cctype>
#include <thread>

using namespace std;
using namespace std::chrono;
// Create a random engine based on current time
random_device rd;
    mt19937 g(rd());

void clearingScreen(){
    #ifdef _WIN32
        system("cls");  // Windows version
    #else
        system("clear");  // Linux/macOS version
    #endif
}
//Converts String to lower case
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// 1) Word Unscrambling (Has 3 attempts)-----------------------------
// Function to shuffle the word using shuffle
string shuffleWord(string word) {
    // Shuffle the word using shuffle
    shuffle(word.begin(), word.end(), g);
    return word;
}

bool wordUnscramble(){
    
    srand(time(0));// Random number generator

    vector<string> words;// Vector to store words

    // Adding words to the list 
    words.push_back("cosmos");
    words.push_back("planet");
    words.push_back("escape");
    words.push_back("guardian");
    words.push_back("explore");
    words.push_back("maze");
    words.push_back("labyrinth");
    words.push_back("discovery");
    words.push_back("curiosity");

    // Randomly select an index for the word
    int randomIndex = rand() % words.size();
    string selectedWord = words[randomIndex];

    string scrambledWord = shuffleWord(selectedWord);// Shuffle the selected word

    // Display the scrambled word
    cout << "Welcome to the Word Unscrambling!" << endl;
    cout << "Unscramble the following word to proceed: " << scrambledWord << endl;

    string playerGuess;
    int attempts = 3;

    // Allow the player a few attempts to guess the word
    while (attempts > 0) {
        cout << "Enter your guess (" << attempts << " attempts left): ";
        cin >> playerGuess;

        // Check if the player's guess is correct
        if (toLowerCase(playerGuess) == toLowerCase(selectedWord)) {
            cout << "Congratulations! You've guessed the word correctly!" << endl;
            return true;
            break;
        } else {
            cout << "Incorrect guess." << endl;
            attempts--;
        }

        if (attempts == 0) {
            cout << "Sorry! You're out of attempts. The correct word was: " << selectedWord << endl;
            return false;
        }
    }
    return false;
}

// 2) Riddle (3 attempts)----------------------------------------
// Riddle Structure
struct Riddle {
    string question;
    string answer;
};

// Function to ask a riddle
bool askRiddle(const Riddle& riddle, int& attemptsLeft) {
    string playerAnswer;
    cout << "Riddle " << "(" << attemptsLeft << " attempts left): " << riddle.question << endl;
    cout << "Your answer: ";
    cin >> playerAnswer;

    // Convert both player's answer and correct answer to lowercase for case-insensitive comparison
    if (toLowerCase(playerAnswer) == toLowerCase(riddle.answer)) {
        cout << "Correct! You've solved the riddle!" << endl;
        return true;  // Correct answer
    } else {
        cout << "Incorrect answer. Try again." << endl;
        attemptsLeft--;
        return false;  // Incorrect answer
    }
}

bool riddle(){
    
    srand(time(0)); // Random number generator

    // List of riddles
    vector<Riddle> riddles = {
        {"What has keys but can't open locks?", "piano"},
        {"I speak without a mouth and hear without ears. I have no body, but I come alive with wind. What am I?", "echo"},
        {"What comes once in a minute, twice in a moment, but never in a thousand years?", "the letter m"},
        {"I am not alive, but I grow; I don't have lungs, but I need air; I don't have a mouth, and I can drown. What am I?", "fire"},
        {"The more of this there is, the less you see. What is it?", "darkness"}
    };

    // Allow the player 3 attempts to answer the riddle
    int attempts = 3;
    bool isCorrect = false;

    // Randomly select a riddle
    int randomIndex = rand() % riddles.size();
    Riddle selectedRiddle = riddles[randomIndex];

    // Ask the selected riddle
    while (attempts > 0 && !isCorrect) {
        isCorrect = askRiddle(selectedRiddle, attempts);
        // Continue with the game (maze, etc.)
    }
    
    if (attempts == 0) {
        cout << "Sorry! You're out of attempts. The correct answer was: " << selectedRiddle.answer << endl;
        return false;
    }
    if (isCorrect) {
    cout << "You may now proceed through the maze!" << endl;
    return true;
    }

return false;
}

// 3) Pattern reconition (3 attempts)---------------------------
// Number pattern recognition puzzle
bool patternRecognition(){
    int addtionRange = 11; 
    int multipleRange = 5;
    int firstTerm = rand() % 11;  // Random starting point between 1 and 10
    int commonAdditionRatio = rand() % addtionRange; //Random common addtion ratio between 1 and 11
    int commonMultipleRatio = rand() % multipleRange; //Random common mutliple ratio between 1 and 5

    // Randomly choose to use addition or multiplication for the pattern
    bool ratioType = rand() % 2;  // 0 for addition, 1 for multiplication

    vector<int> sequence; // Sequence to hold the generated pattern
    if (ratioType) {
        // If using addition, generate the sequence using the addition ratio
        for (int i = 0; i < 5; ++i) {
            sequence.push_back(firstTerm + i * commonAdditionRatio);
        }
    } else {
        // If using multiplication, generate the sequence using the multiplication ratio
        for (int i = 0; i < 5; ++i) {
            sequence.push_back(firstTerm * pow(commonMultipleRatio, i));
        }
    }

    // Randomly choose an index to hide (the missing number in the sequence)
    int missingIndex = rand() % sequence.size(); // Randomly choose an index to hid
    int correctAnswer = sequence[missingIndex]; // Value at the missing number index
    sequence[missingIndex] = -1; // Placeholder for the missing number

    // Display the sequence with a missing element as '?'
    cout << "Number Pattern Recognition Puzzle: Find the missing number in the sequence." << endl;
    cout << "Here is the sequence: ";
    for (int num : sequence) {
        if (num == -1) {
            cout << "? "; // Display '?' for the missing number
        } else {
            cout << num << " ";  // Display the number in the sequence
        }
    }
    cout << endl;

    // Give the player 3 attempts to guess the missing number
    int attempts = 3;  // Set the number of attempts allowed for the player
    int playerGuess;  // Variable to store the player's guess
    while (attempts > 0) {
        cout << "What is the missing number? (Attempts left: " << attempts << "): ";
        
        // Validate the player's input to ensure it's a valid number
        while (!(cin >> playerGuess)) {
            // If the input is invalid, clear the error state and ignore the bad input
            cin.clear();  // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input

            // Ask for the input again
            cout << "Invalid input. Please enter a number: ";
        }

        // Check if the player's guess is correct
        if (playerGuess == correctAnswer ) {
           cout << "Correct! You've identified the pattern!" << endl;
           return true; // Player wins the game
        } else {
        cout << "Incorrect answer. Try again." << endl;
        attempts--;
        }
    }
    // If the player fails all attempts, show the correct answer
    cout << "Sorry! You've used all attempts. The correct answer is: " << correctAnswer << endl;
   return false; // Player loses the game
}

// 4) True or False (1 attempt)---------------------------
// Function to randomly generate a True or False question
bool trueOrFalse() {
    // List of questions and their correct answers (true or false)
    vector<pair<string, bool>> questions = {
        {"The Earth is flat.", false},
        {"The sky is blue.", true},
        {"2 + 2 equals 5.", false},
        {"Cats can fly.", false},
        {"Humans have walked on the moon.", true},
        {"Water boils at 100°C at sea level.", true}
    };

    // Randomly select a question from list
    int questionIndex = rand() % questions.size();  // Generate a random index within the range of available questions
    string question = questions[questionIndex].first;  // Get the question text
    bool correctAnswer = questions[questionIndex].second;  // Get the correct answer (true or false)

    // Display the question to the player
    cout << "True or False: " << question << endl;

    // Get the player's answer
    string playerAnswer;
    cout << "Enter 'True' or 'False': ";
    cin >> playerAnswer;

    // Convert the player's answer to lowercase for case insensitivity
    for (auto &c : playerAnswer) c = tolower(c);

    // Check the player's answer (consider both text and character input)
    if ((playerAnswer == "true" && correctAnswer) || (playerAnswer == "false" && !correctAnswer) ||
        (playerAnswer == "t" && correctAnswer) || (playerAnswer == "f" && !correctAnswer)) {
        cout << "Correct!" << endl;
        return true; // Player wins game
    } else {
        cout << "Incorrect! The correct answer is " << (correctAnswer ? "True" : "False") << "." << endl;
        return false; // Player loses game
    }
}
// 5) Sudoku ( 1 Attempt, non case & number sensitive)---------------------------------------------
// Function to print the Sudoku grid with table lines and labeled cells
void printSudokuGrid(const vector<vector<char>>& grid, int size) {
    int separatorLength = size * 2 + (size / 2) - 1;  // Adjusted for spaces and grid structure

    for (int i = 0; i < size; ++i) {
        // Print horizontal line for the grid at appropriate rows
        if (i % (size / 2) == 0 && i != 0) {
            for (int k = 0; k < separatorLength; ++k) {
                cout << "-";  // Dynamically generate the separator line
            }
            cout << endl;
        }

        // Print each row of the grid
        for (int j = 0; j < size; ++j) {
            // Print vertical lines within the grid
            if (j % (size / 2) == 0 && j != 0) {
                cout << "| ";
            }
            cout << grid[i][j] << " ";  // Print the cell content
        }
        cout << endl;
    }
}

// Function to check if a number can be placed at (row, col)
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num, int size) {
    // Check if the number already exists in the row
    for (int x = 0; x < size; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }
       // Check if the number already exists in the column
    for (int x = 0; x < size; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check if the number already exists in the subgrid (2x2 for 4x4)
    int startRow = row - row % (size / 2);
    int startCol = col - col % (size / 2);
    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size / 2; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku grid (backtracking)
bool solveSudoku(vector<vector<int>>& grid, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (grid[row][col] == 0) {  // Find an empty cell
                // Try numbers 1 to size
                for (int num = 1; num <= size; num++) {
                    if (isSafe(grid, row, col, num, size)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid, size)) {
                            return true;
                        }
                        grid[row][col] = 0;  // Backtrack
                    }
                }
                return false;  // No valid number found, need to backtrack
            }
        }
    }
    return true;  // Puzzle solved
}

// Function to generate a puzzle by removing some numbers from the filled grid
void generatePuzzle(vector<vector<int>>& grid, int size) {
    solveSudoku(grid, size);  // Directly solve an empty grid to create a filled grid
    
    // Randomly remove some numbers to create a puzzle (keeping some cells empty)
    srand(time(0));
    int cellsToRemove = (size * size) / 2;  // Removing approximately half of the cells

    while (cellsToRemove > 0) {
        int row = rand() % size;
        int col = rand() % size;
        if (grid[row][col] != 0) {
            grid[row][col] = 0;  // Set the cell to empty (0)
            cellsToRemove--;
        }
    }
}

bool playerSolve(vector<vector<int>>& grid, const vector<vector<int>>& solvedGrid, int size, const map<char, pair<int, int>>& emptyCells) {
    int playerInput;
    char label;

    // Allow the player to enter numbers for the empty cells using labels
    for (const auto& [label, coordinates] : emptyCells) {
        cout << "Enter a number for cell (" << label << "): ";

        // Validate input until it's correct
        while (true) {
            cin >> playerInput;

            // Check if the input is a valid number
            if (cin.fail()) {
                cout << "Invalid input! Please enter a valid number." << endl;
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input
                cout << "Enter a number for cell (" << label << "): ";
            }
            // Check if the input is within the valid range
            else if (playerInput < 1 || playerInput > size) {
                cout << "Invalid number! Please enter a number between 1 and " << size << endl;
                cout << "Enter a number for cell (" << label << "): ";
            }
            else {
                // Input is valid
                break;
            }
        }

        // Update the grid with the valid input
        int row = coordinates.first;
        int col = coordinates.second;
        grid[row][col] = playerInput;
    }

    // Check if the player's grid matches the solved grid
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (grid[row][col] != solvedGrid[row][col]) {
                return false;  // Mismatch found, puzzle not solved correctly
            }
        }
    }

    return true;  // Puzzle solved correctly
}

bool sudoku() {
    int size = 4;  //Define grid size (4x4 grid)

    // Initialize Sudoku grid with size
    vector<vector<int>> grid(size, vector<int>(size, 0));
    vector<vector<char>> displayGrid(size, vector<char>(size, ' '));

    generatePuzzle(grid, size); // Generate a random Sudoku puzzle (incomplete)

    map<char, pair<int, int>> emptyCells; // Map to keep track of empty cells and their corresponding labels
    char label = 'A';  // Starting label for empty cells

    // Fill display grid with alphabetic labels
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] == 0) {
                displayGrid[i][j] = label;  // Label empty cells with alphabets
                emptyCells[label] = {i, j};  // Track the position of each empty cell
                label++;
            } else {
                displayGrid[i][j] = '0' + grid[i][j];  // Convert the number to a character
            }
        }
    }

    // Display the initial puzzle
    cout << "Generated Sudoku Puzzle (" << size << "x" << size << "):" << endl;
    printSudokuGrid(displayGrid, size);

    // Create solved version of the puzzle
    vector<vector<int>> solvedGrid = grid;  // Copy current grid
    solveSudoku(solvedGrid, size);          // Solve the copied grid to get the correct solution

    // Allow player to try solving the puzzle
    bool correctSolution = playerSolve(grid, solvedGrid, size, emptyCells);

    //Check player's anwers
    if (correctSolution) {
        cout << "Congratulations! You've solved the puzzle!" << endl;
        return true; // Player wins game
    } else {
        cout << "Incorrect solution! Here's the solved Sudoku:" << endl;
        vector<vector<char>> solvedDisplayGrid(size, vector<char>(size, ' '));  // Prepare a display grid for the solved puzzle

        // Copy the solved grid into the display grid
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                solvedDisplayGrid[i][j] = '0' + solvedGrid[i][j];  // Fill solved numbers
            }
        }

        // Display the solved Sudoku grid
        printSudokuGrid(solvedDisplayGrid, size);  // Display the solved puzzle
        return false; // Player loses game
    }
    return false; // Default return value
}
//Code Cracker (10 attempts)---------------------------------------------
// Function to generate a random code
vector<int> generateCode(int length) {
    vector<int> code; // Vector to store the generated code
    for (int i = 0; i < length; ++i) {
        code.push_back(rand() % 10); // Generate random digits (0-9) and add to the code
    }
    return code;
}

// Function to get the user's guess
vector<int> getUserGuess(int length) {
    vector<int> guess(length); // Vector to store the user's guess
    string input; // String to store user input
    while (true) {
         cout << "------------------------------------" << endl;
        cout << "Enter your guess (" << length << "-digit code): ";
        cin >> input; // Get input from user

        // Check if input length matches the code length
        if (input.length() != length) {
            cout << "Invalid input! Please enter a " << length << "-digit code." << endl;
            continue; // Prompt the user to input again
        }

        // Convert the string input to a vector of integers
        bool valid = true; // Flag to check if input is valid
        for (int i = 0; i < length; ++i) {
            if (!isdigit(input[i])) { // Check if the input is a digit
                valid = false; // Set flag to false if input contains non-digit characters
                break;
            }
            guess[i] = input[i] - '0'; // Convert char to integer
        }

        // If input is invalid (contains non-digits), prompt user again
        if (!valid) {
            cout << "Invalid input! Please enter digits only." << endl;
        } else {
            break; // Valid guess, break the loop
        }
    }
    return guess;
}

// Function to compare the guess with the actual code and provide feedback
void giveFeedback(const vector<int>& code, const vector<int>& guess) {
    int correctPosition = 0, correctDigitWrongPosition = 0; // Counters for feedback
    vector<bool> codeChecked(code.size(), false), guessChecked(guess.size(), false); // Track which digits have been checked

    // Check for digits in the correct position
    for (int i = 0; i < code.size(); ++i) {
        if (guess[i] == code[i]) { // If digit in guess matches the code at the same position
            correctPosition++; // Increment correct position counter
            codeChecked[i] = true; // Mark this position as checked in the code
            guessChecked[i] = true; // Mark this position as checked in the guess
        }
    }

    // Check for correct digits but in the wrong position
    for (int i = 0; i < guess.size(); ++i) {
        if (guessChecked[i]) continue; // Skip already checked correct positions
        for (int j = 0; j < code.size(); ++j) {
            if (!codeChecked[j] && guess[i] == code[j]) { // If digit exists in code but at a different position
                correctDigitWrongPosition++; // Increment wrong position counter
                codeChecked[j] = true; // Mark this digit as checked in the code
                break;
            }
        }
    }
    
    // Output feedback to the user
    cout << "Correct digits in correct position: " << correctPosition << endl;
    cout << "Correct digits in wrong position: " << correctDigitWrongPosition << endl;
}

// Main game loop
bool codeCracker() {
    srand(time(0)); // Seed for random number generation
    int length = 3; // Length of the code
    int maxAttempts = 10; // Maximum attempts allowed

    vector<int> code = generateCode(length); // Generate the secret code
    int attempts = 0; // Initialize attempts counter

    cout << "Welcome to Code Cracker! Try to guess the " << length << "-digit code.(Between: 0 - 9)" << endl;

    // Loop to allow the user to guess until max attempts are reached
    while (attempts < maxAttempts) {
        vector<int> guess = getUserGuess(length); // Get the user's guess
        attempts++; // Increment attempts counter

        // If guess is correct, user wins
        if (guess == code) {
            cout << "Congratulations! You've cracked the code in " << attempts << " attempts!" << endl;
            return true; // Game ends with success
        }

        giveFeedback(code, guess); // Provide feedback on the guess

        // Inform the user how many attempts are left
        if (attempts < maxAttempts) {
            cout << "Attempts left: " << maxAttempts - attempts << endl;
        } else { // If no attempts left, reveal the correct code
            cout << "Sorry, you've used all your attempts. The code was: ";
            for (int num : code) { // Output the correct code
                cout << num;
            }
            cout << endl;
            return false; // Game ends with failure
        }
    }
    return false;
}

//Decode (Language) (1 attemnpt)--------------------------------------------
// Function to generate a random mapping for letters
unordered_map<char, char> generateRandomMapping() {
    unordered_map<char, char> mapping;
    vector<char> pool; // Pool of digits and letters to map to

    // Add digits 0-9 and letters A-Z to the pool
    for (char i = '0'; i <= '9'; i++) pool.push_back(i);
    for (char i = 'A'; i <= 'Z'; i++) pool.push_back(i);

    // Shuffle the pool to create randomness in mappings
    shuffle(pool.begin(), pool.end(), g);

    // Create a random mapping for each letter A-Z
    char letter = 'A';
    for (int i = 0; i < 26; ++i) {
        mapping[letter] = pool[i]; // Map each letter to a random character from the pool
        letter++;
    }

    return mapping;
}

// Function to encode a given string using the mapping
string encodeString(const string& word, const unordered_map<char, char>& mapping) {
    string encoded;
    // Iterate through each character in the word
    for (char c : word) {
        // Check if the letter exists in the mapping
        if (mapping.find(toupper(c)) != mapping.end()) {
            encoded += mapping.at(toupper(c)); // Encode each letter
        } else {
            encoded += c; // Leave non-alphabetic characters as they are
        }
    }
    return encoded;
}

// Function to generate a random word from a predefined list
string getRandomWord() {
    vector<string> wordList = {"LABYRINTH", "PLANET", "QUEST", "ESCAPE", "GUARDIAN", "GUARDIAN", "MAZE"};
    return wordList[rand() % wordList.size()]; // Pick a random word from the list
}

// Function to display the current mapping to the player (for them to decode the puzzle)
void displayMapping(const unordered_map<char, char>& mapping) {
    cout << "Decoding Key:" << endl;
    int count = 0; // Counter to keep track of how many mappings have been printed in the current row
    for (char letter = 'A'; letter <= 'Z'; ++letter) { // Iterate through letters A-Z and print their mappings
       cout << letter << " = " << mapping.at(letter) << " | "; 
        count++; // Increment counter after each mapping
        if (count % 6 == 0) {
            cout << endl; // After every 6 mappings, print a newline
        }
    }
    cout << endl;
}

// Main game loop
bool decode(){
    srand(time(0)); // Seed random number generator

    unordered_map<char, char> mapping = generateRandomMapping(); // Generate the random letter to symbol mapping

    string word = getRandomWord(); // Get a random word for the puzzle
    string encodedWord = encodeString(word, mapping); // Encode the word using the mapping

    cout << "Welcome to the Decode Language Puzzle!" << endl;
    cout << "Here is the encoded message: " << encodedWord << endl;

    displayMapping(mapping); // Display the key for decoding

    // Get the player's guess for decoding the message
    string userGuess;
    cout << "Try to decode the message: ";
    cin >> userGuess;

    // Convert each character in the string to uppercase
    for (char &c : userGuess) {
        c = toupper(c);
    }

    // Check if the user's guess is correct
    if (userGuess == word) {
        cout << "Congratulations! You decoded the message correctly!" << endl;
        return true;
    } else {
        cout << "Sorry, that's not correct. The correct word was: " << word << endl;
        return false;
    }
    
    return false; // In case of failure, return false
}

// Connect 4 ------------------------------------------------------
const int ROWS = 6; // Number of rows on the board
const int COLS = 7; // Number of columns on the board

// Function to display the board with row labels
void displayBoard(const vector<vector<char>>& board) {
    cout << "   0 1 2 3 4 5 6\n"; // Display column labels (0 to 6)
    // Display the board rows with labels ('F' to 'A')
    char rowLabel = 'F'; // Start with 'F' for the first row
    for (int i = 0; i < ROWS; ++i) {
         cout << rowLabel-- << " "; // Print the current row label and decrement for next
        for (int j = 0; j < COLS; ++j) {
            cout << "|" << board[i][j]; // Print each cell with a '|' separator
        }
        cout << "|\n"; // End the row with a '|'
    }
    cout << "------------------\n"; // Separator line below the board
}

// Function to check if a column is valid for a move
bool isValidMove(const vector<vector<char>>& board, int col) {
    return board[0][col] == ' '; // Check if the top cell in the selected column is empty
}

// Function to drop a piece in the chosen column
bool dropPiece(vector<vector<char>>& board, int col, char player) {
    if (!isValidMove(board, col)) { // Check if the selected column is full
        cout << "Column is full. Try another one.\n";
        return false;
    }

    // Drop the piece into the lowest available row
    for (int i = ROWS - 1; i >= 0; --i) { // Start from the bottom row
        if (board[i][col] == ' ') { // Find the first empty cell
            board[i][col] = player; // Place the player's piece
            return true; // Move successful
        }
    }
    return false; 
}

// Function to check if a player has won
bool checkWin(const vector<vector<char>>& board, char player) {
    // Check horizontal, vertical, and diagonal lines for a win
    // Horizontal check
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            // Check if there are 4 consecutive horizontal pieces for the player
            if (board[row][col] == player && board[row][col + 1] == player && board[row][col + 2] == player && board[row][col + 3] == player) {
                return true;
            }
        }
    }

    // Vertical check
    for (int col = 0; col < COLS; ++col) {
        for (int row = 0; row < ROWS - 3; ++row) {
            // Check if there are 4 consecutive vertical pieces for the player
            if (board[row][col] == player && board[row + 1][col] == player && board[row + 2][col] == player && board[row + 3][col] == player) {
                return true;
            }
        }
    }

    // Diagonal checks (bottom-left to top-right)
    for (int row = 3; row < ROWS; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            // Check for 4 consecutive diagonal pieces for the player
            if (board[row][col] == player && board[row - 1][col + 1] == player && board[row - 2][col + 2] == player && board[row - 3][col + 3] == player) {
                return true;
            }
        }
    }

    // Diagonal checks (top-left to bottom-right)
    for (int row = 0; row < ROWS - 3; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            // Check for 4 consecutive diagonal pieces for the player
            if (board[row][col] == player && board[row + 1][col + 1] == player && board[row + 2][col + 2] == player && board[row + 3][col + 3] == player) {
                return true;
            }
        }
    }

    return false;
}

// Function to let the computer make a random move
int getComputerMove(const vector<vector<char>>& board) {
    vector<int> validCols; // Store all valid columns
    for (int col = 0; col < COLS; ++col) {
        if (isValidMove(board, col)) { // If the column is not full
            validCols.push_back(col); // Add to valid move
        }
    }

    // Randomly select a valid column for the computer to drop its piece
    return validCols[rand() % validCols.size()];
}

// Main game function for Connect 4 (Player vs Computer)
bool connectFour() {
    srand(time(0)); // Seed the random number generator

    vector<vector<char>> board(ROWS, vector<char>(COLS, ' '));
    char currentPlayer = 'X'; // Player 'X' starts first
    bool gameWon = false; // Track if the game is won
    int moveCol;

    cout << "Welcome to Connect 4 (Player vs Computer)!\n";

    while (!gameWon) {
    displayBoard(board); // Show the board

    if (currentPlayer == 'X') { // Player's turn
        int moveCol;
        bool validInput = false;

        // Loop to get valid input from the player
        while (!validInput) {
            cout << "Player's turn (X). Choose a column (0 to 6): ";
            cin >> moveCol;

            // Check if input is a number
            if (cin.fail()) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the rest of the input
                continue;
            }

            // Check if the column is within valid range
            if (moveCol < 0 || moveCol >= COLS) {
                cout << "Invalid column. Please choose a column between 0 and 6.\n";
                continue;
            }

            // If column is valid, attempt to drop the piece
            validInput = true;
            if (!dropPiece(board, moveCol, currentPlayer)) {
                cout << "Column is full. Try again.\n";
                validInput = false;  // Ask for input again
            }
        }

        clearingScreen();

    } else { // Computer's turn (O)
        cout << "Computer's turn (O)...\n";
        moveCol = getComputerMove(board); // Get a valid random move for the computer
        dropPiece(board, moveCol, currentPlayer); // Drop computer's piece
        cout << "Computer chose column " << moveCol << ".\n";
    }

    // Check if the current player won
    if (checkWin(board, currentPlayer)) {
        displayBoard(board); // Show final board state
        if (currentPlayer == 'X') {
            cout << "Player X wins!\n";
            return true; // Player wins
        } else {
            cout << "Computer wins!\n";
            return false; // Computer wins
        }
        gameWon = true;
    }

    // Switch players for the next turn
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    return false;
}

//---------------------------------------------
// Function to display the menu and get user's choice
int displayMenu(int difficulty, bool puzzleOptions) {
    int choice; // Variable to store user's choice
    bool validInput = false; // Flag to ensure valid input is received
    clearingScreen(); // Clears the console screen

    // Display the welcome message and instructions
    cout << "Welcome to the Puzzle Game! Win a puzzle to continue your way!" << endl;
    cout << "Please select a puzzle to play:" << endl;

    // If puzzleOptions is false, display puzzles based on difficulty level
    if (!puzzleOptions) {
        // If puzzleOptions is false, display puzzles based on difficulty level
        if (difficulty == 0) { // Easy Difficulty
            cout << "1. Word Unscramble" << endl;
            cout << "2. Riddle" << endl;
            cout << "3. Pattern Recognition" << endl;
            cout << "4. True or False" << endl;
        }
        else if (difficulty == 1) { // Medium Difficulty
            cout << "1. Sudoku" << endl;
            cout << "2. Code Cracker" << endl;
            cout << "3. Decode Language Puzzle" << endl;
            cout << "4. Connect Four" << endl;
        }
        else if (difficulty == 2) { // Hard Difficulty
            cout << "1. Word Unscramble" << endl;
            cout << "2. Riddle" << endl;
            cout << "3. Pattern Recognition" << endl;
            cout << "4. Sudoku" << endl;
        }
        else {
            // If the difficulty doesn't match Easy, Medium, or Hard, show all options
            cout << "1. Word Unscramble" << endl;
            cout << "2. Riddle" << endl;
            cout << "3. Pattern Recognition" << endl;
            cout << "4. True or False" << endl;
            cout << "5. Sudoku" << endl;
            cout << "6. Code Cracker" << endl;
            cout << "7. Decode Language Puzzle" << endl;
            cout << "8. Connect Four" << endl;
        }
    } else {
        // If puzzleOptions is true, show all puzzles regardless of difficulty
        cout << "1. Word Unscramble" << endl;
        cout << "2. Riddle" << endl;
        cout << "3. Pattern Recognition" << endl;
        cout << "4. True or False" << endl;
        cout << "5. Sudoku" << endl;
        cout << "6. Code Cracker" << endl;
        cout << "7. Decode Language Puzzle" << endl;
        cout << "8. Connect Four" << endl;
    }
    cout << "0. Exit" << endl; // Display the option to exit the game
    
    // Loop until a valid input is provided
    while (!validInput) {
        int numOfChoice; // Variable to store the total number of choices

        // Set the number of choices based on whether puzzleOptions is true or not
        if (!puzzleOptions) {
            numOfChoice = 4;  // Random puzzles, choices range from 0 to 4
        } else {
            numOfChoice = 8;  // All puzzles, choices range from 0 to 8
        }

    // Prompt the user to enter a choice between 0 and the number of valid options
    cout << "Enter your choice (0-" << numOfChoice << "): ";  

    // Read the input from the user and check if it's a valid number
    if (cin >> choice) {
        // Check if the input choice is within the valid range
        if (choice >= 0 && choice <= numOfChoice) {
            validInput = true;  // Valid input, exit the loop
        } else {
            // Inform the user if the choice is invalid
            cout << "Invalid choice. Please enter a number between 0 and " << numOfChoice << "." << endl;
        }
    } else {
        // Handle non-numeric input (if the user enters something other than a number)
        cout << "Invalid input. Please enter a valid number between 0 and " << numOfChoice << "." << endl;

        // Clear the error flag caused by invalid input
        cin.clear();  

        // Discard the invalid input from the buffer to allow for future input attempts
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    }
}
// Return the valid choice once input is validated
return choice;
}
 
// Function to handle puzzle solving
bool solvePuzzle(int difficulty, bool puzzleOptions) {
    bool puzzleSolved = false; // Flag to track whether the puzzle is solved
    int choice = displayMenu(difficulty, puzzleOptions);  // Call puzzle menu
    
    // If the player chooses to exit the menu (choice == 0), return false and exit
    if (choice == 0) {
        cout << "Exiting puzzle menu..." << endl;
        this_thread::sleep_for(seconds(1)); // Wait for 1 second before exiting
        return false; // Exit the puzzle menu
    }

    // If puzzleOptions is false, show a different set of puzzles based on difficulty level
    if (!puzzleOptions){
        // Puzzle solving based on the difficulty level and user's choice
        switch (difficulty) {
        
            case 0:  // Easy Difficulty
            clearingScreen();
            if (choice == 1) {
                puzzleSolved = wordUnscramble();
            } else if (choice == 2) {
                puzzleSolved = riddle();
            } else if (choice == 3) {
                puzzleSolved = patternRecognition();
            } else if (choice == 4) {
                puzzleSolved = trueOrFalse();
            }
            break;

            case 1:  // Medium Difficulty
            clearingScreen();
            if (choice == 1) {
                puzzleSolved = sudoku();
            } else if (choice == 2) {
                puzzleSolved = codeCracker();
            } else if (choice == 3) {
                puzzleSolved = decode();
            } else if (choice == 4) {
                puzzleSolved = connectFour();
            }
            break;

            case 2: // Hard Difficulty
            clearingScreen();
            if (choice == 1) {
                puzzleSolved = wordUnscramble();
            } else if (choice == 2) {
                puzzleSolved = riddle();
            } else if (choice == 3) {
                puzzleSolved = patternRecognition();
            } else if (choice == 4) {
                puzzleSolved = sudoku();
            }
            break;
        }
    // Handling puzzle choices when puzzleOptions is true
    } else {
        // Switch to handle the player's choice for puzzle selection
        switch (choice) {
                case 1:
                    clearingScreen();
                    puzzleSolved = wordUnscramble();  // Replace with actual puzzle function
                    break;
                case 2:
                    clearingScreen();
                    puzzleSolved = riddle();  
                    break;
                case 3:
                    clearingScreen();
                    puzzleSolved = patternRecognition(); 
                    break;
                case 4:
                    clearingScreen();
                    puzzleSolved = trueOrFalse(); 
                    break;
                case 5:
                    clearingScreen();
                    puzzleSolved = sudoku(); 
                    break;
                case 6:
                    clearingScreen();
                    puzzleSolved = codeCracker();  
                    break;
                case 7:
                    clearingScreen();
                    puzzleSolved = decode();
                    break;
                case 8:
                    clearingScreen();
                    puzzleSolved = connectFour();
                    break;
                case 0:
                    return false;  // Exit if player chooses to exit the puzzle menu
                default:
                    clearingScreen();
                    cout << "Invalid choice. Please try again." << endl; // Handle invalid choice
                    return false;
                    break;
            }
    
    }

// Check if the puzzle was successfully solved
    if (puzzleSolved) {
        cout << "Puzzle solved! Path unlocked.\n";
        cout << "Returning to maze..." ;
        this_thread::sleep_for(seconds(2)); // Pause for 2 seconds
        return true;  // Return true when puzzle is solved
    } else {    
        cout << "Returning to maze..." ;
        this_thread::sleep_for(seconds(2));
        return false; // Return false when the puzzle is unsolved
    }
    
return false;
}
   