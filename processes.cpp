#include "processes.h"

Processes::Processes() {
    this->set_process_array();
    this->sort_process_array();
}

std::vector<ProcessInfo> Processes::get_process_array(){
   return process_array;
}
Processes::Processes(std::vector<ProcessInfo> vec){
    if(!process_array.empty())
        process_array.clear();
    process_array = vec;
}
void Processes::set_process_array() {
    std::string str;
    int i = 0, pid = 0;
    str = Parse::systemExec("ls /proc");

    while ((str[i] >= '0') && (str[i] <= '9') || (str[i] == '\n')){
        if((str[i]>='0') && (str[i]) <= '9'){
            pid *= 10;
            pid += str[i] - 48;
        }
        if (str[i] == '\n'){
            ProcessInfo processInfo(pid);
            process_array.push_back(processInfo);
            pid = 0;
        }
        i++;
    }
}
void Processes::sort_process_array() {
    std::sort(process_array.begin(), process_array.end());
}
void Processes::sort_process_array_by_name() {
    std::sort(process_array.begin(), process_array.end(),
              [](const ProcessInfo& obj1, const ProcessInfo& obj2){
        if(obj1.get_name() < obj2.get_name())
            return true;
        else
            return false;
    });
}
void Processes::delProcesses(int pid){
    kill(pid, 9);
    process_array.clear();
    set_process_array();
    sort_process_array();
}
void Processes::sort_process_array_by_mem() {
    std::sort(process_array.begin(), process_array.end(),
              [](const ProcessInfo& obj1, const ProcessInfo& obj2){
                  if (obj1.get_mem() > obj2.get_mem())
                      return true;
                  else
                      return false;
    });
}
ProcessInfo Processes::find_process_array_by_pid(int source_pid) {
    std::vector<ProcessInfo>::iterator iterator;
    iterator = std::find_if(process_array.begin(), process_array.end(),
                         [&source_pid](const ProcessInfo& obj1){
        return source_pid == obj1.get_pid();
    });

    if(iterator != process_array.end()){
        auto index = std::distance(process_array.begin(), iterator);
        //process_array[index].output_object();
        return process_array[index];
    } else {
        return ProcessInfo(0);
    }
}
std::vector<ProcessInfo> Processes::find_process_array_by_processname(std::string source_name) {
    std::vector<ProcessInfo>::iterator start_it, end_it;
    this->sort_process_array_by_name();
    start_it = std::find_if(process_array.begin(), process_array.end(),
                            [&source_name](const ProcessInfo& obj1) {
                                return source_name == obj1.get_name();
                            });

    end_it = std::find_if_not(start_it, process_array.end(),
                              [&source_name](const ProcessInfo& obj1) {
                                  return source_name == obj1.get_name();
                              });

    std::vector<ProcessInfo> tmp;
    for (auto i = start_it; i < end_it; ++i){
        //i->output_object();
        tmp.push_back(*i);
    }
    this->sort_process_array();

    return tmp;
}
void Processes::sort_procrss_array_by_thread_numb(){

    std::sort(process_array.begin(), process_array.end(),
              [](const ProcessInfo& obj1, const ProcessInfo& obj2){
                  return obj1.get_threads() > obj2.get_threads();
    });
}
