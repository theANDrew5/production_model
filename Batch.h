//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_BATCH_H
#define MODEL_BATCH_H

#include <string>
//класс партии
class Batch {
public:
    Batch(std::string name, unsigned int count);
    Batch(const Batch &p);

private:
    std::string _name; //имя партии
    unsigned int _count; //число пластин
};


#endif //MODEL_BATCH_H
