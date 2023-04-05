cc_binary(
    name = "foo",
    srcs = ["main.cc"],
    deps = ["@com_github_nlohmann_json//:json"],
    copts = ["-std=c++17"],
)

cc_library(
    name = "session",
    srcs = ["session.cc"],
    hdrs = ["session.hh"],
    copts = ["-std=c++17"],
)
