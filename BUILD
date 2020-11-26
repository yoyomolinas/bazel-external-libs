load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

# Build opencv
cmake_external(
    name = "opencv",
    cmake_options = [
        "-GNinja",
        "-DBUILD_LIST=core,highgui,videoio,imgproc",
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
        "libopencv_videoio.dylib",
        "libopencv_videoio.4.5.dylib",
        "libopencv_imgproc.dylib",
        "libopencv_imgproc.4.5.dylib",
    ],
    visibility = ["//visibility:public"],
)
