#pragma once

#include <vector>

struct rbo
{
private:
	static std::vector<unsigned int> id;
	static unsigned int SelectID;

public:
	static void bind(unsigned int id);

	static unsigned int create();

	static void Delete(unsigned int id);
	static void DeleteALL();
};

class RBO : private rbo
{

};