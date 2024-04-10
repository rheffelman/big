#pragma once

class Cell
{
public:

    int getRow() const;
    void setRow(int x);
    
    int getColumn() const;
    void setColumn(int x);

    int getIndex() const;
    void setIndex(int x);

    char getCellType() const;
    void setCellType(char x);

    bool getIsTraversed() const;
    void setIsTraversed(bool x);

    bool getOnPath() const;
    void setOnPath(bool x);

private:

    int row = 0;
    int column = 0;
    int index = 0;
    char cellType = 'F';
    bool isTraversed = false;
    bool onPath = false;

};