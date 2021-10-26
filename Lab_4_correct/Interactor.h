#pragma once
#include <iostream>
#include <windows.h>
#include "BaseContainer.h"
#include "FlatsContainer.h"
#include "CandidatesContainer.h"

class Console {
public:
	Console() {
		_flatsContainer.SetItem();
		_candidatesContainer.SetItem();

		_menuItems.push_back(MenuItem{ QuickFindItemByAreaIdDialog, "Quickly find a flat by area(map)", new QuickFindFlatByArea(this) });
		_menuItems.push_back(MenuItem{ ShowAllFlatsIdDialog, "Show all flats", new ShowAllFlats(this) });
		_menuItems.push_back(MenuItem{ RemoveFlatIdDialog , "Remove flat", new RemoveFlat(this) });
		_menuItems.push_back(MenuItem{ FindFlatByAreaIdDialog, "Find a flat by area(vector)", new FindFlat(this) });
		_menuItems.push_back(MenuItem{ AddFlatIdDialog, "Add flat", new AddFlat(this) });
		_menuItems.push_back(MenuItem{ FindCandidatesIdDialog, "Find candidates who have a higher rating(multimap)", new FindCandidate(this) });
		_menuItems.push_back(MenuItem{ ShowCandidatesIdDialog, "Show all Candidates", new ShowAllCandidates(this) });
		_menuItems.push_back(MenuItem{ RemoveCandidateIdDialog, "Remove Candidate", new RemoveCandidate(this) });
		_menuItems.push_back(MenuItem{ AddCandidateIdDialog, "Add Candidate", new AddCandidate(this) });
		_menuItems.push_back(MenuItem{ ExitIdDialog, "Exit", new Exit });
	}

	void Run() {
		int action = 1;

		while (action) {
			try {

				ShowDialogItems();
				cin >> action;

				if (action >= _menuItems.size()) {
					cout << "Action not found" << endl << endl;
					continue;
				}

				for (auto& menuItem : _menuItems) {
					if (menuItem.GetId() == action) {
						menuItem.dialogFuncObj->operator()();
					}
				}
			}
			catch (const exception& ex) {
				cerr << ex.what() << endl;
				break;
			}
		}
	}

	//funcObjects
	class IDialog {
	public:
		virtual void operator() () = 0;
		virtual ~IDialog() = default;
	};

	//flats
	class QuickFindFlatByArea : public IDialog {
	public:
		QuickFindFlatByArea(Console* owner)
			: _owner(owner) {}

		virtual void operator() () {
			FlatArea area;
			cout << "Enter area(map):";
			cin >> area;
			vector<FlatId> flatsByArea = _owner->_flatsContainer.QuickFindItemByArea(area);//здесь все айди квартир подходящих по площади
			if (flatsByArea.size() == 0) {
				cout << "Flats with such an area have not been found" << endl << endl;
			}
			else {
				for (auto flat : flatsByArea) {//проходим по всем айди
					cout << _owner->_flatsContainer.GetFlatById(flat)->ToString() << endl;//получаем квартиру по айди и выводим её описание
				}
			}
		}
	private:
		Console* _owner;
	};

	class ShowAllFlats : public IDialog {
	public:

		ShowAllFlats(Console* owner)
			: _owner(owner) {}

		virtual void operator() () {
			_owner->_flatsContainer.ShowAllFlats();
		}

	private:
		Console* _owner;
	};

	class RemoveFlat : public IDialog {
	public:
		RemoveFlat(Console* owner)
			: _owner(owner) {}

		virtual void operator() () {
			FlatId id;
			cout << "Enter id:";
			cin >> id;
			_owner->_flatsContainer.RemoveFlat(id);
		}

	private:
		Console* _owner;
	};

	class FindFlat : public IDialog {
	public:
		FindFlat(Console* owner)
			:_owner(owner) {}

		virtual void operator () () {
			double area;
			cout << "Enter area(vector):";
			cin >> area;
			_owner->_flatsContainer.FindItem(area);
		}

	private:
		Console* _owner;
	};

	class AddFlat : public IDialog {
	public:
		AddFlat(Console* owner)
			:_owner(owner) {}

		virtual void operator () () {
			FlatId id;
			FlatArea area;
			int numberOfRooms;
			int floor;
			string district;
			cout << "Id:";
			cin >> id;
			cout << "Area:";
			cin >> area;
			cout << "Number of rooms:";
			cin >> numberOfRooms;
			cout << "Floor:";
			cin >> floor;
			cout << "District:";
			cin >> district;
			cout << endl;
			shared_ptr<Flat> tmpFlat(make_shared<Flat>(id, area, numberOfRooms, floor, district));
			_owner->_flatsContainer.AddFlat(tmpFlat);
		}
	private:
		Console* _owner;
	};

	//candidates
	class FindCandidate : public IDialog {
	public:
		FindCandidate(Console* owner)
			:_owner(owner) {}

		virtual void operator () () {
			double rating;
			cout << "Enter rating(multimap):";
			cin >> rating;
			_owner->_candidatesContainer.FindItem(rating);
		}

	private:
		Console* _owner;
	};

	class ShowAllCandidates : public IDialog {
	public:

		ShowAllCandidates(Console* owner)
			: _owner(owner) {}

		virtual void operator() () {
			_owner->_candidatesContainer.ShowCandidates();
		}

	private:
		Console* _owner;
	};

	class RemoveCandidate : public IDialog {
	public:
		RemoveCandidate(Console* owner)
			: _owner(owner) {}

		virtual void operator () () {
			int id;
			cout << "Enter id:";
			cin >> id;
			_owner->_candidatesContainer.RemoveCandidate(id);
		}
	private:
		Console* _owner;
	};

	class AddCandidate : public IDialog {
	public:

		AddCandidate(Console* owner)
			: _owner(owner) {}

		virtual void operator() () {
			int id;
			string firstname;
			string lastname;
			string patronymic;
			string dateOfBirth;
			string placeOfJob;
			double rating;

			cout << "Id:";
			cin >> id;
			cout << "Firstname:";
			cin >> firstname;
			cout << "Lastname:";
			cin >> lastname;
			cout << "Patronymic:";
			cin >> patronymic;
			cout << "Date of birth:";
			cin >> dateOfBirth;
			cout << "Place of job:";
			cin >> placeOfJob;
			cout << "Rating:";
			cin >> rating;
			cout << endl;

			shared_ptr<Candidate> tmpCnd = make_shared<Candidate>(id, firstname, lastname, patronymic, dateOfBirth, placeOfJob, rating);
			_owner->_candidatesContainer.AddCandidate(tmpCnd);
		}

	private:
		Console* _owner;
	};

	class Exit : public IDialog {
		virtual void operator() () {}
	};
	//funcObjects

	~Console() {
		for (auto menuItem : _menuItems) {
			delete[] menuItem.dialogFuncObj;
		}
	}

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

private:
	
	void ShowDialogItems() {
		for (auto& dialogItem : _menuItems) {
			cout << dialogItem.GetId() << " " << dialogItem.GetInfo() << endl;
		}
	}

	FlatsContainer _flatsContainer;
	CandidatesContainer _candidatesContainer;
	vector<MenuItem> _menuItems;

	const int ExitIdDialog = 0;
	const int QuickFindItemByAreaIdDialog = 1;
	const int ShowAllFlatsIdDialog = 2;
	const int RemoveFlatIdDialog = 3;
	const int FindFlatByAreaIdDialog = 4;
	const int AddFlatIdDialog = 5;
	const int FindCandidatesIdDialog = 6;
	const int ShowCandidatesIdDialog = 7;
	const int RemoveCandidateIdDialog = 8;
	const int AddCandidateIdDialog = 9;
};