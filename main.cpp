#include <iostream>
#include <fstream>
#include "Environment.h"

int main()
{

    std::ifstream if_Str ("state.txt");
    Environment ev(if_Str,std::cout);
    //ev.add_batch(2,1,0);
    //ev.add_batch(1,1,0);
    //ev.add_batch(3,1,0);
    ev.time_shift(3500);
    std::cout<<ev<<'\n';
    //ev.make_events();
    //ev.do_step(2);
    //ev.make_events();
   // ev.do_step(2);
    //std::cout<<ev;



    return 0;

}