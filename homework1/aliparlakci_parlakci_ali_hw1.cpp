#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct coordinate
{
	int x, y;
};

struct word
{
	string text, direction, orientation;
	coordinate start;
};

void printMatrix(const vector<vector<char>> &matrix);
bool placeWordToMatrix(const word &givenWord, vector<vector<char>> &matrix);
bool getAvailability(const coordinate &cell, vector<vector<char>> &matrix);
string getNextDirection(string currDirection, string orientation);
bool getNextCoordinate(const coordinate &current, coordinate &next, const coordinate &bounds, string direction);
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
		vector<vector<char>> matrix(height, vector<char>(width, '-'));

		string line = "";
		while (getline(inputFile, line))
		{
			istringstream lineStream(line);

			word givenWord;
			bool isLineValid = false;
			bool isPlacementSuccessful = false;

			if (readLine(lineStream, givenWord))	// If number of inputs in the line is 5
			{
				isLineValid = validateLine(givenWord, height, width);
			}
			else
			{
				cout << "Invalid line! Number of values is different than 5." << endl;
			}

			if (isLineValid)
			{
				isPlacementSuccessful = placeWordToMatrix(givenWord, matrix);

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

				printMatrix(matrix);
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

// Prints matrix
void printMatrix(const vector<vector<char>> &matrix)
{
	for (int row = 0; row < matrix.size(); row++)
	{
		for (int col = 0; col < matrix[0].size(); col++)
		{
			cout << matrix[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Tries to place word into matrix.
//
// If it is successful, matrix parameter will be replaced by the new matrix and it will return true.
// If it is NOT succesful, matrix parameter will not be changed and function returns false.
bool placeWordToMatrix(const word &givenWord, vector<vector<char>> &matrix)
{
	vector<vector<char>> newMatrix = matrix;

	coordinate bounds;
	bounds.x = newMatrix.size() - 1;
	bounds.y = newMatrix[0].size() - 1;	// It is guaranteed that first element of vector is
										// also a vector. So, newMatrix[0].size() would not throw
										// any exception.

	char currChar = givenWord.text[0];
	coordinate currCoor = givenWord.start;
	coordinate nextCoor;

	bool isSuccesful = true;

	if (getAvailability(currCoor, newMatrix))
	{
		newMatrix[currCoor.x][currCoor.y] = currChar;

		for (int i = 1; i < givenWord.text.length(); i++)
		{
			char currChar = givenWord.text[i];
			string currDirection = givenWord.direction;
			
			bool isCellAvailable = getNextCoordinate(currCoor, nextCoor, bounds, currDirection) && getAvailability(nextCoor, newMatrix);

			for (int i = 0; i < 3 && !isCellAvailable; i++)
			{
				string nextDirection = getNextDirection(currDirection, givenWord.orientation);
				isCellAvailable = getNextCoordinate(currCoor, nextCoor, bounds, nextDirection) && getAvailability(nextCoor, newMatrix);
				currDirection = nextDirection;
			}

			if (isCellAvailable)
			{
				newMatrix[nextCoor.x][nextCoor.y] = currChar;
				currCoor = nextCoor;
			}
			else
			{
				isSuccesful = false;
				break;
			}
		}
	}
	else
	{
		isSuccesful = false;
	}

	matrix = isSuccesful ? newMatrix : matrix;

	return isSuccesful;
}

bool getAvailability(const coordinate &cell, vector<vector<char>> &matrix)
{
	return matrix[cell.x][cell.y] == '-';
}

// Rotates the direction with the given orientation and returns the new direction
string getNextDirection(string currDirection, string orientation)
{
	string cw[] = { "r", "d", "l", "u" };
	string ccw[] = { "r", "u", "l", "d" };

	for (int i = 0; i < 4; i++)
	{
		if (orientation == "CW")
		{
			if (cw[i] == currDirection)
			{
				return i == 3 ? cw[0] : cw[i+1];
			}
		}
		else if (orientation == "CCW")
		{
			if (ccw[i] == currDirection)
			{
				return i == 3 ? ccw[0] : ccw[i+1];
			}
		}
	}

	return "";	// Fallback string. Function is not expected to reach this line.
}

bool getNextCoordinate(const coordinate &current, coordinate &next, const coordinate &bounds, string direction)
{
	if (direction == "d")
	{
		if (current.x + 1 <= bounds.x)
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
		if (current.y + 1 <= bounds.y)
		{
			next.x = current.x;
			next.y = current.y + 1;
			return true;
		}		
	}
	
	return false;
	
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
		isFail = !lineStream.fail();	// We expect lineStream to fail
	}

	return !isFail;	// Success is inverse of fail
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