# GameOfLife
Conway's Game of Life, also known as the Game of Life or simply Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is the best-known example of a cellular automaton.

My implementation was made in QT Creator in C++ using QT widgets

![alt text](https://user-images.githubusercontent.com/76635569/154850077-a83edf59-a915-4c0c-bcb8-72933a48a835.png)

The field is stored in a matrix, and all calculations are also made in it. Visual changes to the field with each iteration are made with QPainter.

# Buttons
The "Start" button is responsible for starting the process. 
The "Clear" button clears the field completely. 
The "Stop" button stops the iteration. 
The "Set Glider" button sets the "glider" figure in the upper left corner. 
The "Random fill" button randomly fills the field, leaning more toward the "live" cells.
The "Next step" button makes 1 iteration.

# Example

The glider's encounter with the field boundary in my cellular automaton:

![alt text](https://user-images.githubusercontent.com/76635569/154850247-b34059b4-83d0-4b22-962d-6b7ac96052ee.png)
