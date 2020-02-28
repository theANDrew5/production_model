#include <iostream>
#include <algorithm>
#include "Machine.h"

int main() {

    std::deque <Recipe> r1_d = {Recipe ("r1",1000),Recipe ("r2",10),
                                      Recipe ("r3",20),Recipe ("r4",500),
                                      Recipe ("r5",150)};

    std::list <Batch> lst_bat = {Batch ("btc1",10,r1_d),Batch ("btc2",5,r1_d),
                                 Batch ("btc3",15,r1_d)};
    std::list <std::reference_wrapper<Batch>> lst_bat_ptr;
    for (Batch & n:lst_bat) lst_bat_ptr.push_back(n);
    //for (Batch & n:lst_bat_ptr) std::cout<<n<<'\t';
    Machine * m_ptr = new M_flow("mch1",lst_bat_ptr,r1_d, true);
    m_ptr->make_event_vector();
    std::cout<<*m_ptr<<'#'<<'\n';
    Machine *m2_ptr = new M_flow();
    std::cin>>*m2_ptr;
    std::cout<<*m2_ptr;
    return 0;

}