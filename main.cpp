#include <iostream>
#include <fstream>
#include "Environment.h"

int main() {
/*
     std::deque <Recipe> r1_d = {Recipe ("r1",1000),Recipe ("r2",10),
                                      Recipe ("r3",20),Recipe ("r4",500),
                                      Recipe ("r5",150)};

    std::list <Batch> lst_bat = {Batch ("btc1",10,r1_d),Batch ("btc2",5,r1_d),
                                 Batch ("btc3",15,r1_d)};
    std::list <std::reference_wrapper<Batch>> lst_bat_ptr;

    M_flow m1 ("mch1", r1_d, 1);
    r1_d.clear();
    for (auto rcp:r1_d) std::cout<<rcp;
    std::cout<<'\n';
    std::cout<<m1<<'\n';*/


    Environment ev(std::cin);
    std::cout<<ev<<'\n';
    ev.make_events();
    std::cout<<ev;



    return 0;

}