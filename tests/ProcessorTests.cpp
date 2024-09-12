/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include "MockFileHandler.hpp"
#include "Processor.hpp"

#include <gtest/gtest.h>

TEST(ProcessorTest, TestIncludeProcessing)
{
	MockFileHandler mockHandler;
	mockHandler.addMockFile("templates/file1.txt", "File 1 content");

	Processor   processor(std::make_shared<MockFileHandler>(mockHandler));
	std::string input  = "This is a test @include file1.txt@ end of test.";
	std::string output = processor.process(input, "templates");

	EXPECT_EQ(output, "This is a test File 1 content end of test.");
}

TEST(ProcessorTest, TestFrameProcessing)
{
	MockFileHandler mockHandler;
	mockHandler.addMockFile("templates/frame.txt",
				"Header @content@ Footer");

	Processor   processor(std::make_shared<MockFileHandler>(mockHandler));
	std::string input  = "Content@frame frame.txt@";
	std::string output = processor.process(input, "templates");

	EXPECT_EQ(output, "Header Content Footer");
}

TEST(ProcessorTest, TestNestedFrameIntoInclude)
{
	MockFileHandler mockHandler;
	mockHandler.addMockFile("templates/frame.txt",
				"Header @content@ Footer");
	mockHandler.addMockFile("templates/include.txt",
				"Included @frame frame.txt@Content");

	Processor   processor(std::make_shared<MockFileHandler>(mockHandler));
	std::string input  = "@include include.txt@";
	std::string output = processor.process(input, "templates");

	EXPECT_EQ(output, "Header Included Content Footer");
}

TEST(ProcessorTest, TestNestedIncludeInFrame)
{
	MockFileHandler mockHandler;
	mockHandler.addMockFile("templates/frame.txt",
				"Header @content@@include include.txt@ Footer");
	mockHandler.addMockFile("templates/include.txt",
				"Included @include deeper.txt@");
	mockHandler.addMockFile("templates/deeper.txt", "Deeper Content");

	Processor   processor(std::make_shared<MockFileHandler>(mockHandler));
	std::string input  = "@frame frame.txt@";
	std::string output = processor.process(input, "templates");

	EXPECT_EQ(output, "Header Included Deeper Content Footer");
}
