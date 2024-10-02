/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include "CliOptions.h"
#include "FileInputStreamFactory.h"
#include "Processor.h"
#include "StdInputStream.h"
#include "StdOutputStream.h"
#include <iostream>

int
main(int argc, char **argv)
{
	CliOptions options(argc, argv);
	if (!options.parse())
	{
		return 1;
	}

	StdInputStream	       inputStream;
	StdOutputStream	       outputStream;
	FileInputStreamFactory fileInputStreamFactory;

	Processor processor(inputStream, outputStream, fileInputStreamFactory,
			    options.getTemplateDir());

	try
	{
		processor.process();
	}
	catch (const std::exception &ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
