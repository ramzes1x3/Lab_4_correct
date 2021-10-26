#pragma once
#include "FuncObjectsForMenu.h"

class MenuItem {
public:
	MenuItem(int id, const string& info, IDialog* DialogFuncObj) : _id(id), _info(info),
		dialogFuncObj(DialogFuncObj) {};

	const string& GetInfo() const { return _info; }
	const int GetId() const { return _id; }

	IDialog* dialogFuncObj;
private:
	int _id;
	string _info;
};