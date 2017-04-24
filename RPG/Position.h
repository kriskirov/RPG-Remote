#ifndef POSITION_H
#define POSITION_H

struct Position{
	int x, y;//2 axis
	Position();//sets the position to 0,0
	Position(int xPos, int yPos);

	Position operator+(Position& rhs);
	Position operator-(Position& rhs);
};
#endif