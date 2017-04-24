#ifndef MOVABLE_SETTINGS_H
#define MOVABLE_SETTINGS_H
#include "Map.h"

template <typename T>
struct MovableSettings{
	MovableSettings();
	MovableSettings(RPG::Map<T>& map, const Position& position);
	MovableSettings(const MovableSettings& rhs) = default;
	~MovableSettings() = default;
	MovableSettings& operator=(const MovableSettings& rhs) = default;

	RPG::Map<T>& mMap;
	Position mPosition;
};

template <typename T>
MovableSettings<T>::MovableSettings() : mMap(RPG::Map<T>()), mPosition(Position()){

}

template <typename T>
MovableSettings<T>::MovableSettings(RPG::Map<T>& map, const Position& position) : mMap(map), mPosition(position) {

}
#endif