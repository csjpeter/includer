/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include "IInputStream.h"
#include <memory>

class IFileInputStreamFactory
{
	public:

	virtual std::unique_ptr<IInputStream> create(
			const std::string &filename) const
			= 0;
};
