Small games written in C
=========================
Contents
-------------------------
1.Maze<br>
2.Box pushing<br>
Usage
-------------------------
<pre>
	'W'/'w' - Up
	'S'/'s' - Down
	'A'/'a' - Left
	'D'/'d' - Right
	'Q'/'q' - Exit
	When the object(A box in game 2 and yourself in game 1)
	moves to the '!' sign, you win.
</pre>
Map file
--------
<p>The map file(map) should be like this:</p>
<pre>
	1.There should be only 3 kinds of characters:
		- '.': Space,
		- '/': Wall,
		- '!': Exit
	2.The size should be 15*20=300 bytes
</pre>
<p>If not, the program will not run.</p>
Program structure
-----------------
<p>Take box-pushing as exmaple:</p>
<pre>
	1.Read the map file(./map) and load the maze(15x20)
	2.Draw the main character
	3.Draw the box
	4.Listen keyboard input and determine movement
	5.Check if the route is valid(Not approaching the wall).
		- Method: If the next coordinate is wall in the matrix, stop moving.
	6.Move the charachter
	7.Check if the character has successfully gone out.
</pre>
Compatibility
-------------
The program compatibles with both POSIX-Compatible OS(Linux, OSX) and Windows.
