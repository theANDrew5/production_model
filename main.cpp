#include <iostream>
#include "Machine.h"

int main() {
/*
    Recipe r1("r1",1000);
    Recipe r2("r2",10);
    Recipe r3("r3",20);
    Recipe r4("r4",500);
    Recipe r5("r5",150);
    std::vector <Recipe> r1_vector = {r5,r1,r2,r4,r5};
    Batch b1 ("btc1",10,r1_vector);
    Batch b2 ("btc2",5,r1_vector);
    Batch b3 ("btc3",15,r1_vector);
    std::vector<Batch> v_bat = {b1};
    for(Recipe n:r1_vector) std::cout<<n<<' ';
    std::cout<<'\n';
    for(Batch n:v_bat) std::cout<<n<<' ';
    std::cout<<'\n';
    bool b = true;
    M_flow mch("mh1",v_bat,r1_vector,(std::vector<Event>){},b);
    Machine *p = &mch;
    p->make_event_vector();
    std::cout<<*p;
    M_flow mch2;
    std::cin>>mch2;
    std::cout<<mch2;*/
    std::vector<Batch> v_bat = {};
    //std::vector <Recipe> r1_vector = {};
    while (std::cin.peek()!='/')
    {
        Batch buf;
        std::cin>>buf;
        v_bat.push_back(buf);
    }
    for(Batch n:v_bat) std::cout<<n<<' ';
    return 0;

}