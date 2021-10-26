#pragma once
#include "Interactor.h"

class IDialog {
public:
	virtual void operator() (BaseContainer*) = 0;
	virtual ~IDialog() = default;
};

//candidatesOperations
class ShowAllCandidates1 : public IDialog {
public:
	virtual void operator() (BaseContainer* container) {
		container->ShowCandidates();
	}
};


class FindCandidate : public IDialog {
public:
	virtual void operator () (BaseContainer* container) {
		double rating;
		cout << "Enter rating(multimap):";
		cin >> rating;
		container->FindItem(rating);
	}
};


class ShowAllCandidates : public IDialog {
public:
	virtual void operator() (BaseContainer* container) {
		container->ShowCandidates();
	}
};


class RemoveCandidate : public IDialog {
public:
	virtual void operator () (BaseContainer* container) {
		int id;
		cout << "Enter id:";
		cin >> id;
		container->RemoveCandidate(id);
	}
};


class AddCandidate : public IDialog {
public:
	virtual void operator() (BaseContainer* container) {
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
		container->AddCandidate(tmpCnd);
	}
};


//flatsOperations
class QuickFindFlatByArea : public IDialog {
public:
	virtual void operator() (BaseContainer* container) {
		FlatArea area;
		cout << "Enter area(map):";
		cin >> area;
		vector<FlatId> flatsByArea = container->QuickFindItemByArea(area);//здесь все айди квартир подходящих по площади
		if (flatsByArea.size() == 0) {
			cout << "Flats with such an area have not been found" << endl << endl;
		}
		else {
			for (auto flat : flatsByArea) {//проходим по всем айди
				cout << container->GetFlatById(flat)->ToString() << endl;//получаем квартиру по айди и выводим её описание
			}
		}
	}
};


class ShowAllFlats : public IDialog {
public:
	virtual void operator() (BaseContainer* container) {
		container->ShowAllFlats();
	}
};


class RemoveFlat : public IDialog {
public:
	virtual void operator() (BaseContainer* container) {
		FlatId id;
		cout << "Enter id:";
		cin >> id;
		container->RemoveFlat(id);
	}
};


class FindFlat : public IDialog {
public:
	virtual void operator () (BaseContainer* container) {
		double area;
		cout << "Enter area(vector):";
		cin >> area;
		container->FindItem(area);
	}
};


class AddFlat : public IDialog {
public:
	virtual void operator () (BaseContainer* container) {
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
		container->AddFlat(tmpFlat);
	}
};


class Exit : public IDialog {
	virtual void operator() (BaseContainer* container) {}
};