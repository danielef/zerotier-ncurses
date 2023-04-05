load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_github_nlohmann_json",
    sha256 = "1155fd1a83049767360e9a120c43c578145db3204d2b309eba49fbbedd0f4ed3",
    urls = ["https://github.com/nlohmann/json/archive/v3.10.4.tar.gz"],
    strip_prefix = "json-3.10.4",
    build_file = "//third_party:json.BUILD"
)
