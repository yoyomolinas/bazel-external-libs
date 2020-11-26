load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hello-opencv",
    srcs = ["hello-opencv.cc"],
    deps = [
        "//:opencv",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
    ],
)
