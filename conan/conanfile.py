from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import check_min_cppstd
from conan.tools.files import get, copy
from conan.tools.cmake import cmake_layout, CMakeToolchain, CMake, CMakeDeps

from os.path import join


class Base64pp(ConanFile):

    settings = ("os", "compiler", "build_type", "arch")

    def source(self):
        get(self, "https://github.com/matheusgomes28/base64pp/archive/refs/tags/v0.1.0-rc0.zip", strip_root=True)

    def layout(self):
        self.folders.source = "src"
        self.folders.build = "build"

        self.cpp.source.includedirs = ["include"]
        self.cpp.build.libdirs = ["lib"]
        self.cpp.build.libs = ["base64pp"]

        cmake_layout(self, src_folder="src", build_folder="build")

    def configure(self):
        print(dir(self.settings))
        self.settings.compiler.cppstd = 20

    def validate(self):
        check_min_cppstd(self, 20, False)

        compiler = self.settings.get_safe("compiler", "unknown")
        compiler_version_major = self.settings.get_safe("compiler.version", "0")
        required_versions = {
            "gcc": 10,
            "clang": 12,
            "msvc": 191
        }
        
        if compiler not in required_versions.keys():
            raise ConanInvalidConfiguration(f"compiler not supported by Base64pp")

        if int(compiler_version_major) < required_versions[compiler]:
            raise ConanInvalidConfiguration(f"you have {compiler} {compiler_version_major}, need {compiler} >= {required_versions[compiler]}")


    def generate(self):

        tc = CMakeToolchain(self)
        tc.generate()
        CMakeDeps(self).generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    
    def package(self):
        cmake = CMake(self)
        cmake.install()
        
    def package_info(self):
        self.cpp_info.libs = ["base64pp"]
        self.cpp_info.libdirs = ["lib"]
        self.cpp_info.includedirs = ["include"]
