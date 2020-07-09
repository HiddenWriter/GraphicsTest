#include <iostream>

int GenBox(char**& _box, int _num) {
	_box = new char* [_num];
	for (int i = 0; i < (2 * _num) - 1; i++) {
		_box[i] = new char[(2 * _num) - 1];
	}
	for (int i = 0; i < _num; i++) {
		for (int j = 0; j < (2 * _num) - 1; j++) {
			_box[i][j] = ' ';
		}
	}
	return 1;
}

int FreeMem(char**& _box, int _num) {
	for (int i = 0; i < _num; i++) {
		_box[i] = nullptr;
		delete[] _box[i];
	}
	_box = nullptr;
	delete[] _box;
	return 1;
}

int GenLeftStar(char**& _box, int _num, int _x, int _y) {
	if (_num == 1) {
		_box[_x][_y] = '*';
		return 1;
	}
	else {
		_box[_x][_y] = '*';
		GenLeftStar(_box, _num - 1, _x + 1, _y - 1);
	}
	return 1;
}

int GenRightStar(char**& _box, int _num, int _x, int _y) {
	if (_num == 1) {
		_box[_x][_y] = '*';
		return 1;
	}
	else {
		_box[_x][_y] = '*';
		GenRightStar(_box, _num - 1, _x + 1, _y + 1);
	}
	return 1;
}

int PrintStar(char** _box, int _num) {
	for (int i = 0; i < _num; i++) {
		for (int j = 0; j < (2 * _num) - 1; j++) {
			std::cout << _box[i][j];
		}
		std::cout << '\n';
	}
	return 1;
}

int main(void) {
	char** box = nullptr;
	int num = -1;
	std::cin >> num;
	GenBox(box, num);
	GenLeftStar(box, num, 0, (2 * num - 1) / 2);
	GenRightStar(box, num, 0, (2 * num - 1) / 2);
	PrintStar(box, num);
	FreeMem(box, num);
	return 0;
}