#include "core/core.hpp"

int main()
{
	try
	{
		core::Init();
		
		// ваш код
	}
	catch (...)
	{
		core::Terminate();
		return -1;
	}

	core::Terminate();
	return 0;
}
