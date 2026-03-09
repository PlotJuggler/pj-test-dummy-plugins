from conan import ConanFile


class PlotjugglerPluginsConan(ConanFile):
    name = "plotjuggler-plugins"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("gtest/1.14.0")
