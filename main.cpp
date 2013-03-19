/*
 * main.cpp
 *
 *  Created on: 13.06.2012
 *      Author: igor
 *  Программа удаляет ненужные скобки из выражения
 */

#include <iostream>
#include <cstdlib>
#include <exception>
#include "remove_brackets.h"

int
main(int argc, char *argv[]) try 
{
    std::cout << "Введите выражение для разбора :";
    std::string cur_str;
    getline(std::cin, cur_str);
    Remove_brackets r(cur_str);
    std::cout << r.Remove() << std::endl;
    return EXIT_SUCCESS;
}
catch(std::exception& err) 
{
	std::cerr << "Возникло исключение : " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch(...) 
{
    std::cerr << "Неизвестное исключение" << std::endl;
	return EXIT_FAILURE;
}






