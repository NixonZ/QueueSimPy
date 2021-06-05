from setuptools import setup

# Available at setup time due to pyproject.toml
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir

import sys

__version__ = "0.0.1"

# The main interface is through Pybind11Extension.
# * You can add cxx_std=11/14/17, and then build_ext can be removed.
# * You can set include_pybind11=false to add the include directory yourself,
#   say from a submodule.
#

ext_modules = [
    Pybind11Extension("simulationpy",
        ["src/main.cpp","src/station.cpp","src/tandem.cpp","src/queue_graphv2.cpp"],
        # Example: passing in the version to the compiled code
        define_macros = [('VERSION_INFO', __version__)],
        ),
]

setup(
    name="simulationpy",
    version=__version__,
    author="Nalin Shani",
    author_email="nalinshani14@gmail.com",
    url="https://github.com/NixonZ/SimulationPy",
    description="Simulation for delay prediction",
    long_description="Simulation for delay prediction.\n We follow a object oriented approach for creating a general Queueing System and getting simulated wait time data.",
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)