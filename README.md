
# Lazy Digger:

* This is a very simplified C++ terminal mini game without a clock, based on the notrious game - "Crazy Digger", can be found here 
- https://www.youtube.com/watch?v=7vkOX77n1G0.

* This game was created for school project, and it demonstrates the use of interface designing, complex classes that
contain objects of different classes, communication between different classses, exchanage of information, etc.

## The board consists of several objects:

* Digger: The player displayed by a single char - '/'.
* Monster : The enemy displayed by - '!'.
* Diamond: Immovable object that can be collected by the digger - 'D'.
* Stone: Imovable object that can be eaten by the digger until a certain amount - '@'.
* Wall : An obstacle - '#'.

The different stages can be found and edited in the Board.txt file inside resources folder.

### There are two numbers above every stage:
The 1st number is to determine how many rows and coulmns (N*N) the stage consists of.
The 2nd number determines the amount of stones a player can eat before losing a life.

* The movement of the player is with the keyboard (UP, DOWN, LEFT, RIGHT).
In order to advance to the next stage and finish the game, the player must collect all of the diamonds.

This is a C++ CMAKE project, created with Visual Studio 2019.
Written by : Ors



