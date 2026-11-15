 #pragma once

#include <iostream>
#include <string>
#include<array>
#include <map>
#include <vector>
#include <random>

#include "cell.h"

class Player{
    //Cell cell_;
    std::string name{"Default"};
    bool human{false};
    std::array<Cell, 100> grid ;
    std::map<char, unsigned int> boats{{'A', 5},{'C',4},{'D',3},{'S',3},{'M',2}};
    std::vector<unsigned int> hist{};
public:
    Player(std::string name_, bool human_) : name(name_) , human(human_){assignBoats();}

    void assignBoats()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        for (const auto& boat : boats)
        {
            std::uniform_int_distribution<int>distrib(0,9);
            std::uniform_int_distribution<int>distribDir(0,1);
            int randomRow=0;
            int randomCol=0;
            int randomDir=0;
            bool superposeBoats = false;
            bool outboundBoats = false;
            do{
                randomRow=distrib(gen);
                randomCol=distrib(gen);
                randomDir=distribDir(gen);
                superposeBoats = false;
                outboundBoats = false;
                if(!(randomRow + (boat.second-1)*randomDir > 9 || randomCol +(boat.second-1)*(1 - randomDir) >9)){
                    for(int j = 0 ; j<boat.second ; j++)
                    {
                        if (this->cell(randomRow + j*randomDir, randomCol +j*(1 - randomDir)).isEmpty()){superposeBoats = false;}
                        else{superposeBoats = true; break;}
                        //this->cell(randomRow + j*randomDir, randomCol +j*(1 - randomDir)).isEmpty() ? false : superposeBoats = true; break; // not working
                    }
                } else {outboundBoats = true;}
            }while (outboundBoats || superposeBoats ); //while superpose //not empty

            for(int j = 0 ; j<boat.second ; j++)
            {
                this->cell(randomRow + j*randomDir, randomCol +j*(1 - randomDir)) = boat.first;
            }
        }
    }

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
