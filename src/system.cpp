#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include<algorithm>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  vector<Process> foundProcess;
  vector<int> processids = LinuxParser::Pids();
  for(int p:processids){
    Process pro{p};
    foundProcess.push_back(pro);
  } sort(foundProcesses.begin(), foundProcesses.end(),
       [](const Process& pa, const Process& pb) {
         return (pb.CpuUtilization() < pa.CpuUtilization());
       });
  // update list of processes
  processes_ = foundProcesses;

  return processes_;
}
 

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
  return LinuxParser::kernel();
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
  return LinuxParser::MemoryUtilization();
 }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
  return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
  return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
  return LinuxParser::TotalProcesses();
 }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
  return LinuxParser::UpTime();
 }
