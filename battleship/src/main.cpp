#include <iostream>
//#include <vector>
#include "cell.h"
#include "player.h"

void printGrid(Player& p)
{
    std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
    for (int row = 0; row < 10; ++row)
    {
        std::cout << row << ' ';
        for (int col = 0; col < 10; ++col)
            std::cout << p.cell(row, col).display(true) << ' ';
        std::cout << '\n';
    }
}

// count how many cells of each boat letter are on the grid
void countBoats(Player& p)
{
    std::map<char, int> count;
    for (int row = 0; row < 10; ++row)
        for (int col = 0; col < 10; ++col)
            if (!p.cell(row, col).isEmpty())
                count[p.cell(row, col).cell_value]++;

    int total = 0;
    for (const auto& [letter, n] : count)
    {
        std::cout << letter << ':' << n << "  ";
        total += n;
    }
    std::cout << " total:" << total << "  (expected A:5 C:4 D:3 M:2 S:3 total:17)\n";
}

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

    //Player p("Test");
    // p.cell(3, 4) = Cell('D');
    // std::cout << p.cell(3, 4).display(true) << p.cell(4, 3).display(true) << '\n';  // D.
    // p.cell(3, 4).was_hit = true;
    // std::cout << p.cell(3, 4).display(true) << p.cell(3, 4).display(false) << '\n'; // xD
    // p.cell(12, 3);

    //p.assignBoats();

    Player p1("Player", true);
    Player p2("Computer", false);
    //Step 3
    // std::cout << "=== p1 ===\n";
    // printGrid(p1);
    // countBoats(p1);
    // std::cout << "\n=== p2 ===\n";
    // printGrid(p2);
    // countBoats(p2);
    //Step5 : print both hits
    for(int col = 0 ; col < 10 ; col++ ){//hit an entire line
        p2.cell(4, col).was_hit = true;
        p1.cell(4, col).was_hit = true;
    }

    p1.Print(p2);

    return 0;
}
