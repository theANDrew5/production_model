#include <iostream>
#include <fstream>
#include "Environment.h"

int main()
{

    std::ifstream config ("ConfigFile.txt");
    std::ifstream state ("StateFile.txt");
    std::ofstream log("LOG.txt");
    Environment ev(config,state,log);
    ev.do_step_till_end();

    //ev.add_batch(2,1,0);
    //ev.add_batch(1,1,0);
    //ev.add_batch(3,1,0);
    std::cout<<ev<<'\n';
    //ev.make_events();
    //
    //ev.make_events();
   // ev.do_step(2);
    //std::cout<<ev;


    return 0;

}