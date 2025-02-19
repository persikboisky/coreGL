#ifndef SRC_CORE_FILE_OBJ_H_
#define SRC_CORE_FILE_OBJ_H_

#include <vector>

namespace obj
{
	void load(std::vector<float> &vert, std::vector<int> &face, std::vector<float>& vert_normal, std::vector<float>& coord_texture, const char* path);
}

#endif //! SRC_CORE_FILE_OBJ_H_