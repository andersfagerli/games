#include "Minesweeper.h"
using namespace std;

Minesweeper::Minesweeper(int width, int height, int mines) {
    this-> width = width;
    this-> height = height;
    this-> mines = mines;
    //lager en-dimensjonal tabell
    list = new Tile[height*width]; //lager en tabell med Tiles som er height*width lang
    for (int i = 0; i < height*width; i++) {
        list[i].open = false;
        list[i].mine = false;
        list[i].flag = false;
    }
    
    //legger miner på tilfeldige posisjoner
    int randomPos;
    for (int i = 0; i < mines;) { //oppdaterer i kun dersom minen ikke eksisterer fra før
        randomPos = rand() % (height*width);
        if (list[randomPos].mine == false) { //sjekker om minen eksisterer i lista
            list[randomPos].mine = true;
            i++;
        }
    }
}

Minesweeper::~Minesweeper() {
    delete[] list;
}

bool Minesweeper::isGameOver() const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (isTileOpen(i,j) && isTileMine(i, j)) {
                return true;
            }
        }
    }
    return false;
}

bool Minesweeper::isTileOpen(int row, int col) const {
    return list[row*width + col].open; //endring
}

bool Minesweeper::isTileMine(int row, int col) const {
    return list[row*width + col].mine; //endring
}

void Minesweeper::openTile(int row, int col) {
    list[row*width + col].open = true; //endring
    
    int L = -1, R = 1, U = -1, D = 1;
    
    if(!isTileMine(row, col) && numAdjacentMines(row, col) == 0) {
        for (int i = row + U; i <= row + D; ++i){
            for (int j = col + L; j <= col + R; ++j){
                if (i < width && i >= 0 && j < height && j >= 0) { //Sjekker om innenfor grensene
                    if (!isTileOpen(i, j)) {
                        openTile(i,j);
                    }
                }
            }
        }
    }

    //Åpner rutene rundt dersom det ikke er miner i dem
    /*if(!isTileMine(row, col) && numAdjacentMines(row, col) == 0) {
        if (row >= 0 && col >= 0 && row < height && col < width) { //Unngår ytterkanter
            for (int i = row-1; i <= row + 1; i++) { //Åpner alle 8 rutene rundt
                for (int j = col-1; j <= col + 1; j++){
                    if (!isTileOpen(i, j)) { //Åpner kun dersom den ikke er åpnet fra før
                        openTile(i, j);
                    }
                }
            }
        }
    }*/
}

int Minesweeper::numAdjacentMines(int row, int col) const {
    int numMines = 0;
    int L = -1, R = 1, U = -1, D = 1;
    
    for (int i = row + U; i <= row + D; ++i){
        for (int j = col + L; j <= col + R; ++j){
           if (i < width && i >= 0 && j < height && j >= 0) { //Sjekker om innenfor grensene
                if (isTileMine(i, j)) {
                    numMines++;
                }
           }
        }
    }
    return numMines;
}

bool Minesweeper::hasWon() {
    numClosed = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!isTileOpen(i, j)) {
                numClosed++;
            }
        }
    }
    
    //cout << numClosed << endl;
    return numClosed == mines;
}

bool Minesweeper::isFlag(int row, int col) const{
    return list[row*width + col].flag; //endring
}

void Minesweeper::setFlag(int row, int col) {
    list[row*width + col].flag = true; //endring
}

void Minesweeper::unsetFlag(int row, int col) {
    list[row*width + col].flag = false; //endring
}

