#include <core/core.hpp>

int main()
{
	try
	{
		core::Init();
	}
	catch (...)
	{
		core::Terminate();
		return -1;
	}

	core::Terminate();
	return 0;
}