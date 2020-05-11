#pragma once
#include "SGIRuntimeModule.h"
#include "SGMemoryMacros.h"
#include "SGLog.h"

#include <string>
#include <memory>
#include <map>

namespace SG
{
	enum File_Type
	{
		UNKNOWN = 0,
		TEXT,
		TEXTURE,
		MODEL,
	};

	struct FileBuffer
	{
		File_Type type = UNKNOWN;
		uint32_t size = 0;
		uint8_t* buffer = nullptr;
	};

	using StrongBufferPtr = std::shared_ptr<FileBuffer>;

	class SGFileManager : implements SGIRuntimeModule<SGFileManager>
	{
		//SG_MEMORYPOOL_DECLARATION(0);
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;

		virtual void Tick() override;
	public:
		bool CheckFileExist(const std::string& filename);
		// TODO: implements sync read file
		StrongBufferPtr ReadFileSync(File_Type type, std::string path);
		// TODO: implements async read file
		StrongBufferPtr ReadFileASync(File_Type type, std::string path) { return StrongBufferPtr(); }

	protected:
		// decide search file in normal file system or in zip file
		bool m_isDeveloping = true;
		std::map<std::string, StrongBufferPtr> m_BufferMap;
	};
}
