#pragma once


struct Cell{

     Cell(char _cell_value = '.') : cell_value(_cell_value) {}; // '.' = water , A C D S M are types of ships

     char cell_value;
     bool was_hit = false;

     bool isEmpty() const  {return cell_value == '.';}
     bool isAlive() const { return !isEmpty() && !was_hit; }
     // bool isAlive() const  {
     //     if(!isEmpty() && !was_hit) //&& instead of and
     //         return true;
     //     else
     //         return false;
     //    }

     // character to print; human = true for my own grid (boats visible)
     char display(bool human) const
     {
         if (isEmpty())                      // water: same for both grids
             return was_hit ? 'x' : '.';

         if (human)                          // my boat
             return was_hit ? 'x' : cell_value;

         return was_hit ? cell_value : '.';  // enemy boat: hidden until hit
     }
     // char display(bool human) const {
     //     if(human){//i am human
     //        if(isEmpty()){
     //             if(was_hit){return 'x';}
     //             else{return '.';}
     //        } else{
     //             if(was_hit){return 'x';}
     //             else{return cell_value;}
     //        }
     //     }else{ //Computer
     //         if(isEmpty()){
     //             if(was_hit){return 'x';}
     //             else{return '.';}
     //         } else{
     //             if(was_hit){return cell_value;}
     //             else{return '.';}
     //         }
     //     }
     // }
 };
