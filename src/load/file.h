#ifndef SRC_LOAD_FILE_H_
#define SRC_LOAD_FILE_H_

#include <string>

struct file
{
    static std::string read(const char* filename);
};

#endif // !SRC_LOAD_FILE_H_
