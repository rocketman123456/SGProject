#include "SGFileManager.h"
#include "SGJsonLoader.h"
#include "SGTextureLoader.h"

namespace SG
{
	//SG_MEMORYPOOL_DEFINITION(SGFileManager);
	//SG_MEMORYPOOL_AUTOINIT(SGFileManager, 512);
}

int SG::SGFileManager::Initialize()
{
	LOG_INFO("SGFileManager Initialize");
	return 0;
}

void SG::SGFileManager::Finalize()
{
	LOG_INFO("SGFileManager Finalize");
}

void SG::SGFileManager::Tick()
{
}

bool SG::SGFileManager::CheckFileExist(const std::string& filename)
{
	return false;
}

SG::StrongBufferPtr SG::SGFileManager::ReadFileSync(File_Type type, std::string path)
{
	auto iter = m_BufferMap.find(path);
	if (iter != m_BufferMap.end())
	{
		return iter->second;
	} 
	else
	{
		StrongBufferPtr buf = StrongBufferPtr(new FileBuffer);
		buf->type = type;
		switch (type)
		{
		case TEXT: {
			buf->size = 0;
			buf->buffer = nullptr;
		}break;
		case TEXTURE: {
			buf->size = 0;
			buf->buffer = nullptr;
		}break;
		case MODEL: {
			buf->size = 0;
			buf->buffer = nullptr;
		}break;
		case UNKNOWN: {
			buf->size = 0;
			buf->buffer = nullptr;
		}break;
		}
		m_BufferMap[path] = buf;
		return buf;
	}
}
