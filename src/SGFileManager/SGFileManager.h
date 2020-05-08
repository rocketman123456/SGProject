#pragma once
#include "SGIRuntimeModule.h"
#include <string>

namespace SG
{
	enum File_Type
	{
		UNKNOWN = 0,
		TEXT,
		TEXTURE,
		MODEL,
	};

	class SGFileManager : implements SGIRuntimeModule<SGFileManager>
	{
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;

		virtual void Tick() override;
	public:
		bool CheckFileExist(const std::string& filename);

	protected:
		// decide search file in normal file system or in zip file
		bool m_isDeveloping = true; 
	};
}
