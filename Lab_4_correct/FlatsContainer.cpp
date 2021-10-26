#include "FlatsContainer.h"

void FlatsContainer::SetItem() {
	ifstream fin("inputFlats.txt");
	if (!fin.is_open()) {
		throw "No file with flats";
	}
	else {
		int i = 0;
		while (!fin.eof()) {
			FlatId id;
			FlatArea area;
			int numberOfRooms;
			int floor;
			string district;
			fin >> id >> area >> numberOfRooms >> floor >> district;
			shared_ptr<Flat> tmpFlat(make_shared<Flat>(id, area, numberOfRooms, floor, district));
			AddFlat(tmpFlat);
		}
		fin.close();
	}

}

void FlatsContainer::ShowAllFlats() const {
	for (auto it = _flats.begin(); it != _flats.end(); it++) {
		cout << (*it)->ToString();
	}
	cout << endl;
}

void FlatsContainer::FindItem(double area) {

	sort(_flats.begin(), _flats.end(), 
		[](shared_ptr<Flat> flat1, shared_ptr<Flat> flat2)->bool { return flat1->GetArea() < flat2->GetArea(); });

	auto it = _flats.begin();
	int counterF = 0;

	while (it != _flats.end()) {

		it = find_if(it, _flats.end(),
			[&area](shared_ptr<Flat> flat)->bool { return flat->GetArea() >= area * 0.9 && flat->GetArea() <= area * 1.1; });

		if (it == _flats.end() && counterF == 0) {
			cout << "Flats with such an area have not been found" << endl;
		}
		else if(it != _flats.end()) {
			cout << (*it)->ToString();
			counterF++;
			it++;
		}
	}

	cout << endl;
}

void FlatsContainer::AddFlat(shared_ptr<Flat> flat) {
	auto resAdd =_flatsById.emplace(flat->GetId(), flat);//довавить в мап по айди
	if (!resAdd.second) {
		cout << "Such an id exists" << endl << endl;
	}
	_flats.push_back(flat);//добавить в вектор
	_flatsByArea[flat->GetArea()].insert(flat->GetId());//добавить в мап по площади
}


//quick
shared_ptr<Flat> FlatsContainer::GetFlatById(FlatId id) const {
	return (*_flatsById.find(id)).second;//возвращаем квартиру по айди
}

vector<FlatId>  FlatsContainer::QuickFindItemByArea(FlatArea FindArea) {
	vector<FlatId> idByArea;
	auto begIt = _flatsByArea.lower_bound(FindArea * 0.9);//итератор на первый элемент больший или равный заданному значению
	auto endIt = _flatsByArea.lower_bound(FindArea * 1.1);//
	if (begIt != endIt) {
		for (auto areaIt = begIt; areaIt != endIt; areaIt++) {//идем по всем итераторам в отрезке
			auto& flatsOfThisArea = areaIt->second;			//выбираем множество айди, которые принадлежат такой площади
			copy(flatsOfThisArea.begin(), flatsOfThisArea.end(), back_inserter(idByArea));//добавляет все множество в idByArea(вызывает пушбэк для каждого айди в сете)
		}
	}
	return idByArea;
}


void FlatsContainer::RemoveFlat(FlatId id) {
	auto resRem = find_if(_flats.begin(), _flats.end(), [&id](shared_ptr<Flat> flat)->bool { return id == flat->GetId(); });
	if (resRem != _flats.end()) {
		_flatsById.erase((*resRem)->GetId());
		_flatsByArea[(*resRem)->GetArea()].erase((*resRem)->GetId());
		_flats.erase(resRem);
	}
	else {
		cout << "Id not found" << endl << endl;
	}
}