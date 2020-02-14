#include <iostream>
#include "Machine.h"

int main() {
    /*
    std::cout << "Hello, World!" << std::endl;
    Recipe r1("r1",1000);
    Recipe r2("r2",10);
    Recipe r3("r3",20);
    Recipe r4("r4",500);
    Recipe r5("r5",150);
    std::vector <Recipe> r1_vector = {r5,r1,r2,r4,r5};
    Batch b1 ("btc1",10,r1_vector);
    std::vector <Batch> batches = {b1};
    std::vector <Recipe> r2_vector = {r1,r2,r3,r4,r5};
    bool b = true;
    M_flow mch("mh1",batches,r2_vector,b);
    //std::cin>>mch;
    std::cout<<mch;*/
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
    M_flow mch("mh1",v_bat,r1_vector,b);
    std::cout<<mch;
    return 0;

}