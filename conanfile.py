from conan import ConanFile

class MoxPPRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PremakeDeps"

    def requirements(self):
        self.requires("boost/1.84.0")

    def configure(self):
        self.options["boost"].without_fiber = False
