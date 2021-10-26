#pragma once
#include <string>
#include <sstream>
using namespace std;
using FlatId = int;
using FlatArea = double;

class Flat {

public:

	Flat() {};
	Flat(FlatId id, const FlatArea& area, int numberOfRooms, int floor, const string& district)
		: _id(id), _area(area), _numberOfRooms(numberOfRooms), _floor(floor), _district(district) {};

	const FlatId GetId() const { return _id; }
	const FlatArea GetArea() const { return _area; }
	const int GetNumberOfRooms() const { return _numberOfRooms; }
	const int GetFloor() const { return _floor; };
	const char* GetDistrict() const { return _district.c_str(); }

	string ToString() const {
		ostringstream sout;
		sout << "Id:" << _id << endl
			<< "Area:" << _area << endl
			<< "Number of rooms:" << _numberOfRooms << endl
			<< "Floor:" << _floor << endl
			<< "District:" << _district << endl
			<< "*******************************************************************" << endl;

		return sout.str();
	}

private:
	FlatId _id = 0;
	FlatArea _area = 0.0;
	int _numberOfRooms = 0;
	int _floor = 0;
	string _district;
};