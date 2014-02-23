#Ariadne's thread

Given the binary matrix representative of all places in a game (i.e. if there is a direct passage between two places, M(i,j)=1 otherwise 0), list all levels (strongly connected components of places), find the map presented in a matrix M where M(i,j)=k if there exist k direct passages from level i to level j and finally find the longest path from the level which contains place 1 to the level containing the latest place in the game.<br>

For further information, see *Subject.pdf* and *Report.pdf* files.

####Author:
Quentin SCHULZ (quentin.schulz@utbm.fr)

####Usage:

**Needed file**

* *matrix.txt* which is the source file of the binary matrix representative of all places in the game.

**Needed dependencies**

* g++ (you can install it on Windows via CygWin or on Linux with: sudo apt-get install g++ )

Download all files (except PDF files if you do not need them) and run the make file with: make.<br>
You can run your program with: /path/to/project/project matrix.txt<br>

#####Changelog

**v0.1 - 2014-02-23**
Initial release.<br>
