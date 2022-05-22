#ifndef PROCESSINFO_H
#define PROCESSINFO_H
#include "parse.h"

#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
#include <termcap.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>

class ProcessInfo{
private:
    char status;
    int pid;
    int threads;
    int memory;
    std::string user;
    std::string process_name;
public:
    ProcessInfo();
    ProcessInfo(int);

    bool empty();

    char get_status() const;
    int get_pid() const;
    int get_mem() const;
    int get_threads() const;
    std::string get_username() const;
    std::string get_name() const;

    char extract_process_status() const;
    int extract_memory() const;
    int extract_threads() const;
    std::string extract_cmdline() const;
    std::string extract_name() const;
    std::string extract_user() const;

    void set_pid(int) const;

    bool operator < (const ProcessInfo&) const;
    void operator = (const ProcessInfo&);
};
#endif
