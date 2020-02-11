//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_ENVIRONMENT_H
#define MODEL_ENVIRONMENT_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Event.h"
#include "Batch.h"
#include "Machine.h"
class Environment {
public:

private:
    std::string name;//имя среды
    std::vector <Event> envents;//вектор событий, по которому происходят шаги
    std::vector <Machine> machines;//вектор машин
    std::ifstream is_state_file;//входной файл состояния, чтобы создать среду
    std::ofstream os_state_file;//выходной файл состояния, чтобы среду сохранить
    std::ofstream log_file;//последовательность ивентов
};


#endif //MODEL_ENVIRONMENT_H
