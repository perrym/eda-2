// util.h -- May 9, 2009
//    by geohot
// part of "The Embedded Disassembler"
//  released under GPLv3, see http://gplv3.fsf.org/

#ifndef EDA_UTIL_H_
#define EDA_UTIL_H_

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace eda {

const std::string XMLHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
const std::string DataDirectory = "..\eda-2\Data\";

// Returns things like 9 and 0x4F
std::string immed(uint32_t data);
// Signed
std::string immed_signed(int32_t data);

uint32_t stoi(const std::string& num);

bool file_to_string(const std::string& filename, std::string* out);

int find_matching(const std::string& s, int start, char open, char close);

void SerializeToXML(std::ostringstream& out, const std::vector<int>* v, std::string name, std::string item);

void StringSplit(const char* a, const std::string& in, std::vector<std::string>* argv);

// LOG(INFO)
// LOG(ERROR)

#ifdef WIN32
#define THIS_FILE ((strrchr(__FILE__, 0x5C) ?: __FILE__ - 1) + 1)
#else
#define THIS_FILE ((strrchr(__FILE__, '/') ?: __FILE__ - 1) + 1)
#endif

//#define LOG std::cout << std::endl << std::hex << THIS_FILE << "--" << __PRETTY_FUNCTION__ << ": "
//#define LOG std::cout << std::dec << THIS_FILE << "--" << __PRETTY_FUNCTION__ << ": "
//#define LOG std::cout << std::dec << THIS_FILE << "--" << __FUNCTION__  << ": "
//#define INFO std::cout << std::dec << THIS_FILE << ": "

#define LOG(x) Logging(x, THIS_FILE, __PRETTY_FUNCTION__, __FUNCTION__, __LINE__).stream()

#define INFO 0
#define WARNING 1
#define ERROR 2

class Logging {
public:
  Logging(int level, const char* file, const char* pretty_function, const char* function, int line_number);
  ~Logging() {
    // Is the .str needed?
    std::cout << stream_.str() << std::endl;
  }
  std::ostream& stream() { return stream_; }
private:
  std::ostringstream stream_;
};

//inline uint32_t rol(uint32_t data, int len);
#define rol(data, len) ((data << len) | (data >> (32-len)))
//inline uint32_t ror(uint32_t data, int len);
#define ror(data, len) ((data >> len) | (data << (32-len)))

}

#endif
