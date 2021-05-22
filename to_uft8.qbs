import qbs

CppApplication {
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++17"
    cpp.includePaths: [
        "inc",
        "inc_ext",
    ]
    files: [
        "inc/to_utf8/from_utf16.hpp",
        "inc/to_utf8/from_utf32.hpp",
        "test/utf16.cpp",
        "test/utf32.cpp",
    ]

    Group {
        fileTagsFilter: "application"
        qbs.install: false
    }
}
