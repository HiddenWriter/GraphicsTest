#include <iostream>

int GenBox(char**& _box, int _num) {
    _box = new char*[_num];
    for(int i = 0; i < (_num * 2) - 1; i++) {
        _box[i] = new char[(_num * 2) - 1];
    }

    for(int i = 0; i < _num; i++) {
        for(int j = 0; j < (_num * 2) - 1; j++) {
            _box[i][j] = ' ';
        }
    }
    return 1;
}

int FreeMem(char**& _box, int _num) {
    for (int i = 0; i < (2 * _num) - 1; i++) {
        _box = nullptr;
        delete[] _box[i];

    }
    _box = nullptr;
    delete[] _box;
    return 1;
}

int GenStar(char**& _box, int _num, int _x, int _y) {
    if (_num == 3 ) {
        _box[_x][_y] = '*';
        _box[_x + 1][_y + 1] = '*';
        _box[_x + 1][_y - 1] = '*';
        for(int i = -2; i < 3; i++) {
            _box[_x + 2][_y + i] = '*';
        }
        return 1;
    }
    else {
        GenStar(_box, _num / 2, _x, _y);
        GenStar(_box, _num / 2, _x + (_num / 2), _y - (_num / 2));
        GenStar(_box, _num / 2, _x + (_num / 2), _y + (_num / 2));
        return 1;
    }
}

int PrintStar(char** _box, int _num) {
    for (int i = 0; i < _num; i++) {
        for (int j = 0; j < (_num * 2) - 1; j++) {
            std::cout << _box[i][j];
        }
        std::cout << '\n';
    }
    return 1;
} 

int main(void) {
    int num = -1;
    std::cin >> num;
    char** box = nullptr;
    GenBox(box, num);
    GenStar(box, num, 0, ((2 * num) - 1) / 2);
    PrintStar(box, num);
    FreeMem(box, num);
    return 0;
}