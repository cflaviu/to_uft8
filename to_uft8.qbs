import qbs

CppApplication {
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++17"
    cpp.includePaths: [
        "inc",
    ]
    cpp.staticLibraries: [
        "/usr/local/lib/libCatch2Main.a",
        "/usr/local/lib/libCatch2.a",
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
