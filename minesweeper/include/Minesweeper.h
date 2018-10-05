#pragma once
#include <cstdlib>
#include <vector>
#include <iostream>

struct Tile {
    bool open;
    bool mine;
    bool flag;
};

class Minesweeper {
private:
    // Legg til de medlemsvariablene og hjelpefunksjonene du trenger
    Tile* list;
    int mines;
    int height;
    int width;
    int numClosed;

public:
    Minesweeper(int width, int height, int mines);
    ~Minesweeper();

    bool isGameOver() const;

    bool isTileOpen(int row, int col) const;
    bool isTileMine(int row, int col) const;

    void openTile(int row, int col);

    int numAdjacentMines(int row, int col) const;
    
    bool hasWon();
    
    bool isFlag(int row, int col) const;
    void setFlag(int row, int col);
    void unsetFlag(int row, int col);

    //Slår av autogenerert kopikonstruktør og tilordningsoperator for å unngå feil
    Minesweeper(const Minesweeper &) = delete;
    Minesweeper &operator=(const Minesweeper &) = delete;
};

