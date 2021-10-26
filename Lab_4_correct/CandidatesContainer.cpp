#include "CandidatesContainer.h"

void CandidatesContainer::SetItem() {
	ifstream fin("inputCandidates.txt");
	if (!fin.is_open()) {
		throw logic_error("No file with candidates");
	}
	else {
		while (!fin.eof()) {
			int id;
			string firstname;
			string lastname;
			string patronymic;
			string dateOfBirth;
			string placeOfJob;
			double rating;

			fin >> id >> firstname >> lastname >> patronymic;
			fin.ignore(1, '\n');
			getline(fin, dateOfBirth);
			getline(fin, placeOfJob);
			fin >> rating;

			shared_ptr<Candidate> tmpCnd = make_shared<Candidate>(id, firstname, lastname, patronymic, dateOfBirth, placeOfJob, rating);
			_candidates.emplace(tmpCnd->GetRating(), tmpCnd);
		}
		fin.close();
	}
}

void CandidatesContainer::FindItem(double rating) {
	auto item = _candidates.upper_bound(rating);
	if (item != _candidates.end()) {
		for (auto it = item; it != _candidates.end(); it++) {
			cout << (*it).second->ToString();
		}
	}
	else {
		cout << "There are no candidates with such a rating" << endl;
	}
}

void CandidatesContainer::ShowCandidates() const{
	for (auto& candidate : _candidates) {
		cout << candidate.second->ToString();
	}
	cout << endl;
}

void CandidatesContainer::AddCandidate(shared_ptr<Candidate> candidate) {
	int counterCopyId = 0;
	for (auto& item : _candidates) {
		if (item.second->GetId() == candidate->GetId()) {
			counterCopyId++;
			break;
		}
	}

	if (!counterCopyId) {
		_candidates.emplace(candidate->GetRating(), candidate);
	}
	else {
		cout << "Such an id exists" << endl << endl;
	}
}

void CandidatesContainer::RemoveCandidate(int id) {
	int check = 0;
	for (auto& candidate : _candidates) {
		if (candidate.second->GetId() == id) {
			_candidates.erase(candidate.second->GetRating());
			check++;
			break;
		}
	}
	
	if (!check) {
		cout << "Id not found" << endl << endl;
	}
}