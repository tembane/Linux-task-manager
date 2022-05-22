#include "processinfo.h"

ProcessInfo::ProcessInfo() {
    process_name = "";
    user = "";
    threads = 0;
    pid = 0;
    status = '-';
    memory = 0;
}
ProcessInfo::ProcessInfo(int numb) {
    pid = numb;
    status = extract_process_status();
    user = extract_user();
    memory = extract_memory();
    process_name = extract_name();
    threads = extract_threads();
}

bool ProcessInfo::empty(){
    return pid == 0;
}

//===============GETERS===================//
char ProcessInfo::get_status() const{
    return status;
}

int ProcessInfo::get_pid() const {
    return pid;
}
int ProcessInfo::get_mem() const {
    return memory;
}
int ProcessInfo::get_threads() const {
    return threads;
}
std::string ProcessInfo::get_name() const {
    return process_name;
}
std::string ProcessInfo::get_username() const {
    return user;
}


//==============EXTRACTS===================//

char ProcessInfo::extract_process_status() const{
    std::string str = "cat /proc/";
    str+= Parse::itoa(pid);
    str+="/status | grep State";
    str = Parse::systemExec(str.c_str());
    if(str.empty())
        return '-';
    return str[7];
}

int ProcessInfo::extract_threads() const {
    int i = 9;
    std::string str = "cat /proc/", numbOfThreads;
    str += Parse::itoa(pid);
    str += "/status 2> /dev/null | grep Threads";
    const char * c = str.c_str();
    str = Parse::systemExec(c);
    if (str.empty())
        return 0;
    while (str[i] != '\n'){
        if((str[i] != ' ')){
            numbOfThreads += str[i];
        }
        i++;
    }
    return Parse::atoi(numbOfThreads);
}
int ProcessInfo::extract_memory() const {
    int i = 9;
    std::string str = "cat /proc/", mem;
    str += Parse::itoa(pid);
    str += "/status 2> /dev/null | grep RssAnon";
    str = Parse::systemExec(str.c_str());
    if(str.empty())
        return 0;

    while(str[i] != 'k' && str[i] != '\n') {
        if((str[i] != ' ')) {
            mem += str[i];
        }
        i++;
    }
    return Parse::atoi(mem);
}
std::string ProcessInfo::extract_name() const {
    std::string str = "cat /proc/";
    str += Parse::itoa(pid);
    str += "/comm 2> /dev/null";
    str = Parse::systemExec(str.c_str());
    if(!str.empty())
        str.resize(str.size() - 1);
    else
        return "Unnamed";
    return str;
}
std::string ProcessInfo::extract_user() const {
    std::string str = "id -nu 2> /dev/null </proc/";
    str += Parse::itoa(pid);
    str += "/loginuid";
    const char * c = str.c_str();
    str = Parse::systemExec(c);
    if (!str.empty())
        str.resize(str.size() - 1);
    else
        return "Unknown";
    return str;
}

bool ProcessInfo::operator<(const ProcessInfo &obj) const {
    return  (pid < obj.pid);
}

void ProcessInfo::operator=(const ProcessInfo& obj){
    this->pid = obj.pid;
    this->process_name = obj.process_name;
    this->status = obj.status;
    this->threads = obj.threads;
    this->user = obj.user;
    this->memory = obj.memory;
}
