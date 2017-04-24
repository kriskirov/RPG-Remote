#ifndef MAP_H
#define MAP_H
#include "Position.h"
#include "IPosition.h"
#include <math.h>
#include <vector>
#include <set>
#include <type_traits>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <functional>

namespace RPG{

	template <typename T>
	class Map {
	public:
		Map(unsigned int horizontalSize, unsigned int verticalSize);
		unsigned int getHorizontalSize();
		unsigned int getVerticalSize();
		unsigned int getRoundedHorizontalCentre();
		unsigned int getRoundedVerticalCentre();
		Position getRoundedCentre();
		void locate_relative(Position& offset, T obj);//if it does not exists - locate it, if it exists - simply change the location (no duplicates)
		void locate_absolute(Position& absolute, T obj);//same here
		void erase(T obj);//delete from the map
		std::set<T> getAllAtPositionWhere(Position& absolute, std::function<bool(T)> boolExpression);
		std::set<T> getAllAtPosition(Position& absolute);
	private:
		void add(Position& pos, T obj);
		void remove(T obj);
		bool find(T obj, Position* foundObjCoord);
		bool exists(T obj);
		unsigned int position2Dto1D(Position& pos);
		Position position1Dto2D(unsigned int pos);
		Position clampToBounds(Position& pos);

		int mHorizontalSize, mVerticalSize;
		std::vector< std::set<T> > mMap;
	};

	//<summary>
	//NOTE: The map size accepts only sizes greater than 0. Any other size will be automatically assumed as 1.
	//</summary>
	template <typename T>
	Map<T>::Map(unsigned int horizontalSize, unsigned int verticalSize){
		assert(horizontalSize > 0 && verticalSize > 0);
		static_assert(std::is_pointer<T>::value, "T must be a pointer type");
		static_assert(std::is_base_of<IPosition, remove_pointer<T>::type>::value, "T must implement IPosition");
		mHorizontalSize = std::max<unsigned int>(1,horizontalSize);
		mVerticalSize = std::max<unsigned int>(1,verticalSize);
		mMap = std::vector< std::set<T> >(mHorizontalSize*mVerticalSize);
	}

	template <typename T>
	unsigned int Map<T>::getHorizontalSize(){
		return mHorizontalSize;
	}

	template <typename T>
	unsigned int Map<T>::getVerticalSize(){
		return mRightEnd;
	}

	template <typename T>
	unsigned int Map<T>::getRoundedHorizontalCentre(){
		return mHorizontalSize / 2;
	}

	template <typename T>
	unsigned int Map<T>::getRoundedVerticalCentre(){
		return mVericalSize / 2;
	}

	template <typename T>
	Position Map<T>::getRoundedCentre(){
		return Position(getRoundedHorizontalCentre(), getRoundedVerticalCentre());
	}

	template <typename T>
	bool Map<T>::find(T obj, Position* foundObjCoord){
		typename std::vector< std::set<T> >::iterator iter;
		for (iter = mMap.begin(); iter < mMap.end(); ++iter){
			if ((*iter).find(obj) != (*iter).end()){
				Position pos2d = position1Dto2D(std::distance(mMap.begin(),iter));
				*foundObjCoord = pos2d;
				return true;
			}
		}
		return false;
	}

	template<typename T>
	bool Map<T>::exists(T obj){
		typename std::vector< std::set<T> >::iterator iter;
		for (iter = mMap.begin(); iter < mMap.end(); ++iter){
			if ((*iter).find(obj) != (*iter).end()){
				return true;
			}
		}
		return false;
	}

	template <typename T>
	void Map<T>::add(Position& pos, T obj){
		if (!exists(obj)){
			Position newPosition = clampToBounds(pos);
			mMap.at(position2Dto1D(newPosition)).insert(obj);
			obj->setPosition(newPosition);
		}
	}

	template <typename T>
	void Map<T>::remove(T obj){
		Position result;
		if (find(obj, &result)){
			//std::cout << mMap.at(position2Dto1D(result)).erase(obj) << " element erased!" << std::endl;
			mMap.at(position2Dto1D(result)).erase(obj);
		}
	}

	template <typename T>
	void Map<T>::locate_relative(Position& relative, T obj){
		if (exists(obj)){
			remove(obj);
		}
		add(obj->getPosition() + relative, obj);
	}

	template <typename T>
	void Map<T>::locate_absolute(Position& absolute, T obj){
		if (exists(obj)){
			remove(obj);
		}
		add(absolute, obj);
	}

	template <typename T>
	void Map<T>::erase(T obj){
		remove(obj);
	}

	template <typename T>
	std::set<T> Map<T>::getAllAtPositionWhere(Position& absolute, std::function<bool(T)> boolExpression){
		Position clampedPos = clampToBounds(absolute);
		unsigned int clampedPos1D = position2Dto1D(clampedPos);
		std::set<T>& referencedSet = mMap.at(clampedPos1D);
		std::set<T> filteredSet;
		for (std::set<T>::iterator iter = referencedSet.begin(); iter != referencedSet.end(); ++iter){
			if (boolExpression(*iter))
				filteredSet.insert(*iter);
		}
		return filteredSet;
	}

	template <typename T>
	std::set<T> Map<T>::getAllAtPosition(Position& absolute){
		Position clampedPos = clampToBounds(absolute);
		clampedPos = position2Dto1D(clampedPos);
		return mMap.at(clampedPos);
	}

	template <typename T>
	unsigned int Map<T>::position2Dto1D(Position& pos){
		return pos.y*mHorizontalSize + (mHorizontalSize - (mHorizontalSize - pos.x));
	}

	template<typename T>
	Position Map<T>::position1Dto2D(unsigned int pos){
		return Position(pos%mHorizontalSize,pos/mHorizontalSize);
	}

	template<typename T>
	Position Map<T>::clampToBounds(Position& pos){
		unsigned int newX = std::min(mHorizontalSize-1,std::max(0,pos.x));
		unsigned int newY = std::min(mVerticalSize-1, std::max(0, pos.y));
		return Position(newX, newY);
	}
}
#endif