cc_binary(
    name = "foo",
    srcs = ["main.cc"],
    deps = [":session", ":ux", "@com_github_nlohmann_json//:json"],
    copts = ["-std=c++17"],
)

cc_library(
    name = "net",
    srcs = ["net.cc"],
    hdrs = ["net.hh"],
    copts = ["-std=c++17"],
    linkopts = ["-lcurl"],
)

cc_library(
    name = "session",
    srcs = ["session.cc"],
    hdrs = ["session.hh"],
    copts = ["-std=c++17"],
    deps = ["@com_github_nlohmann_json//:json"],
)

cc_library(
    name = "ux",
    srcs = ["ux.cc"],
    hdrs = ["ux.hh"],
    copts = ["-std=c++17"],
    linkopts = ["-lncurses"],
)