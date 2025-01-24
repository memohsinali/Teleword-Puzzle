# Teleword-Puzzle
1. How is Teleword played
It’s a simple game. It consists of a 15 x 15 grid of letters, as you can see in
the following photographs of the puzzle published in the Dawn paper of
September 30, 2018. Other than the grid, it contains a list of words. The goal
is to find all the words of the list in the grid. The words might appear in the
forward or backward direction in a row, column or diagonal of the grid. Two or
more words may overlap. In other words, some letters of the grid maybe
shared by two or more words.
Once the player has found all the words, and circled out all the letters in the
grid covered by these words (as shown in the right hand picture) the left-over
letters (i.e. the uncircled letters) spell the Teleword. Finding this Teleword is
the goal.

2.The first fifteen lines of the file contain 15 letters each of the grid. The letters
in each line are separated by single spaces.
After the grid there is an empty line.
After that is the list of words. The words in the list are separated by a
comma followed by a space. The last word is followed by a full-stop.
(Note: there are no new lines between the words, it only appears that
there is a line between, for example, Chef and Cleaner because of the
small screen size which had to display the content in the next line; there is
no actual new-line character there).
Your program will need to open the file and load both the grid and the
word list. Obviously, no word in the list can be more than 15 letters
long.

3. How should the program work
After reading the data from the file, the Teleword Solver should display the
grid on the screen, followed by the word list, exactly as they are shown in
the picture of the file above.
After this, the program should print 3 options:
1. Press S to solve the puzzle at once.
2. Press T to solve the puzzle step by step.
3. Press X to print puzzle statistics.
The working of these options is explained below:

Option 1 “Press S to solve the puzzle at once.”
If the user selects this option, the program should simply print the entire grid
with all the covered letters in colors and the uncovered letters in white after all
words have been found in the grid. After that, the program should display the
Teleword and terminate.
There is one added feature of this option: the covered letters should be
colored according to the number of words they occur in. If a letter appears is
only one word it should be yellow, if it appears in two words it should be blue,
if it appears in more than two words it should be red; the leftover letters should
be white.

Option 2 “Press T to solve the puzzle step by step.”
If the user selects this option, the program should allow them to see one word
being found at a time. First, they should see the whole grid and list in white.
When they press enter, they should see the first word of the list turned yellow in
the grid. On each successive enter, the next word in the list is turned yellow in
the grid (the shared letters being color coded as in option 1). Once all words
have been found, the grid should look exactly as at the end of option 1, and the
program should terminate.
For instance, in the example shown above, which contains 42 words in the
list, the program will terminate after 42 enters.

Option 3 “Press X to print puzzle statistics.”
If the user presses X, then they should see the entire output of option 1, and
after that the following information printed line by line:
 Time to Solve: the time taken by the program to solve the puzzle (not
including the time to compute statistics): a value in number of seconds
(this could be a fraction of a second). Figure out how to do this in code.
 Word Statistics: Longest word length; shortest word length,
average word length.
 Word Distribution: number of horizontal, vertical and diagonal words.
Each count should also mention how many were forward and backwards
amongthem.
 For example: Horizontal: 16 (10, 6), Vertical: 19 (7, 12), Diagonal: 7
(2, 5) The numbers in the brackets are forward and backward
counts respectively.

 The Teleword Scatter: how many rows were touched by the
Teleword letters. For instance, in the example given in the picture, the
letters of ‘Grandmother’ come from 7 different rows. So the Teleword
Scatter is 7.
 Heaviest Row, Heaviest Column: the row and column numbers
that were touched by most words.
These statistics should be printed line by line in the following order:
Time to Solve:
Longest Word Length: , Shortest Word Length: , Average Word Length:
Word Distribution:
Teleword Scatter:
Heaviest Row:
Heaviest Column:
