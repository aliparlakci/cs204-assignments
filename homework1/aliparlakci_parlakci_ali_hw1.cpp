#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct coordinate
{
	int x = 0, y = 0;
};

struct word
{
	string text, direction, orientation;
	coordinate start;
};

class WordSnake
{
	public:
		WordSnake(int _heigth, int _width);
		void place(word &_givenWord, bool &result);
		void print() const;

	private:
		bool placeWordToMatrix();
		bool placeLetterToMatrix(vector<vector<char>> &matrix, char letter, coordinate &currCoor);
		bool getCellAvailability(const coordinate &cell, vector<vector<char>> &matrix) const;
		string getNextDirection(string currDirection, string orientation) const;
		bool getNextCoordinate(const coordinate &current, coordinate &next, string direction);
		vector<vector<char>> wordMatrix;
		int heigth;
		int width;
		word givenWord;
};

bool validateLine(word &givenWord, int &height, int &width);
bool readLine(istringstream &lineStream, word &givenWord);
bool getMatrixSize(ifstream &inputFile, int &height, int &width);
void openFile(ifstream &file);

int main()
{
	ifstream inputFile;
	openFile(inputFile);

	int height = 0, width = 0;
	bool isMatrixSizeValid = getMatrixSize(inputFile, height, width);

	if (isMatrixSizeValid)
	{
		WordSnake snake(height, width);

		string line = "";
		while (getline(inputFile, line))
		{
			istringstream lineStream(line);

			word givenWord;
			bool isLineValid = false;
			bool isPlacementSuccessful = false;

			if (readLine(lineStream, givenWord)) // If number of inputs in the line is 5
			{
				isLineValid = validateLine(givenWord, height, width);
			}
			else
			{
				cout << "Invalid line! Number of values is different than 5." << endl;
			}

			if (isLineValid)
			{
				bool isSuccessful;
				snake.place(givenWord, isSuccessful);
				snake.print();
			}
			cout << endl;
		}
	}
	else
	{
		cout << "Invalid number for row and/or column!" << endl;
	}

	return 0;
}

// Returns true if the line is given correctly
bool validateLine(word &givenWord, int &height, int &width)
{
	bool isValidX = givenWord.start.x >= 0 && givenWord.start.x < height;
	bool isValidY = givenWord.start.y >= 0 && givenWord.start.y < width;

	if (!isValidX || !isValidY)
	{
		cout << "Starting point is out of range! Point: "
			 << givenWord.start.x << " "
			 << givenWord.start.y
			 << endl;

		return false;
	}

	string dir = givenWord.direction;
	if (dir != "r" && dir != "l" && dir != "u" && dir != "d")
	{
		cout << "Invalid input for direction! Direction: " << dir << endl;

		return false;
	}

	if (givenWord.orientation != "CCW" && givenWord.orientation != "CW")
	{
		cout << "Invalid input for orientation! Orientation: " << givenWord.orientation << endl;

		return false;
	}

	return true;
}

// Extracts information about given word.
//
// Returns FALSE if number of inputs in line is NOT exactly 5
bool readLine(istringstream &lineStream, word &givenWord)
{
	bool isFail = false;
	lineStream >> givenWord.text;
	isFail = lineStream.fail();

	lineStream >> givenWord.start.x;
	isFail = lineStream.fail();

	lineStream >> givenWord.start.y;
	isFail = lineStream.fail();

	lineStream >> givenWord.direction;
	isFail = lineStream.fail();

	lineStream >> givenWord.orientation;
	isFail = lineStream.fail();

	if (!isFail)
	{
		// Check if we can get more entries
		// If we can, there are more than 5 entries
		string _;
		lineStream >> _;
		isFail = !lineStream.fail(); // We expect lineStream to fail
	}

	return !isFail; // Success is inverse of fail
}

// Extracts matrix size from input file's current line
//
// Returns true if the size is valid, false if it is invalid
bool getMatrixSize(ifstream &inputFile, int &height, int &width)
{
	string line = "";

	getline(inputFile, line);
	istringstream lineStream(line);

	lineStream >> height;
	lineStream >> width;

	return height >= 0 && width >= 0;
}

// Makes sure the file is opened and successful
void openFile(ifstream &file)
{
	string filePath;
	do
	{
		if (file.fail())
		{
			cout << "File name is incorrect, please enter again: " << endl;
			file.clear();
		}

		cout << "Please enter the name of the file: ";
		cin >> filePath;
		file.open(filePath.c_str());

	} while (file.fail());

	cout << endl;
}

/*				WORDSNAKE FUNCTIONS STARTING				*/

WordSnake::WordSnake(int _heigth, int _width)
{
	wordMatrix = vector<vector<char>> (_heigth, vector<char>(_width, '-'));
	word givenWord;
	heigth = _heigth;
	width = _width;
}

void WordSnake::place(word &_givenWord, bool &result)
{
	givenWord = _givenWord;

	bool isPlacementSuccessful = placeWordToMatrix();

	if (isPlacementSuccessful)
	{
		cout << "\"" << givenWord.text << "\" "
				<< "was put into matrix with given starting point: "
				<< givenWord.start.x << "," << givenWord.start.y
				<< endl;

		cout << "direction: " << givenWord.direction << " "
				<< "orientation: " << givenWord.orientation
				<< endl;
	}
	else
	{
		cout << "\"" << givenWord.text << "\" "
				<< "could not be put into matrix with given starting point: "
				<< givenWord.start.x << "," << givenWord.start.y
				<< endl;

		cout << "direction: " << givenWord.direction << " "
				<< "orientation: " << givenWord.orientation
				<< endl;
	}

	result = isPlacementSuccessful;
}

// Prints matrix
void WordSnake::print() const
{
	for (int row = 0; row < heigth; row++)
	{
		for (int col = 0; col < width; col++)
		{
			cout << wordMatrix[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Tries to place word into matrix.
//
// If it is successful, matrix parameter will be replaced by the new matrix and it will return true.
// If it is NOT succesful, matrix parameter will not be changed and function returns false.
bool WordSnake::placeWordToMatrix()
{
	vector<vector<char>> newMatrix = wordMatrix;

	char currChar = givenWord.text[0];
	coordinate currCoor = givenWord.start;

	bool isSuccesful = true;

	if (getCellAvailability(currCoor, newMatrix))
	{
		newMatrix[currCoor.x][currCoor.y] = currChar; // Place the first character as we know where to put it

		for (int i = 1; i < givenWord.text.length(); i++) // Start from the second char
		{
			char currChar = givenWord.text[i];
			
			isSuccesful = placeLetterToMatrix(newMatrix, currChar, currCoor);

			if (!isSuccesful)
			{
				break;
			}
		}
	}
	else
	{
		isSuccesful = false;
	}

	wordMatrix = isSuccesful ? newMatrix : wordMatrix;

	return isSuccesful;
}

// Tries to find a cell for a letter in matrix. Places the letter if it founds.
//
// Returns true if it can place the letter. currCoor will be the coordinate of the new letter.
// Returns false if it cannot place the letter, currCoor will stay same.
bool WordSnake::placeLetterToMatrix(vector<vector<char>> &matrix, char letter, coordinate &currCoor)
{
	string currDirection = givenWord.direction;
	coordinate nextCoor;

	bool isCellAvailable;
	int index = 0;
	do
	{
		// Get a new coordinate and check if it is suitable to place a letter there
		isCellAvailable = getNextCoordinate(currCoor, nextCoor, currDirection) && getCellAvailability(nextCoor, matrix);

		// Get a new direction in case we cannot place a letter with the current direction
		currDirection = getNextDirection(currDirection, givenWord.orientation);

		index++;

	} while (!isCellAvailable && index < 4);

	if (isCellAvailable)
	{
		matrix[nextCoor.x][nextCoor.y] = letter;
		currCoor = nextCoor;
		return true;
	}
	else
	{
		return false;
	}
}

// Returns true if we can place a letter to the given coordiante.
bool WordSnake::getCellAvailability(const coordinate &cell, vector<vector<char>> &matrix) const
{
	if (cell.x >= matrix.size() || cell.y >= matrix[0].size())
	{
		return false;
	}
	return matrix[cell.x][cell.y] == '-';
}

// Rotates the direction with the given orientation and returns the new direction
string WordSnake::getNextDirection(string currDirection, string orientation) const
{
	string cw[] = {"r", "d", "l", "u"};
	string ccw[] = {"r", "u", "l", "d"};

	for (int i = 0; i < 4; i++)
	{
		if (orientation == "CW")
		{
			if (cw[i] == currDirection)
			{
				return i == 3 ? cw[0] : cw[i + 1];
			}
		}
		else if (orientation == "CCW")
		{
			if (ccw[i] == currDirection)
			{
				return i == 3 ? ccw[0] : ccw[i + 1];
			}
		}
	}

	return ""; // Fallback string. Function is not expected to reach this line.
}

// Replaces next variable with the next coordinate according to direction.
//
// Returns false if there is no suitable cell towards the given direction.
bool WordSnake::getNextCoordinate(const coordinate &current, coordinate &next, string direction)
{
	if (direction == "d")
	{
		if (current.x + 1 <= heigth)
		{
			next.x = current.x + 1;
			next.y = current.y;
			return true;
		}
	}
	else if (direction == "u")
	{
		if (current.x - 1 >= 0)
		{
			next.x = current.x - 1;
			next.y = current.y;
			return true;
		}
	}
	else if (direction == "l")
	{
		if (current.y - 1 >= 0)
		{
			next.x = current.x;
			next.y = current.y - 1;
			return true;
		}
	}
	else if (direction == "r")
	{
		if (current.y + 1 <= width)
		{
			next.x = current.x;
			next.y = current.y + 1;
			return true;
		}
	}

	return false;
}
/*				WORDSNAKE FUNCTIONS ENDING				*/