from conan import ConanFile
#from conan.tools.cmake import CMake, cmake_layout, CMakeToolchain
from conan.tools.build import check_min_cppstd
#from conan.errors import ConanInvalidConfiguration
#import os
from conan.tools.cmake import CMake, CMakeToolchain
#from conan.tools.files import copy, collect_libs

class IncluderConan(ConanFile):
    name = "includer"
    version = "1.0"
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps" #, "CMakeToolchain"
    #generators = "VirtualBuildEnv", "VirtualRunEnv", "CMakeDeps"
    requires = [
            "cxxopts/3.2.0",
    ]
    
    def validate(self):
        check_min_cppstd(self, "17")

#    def layout(self):
#        self.folders.build = "build"
#        self.folders.generators = "build"
#        self.folders.src = "src"

#    def layout(self):
#        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    
    def package(self):
        cmake = CMake(self)
        cmake.install()
    
    #def package_info(self):
    #    self.cpp_info.libs = collect_libs(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = "ON"
        tc.generate()

#    def requirements(self):
#        if self.options.build_tests:
#            self.test_requires("gtest/1.12.1")
#        pass

