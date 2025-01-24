
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<windows.h>
#include<chrono>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // control coloring in grid

char color[15][15];          // 2D array that control color of each letter from the grid
char your_choice = '0';     
int h_for = 0, h_back = 0, v_for = 0, v_back = 0, d_for = 0, d_back = 0; // word dist.

/* Function: Calculating teleword*/
void teleword(char grid[][15])
{
	cout << endl << endl << "TELEWORD IS:";
	for (int i = 0;i < 15;i++)
	{
		for (int j = 0;j < 15;j++)
		{
			if (color[i][j] == 'w')     // Choosing letters whose color is white
			{
				cout << grid[i][j];
			}
		}
	}
}

/* Function: Printing grid*/
void print_grid(char grid[15][15])
{
	for (int i = 0; i < 15;i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (color[i][j] == 'w')                   // If color's white
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << grid[i][j];
				cout << " ";
			}
			else if (color[i][j] == 'y')              // If color's yellow
			{
				SetConsoleTextAttribute(hConsole, 14);
				cout << grid[i][j];
				cout << " ";
			}
			else if (color[i][j] == 'b')               // If color's blue
			{
				SetConsoleTextAttribute(hConsole, 9);
				cout << grid[i][j];
				cout << " ";
			}
			else if (color[i][j] == 'r')               // If color's red
			{
				SetConsoleTextAttribute(hConsole, 12);
				cout << grid[i][j];
				cout << " ";
			}

		}
		SetConsoleTextAttribute(hConsole, 15);        // Setting color of console-print back to white
		cout << endl;
	}
}

/* Function: Return true if word exists in top-right direction*/
bool d_col(string word, char grid[15][15], int r, int c, int j, int size)
{
	for (j++; j < size; j++)
	{
		if (grid[--r][++c] != word[j])
		{
			return false;
		}
	}
	if (j == word.size())
	{
		return true;
	}
}

/* Function: Return true if word exists in down-left direction*/
bool d_row(string word, char grid[15][15], int r, int c, int j, int size)
{

	for (j++; j < size; j++)
	{
		if (grid[++r][--c] != word[j])
		{
			return false;
		}
	}
	if (j == word.size())
	{
		return true;
	}
}

/* Function: Return true if word exists in top-left direction*/
bool d_backward(string word, char grid[15][15], int r, int c, int j, int size)
{

	for (j++; j < size; j++)
	{
		if (grid[--r][--c] != word[j])
		{
			return false;
		}
	}
	if (j == word.size())
	{
		return true;
	}
}

/* Function: Return true if word exists in down-right direction*/
bool d_forward(string word, char grid[15][15], int r, int c, int j, int size)
{

	for (j++; j < size; j++)
	{
		if (grid[++r][++c] != word[j])
		{
			return false;
		}
	}
	if (j == word.size())
	{
		return true;
	}
}

/* Function: Return true if word exists in top direction*/
bool up(string word, char grid[15][15], int r, int c, int j, int size)
{
	for (j++; j < size; j++)
	{
		if (grid[--r][c] != word[j])
		{
			return false;
		}
	}
	return true;
}

/* Function: Return true if word exists in left direction*/
bool left(string word, char grid[15][15], int r, int c, int j, int size)
{
	for (j++; j < size; j++)
	{
		if (grid[r][--c] != word[j])
		{
			return false;
		}
	}
	if (j == word.size())
	{
		return true;
	}
}

/* Function: Return true if word exists in down direction*/
bool down(string word, char grid[15][15], int r, int c, int j, int size)
{
	for (j++; j < size; j++)
	{
		if (grid[++r][c] != word[j])
		{
			return false;
		}
	}
	if (j == word.size())
	{
		return true;
	}
}

/* Function: Return true if word exists in right direction*/
bool right(string word, char grid[15][15], int r, int c, int j, int size)
{
	for (j++; j < size; j++)
	{
		if (grid[r][++c] != word[j])
		{
			return false;
		}
	}
	if (j == word.size())
	{
		return true;
	}
}

/* Function: Finding a word in grid (same approach)- just to calculate staistics*/
void x_search(string words[], char grid[15][15], int i, int count, int heavy_row[], int heavy_col[])
{
	bool find = false;
	string word;
	word = words[i];
	int size;

	if (count - i == 1)
		size = word.size() - 1;
	else
		size = word.size();

	for (int j = 0;j < size; j++)    // j for characters!
	{
		if (word[j] >= 'a' && word[j] <= 'z')
			word[j] = word[j] - 32;
	}

	for (int r = 0;r < 15 && !find;r++)
	{
		for (int c = 0;c < 15 && !find;c++)
		{
			if (grid[r][c] == word[0])
			{
				if (size + c <= 15)
				{
					int r1 = r; int c1 = c + 1;
					if (grid[r1][c1] == word[1])
					{
						find = right(word, grid, r1, c1, 1, size);
						if (find)
						{
							int c3 = c1;
							h_for++;  // word distribution

							/* heavy row and column*/
							heavy_row[r] ++;
							heavy_col[c] ++;
							heavy_col[c3] ++;
							c3 = c3 + 1;
							for (int l = 2;l < size;l++, c3++)
							{
								heavy_col[c3] ++;
							}
						}
					}
				}
				if (!find && size + r <= 15)
				{
					int r1 = r + 1; int c1 = c;
					if (grid[r1][c1] == word[1])
					{
						find = down(word, grid, r1, c1, 1, size);
						if (find)
						{
							int r3 = r1;

							v_for++;  // word distribution

							/* heavy row and column*/
							heavy_col[c] ++;
							heavy_row[r] ++;
							heavy_row[r3] ++;
							r3 = r3 + 1;
							for (int l = 2;l < size;l++, r3++)
							{
								heavy_row[r3] ++;
							}
						}
					}
				}
				if (!find && short(size - c) <= 1)
				{
					int r1 = r; int c1 = c - 1;
					if (grid[r1][c1] == word[1])
					{
						find = left(word, grid, r1, c1, 1, size);
						if (find)
						{
							int c3 = c1;

							h_back++;  // word distribution

							/* heavy row and column*/
							heavy_row[r] ++;
							heavy_col[c] ++;
							heavy_col[c3] ++;
							c3 = c3 - 1;
							for (int l = 2;l < size;l++, c3--)
							{
								heavy_col[c3] ++;
							}

						}
					}
				}
				if (!find && short(size - r) <= 1)
				{
					int r1 = r - 1; int c1 = c;
					if (grid[r1][c1] == word[1])
					{
						find = up(word, grid, r1, c1, 1, size);
						if (find)
						{
							int r3 = r1;

							v_back++; // word distribution

							/* heavy row and column*/
							heavy_col[c] ++;
							heavy_row[r] ++;
							heavy_row[r3] ++;
							r3 = r3 - 1;
							for (int l = 2;l < size;l++, r3--)
							{
								heavy_row[r3] ++;
							}
						}

					}
				}
				if (!find && size + c <= 15 && size + r <= 15)
				{
					int r1 = r + 1; int c1 = c + 1;
					if (grid[r1][c1] == word[1])
					{
						find = d_forward(word, grid, r1, c1, 1, size);
						if (find)
						{

							int r3 = r1;
							int c3 = c1;

							d_for++; // word distribution

							/* heavy row & column*/
							heavy_col[c] ++;
							heavy_row[r] ++;
							heavy_row[r3] ++;
							heavy_col[c3] ++;
							r3 = r3 + 1;
							c3 = c3 + 1;
							for (int l = 2;l < size;l++, r3++, c3++)
							{
								heavy_row[r3] ++;
								heavy_col[c3] ++;
							}
						}
					}
				}
				if (!find && short(size - r) <= 1 && short(size - c) <= 1)
				{
					int r1 = r - 1; int c1 = c - 1;
					if (grid[r1][c1] == word[1])
					{
						find = d_backward(word, grid, r1, c1, 1, size);
						if (find)
						{
							int c3 = c1;
							int r3 = r1;

							d_back++;  // word distribution

							/* heavy row & column*/
							heavy_col[c] ++;
							heavy_row[r] ++;
							heavy_row[r3] ++;
							heavy_col[c3] ++;
							r3 = r3 - 1;
							c3 = c3 - 1;
							for (int l = 2;l < size;l++, r3--, c3--)
							{
								heavy_row[r3] ++;
								heavy_col[c3] ++;
							}
						}
					}
				}
				if (!find && (size + r <= 15) && (short(size - c) <= 1))
				{
					int r1 = r + 1; int c1 = c - 1;
					if (grid[r1][c1] == word[1])
					{
						find = d_row(word, grid, r1, c1, 1, size);
						if (find)
						{
							int c3 = c1;
							int r3 = r1;

							d_back++;  // word distribution

							/* heavy row & column*/
							heavy_col[c] ++;
							heavy_row[r] ++;
							heavy_row[r3] ++;
							heavy_col[c3] ++;
							r3 = r3 + 1;
							c3 = c3 - 1;
							for (int l = 2;l < size;l++, r3++, c3--)
							{
								heavy_row[r3] ++;
								heavy_col[c3] ++;
							}
						}
					}
				}

				if (!find && (short(size - r) <= 1) && (size + c <= 15))
				{
					int r1 = r - 1; int c1 = c + 1;
					if (grid[r1][c1] == word[1])
					{
						find = d_col(word, grid, r1, c1, 1, size);
						if (find)
						{
							int c3 = c1;
							int r3 = r1;

							d_for++; // word distribution

							/* heavy row & column*/
							heavy_col[c] ++;
							heavy_row[r] ++;
							heavy_row[r3] ++;
							heavy_col[c3] ++;
							r3 = r3 - 1;
							c3 = c3 + 1;
							for (int l = 2;l < size;l++, r3--, c3++)
							{
								heavy_row[r3] ++;
								heavy_col[c3] ++;
							}
						}
					}
				}
			}
		}
	}
}

/* Function: Finding a word in grid*/
void search(string words[], char grid[15][15], int i, int count)
{
	bool find = false;
	int size;

	/* Calculating size of the word to be found*/
	string word = words[i];
	if (count - i == 1)
		size = word.size() - 1;
	else
		size = word.size();

	/* Uppercase all the letters in the word */
	for (int j = 0;j < size; j++)   
	{
		if (word[j] >= 'a' && word[j] <= 'z')
			word[j] = word[j] - 32;
	}

	for (int r = 0;r < 15 && !find;r++)
	{
		for (int c = 0;c < 15 && !find;c++)
		{
			if (grid[r][c] == word[0])               // First letter found
			{
				if (size + c <= 15)                  // Proceed only if word can exist to its right
				{
					int r1 = r; int c1 = c + 1;
					if (grid[r1][c1] == word[1])     // second letter found
					{
						find = right(word, grid, r1, c1, 1, size);  // Search word to its right

						/* If found- set grid's color accordingly*/
						if (find)
						{
							if (color[r][c] == 'w')
								color[r][c] = 'y';
							else if (color[r][c] == 'y')
								color[r][c] = 'b';
							else if (color[r][c] == 'b')
								color[r][c] = 'r';

							if (color[r1][c1] == 'w')
								color[r1][c1] = 'y';
							else if (color[r1][c1] == 'y')
								color[r1][c1] = 'b';
							else if (color[r1][c1] == 'b')
								color[r1][c1] = 'r';

							c1 = c1 + 1;
							for (int l = 2; l < size; l++, c1++)
							{
								if (color[r1][c1] == 'w')
									color[r1][c1] = 'y';
								else if (color[r1][c1] == 'y')
									color[r1][c1] = 'b';
								else if (color[r1][c1] == 'b')
									color[r1][c1] = 'r';
							}
						}
					}
				}

				if (!find && size + r <= 15)         // Proceed only if word can exist below it
				{
					int r1 = r + 1; int c1 = c;
					if (grid[r1][c1] == word[1])
					{
						find = down(word, grid, r1, c1, 1, size);     // Search word at its bottom

						/* If found- set grid's color accordingly*/
						if (find)
						{
							if (color[r][c] == 'w')
								color[r][c] = 'y';
							else if (color[r][c] == 'y')
								color[r][c] = 'b';
							else if (color[r][c] == 'b')
								color[r][c] = 'r';

							if (color[r1][c1] == 'w')
								color[r1][c1] = 'y';
							else if (color[r1][c1] == 'y')
								color[r1][c1] = 'b';
							else if (color[r1][c1] == 'b')
								color[r1][c1] = 'r';

							r1 = r1 + 1;
							for (int l = 2; l < size; l++, r1++)
							{
								if (color[r1][c1] == 'w')
									color[r1][c1] = 'y';
								else if (color[r1][c1] == 'y')
									color[r1][c1] = 'b';
								else if (color[r1][c1] == 'b')
									color[r1][c1] = 'r';
							}
						}
					}
				}

				if (!find && short(size - c) <= 1)      // Proceed only if word can exist to its left
				{
					int r1 = r; int c1 = c - 1;
					if (grid[r1][c1] == word[1])        // Second letter found
					{
						find = left(word, grid, r1, c1, 1, size);   // Search word to its left

						/* If found- set grid's color accordingly*/
						if (find)
						{
							if (color[r][c] == 'w')
								color[r][c] = 'y';
							else if (color[r][c] == 'y')
								color[r][c] = 'b';
							else if (color[r][c] == 'b')
								color[r][c] = 'r';

							if (color[r1][c1] == 'w')
								color[r1][c1] = 'y';
							else if (color[r1][c1] == 'y')
								color[r1][c1] = 'b';
							else if (color[r1][c1] == 'b')
								color[r1][c1] = 'r';

							c1 = c1 - 1;
							for (int l = 2; l < size; l++, c1--)
							{
								if (color[r1][c1] == 'w')
									color[r1][c1] = 'y';
								else if (color[r1][c1] == 'y')
									color[r1][c1] = 'b';
								else if (color[r1][c1] == 'b')
									color[r1][c1] = 'r';
							}
						}
					}
				}

				if (!find && short(size - r) <= 1)     // Proceed only if word can exist to its top
				{
					int r1 = r - 1; int c1 = c;
					if (grid[r1][c1] == word[1])       // Second letter found
					{
						find = up(word, grid, r1, c1, 1, size);  // Search word to its top

						/* If found- set grid's color accordingly*/
						if (find)
						{
							if (color[r][c] == 'w')
								color[r][c] = 'y';
							else if (color[r][c] == 'y')
								color[r][c] = 'b';
							else if (color[r][c] == 'b')
								color[r][c] = 'r';

							if (color[r1][c1] == 'w')
								color[r1][c1] = 'y';
							else if (color[r1][c1] == 'y')
								color[r1][c1] = 'b';
							else if (color[r1][c1] == 'b')
								color[r1][c1] = 'r';

							r1 = r1 - 1;
							for (int l = 2; l < size; l++, r1--)
							{
								if (color[r1][c1] == 'w')
									color[r1][c1] = 'y';
								else if (color[r1][c1] == 'y')
									color[r1][c1] = 'b';
								else if (color[r1][c1] == 'b')
									color[r1][c1] = 'r';
							}
						}

					}
				}

				if (!find && size + c <= 15 && size + r <= 15)    // Proceed only if word can exist to its down-right
				{
					int r1 = r + 1; int c1 = c + 1;
					if (grid[r1][c1] == word[1])             // Second letter found
					{
						find = d_forward(word, grid, r1, c1, 1, size);   // Search word to its down-right

						/* If found- set grid's color accordingly*/
						if (find)
						{
							if (color[r][c] == 'w')
								color[r][c] = 'y';
							else if (color[r][c] == 'y')
								color[r][c] = 'b';
							else if (color[r][c] == 'b')
								color[r][c] = 'r';

							if (color[r1][c1] == 'w')
								color[r1][c1] = 'y';
							else if (color[r1][c1] == 'y')
								color[r1][c1] = 'b';
							else if (color[r1][c1] == 'b')
								color[r1][c1] = 'r';

							c1 = c1 + 1;
							r1 = r1 + 1;
							for (int l = 2; l < size; l++, c1++, r1++)
							{
								if (color[r1][c1] == 'w')
									color[r1][c1] = 'y';
								else if (color[r1][c1] == 'y')
									color[r1][c1] = 'b';
								else if (color[r1][c1] == 'b')
									color[r1][c1] = 'r';
							}
						}
					}
				}

				if (!find && short(size - r) <= 1 && short(size - c) <= 1)  // Proceed only if word can exist to its top-left
				{
					int r1 = r - 1; int c1 = c - 1;
					if (grid[r1][c1] == word[1])          // Second letter found
					{
						find = d_backward(word, grid, r1, c1, 1, size);   // Search word to its top-left

						/* If found- set grid's color accordingly*/
						if (find)
						{
							if (color[r][c] == 'w')
								color[r][c] = 'y';
							else if (color[r][c] == 'y')
								color[r][c] = 'b';
							else if (color[r][c] == 'b')
								color[r][c] = 'r';

							if (color[r1][c1] == 'w')
								color[r1][c1] = 'y';
							else if (color[r1][c1] == 'y')
								color[r1][c1] = 'b';
							else if (color[r1][c1] == 'b')
								color[r1][c1] = 'r';

							c1 = c1 - 1;
							r1 = r1 - 1;
							for (int l = 2; l < size; l++, c1--, r1--)
							{
								if (color[r1][c1] == 'w')
									color[r1][c1] = 'y';
								else if (color[r1][c1] == 'y')
									color[r1][c1] = 'b';
								else if (color[r1][c1] == 'b')
									color[r1][c1] = 'r';
							}
						}
					}
				}

				if (!find && (size + r <= 15) && (short(size - c) <= 1))   // Proceed only if word can exist to its down-left
				{
					int r1 = r + 1; int c1 = c - 1;
					if (grid[r1][c1] == word[1])                // Second letter found
					{
						find = d_row(word, grid, r1, c1, 1, size); // Search word to its down-left

						/* If found- set grid's color accordingly*/
						if (find)
						{
							if (color[r][c] == 'w')
								color[r][c] = 'y';
							else if (color[r][c] == 'y')
								color[r][c] = 'b';
							else if (color[r][c] == 'b')
								color[r][c] = 'r';

							if (color[r1][c1] == 'w')
								color[r1][c1] = 'y';
							else if (color[r1][c1] == 'y')
								color[r1][c1] = 'b';
							else if (color[r1][c1] == 'b')
								color[r1][c1] = 'r';

							c1 = c1 - 1;
							r1 = r1 + 1;
							for (int l = 2; l < size; l++, c1--, r1++)
							{
								if (color[r1][c1] == 'w')
									color[r1][c1] = 'y';
								else if (color[r1][c1] == 'y')
									color[r1][c1] = 'b';
								else if (color[r1][c1] == 'b')
									color[r1][c1] = 'r';
							}
						}
					}
				}

				if (!find && (short(size - r) <= 1) && (size + c <= 15))  // Proceed only if word can exist to its up-right
				{
					int r1 = r - 1; int c1 = c + 1;
					if (grid[r1][c1] == word[1])      // Second letter found
					{
						find = d_col(word, grid, r1, c1, 1, size);  // Search word to its top-left

						/* If found- set grid's color accordingly*/
						if (find)
						{
							if (color[r][c] == 'w')
								color[r][c] = 'y';
							else if (color[r][c] == 'y')
								color[r][c] = 'b';
							else if (color[r][c] == 'b')
								color[r][c] = 'r';

							if (color[r1][c1] == 'w')
								color[r1][c1] = 'y';
							else if (color[r1][c1] == 'y')
								color[r1][c1] = 'b';
							else if (color[r1][c1] == 'b')
								color[r1][c1] = 'r';

							c1 = c1 + 1;
							r1 = r1 - 1;
							for (int l = 2; l < size; l++, c1++, r1--)
							{
								if (color[r1][c1] == 'w')
									color[r1][c1] = 'y';
								else if (color[r1][c1] == 'y')
									color[r1][c1] = 'b';
								else if (color[r1][c1] == 'b')
									color[r1][c1] = 'r';
							}
						}

					}
				}
			}
		}
	}


}

/* Function: Finding all words in grid*/
void S_search(string words[], char grid[15][15], int count, int t_turn)
{
	for (int i = t_turn;i <= count;i++)    // Searching each word 
	{
		search(words, grid, i, count);     // Call to search individual word
	}
}

/* Function: Managing user choice */
void choice(string words[], char grid[15][15], int count, int t_turn, int heavy_row[], int heavy_col[])
{
	cout << "PRESS S TO SOLVE PUZZLE AT ONCE!" << endl;
	cout << "PRESS T SOLVE PUZZLE STEP BY STEP!" << endl;
	cout << "PRESS X TO PRINT PUZZLE STATISTICS!" << endl;
	cout << "Enter your choice:";
	cin >> your_choice;

	if (your_choice == 'S' || your_choice == 's') // Solving puzzle in one click
	{
		system("CLS");

		t_turn = t_turn + 1;					// This variable actually controls turns for T, but S and T are utlizing same function.
		S_search(words, grid, count, t_turn);   // Searching words in grid

		/* Pritning final colored grid along with the teleword */
		print_grid(grid);
		teleword(grid);
	}
	else if (your_choice == 'T' || your_choice == 't') // Solving puzzle with 'count' number of clicks
	{
		system("CLS");

		t_turn = t_turn + 1;                           // t_turn keeps track of current turn
		while (t_turn < count)
		{
			/* Searching word one by one & print colored grid gradually-untill all are searched */
			search(words, grid, t_turn, count);
			print_grid(grid);
			system("pause");

			if (count - t_turn != 1)                    // Keep clearing screen untill we're not finished
				system("CLS");

			t_turn = t_turn + 1;
			if (count - t_turn == 0)
			{
				teleword(grid);                         // Printing teleword once all grid is solved
			}
		}
	}

	/*
	1. Solving grid
	2. Printing final corlored grid
	3. Calculating time & statistics
	*/
	else if (your_choice == 'X' || your_choice == 'x')
	{
		/* Initialization */
		float w = 0;
		float l = 0;
		int max = 0;
		int min = 16;

		t_turn = t_turn + 1;			      // This variable actually controls turns for T, but S and T are utlizing same function
		system("CLS");

		/* Clculating time */
		auto start = chrono::high_resolution_clock::now();
		S_search(words, grid, count, t_turn);  // Searching words in grid         
		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

		/* Printing final colored grid & teleword */
		print_grid(grid);
		teleword(grid);
		cout << "\nTime taken:" << duration << " micro seconds"; // Printing time

		// Calculating statistics: heavy row/column & word distribution
		for (int i = 0; i < count; i++)
		{
			x_search(words, grid, i, count, heavy_row, heavy_col);
		}

		// Calculating statistics : word length data
		for (int i = 0;i < count;i++)
		{
			if (count - i != 1)
			{
				l = words[i].size();
				w = w + l;
			}
			else
				l = (words[i].size()) - 1;

			if (l > max)
			{
				max = l;
			}
			if (l < min)
			{
				min = l;
			}
		}

		// Calculating statistics : word scatter
		int scatter = 0; bool flag = true;
		{
			for (int i = 0;i < 15; i++)
			{
				flag = true;
				for (int j = 0;j < 15 && flag;j++)
				{
					if (color[i][j] == 'w')
					{
						flag = false;
						scatter++;
					}
				}
			}
		}

		// Calculating statistics: Finding index of heaviest row/column
		int hh_row = 0;
		int hh_col = 0;
		int index_r = 0;
		int index_c = 0;
		for (int i = 0; i < 15; i++)
		{
			if (heavy_row[i] > hh_row)
			{
				hh_row = heavy_row[i];
				index_r = i;
			}
			if (heavy_col[i] > hh_col)
			{
				hh_col = heavy_col[i];
				index_c = i;
			}
		}

		/* Printing statistics*/
		cout << endl << "Largest Word Length: " << max;
		cout << ", Shortest Word Length:" << min;
		cout << ", Average Word Length:" << (w) / count << endl;
		cout << "Word Distribution:" << "Horizontal " << h_for + h_back << " ( " << h_for << "," << h_back << " )" << ";" << "Vertical " << v_for + v_back << " ( " << v_for << "," << v_back << " )" << ";" << "Diagnol " << d_for + d_back << " ( " << d_for << "," << d_back << " )";
		cout << endl << "Teleword scatter:" << scatter;
		cout << endl << "Heaviest Row:" << index_r << endl;
		cout << "Heaviest Column:" << index_c << endl;
	}
}

/* Function: Populating 1D array of words from specified file*/
int get_words(string words[], ifstream& fileobj, string file_buffer)
{
	int n = 0;
	while (getline(fileobj, file_buffer, ','))     // reading complete one word
	{
		words[n] = file_buffer;                    // Storing word in array
		n++;
		getline(fileobj, file_buffer, ' ');        // skipping space after , & before next word because there's no space in grid
	}

	/* Discarding . from the last word of the file by adding \0*/
	string s;
	s = words[n - 1];
	s[s.size() - 1] = '\0';
	words[n - 1] = s;
	return n;
}

/* Function: Populating 2D grid(15/15) from specified file*/
void get_grid(char grid[][15], ifstream& fileobj, string file_buffer)
{
	int row = 0;
	int col = 0;

	while (getline(fileobj, file_buffer, '\n'))     // reading complete one row
	{
		col = 0;
		if (!file_buffer.empty())                   // Until whole row is not traversed
		{
			for (int k = 0;k < 29;k++)              // 29 because 14 spaces & 15 character
			{
				if (file_buffer[k] != ' ')          // Omitting spaces, as they are not a part of word
				{
					grid[row][col] = file_buffer[k];
					col++;
				}
			}
			row++;
		}
		else
			return;
	}
}

/* Main function */
int main()
{
	int option = 0;
	int count = 0;
	ifstream fileobj;
	string file_buffer;
	char grid[15][15];
	int heavy_row[15];
	int heavy_col[15];
	string words[100];
	int t_turn = -1;

	/* Populating 1-D array with 0s to calculate heavy row and heavy column later */
	for (int j = 0;j < 15; j++)
	{
		heavy_row[j] = 0;
		heavy_col[j] = 0;
	}
	for (int i = 0;i < 15;i++)
	{
		for (int j = 0;j < 15;j++)
		{
			color[i][j] = 'w';
		}
	}

	/* File reading */
	fileobj.open("teleword.txt");
	if (fileobj.is_open());      //check if the file is opened or not!
	{
		get_grid(grid, fileobj, file_buffer);
		count = get_words(words, fileobj, file_buffer);
	}
	
	fileobj.close();

	/* Printing grid & words (initial state) */
	print_grid(grid);
	cout << endl;
	for (int i = 0;i < count;i++)
	{
		if (i < count - 1)
			cout << words[i] << ", ";
		else
			cout << words[i] << ".";
	}
	cout << endl << endl;

	/* Asing for user choice */
	choice(words, grid, count, t_turn, heavy_row, heavy_col);
}