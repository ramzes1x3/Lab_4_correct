#include "Interactor.h"

void Console::Run() {
	int action = 1;
	int operation = 0;

	while (action) {
		try {
			cout << "1 Operation with flats" << endl;
			cout << "2 Operations with candidates" << endl;
			cout << "0 Exit" << endl;
			cin >> operation;
			cout << endl;

			if (!operation) {
				return;
			}
			else {
				ShowDialogItems(operation);
			}

			cin >> action;
			cout << endl;

			switch (operation) {
			case(1):
				if (action >= _flatsMenuItems.size()) {
					cout << "Action not found" << endl << endl;
					continue;
				}

				for (auto& menuItem : _flatsMenuItems) {
					if (menuItem.GetId() == action) {
						menuItem.dialogFuncObj->operator()(_flatsContainer);
					}
				}
				break;
			case(2):
				if (action >= _candidatesMenuItems.size()) {
					cout << "Action not found" << endl << endl;
					continue;
				}

				for (auto& menuItem : _candidatesMenuItems) {
					if (menuItem.GetId() == action) {
						menuItem.dialogFuncObj->operator()(_candidatesContainer);
					}
				}
				break;
			default:
				break;
			}

		}
		catch (const exception& ex) {
			cerr << ex.what() << endl;
			break;
		}
	}
}

void Console::ShowDialogItems(int opr) {
	if (opr == 1) {
		for (auto& dialogItem : _flatsMenuItems) {
			cout << dialogItem.GetId() << " " << dialogItem.GetInfo() << endl;
		}
	}
	else if (opr == 2) {
		for (auto& dialogItem : _candidatesMenuItems) {
			cout << dialogItem.GetId() << " " << dialogItem.GetInfo() << endl;
		}
	}
	else {
		throw logic_error("Action not found \n");
	}
}