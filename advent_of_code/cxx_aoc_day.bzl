load("@rules_cc//cc:defs.bzl", "cc_binary")

def define_day(day_number, day_prefix="day_", input_suffix="_input.txt", src_extension=".cc"):

    day_padded = str(day_number)
    if len(day_padded) < 2:
        day_padded = "0" + day_padded
    common_name = "{day_prefix}{day_padded}".format(day_prefix=day_prefix, day_padded=day_padded)
    src_file = "{common_name}{src_extension}".format(common_name=common_name, src_extension=src_extension)
    input_file = "{common_name}{input_suffix}".format(common_name=common_name, input_suffix=input_suffix)

    cc_binary(
        name = common_name,
        srcs = [src_file],
        data = [input_file],
        deps = [
            "@googletest//:gtest_main",
            "@fmt//:fmt",
            "@bazel_tools//tools/cpp/runfiles",
        ],
        copts = [
            "-std=c++23",
            "-O3",
            "-g3",
            "-Wall",
            "-Werror",
            "-fsanitize=address,undefined",
        ],
        linkopts = [
            "-fsanitize=address,undefined",
        ],
    )
