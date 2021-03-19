#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using namespace std;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line,key,value;
  float TotalMemory =1;
  float FreeMemory =1;
  float UsedMemory = 1;
  ifstream filename(kProcDirectory+kMeminfoFilename);
  if(filename.is_open()){
          // std::replace(line.begin(), line.end(), ' ', '_');

    while(getline(filename,line)){
        replace(line.begin(),line.end(),' ',':');
        istringstream linestream(line);
        while(linestream>>key>>value){
          if(key == 'MemTotal'){
            replace(line.begin(),line.end(),' ',':');
            linestream>>value;
            TotalMemory = std::stof(value);
          }
          else if(key == 'MemFree'){
            replace(line.begin(),line.end(),' ',':');
            linestream>>value;
            FreeMemory = std::stof(value);
            UsedMemory = TotalMemory - FreeMemory;
            return UsedMemory/TotalMemory;
          }
        }
    }
    return 0;
  }
  //  while(linestream>>key>>value1){
  //         if(key == 'MemTotal'){
  //           replace(line.begin(),line.end(),' ',':');
  //           linestream>>line>>key>>value1;
  //         }
  //       }
  //         while(linestream>>key>>value2){
  //          if(key == 'MemFree'){
  //           replace(line.begin(),line.end(),' ',':');
  //           linestream>>line>>key>>value2;
  //         }
  //         }
        
  //         int totalmem;
  //         if(value1>value2){
  //           totalmem = value1 - value2;
  //         }
  //         else{
  //           totalmem = value2-value1;
  //         }
  //         // else if(key == 'MemAvailable'){
  //         //   replace(line.begin(),line.end(),' ',':');
  //         //   linestream>>line>>key>>value;
  //         // }
  //         //  else if(key == 'Buffers'){
  //         //   replace(line.begin(),line.end(),' ',':');
  //         //   linestream>>line>>key>>value;
  //         // }
        
  //   }
  //             return totalmem;

  // }
 }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line,value;
  long systemUpTime = 0;
  ifstream filename(kProcDirectory + kUptimeFilename);
  if(filename.is_open()){
    while(getline(filename,line)){
      istringstream linestream(line);
      while(linestream>>value){
        linestream>>value;
        systemUpTime = stol(value);
        return systemUpTime
      }
    }
  
  }
    return systemUpTime;
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {  
  long jiffies;
  string key;
  string line;string value;
  ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    while(getline(stream,line)){
      istringstream linestream(line);
      while(linestream >>key){
        if(key == "cpu"){
          while(linestream >>value){
            jiffies += stol(value);
          }
          return jiffies;
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {   string line;
        string key;
        string value;
        long activeJiffies = 0;
        std::ifstream stream(kProcDirectory + kStatFilename);
        if (stream.is_open()) {
                std::getline(stream,line);
                std::stringstream linestream(line);
                while (linestream >> key)
                {
                        if (key == "cpu")
                        {
                                for (int i = 0; i < 3; i++)
                                {
                                        linestream >> value;
                                        activeJiffies += stol(value);
                                }
                                return activeJiffies;
                        }
                }
        }
        return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { {
        string line;
        string key;
        string value;
        long idleJiffies = 1;
        std::ifstream stream(kProcDirectory + kStatFilename);
        if (stream.is_open())
        {
                std::getline(stream,line);
                std::istringstream linestream(line);
                while (linestream >> key)
                {
                        if (key == "cpu")
                        {
                                for (int i = 0; i < 3; i++)
                                {
                                        linestream >> value;
                                }
                                //Getting idle 
                                linestream >> value;
                                idleJiffies = stol(value);
                                      linestream >> value;
                                idleJiffies += stol(value);
                                return idleJiffies;
                        }
                }
        }
        return 0;
               }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
         string line;
        string key;
        string value;
        long idleJiffies = 1;
        std::ifstream stream(kProcDirectory + kStatFilename);
        if (stream.is_open())
        {
                std::getline(stream,line);
                std::istringstream linestream(line);
                while (linestream >> key)
                {
                        if (key == "cpu")
                        {
                                for (int i = 0; i < 3; i++)
                                {
                                        linestream >> value;
                                }
                                //Getting idle 
                                linestream >> value;
                                idleJiffies = stol(value);
                                      linestream >> value;
                                idleJiffies += stol(value);
                                return idleJiffies;
                        }
                }
        }
        return 0; }

// TODO: Read and return CPU utilization
// cat /proc/stat
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpuvalues{}
  string line,key;
  string vuser,vsecond,vt,vf,vfi,vs,vse,vei,vni,vten;
  ifstream filename(kProcDirectory+kStatFilename){
    if(filename.is_open()){
      while(getline(filename,line)){
        istringstream linestream(line);
        while(linestream >>key>>vuser>>vsecond>>vt>>vf>>vfi>>vs>>vse>>vei>>vni>>vten){
          cpuvalues.push_back(vuser);
                    cpuvalues.push_back(vsecond);
          cpuvalues.push_back(vt);
          cpuvalues.push_back(vf);
          cpuvalues.push_back(vfi);
          cpuvalues.push_back(vs);
          cpuvalues.push_back(vse);
          cpuvalues.push_back(vei);
          cpuvalues.push_back(vni);
          cpuvalues.push_back(vten);
            return cpuvalues;
        }
      }
    }
    
  }
  
  return {} }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line,key,value;
  ifstream filename(kProcDirectory+kStatFilename);
  if(filename.is_open()){
    while(getline(filename,line)){
      istringstream linestream(line);
      while(linestream>>key>>value){
        if(key == 'process'){
          linestream>>key>>value;
          std::stol(value);
          return value;
        }
      }
    }
  }
  return 0;
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { string line,key,value;
  ifstream filename(kProcDirectory+kStatFilename);
  if(filename.is_open()){
    while(getline(filename,line)){
      istringstream linestream(line);
      while(linestream>>key>>value){
        if(key == 'procs_running'){
          linestream>>key>>value;
          std::stol(value);
          return value;
        }
      }
    }
  }
  return value;
  
  // return 0;
   }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
       string value = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kCmdlineFilename);  
                           if(filestream.is_open()){
while(getline(filestream,value)){
        // std::replace(line.begin(), line.end(), ' ', '_');

istringstream s1(value);
while(s1>>value){
  s1>>value;
}
return value
}
                           }
                           return value;
 }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  
  string line,key,value;
  ifstream filename(kProcDirectory+'/'+to_string(pid)+kStatusFilename);
  if(filename.is_open()){
    while(getline(filename,line)){
      std::replace(line.begin(), line.end(),':'+' ');

      istringstream linestream(line);
      while(linestream>>key>>value){
        if(key == 'VmSize'){
          linestream>>key>>value;
          return value;
        }
      }
    }
  }
  return value;
   }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line,key,value;
  ifstream filename(kProcDirectory+'/'+to_string(pid)+kStatusFilename);
  if(filename.is_open()){
    while(getline(filename,line)){
      std::replace(line.begin(), line.end(),':'+' ');

      istringstream linestream(line);
      while(linestream>>key>>value){
        if(key == 'uid'){
          linestream>>key>>value;
          return value;
        }
      }
    }
  }
  return value;
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid = Uid(pid);
    string line,key,value;

   ifstream filename(kPasswordPath);
  if(filename.is_open()){
    while(getline(filename,line)){
      std::replace(line.begin(), line.end(),':'+ ' ');

      istringstream linestream(line);
      while(linestream>>key>>value){
        if(key == uid){
          linestream>>key>>value;
          return value;
        }
      }
    }
  }
  return value;
 }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line;
  long uptime =0;
  string value;
  ifstream filename(kProcDirectory + "/" + std::to_string(pid) +
                           kStatFilename);
  if(filestream.is_open())
{
  while(getline(filename,line)){
    istringstream linestream(line);
    for(int i=1;i<=kStarttime_;i++){
      linestream>>value;
    }
    if(i == kStarttime_){
      try{   uptime = stol(value)/sysconf(_SC_CLK_TCK);
   return uptime;
      }
      catch (const std::invalid_argument& arg) {
            return 0;
    }
  }
} 
return uptime; }
