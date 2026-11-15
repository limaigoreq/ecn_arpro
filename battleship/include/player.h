 #pragma once

#include <iostream>
#include <string>
#include<array>
#include <map>
#include <vector>
#include <random>
#include <sstream>
#include <algorithm>

#include "cell.h"

class Player{
    //Cell cell_;
    std::string name{"Default"};
    bool human{true};
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

    std::string PrintRow(int row) const
    {
        std::stringstream printedRow;
        printedRow << row << " ";
        for(int col = 0 ; col<=9 ; col++)
        {
            printedRow << this->cell(row, col).display(this->human) <<" ";
        }
        return printedRow.str();
    }

    void Print (const Player& other)
    {

        std::cout <<"G 0 1 2 3 4 5 6 7 8 9 "<< "     |    " << "G 0 1 2 3 4 5 6 7 8 9 " << std::endl;
        for(int row = 0 ; row <= 9 ; row++)
        {
            std::cout <<this->PrintRow(row) << "     |    " << other.PrintRow(row) << std::endl;
        }
    }

    // computer: random cell never targeted before (uses hist)
    void ComputerRandomInput(int& row, int& col)
    {
        std::uniform_int_distribution<int> distrib(0, 9);
        std::random_device rd;
        std::mt19937 gen(rd());
        do
        {
            row = distrib(gen);
            col = distrib(gen);
        } while (std::find(hist.begin(), hist.end(), 10 * row + col) != hist.end());

        hist.push_back(10 * row + col);
    }

    // human: read two numbers between 0 and 9
    void HumanInput(int& row, int& col)
    {
        while (true)
        {
            std::cout << name << ", enter target as: row col (e.g. 3 7): ";
            if (std::cin >> row >> col && row >= 0 && row <= 9 && col >= 0 && col <= 9)
                return;
            if (std::cin.eof())                 // Ctrl+D: quit
                std::exit(0);
            std::cout << "Please type two numbers between 0 and 9.\n";
            std::cin.clear();                   // reset cin after bad input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // drop the bad line
        }
    }

    // returns true if 'other' has no boat left (game over)
    bool Shoot(Player& other)
    {
        int row = 0;
        int col = 0;

        if (human)
            HumanInput(row, col);
        else
            ComputerRandomInput(row, col);

        std::cout << name << " fires at (" << row << ", " << col << "): ";

        Cell& otherCell = other.cell(row, col);   // reference: we modify the real cell

        if (otherCell.was_hit)                    // 1. already shot (water OR boat)
        {
            std::cout << "Already shot there!\n";
            return false;
        }

        otherCell.was_hit = true;

        if (otherCell.isEmpty())                  // 2. water
        {
            std::cout << "Miss!\n";
        }
        else                                      // 3. a boat piece, hit for the first time
        {
            unsigned int& alive = other.boats[otherCell.cell_value];
            alive--;
            if (alive == 0)
                std::cout << "Sank a " << otherCell.cell_value << "!\n";
            else
                std::cout << "Hit a " << otherCell.cell_value << "!\n";
        }

        // game over if no boat piece is left
        unsigned int total = 0;
        for (const auto& boat : other.boats)
            total += boat.second;
        return total == 0;
    }

    void wins() const { std::cout << name << " wins!\n"; }


};
