workspace(name = "stage4")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

# googletest for testing
git_repository(
    name = "com_google_googletest",
    branch = "master",
    remote = "https://github.com/google/googletest",
)

# gflags for commandline flags
git_repository(
    name = "com_github_gflags_gflags",
    branch = "master",
    remote = "https://github.com/gflags/gflags",
)

# glog for logging
git_repository(
    name = "com_github_google_glog",
    branch = "master",
    remote = "https://github.com/google/glog",
)

# build file content for external libraries
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

# opencv for visual processing
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
