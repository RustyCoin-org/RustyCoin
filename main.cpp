/**
 * @file main.cpp
 * @author JoaoAJMatos (github.com/JoaoAJMatos)
 * @brief 
 * @version 0.1
 * @date 2022-07-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>

#include <net/Endpoint.hpp>

int main(void) 
{
    net::Endpoint ep("127.0.0.1", 80);

    ep.print();

    return 0;
}