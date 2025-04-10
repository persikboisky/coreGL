#pragma once

#include <vector>

struct fbo
{
private:
	static std::vector<unsigned int> id;

public:
	static unsigned int create();
	static void Delete(unsigned int id);
	static void DeleteALL();
};