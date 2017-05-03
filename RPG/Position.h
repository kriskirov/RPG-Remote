#ifndef POSITION_H
#define POSITION_H

struct Position{
	int x, y;
	Position();
	Position(int xPos, int yPos);

	Position operator+(Position& rhs);
	Position operator-(Position& rhs);
};
#endif