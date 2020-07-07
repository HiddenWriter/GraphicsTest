#include <iostream>

char** BoxInit(int _n) {
    char** box = new char*[_n];
    for(int i = 0; i < _n; i++) {
        box[i] = new char[_n];
    }
    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _n; j++) {
            box[i][j] = ' ';
        }
    }
    return box;
}

void GenStars(char** _a, int _n, int _x, int _y) {
    if(_n < 3) {
        _a[_x][_y] = '*';
        return;
    }
    else {
        for(int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(i == 1 && j == 1);
                else {
                    GenStars(_a, _n/3, _x + i * (_n/3), _y + j * (_n /3));
                }
            }
        }
        return;
    }
}

void PrintStars(char** _a, int _n) {
    for(int i = 0; i < _n; i++) {
        for(int j = 0; j < _n; j++) {
            std::cout << _a[i][j];
        }
        std::cout << '\n';
    }
    return;   
}

int main(void) {
    int num =-1;
    std::cin >> num;
    char** Box = BoxInit(num);
    GenStars(Box, num, 0, 0);
    PrintStars(Box, num);
    return 0;
}