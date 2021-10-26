#pragma once
#include "BaseContainer.h"

class FlatsContainer : public BaseContainer {
public:
	void SetItem() override;
	void FindItem(double) override;

	void ShowAllFlats() const;
	vector<FlatId> QuickFindItemByArea(FlatArea);
	shared_ptr<Flat> GetFlatById(FlatId) const;

	void AddFlat(shared_ptr<Flat>);
	void RemoveFlat(FlatId);

private:
	vector<shared_ptr<Flat>> _flats;
	map<FlatId, shared_ptr<Flat>> _flatsById;
	map<FlatArea, set<FlatId>> _flatsByArea;
};