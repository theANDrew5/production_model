#include <iostream>
#include <fstream>
#include "Environment.h"

int main()
{

    std::ifstream if_Str ("state.txt");
    Environment ev(if_Str,std::cout);
    std::cout<<ev<<'\n';
    ev.do_step(2);
    //ev.make_events();
    //ev.do_step(2);
    //ev.make_events();
   // ev.do_step(2);
    //std::cout<<ev;



    return 0;

}