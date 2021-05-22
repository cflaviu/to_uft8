#include "to_utf8/from_utf16.hpp"
#include <catch2/catch_all.hpp>
#include <iostream>

namespace to_utf8
{
    TEST_CASE("Convert UTF16 to ASCII char", "[from_utf16]")
    {
        using string = std::array<char, 2>;
        string text;
        auto p = from_utf16('c', text.begin());
        REQUIRE(std::distance(text.begin(), p) == 1);
        REQUIRE(text[0] == 'c');
    }

    TEST_CASE("Convert UTF16 to 2 byte UTF8", "[from_utf16]")
    {
        using string = std::array<unsigned char, 3>;
        string text = {};
        auto p = from_utf16(L'ș', text.begin());
        std::cout << (const char*) text.data() << '\n';
        REQUIRE(std::distance(text.begin(), p) == 2);
        REQUIRE(text[0] == 200u);
        REQUIRE(text[1] == 153u);
    }

    TEST_CASE("Convert UTF16 < 2947 to 3 byte UTF8", "[from_utf16]")
    {
        using string = std::array<unsigned char, 4>;
        string text = {};
        auto p = from_utf16(L'Ḉ', text.begin());
        std::cout << (const char*) text.data() << '\n';
        REQUIRE(std::distance(text.begin(), p) == 3);
        REQUIRE(text[0] == 0xE1);
        REQUIRE(text[1] == 0xB8);
        REQUIRE(text[2] == 0x88);
    }

    TEST_CASE("Convert UTF16 > 2047 to 3 byte UTF8", "[from_utf32]")
    {
        using string = std::array<unsigned char, 4>;
        string text = {};
        auto p = from_utf16(L'中', text.begin());
        std::cout << (const char*) text.data() << '\n';
        REQUIRE(std::distance(text.begin(), p) == 3);
        REQUIRE(text[0] == 0xE4);
        REQUIRE(text[1] == 0xB8);
        REQUIRE(text[2] == 0xAD);
    }
}
