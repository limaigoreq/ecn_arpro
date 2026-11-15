 #pragma once

#include <iostream>
#include <string>
#include<array>
#include <map>
#include <vector>

#include "cell.h"

class Player{
    //Cell cell_;
    std::string name{"Default"};
    bool human{false};
    std::array<Cell, 100> grid ;
    std::map<char, unsigned int> boats{{'A', 5},{'C',4},{'D',3},{'S',3},{'M',2}};
    std::vector<unsigned int> hist{};
public:
    Player(std::string name_) : name(name_){}

    Player(std::string name_, bool human_) : name(name_) , human(human_){}

    Cell &cell(int row , int col)
    {
        if(row <= 9 && row>=0 && col <= 9 && col >= 0){
            return this->grid[10*row + col];
        }else{
            std::cout<<"Error, this cell does not exist, returning grid[0] or cell(0,0)" <<std::endl;
            return this->grid[0];
        }
    }

    const Cell &cell(int row , int col) const //read only
    {
        if(row <= 9 && row>=0 && col <= 9 && col >= 0){
            return this->grid[10*row + col];
        }else{
            std::cout<<"Error, this cell does not exist, returning grid[0] or cell(0,0)" <<std::endl;
            return this->grid[0];
        }
    }


};
