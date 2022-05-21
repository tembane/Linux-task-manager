#include "processinfo.h"

ProcessInfo::ProcessInfo() {
    cmdline = "";
    process_name = "";
    user = "";
    threads = 0;
    pid = 0;
}
ProcessInfo::ProcessInfo(int numb) {
    pid = numb;
    user = extract_user();
    memory = extract_memory();
    process_name = extract_name();
    threads = extract_threads();
    cmdline = extract_cmdline();

}

//===============GETERS===================//
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
std::string ProcessInfo::extract_cmdline() const {
    std::string str = "cat /proc/";
    str += Parse::itoa(pid);
    str += "/cmdline 2> /dev/null";
    str = Parse::systemExec(str.c_str());
    if(str.empty())
        return "Cmdline not found";
    return str;
}
std::string ProcessInfo::extract_name() const {
    std::string str = "cat /proc/";
    str += Parse::itoa(pid);
    str += "/comm 2> /dev/null";
    const char * c = str.c_str();
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

void ProcessInfo::output_object() {
    std::cout.setf(std::ios::left);
    std::cout << "pid: " << std::setw(10) << pid
              << "name: " << std::setw(40) << process_name
              << "threads: " << std::setw(5) << threads
              << "memory: " << std::setw(10) << Parse::itomem(memory)
              << "user: " << user
              << std::endl;
}

bool ProcessInfo::operator<(const ProcessInfo &obj) const {
    return  (pid < obj.pid);
}

void ProcessInfo::output_obj_by_name(const std::string& name) const {
    if (name == process_name) {
        std::cout.setf(std::ios::left);
        std::cout << "pid: " << std::setw(10) << pid
                  << "name: " << std::setw(40) << process_name
                  << "threads: " << std::setw(5) << threads
                  << "memory: " << std::setw(10) << Parse::itomem(memory)
                  << "user: " << user
                  << std::endl;
    }
}


