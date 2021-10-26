#pragma once
#include <iostream>
#include <windows.h>
#include "BaseContainer.h"
#include "FlatsContainer.h"
#include "CandidatesContainer.h"
#include "FuncObjectsForMenu.h"
#include "DialogMenuItem.h"

class Console {
public:
	Console() {
		_flatsContainer->SetItem();
		_candidatesContainer->SetItem();

		_flatsMenuItems.push_back(MenuItem{ QuickFindItemByAreaIdDialog, "Quickly find a flat by area(map)", new QuickFindFlatByArea() });
		_flatsMenuItems.push_back(MenuItem{ ShowAllFlatsIdDialog, "Show all flats", new ShowAllFlats() });
		_flatsMenuItems.push_back(MenuItem{ RemoveFlatIdDialog , "Remove flat", new RemoveFlat() });
		_flatsMenuItems.push_back(MenuItem{ FindFlatByAreaIdDialog, "Find a flat by area(vector)", new FindFlat() });
		_flatsMenuItems.push_back(MenuItem{ AddFlatIdDialog, "Add flat", new AddFlat() });
		_flatsMenuItems.push_back(MenuItem{ ExitIdDialog, "Exit", new Exit });

		_candidatesMenuItems.push_back(MenuItem{ FindCandidatesIdDialog, "Find candidates who have a higher rating(multimap)", new FindCandidate() });
		_candidatesMenuItems.push_back(MenuItem{ ShowCandidatesIdDialog, "Show all Candidates", new ShowAllCandidates() });
		_candidatesMenuItems.push_back(MenuItem{ RemoveCandidateIdDialog, "Remove Candidate", new RemoveCandidate() });
		_candidatesMenuItems.push_back(MenuItem{ AddCandidateIdDialog, "Add Candidate", new AddCandidate() });
		_candidatesMenuItems.push_back(MenuItem{ ExitIdDialog, "Exit", new Exit });
	}

	void Run();

	~Console() {
		for (auto menuItem : _flatsMenuItems) {
			delete[] menuItem.dialogFuncObj;
		}

		for (auto menuItem : _candidatesMenuItems) {
			delete[] menuItem.dialogFuncObj;
		}

		delete _flatsContainer;
		delete _candidatesContainer;
	}

private:
	
	void ShowDialogItems(int);

	BaseContainer* _flatsContainer  = new FlatsContainer;
	BaseContainer* _candidatesContainer = new CandidatesContainer;
	vector<MenuItem> _flatsMenuItems;
	vector<MenuItem> _candidatesMenuItems;

	const int ExitIdDialog = 0;

	const int QuickFindItemByAreaIdDialog = 1;
	const int ShowAllFlatsIdDialog = 2;
	const int RemoveFlatIdDialog = 3;
	const int FindFlatByAreaIdDialog = 4;
	const int AddFlatIdDialog = 5;

	const int FindCandidatesIdDialog = 1;
	const int ShowCandidatesIdDialog = 2;
	const int RemoveCandidateIdDialog = 3;
	const int AddCandidateIdDialog = 4;
};