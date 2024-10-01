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

	explicit FileInputStreamFactory(std::string templateDir)
			: templateDir(std::move(templateDir))
	{
	}

	std::unique_ptr<IInputStream>
	create(const std::string &filename) const override
	{
		std::filesystem::path filePath
				= std::filesystem::path(templateDir);
		return std::make_unique<FileInputStream>(filePath.string());
	}

	private:

	std::string templateDir;
};
