/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include "IInputStream.h"
#include <filesystem>
#include <memory>

class IFileInputStreamFactory
{
	public:

	virtual std::unique_ptr<IInputStream> create(
			const std::filesystem::path &filePath) const
			= 0;
};
