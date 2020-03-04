//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_RECIPE_H
#define MODEL_RECIPE_H

#include <string>
#include <iostream>


class Recipe {
public:
    
	//		Default constructor 
	Recipe();
    
	//		Main Constructor
	Recipe(std::string name, unsigned int time, unsigned int recSetTime = 0);

	//		Copy Constructor
    Recipe(const Recipe &p);

	//		Private Variables setters
	void setName(std::string newName);

	void setTime(unsigned int newTime);

	void setRecSetTime(unsigned int newRecSetTime);


	//		Private Variables getters
    std::string get_name() ;
    
	unsigned int get_time() ;

	unsigned int getRecSetTime();
	


    friend std::istream & operator>> (std::istream & is, Recipe & p);//перегрузка оператора сдвига для потока ввода
    
	friend std::ostream &operator<<(std::ostream & os, Recipe & p);//перегрузка оператора сдвига для вывода
    
	friend bool operator==(Recipe &left, Recipe &right);//перегрузка оператора сравнения
    
	friend bool operator==(const Recipe &left, const Recipe &right);//перегрузка оператора сравнения

private:
    std::string _name; //имя рецепта
    
	unsigned int _time; //константа времени рецепта

	unsigned int recipeSettingTime;
};





#endif //MODEL_RECIPE_H
