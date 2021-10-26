#pragma once
#include "BaseContainer.h"

class CandidatesContainer : public BaseContainer {
public:
	void SetItem() override;
	void FindItem(double) override;

	void ShowCandidates();
	void AddCandidate(shared_ptr<Candidate>);
	void RemoveCandidate(int);
private:
	multimap<double, shared_ptr<Candidate>> _candidates;
};