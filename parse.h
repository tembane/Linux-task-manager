#ifndef PARSE_H
#define PARSE_H


#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>

class Parse
{
public:
    Parse();
    static std::string systemExec(const char* cmd);
    static std::string itoa(int);
    static int atoi(std::string);
    static std::string itomem(int);
    static std::string dtoa(double,int);
};


#endif // PARSE_H
