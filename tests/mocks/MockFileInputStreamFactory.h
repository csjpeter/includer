/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include "IFileInputStreamFactory.h"
#include <gmock/gmock.h>

class MockFileInputStreamFactory : public IFileInputStreamFactory
{
	public:

	MOCK_METHOD(std::unique_ptr<IInputStream>, create,
		    (const std::string &), (const, override));
};
