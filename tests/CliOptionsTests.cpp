/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include "CliOptions.h"

#include <gtest/gtest.h>

TEST(CliOptionsTest, TestValidTemplateDir)
{
	const char *argv[] = {"program", "--template", "templates"};
	int	    argc   = 3;

	CliOptions  options(argc, (char **)argv);
	bool	    success = options.parse();

	EXPECT_TRUE(success);
	EXPECT_EQ(options.getTemplateDir(), "templates");
	EXPECT_FALSE(options.shouldShowHelp());
}

TEST(CliOptionsTest, TestHelpOption)
{
	const char *argv[] = {"program", "--help"};
	int	    argc   = 2;

	CliOptions  options(argc, (char **)argv);
	bool	    success = options.parse();

	EXPECT_FALSE(success);
	EXPECT_TRUE(options.shouldShowHelp());
}

TEST(CliOptionsTest, TestMissingTemplateDir)
{
	const char *argv[] = {"program"};
	int	    argc   = 1;

	CliOptions  options(argc, (char **)argv);
	bool	    success = options.parse();

	EXPECT_FALSE(success);
	EXPECT_EQ(options.getTemplateDir(), "");
}
