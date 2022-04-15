#pragma once

#include <string>

// Disable assertions for Rlease Builds
#ifdef TF3D_DEBUG
#define TF3D_ASSERT(x, message) TerraForge3D::Assert(x, message, __FILE__, std::to_string(__LINE__), __PRETTY_FUNCTION__);
#else
#define TF3D_ASSERT(x, message)
#endif

#ifdef TF3D_DEBUG
namespace TerraForge3D
{
	/*
	* This fuunction will print the assertion to the logs as well as create a debugbreak
	* 
	* @param condition : the condition
	* @param messsage  : the message to be logged
	*/
	void Assert(bool condition, std::string message, std::string file, std::string line, std::string function);
}
#endif
