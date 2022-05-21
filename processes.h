#ifndef PROCESSES_H
#define PROCESSES_H


#include "algorithm"
#include "processinfo.h"

class Processes{
private:
    std::vector<ProcessInfo> process_array;
public:
    Processes();
    Processes(std::vector<ProcessInfo>);
    std::vector<ProcessInfo> get_process_array();

    void set_process_array();
    void output_process_array();
    void output_process_array_by_name();
    void sort_process_array();
    void sort_process_array_by_name();
    void sort_procrss_array_by_thread_numb();
    void delProcesses();
    void sort_process_array_by_mem();
    void find_process_array_by_pid(int);
    std::vector<ProcessInfo> find_process_array_by_processname(std::string);
};
#endif // PROCESSES_H
