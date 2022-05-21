#include "parse.h"

Parse::Parse() {}

std::string Parse::systemExec(const char *cmd) {
    std::array<char, 128> buf;
    std::string res;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if(!pipe) throw std::runtime_error("popen() failed");
    while (!feof(pipe.get())){
        if(fgets(buf.data(), 128, pipe.get()) != nullptr)
            res += buf.data();
    }
    return res;
}
int Parse::atoi(std::string str) {
    int num = 0;
    for(int i = 0; i < str.size() ; i++){
        if(str[i] == '\n') return num;
        num *= 10;
        num += str[i] - 48;
    }
    return num;
}
std::string Parse::itoa(int num){
    std::string str;
    int div = 1;
    while(num/div > 9) div *= 10;
    while(div != 0) {
        str += (num/div) + 48;
        num %= div;
        div /= 10;
    }
    return str;
}
std:: string Parse::dtoa(double dnum, int number_of_characters){
    int num = dnum, afterdot;
    dnum -= num;
    std::string str;
    str = itoa(num);
    if(number_of_characters > 0) {
        str += ".";
        for(int i = 0; i < number_of_characters; i++) {
            dnum *= 10;
            afterdot = dnum + 48;
            num = dnum;
            dnum -= num;
            str += afterdot;
        }
    }
    return str;
}
std::string Parse::itomem(int num) {
    double dnum = num;
    int number_of_characters_after_dot = 0;
    std::string str,measurment = " Kb";

    if(dnum < 0) return "Incorrect memory";
    if(dnum > 1024) { dnum /= 1024; number_of_characters_after_dot++; measurment = " Mb"; }
    if(dnum > 1024) { dnum /= 1024; number_of_characters_after_dot++; measurment = " Gb"; }

    str += dtoa(dnum,number_of_characters_after_dot);

    str += measurment;
    return str;
}
