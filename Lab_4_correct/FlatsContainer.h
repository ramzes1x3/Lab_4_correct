#pragma once
#include "BaseContainer.h"

class FlatsContainer : public BaseContainer {
public:

	void SetItem() override;
	void FindItem(double) override;
	void ShowAllFlats() const override;
	vector<FlatId> QuickFindItemByArea(FlatArea) override;
	shared_ptr<Flat> GetFlatById(FlatId) const override;
	void AddFlat(shared_ptr<Flat>) override;
	void RemoveFlat(FlatId) override;

private:

	vector<shared_ptr<Flat>> _flats;
	map<FlatId, shared_ptr<Flat>> _flatsById;
	map<FlatArea, set<FlatId>> _flatsByArea;
};