#include <iostream>
#include "Machine.h"

int main() {

    Recipe r1("r1",1000);
    Recipe r2("r2",10);
    Recipe r3("r3",20);
    Recipe r4("r4",500);
    Recipe r5("r5",150);
    std::vector <Recipe> r1_vector = {r5,r1};
    Batch b1 ("btc1",10,r1_vector);
    Batch b2 ("btc2",5,r1_vector);
    Batch b3 ("btc3",15,r1_vector);
    std::vector<Batch> v_bat = {b1,b2,b3};
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
    std::cout<<mch2;
    /*std::stringstream buf_stream;
    buf_stream.str(str_buf);

    while (buf_stream.peek()!=-1)
    {
        //buf_stream.unget();
        Batch buf;
        buf_stream>>buf;
        v_bat.push_back(buf);

    }*/

    return 0;

}