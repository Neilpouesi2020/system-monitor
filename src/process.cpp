
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "process.h"

#include "linux_parser.h"
#define _GLIBCXX_USE_CXX11_ABI 0
// using namespace std;
using std::string;
using std::to_string;
using std::vector;

#include "linux_parser.h"

#include "process.h"

using std::string;
using std::to_string;
using std::vector;
void Process::setId(int pid) { pid_ = pid; }
int Process::getRam() const { return ram_; }
void Process::Ram(int ram) { ram_ = ram; }
// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  return LinuxParser::CpuUtilization(Process::Pid());
}

// TODO: Return the command that generated this process
std::string Process::Command() { return LinuxParser::Command(Process::Pid()); }

// TODO: Return this process's memory utilization
std::string Process::Ram() { return LinuxParser::Ram(Process::Pid()); }

// TODO: Return the user (name) that generated this process
std::string Process::User() { return LinuxParser::User(Process::Pid()); }
string Process::Command() { return LinuxParser::Command(Process : Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Process::Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Process::Pid()) / 100; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a ) const {
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  if (this.CpuUtilization() > a.CpuUtilization()) {
    return true;
  } else {
    return false;
  }
}

void Process::setId(int pid) { 
    pid_ = pid; }
int Process::getRam() const {
     return ram_; }
void Process::Ram(int ram) { 
    ram_ = ram; }
