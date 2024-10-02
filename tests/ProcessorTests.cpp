/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include "MockFileInputStreamFactory.h"
#include "MockInputStream.h"
#include "MockOutputStream.h"
#include "Processor.h"

#include <gtest/gtest.h>
#include <filesystem>

TEST(ProcessorTest, TestIncludeProcessing)
{
	MockInputStream inputStream(
			"This is a test @include file1.txt@ end of test.");
	MockOutputStream	   outputStream;
	MockFileInputStreamFactory mockFactory;

	// Create a MockInputStream for the included file
	auto			   includedFileStream
			= std::make_unique<MockInputStream>("File 1 content");

	// Set up expectation for the create() method
	EXPECT_CALL(mockFactory, create(std::filesystem::path("templates/file1.txt")))
			.WillOnce(testing::Return(testing::ByMove(
					std::move(includedFileStream))));

	Processor processor(inputStream, outputStream, mockFactory,
			    "templates");

	processor.process();

	EXPECT_EQ(outputStream.getOutput(),
		  "This is a test File 1 content end of test.");
}

TEST(ProcessorTest, TestTemplateProcessing)
{
	MockInputStream	 inputStream("@template_head template.txt@Content");
	MockOutputStream outputStream;
	MockFileInputStreamFactory mockFactory;

	// Create a MockInputStream for the frame file
	auto frameFileStream = std::make_unique<MockInputStream>(
			"Header @split@ Footer");

	// Set up expectation for the create() method
	EXPECT_CALL(mockFactory, create(std::filesystem::path("templates/template.txt")))
			.WillOnce(testing::Return(testing::ByMove(
					std::move(frameFileStream))));

	Processor processor(inputStream, outputStream, mockFactory,
			    "templates");

	processor.process();

	EXPECT_EQ(outputStream.getOutput(), "Header Content Footer");
}

TEST(ProcessorTest, TestNestedTemplateWithTailIntoInclude)
{
	MockInputStream		   inputStream("@include include.txt@");
	MockOutputStream	   outputStream;
	MockFileInputStreamFactory mockFactory;

	// Create MockInputStreams for the included files
	auto includeFileStream = std::make_unique<MockInputStream>(
			"Included @template_head template.txt@Content1@tail@ "
			"Content2");
	auto templateFileStream = std::make_unique<MockInputStream>(
			"Header @split@ Footer");

	// Set up expectations for the create() method calls
	EXPECT_CALL(mockFactory, create(std::filesystem::path("templates/include.txt")))
			.WillOnce(testing::Return(testing::ByMove(
					std::move(includeFileStream))));
	EXPECT_CALL(mockFactory, create(std::filesystem::path("templates/template.txt")))
			.WillOnce(testing::Return(testing::ByMove(
					std::move(templateFileStream))));

	Processor processor(inputStream, outputStream, mockFactory,
			    "templates");

	processor.process();

	EXPECT_EQ(outputStream.getOutput(),
		  "Included Header Content1 Footer Content2");
}

TEST(ProcessorTest, TestNestedTemplateIntoInclude)
{
	MockInputStream		   inputStream("@include include.txt@");
	MockOutputStream	   outputStream;
	MockFileInputStreamFactory mockFactory;

	// Create MockInputStreams for the included files
	auto includeFileStream = std::make_unique<MockInputStream>(
			"Included @template_head template.txt@Content");
	auto templateFileStream = std::make_unique<MockInputStream>(
			"Header @split@ Footer");

	// Set up expectations for the create() method calls
	EXPECT_CALL(mockFactory, create(std::filesystem::path("templates/include.txt")))
			.WillOnce(testing::Return(testing::ByMove(
					std::move(includeFileStream))));
	EXPECT_CALL(mockFactory, create(std::filesystem::path("templates/template.txt")))
			.WillOnce(testing::Return(testing::ByMove(
					std::move(templateFileStream))));

	Processor processor(inputStream, outputStream, mockFactory,
			    "templates");

	processor.process();

	EXPECT_EQ(outputStream.getOutput(), "Included Header Content Footer");
}

TEST(ProcessorTest, TestNestedIncludeInTemplate)
{
	MockInputStream		   inputStream("@template_head template.txt@");
	MockOutputStream	   outputStream;
	MockFileInputStreamFactory mockFactory;

	// Create MockInputStreams for the included files
	auto templateFileStream = std::make_unique<MockInputStream>(
			"Header @split@@include include.txt@ Footer");
	auto includeFileStream = std::make_unique<MockInputStream>(
			"Included @include deeper.txt@");
	auto deeperFileStream
			= std::make_unique<MockInputStream>("Deeper Content");

	// Set up expectations for the create() method calls
	EXPECT_CALL(mockFactory, create(std::filesystem::path("templates/template.txt")))
			.WillOnce(testing::Return(testing::ByMove(
					std::move(templateFileStream))));
	EXPECT_CALL(mockFactory, create(std::filesystem::path("templates/include.txt")))
			.WillOnce(testing::Return(testing::ByMove(
					std::move(includeFileStream))));
	EXPECT_CALL(mockFactory, create(std::filesystem::path("templates/deeper.txt")))
			.WillOnce(testing::Return(testing::ByMove(
					std::move(deeperFileStream))));

	Processor processor(inputStream, outputStream, mockFactory,
			    "templates");

	processor.process();

	EXPECT_EQ(outputStream.getOutput(),
		  "Header Included Deeper Content Footer");
}
