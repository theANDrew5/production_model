#include <iostream>
#include <fstream>
#include "Environment.h"

int main()
{

    std::ifstream config ("ConfigFile.txt");
    std::ifstream state ("StateFile.txt");
    std::ofstream of_Str("SaveState.txt");
    Environment ev(config,state);
    //ev.add_batch(2,1,0);
    //ev.add_batch(1,1,0);
    //ev.add_batch(3,1,0);
    std::cout<<ev<<'\n';
    //ev.make_events();
    //ev.do_step(2);
    //ev.make_events();
   // ev.do_step(2);
    //std::cout<<ev;


    return 0;

}