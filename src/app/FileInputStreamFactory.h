/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include "FileInputStream.h"
#include "IFileInputStreamFactory.h"
#include <filesystem>

class FileInputStreamFactory : public IFileInputStreamFactory
{
	public:

	explicit FileInputStreamFactory()
	{
	}

	std::unique_ptr<IInputStream>
	create(const std::filesystem::path &filePath) const override
	{
		return std::make_unique<FileInputStream>(filePath.string());
	}
};
