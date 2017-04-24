#include "Position.h"

Position::Position(){
	x = 0;
	y = 0;
}

Position::Position(int xPos, int yPos){
	x = xPos;
	y = yPos;
}

Position Position::operator+(Position& rhs){
	return Position(x + rhs.x, y + rhs.y);
}

Position Position::operator-(Position& rhs){
	return Position(x - rhs.x, y - rhs.y);
}