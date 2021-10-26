#pragma once
#include "Flat.h"
#include "Candidate.h"
#include <vector>
#include <map>
#include <set>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
using FlatId = int;
using FlatArea = double;

class BaseContainer {
public:
	virtual void SetItem() = 0;
	virtual void FindItem(double) = 0;

	virtual ~BaseContainer() = default;
};