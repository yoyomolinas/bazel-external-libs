# Using Bazel with external C++ libraries

Build projects using Bazel and external C++ libraries such as [gflags](https://github.com/gflags/gflags), [glog](https://github.com/google/glog) , [googletest](https://github.com/google/googletest), [opencv](https://github.com/opencv/opencv).

## Building OpenCV with Bazel
OpenCV is not a Bazel library, so we build it differently. Having a portable OpenCV build in your project is possible with Bazel. Using various Bazel tools such as `cmake_external` and `new_git_repository` you can build OpenCV during a Bazel build. 

Include this in your `WORKSPACE` file:
```starlark
# opencv.BUILD file content
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

# include opencv in this project
new_git_repository(
	name = "opencv",
	branch = "master",
	build_file_content = all_content,
	remote = "https://github.com/opencv/opencv",
)

# utilities for building foreign c++ libraries
git_repository(
	name = "rules_foreign_cc",
	branch = "master",
	remote = "https://github.com/bazelbuild/rules_foreign_cc",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()
```

Now navigate to your `BUILD` file in your root folder.
```starlark
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

# Build opencv
cmake_external(
	name = "opencv",
	cmake_options = [
		"-GNinja",
		"-DBUILD_LIST=core,highgui",
	],
	lib_source = "@opencv//:all",
	make_commands = [
		"ninja",
		"ninja install",
	],
	out_include_dir = "include/opencv4",
	shared_libraries = [
		"libopencv_core.dylib",
		"libopencv_core.4.5.dylib",
		"libopencv_highgui.dylib",
		"libopencv_highgui.4.5.dylib",
	],

	visibility = ["//visibility:public"],
)
```

The `BUILD` file outlined above builds the `core` and `highgui` libraries from OpenCV. You can add the libraries you would like to build to `-DBUILD_LIST` argument separated by commas.

This code is tested on macOS. When working with different platforms, you might need to change the `.dylib` extensions to `.so`.
