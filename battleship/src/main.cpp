#include <iostream>
//#include <vector>
#include "cell.h"
#include "player.h"

int main()
{
    std::cout<<"Battleship"<< '\n';

    //Step1
    // for (const auto& cell: cells){
    // }
    // for loop to test cell.h
    // auto cells = std::vector<Cell> {'.', 'C', 'A' , '.'};
    // for (auto i = 0; i <= cells.size()-1; i++){
    //     cells[i+2].was_hit = true;
    //     std::cout << cells[i].display(true) << std::endl;
    // }

    //Step2
    // Player p = Player("Me");
    // Player pc("Computer");
    // p.cell(2,3) = Cell('D');
    // p.cell(2,3).was_hit = true;

    // std::cout << p.cell(2,3).display(true) << std::endl;

    Player p("Test");
    p.cell(3, 4) = Cell('D');
    std::cout << p.cell(3, 4).display(true) << p.cell(4, 3).display(true) << '\n';  // D.
    p.cell(3, 4).was_hit = true;
    std::cout << p.cell(3, 4).display(true) << p.cell(3, 4).display(false) << '\n'; // xD
    p.cell(12, 3);

    return 0;
}
