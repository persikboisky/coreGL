#ifndef SRC_CORE_FILE_OBJ_H_
#define SRC_CORE_FILE_OBJ_H_

#include <vector>

namespace obj
{
	void load(std::vector<float> &vert, std::vector<int> &face, const char* path);
}

#endif //! SRC_CORE_FILE_OBJ_H_