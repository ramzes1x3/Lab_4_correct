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

	virtual void ShowAllFlats() const {};
	virtual vector<FlatId> QuickFindItemByArea(FlatArea) { vector<FlatId> flatId; return flatId; }
	virtual shared_ptr<Flat> GetFlatById(FlatId) const { shared_ptr<Flat> flat; return flat; }
	virtual void AddFlat(shared_ptr<Flat>) {}
	virtual void RemoveFlat(FlatId) {}

	virtual void ShowCandidates() const {}
	virtual void AddCandidate(shared_ptr<Candidate>) {}
	virtual void RemoveCandidate(int) {}

	virtual ~BaseContainer() = default;
};