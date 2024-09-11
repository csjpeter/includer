from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.build import check_min_cppstd

class IncluderConan(ConanFile):
    name = "includer"
    version = "1.0"
    license = "BSD-3-Clause"
    author = "Peter Csaszar <csjpeter@gmail.com>"
    url = "http://github.com/csjpeter/includer"
    description = "A project that processes include and frame commands for flexible document content generation."
    topics = ("template", "include", "frame", "document", "content", "generation")
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"
    requires = [
            "gtest/1.12.1",
            "cxxopts/3.2.0",
    ]
    
    def validate(self):
        check_min_cppstd(self, "23")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    
    def package(self):
        cmake = CMake(self)
        cmake.install()

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = "ON"
        tc.generate()

