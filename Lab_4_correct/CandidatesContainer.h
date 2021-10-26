#pragma once
#include "BaseContainer.h"

class CandidatesContainer : public BaseContainer {
public:

	void SetItem() override;
	void FindItem(double) override;
	void ShowCandidates() const override;
	void AddCandidate(shared_ptr<Candidate>) override;
	void RemoveCandidate(int) override;

private:
	multimap<double, shared_ptr<Candidate>> _candidates;
};