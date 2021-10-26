#pragma once
#include <string>
#include <sstream>
using namespace std;

class Candidate {
public:
	Candidate() {}
	Candidate(int id, const string& firstname, const string& lastname, const string& patronymic, const string& dateOfBirth, const string& placeOfJob, double rating)
		: _id(id), _firstname(firstname), _lastname(lastname), _patronymic(patronymic), _dateOfBirth(dateOfBirth), _placeOfJob(placeOfJob), _rating(rating) {}

	const int GetId() const { return _id; }
	const string& GetFirstname() const { return _firstname; }
	const string& GetLastname() const { return _lastname; }
	const string& GetPatronymic() const { return _patronymic; }
	const string& GetDateOfBirth() const { return _dateOfBirth; }
	const string& GetPlaceOfJob() const { return _placeOfJob; }
	const double GetRating() const { return _rating; }

	string ToString() {
		ostringstream sout;
		sout << "Id:" << _id << endl
		<< "Firstname:" << _firstname << endl
		<< "Lastname:" << _lastname << endl
		<< "Patronymic:" << _patronymic << endl
		<< "Date of birth:" << _dateOfBirth << endl
		<< "Place of job:" << _placeOfJob << endl
		<< "Rating:" << _rating << endl
		<< "*******************************************************************" << endl;

		return sout.str();
	}
private:
	int _id = 0;;
	string _firstname;
	string _lastname;
	string _patronymic;
	string _dateOfBirth;
	string _placeOfJob;
	double _rating = 0.0;
};