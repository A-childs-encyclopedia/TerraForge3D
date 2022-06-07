#pragma once
#include "Base/Core/Core.hpp"

#include <glm/gtc/type_ptr.hpp>


namespace TerraForge3D
{

	namespace RendererAPI
	{
		enum ShaderStage
		{
			ShaderStage_Vertex = 0,
			ShaderStage_Geometry,
			ShaderStage_Fragment
		};

		enum ShaderDataType
		{
			ShaderDataType_Mat3 = 0,
			ShaderDataType_Mat4,
			ShaderDataType_Vec2,
			ShaderDataType_Vec3,
			ShaderDataType_Vec4,
			ShaderDataType_IVec2,
			ShaderDataType_IVec3,
			ShaderDataType_IVec4,
			ShaderDataType_Bool
		};

		struct UBOEntry
		{
			std::string name;
			ShaderDataType type;

			UBOEntry(std::string n, ShaderDataType t)
				:name(n), type(t)
			{}
		};

		class Shader
		{
		public:

			Shader() = default;
			virtual ~Shader() = default;

			virtual void Cleanup() = 0;
			virtual bool Compile() = 0;
			virtual bool LoadFromBinary(std::vector<uint32_t> binary) = 0;

			inline bool IsCompiled() { return this->isCompiled; }
			inline std::vector<uint32_t> GetBinary() { if (isCompiled && loadedFromBinary) return binary; TF3D_ASSERT(false, "Shader binary not available");  return std::vector<uint32_t>(); }

			inline Shader* SetIncludeDir(std::string dir) { this->includeDir = dir; if (this->includeDir[this->includeDir.size() - 1] != PATH_SEPERATOR[0]) { this->includeDir += PATH_SEPERATOR; } return this; }
			inline Shader* SetCacheDir(std::string dir) { this->cacheDir = dir; return this; }
			inline Shader* SetMacro(std::string name, std::string value) { this->macros[name] = value; return this; }
			inline Shader* SetUBOLayout(std::vector<UBOEntry> layout) { this->uboLayout = layout; return this; };

			inline Shader* SetSource(std::string& source, ShaderStage stage)
			{
				switch (stage)
				{
				case ShaderStage_Vertex:
					this->vertexSource = source;
					break;
				case ShaderStage_Geometry:
					TF3D_ASSERT(false, "Geometry shaders are not yet suppoted");
					break;
				case ShaderStage_Fragment:
					this->fragmentSource = source;
					break;
				default:
					TF3D_ASSERT(false, "Unknown shader stage!");
				}
				isCompiled = false;
				return this;
			}


		public:
			static Shader* Create();


		protected:
			bool isCompiled = false;
			bool wasCompiled = false;
			bool loadedFromBinary = false;
			std::string vertexSource = "";
			std::string fragmentSource = "";
			std::vector<uint32_t> binary;
			std::string includeDir = "";
			std::string cacheDir = ""; // For SPIRV cache
			std::unordered_map<std::string, std::string> macros;
			std::vector<UBOEntry> uboLayout;

		public:
			std::string name = "Shader";
		};

	}

}