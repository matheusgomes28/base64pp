#include <array>
#include <base64pp/base64pp.h>
#include <cstdint>
#include <gtest/gtest.h>
#include <string>

// NOLINTNEXTLINE
TEST(Base64Encode, EncodesEmpty)
{
    std::string const expected{};
    std::string const actual{base64pp::encode({})};
    ASSERT_EQ(expected, actual);
}

// NOLINTNEXTLINE
TEST(Base64Encode, EncodesThreeBytesZeros)
{
    std::array<std::uint8_t, 3> const input{0x00, 0x00, 0x00};
    auto const expected{"AAAA"};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(expected, actual);
}

// NOLINTNEXTLINE
TEST(Base64Encode, EncodesThreeBytesRandom)
{
    std::array<std::uint8_t, 3> const input{0xFE, 0xE9, 0x72};
    auto const expected{"/uly"};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(expected, actual);
}

// NOLINTNEXTLINE
TEST(Base64Encode, EncodesTwoBytes)
{
    std::array<std::uint8_t, 2> const input{0x00, 0x00};
    auto const expected{"AAA="};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(expected, actual);
}

// NOLINTNEXTLINE
TEST(Base64Encode, EncodesOneByte)
{
    std::array<std::uint8_t, 1> const input{0x00};
    auto const expected{"AA=="};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(expected, actual);
}

// NOLINTNEXTLINE
TEST(Base64Encode, EncodesFourBytes)
{
    std::array<std::uint8_t, 4> const input{0x74, 0x68, 0x65, 0x20};
    auto const expected{"dGhlIA=="};
    auto actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(expected, actual);
}

// NOLINTNEXTLINE
TEST(Base64Encode, EncodesFiveBytes)
{
    std::array<std::uint8_t, 5> const input{0x20, 0x62, 0x72, 0x6f, 0x77};
    auto const expected{"IGJyb3c="};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Encode, EncodesSixBytes)
{
    std::array<std::uint8_t, 6> const input{0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73};
    auto const expected{"IGp1bXBz"};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Encode, EncodesBrownFox)
{
    std::array<std::uint8_t, 43> const input{0x74, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6b, 0x20, 0x62, 0x72,
        0x6f, 0x77, 0x6e, 0x20, 0x66, 0x6f, 0x78, 0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73, 0x20, 0x6f, 0x76, 0x65, 0x72,
        0x20, 0x74, 0x68, 0x65, 0x20, 0x6c, 0x61, 0x7a, 0x79, 0x20, 0x64, 0x6f, 0x67};

    auto const expected{"dGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw=="};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Encode, EncodesBrownFastFoxNullInMiddle)
{
    std::array<std::uint8_t, 45> const input{0x74, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6b, 0x21, 0x20, 0x62,
        0x72, 0x6f, 0x77, 0x6e, 0x20, 0x66, 0x6f, 0x78, 0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73, 0x20, 0x6f, 0x76, 0x65,
        0x72, 0x20, 0x74, 0x68, 0x65, 0x00, 0x20, 0x6c, 0x61, 0x7a, 0x79, 0x20, 0x64, 0x6f, 0x67};

    auto const expected{"dGhlIHF1aWNrISBicm93biBmb3gganVtcHMgb3ZlciB0aGUAIGxhenkgZG9n"};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Decode, FailDecodeOneString)
{
    std::string const input{"1"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

// NOLINTNEXTLINE
TEST(Base64Decode, FailDecodeOneStringPadded)
{
    std::string const input{"1==="};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

// NOLINTNEXTLINE
TEST(Base64Decode, FailDecodeOneCharRemaining)
{
    std::string const input{"something"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

// NOLINTNEXTLINE
TEST(Base64Decode, FailDecodeNonSize4Bigger)
{
    std::string const input{"SomethingEntirelyDifferent"};
    auto const actual{base64pp::decode(input)};
    std::vector<std::uint8_t> const expected{0x4A, 0x89, 0x9E, 0xB6, 0x18, 0xA7, 0x80, 0x49, 0xED, 0x8A, 0xB7, 0xA5,
        0xC8, 0x38, 0x9F, 0x7D, 0xEA, 0xDE, 0x9E};

    ASSERT_TRUE(actual);
    ASSERT_EQ(*actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Decode, FailDecodeNonBase64Short)
{
    std::string const input{"a aa"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

// NOLINTNEXTLINE
TEST(Base64Decode, FailDecodeNonBase64Longer)
{
    std::string const input{"aaa`aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

// NOLINTNEXTLINE
TEST(Base64Decode, DecodesMissingTwoPads0)
{
    std::string const input{"12"};
    auto const actual{base64pp::decode(input)};
    std::vector<std::uint8_t> const expected{0xD7};

    ASSERT_TRUE(actual);
    ASSERT_EQ(*actual, expected);
}


// NOLINTNEXTLINE
TEST(Base64Decode, DecodesMissingTwoPads1)
{
    std::string const input = "AA";
    auto const actual{base64pp::decode(input)};
    std::vector<std::uint8_t> const expected{0x00};

    ASSERT_TRUE(actual);
    ASSERT_EQ(*actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Decode, DecodesMissingOnePad0)
{
    std::string const input = "AAA";
    auto const actual{base64pp::decode(input)};
    std::vector<std::uint8_t> const expected{0x00, 0x00};

    ASSERT_TRUE(actual);
    ASSERT_EQ(*actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Decode, DecodesMissingOnePad1)
{
    std::string const input{"12a"};
    auto const actual{base64pp::decode(input)};
    std::vector<std::uint8_t> const expected{0xD7, 0x66};

    ASSERT_TRUE(actual);
    ASSERT_EQ(*actual, expected);
}


// Feature request - #84
// NOLINTNEXTLINE
TEST(Base64Decode, DecodesMissingIssueExample)
{
    std::string const input = "eyJuYW1lIjoiSm9obiBEb2UifQ";
    auto const actual{base64pp::decode(input)};

    std::string const expected_str = R"({"name":"John Doe"})";
    std::vector<std::uint8_t> const expected{begin(expected_str), end(expected_str)};

    ASSERT_TRUE(actual);
    ASSERT_EQ(*actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Decode, DecodesEmptyString)
{
    std::string const input{};
    std::vector<std::uint8_t> expected{};
    auto const actual{base64pp::decode("")};

    ASSERT_EQ(expected, actual);
}

// NOLINTNEXTLINE
TEST(Base64Decode, DecodesZeroArray)
{
    std::string const input{"AAAA"};
    std::vector<std::uint8_t> const expected{0x00, 0x00, 0x00};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Decode, DecodesZeroArrayTwice)
{
    std::string const input{"AAAAAAAA"};
    std::vector<std::uint8_t> const expected{0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Decode, DecodesZeroArrayOneByte)
{
    std::string const input{"AA=="};
    std::vector<std::uint8_t> const expected{0x00};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Decode, DecodesZeroArrayTwoBytes)
{
    std::string const input{"AAA="};
    std::vector<std::uint8_t> const expected{0x00, 0x00};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64Decode, DecodesQuickFox)
{
    std::string const input{"VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw=="};
    std::vector<std::uint8_t> const expected{0x54, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6b, 0x20, 0x62, 0x72,
        0x6f, 0x77, 0x6e, 0x20, 0x66, 0x6f, 0x78, 0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73, 0x20, 0x6f, 0x76, 0x65, 0x72,
        0x20, 0x74, 0x68, 0x65, 0x20, 0x6c, 0x61, 0x7a, 0x79, 0x20, 0x64, 0x6f, 0x67};
    auto const actual{base64pp::decode(input)};
    ASSERT_EQ(actual, expected);
}

// NOLINTNEXTLINE
TEST(Base64RoundTripTests, AllPossibleBytes)
{
    std::vector<std::uint8_t> all_possible_bytes;
    for (std::size_t i = 0; i <= 255; ++i)
    {
        all_possible_bytes.push_back(static_cast<std::uint8_t>(i));
    }

    auto const encode_string = base64pp::encode({begin(all_possible_bytes), end(all_possible_bytes)});
    auto const decoded_bytes = base64pp::decode(encode_string);
    ASSERT_TRUE(decoded_bytes);
    ASSERT_EQ(all_possible_bytes, *decoded_bytes);
}

// NOLINTNEXTLINE
TEST(Base64RoundTripTests, ExhaustiveTests)
{
    std::vector<std::string> const base64_strings = {
        "YW55IGNhcm5hbCBwbGVhcw==",
        "bGVnYWwgcGFzcw==",
        "dGVzdCBzdHJpbmc=",
        "bGVnYWwgcHJvdmlkZXI=",
        "ZW5vdWdoIHRoZSBzYW1lIG9mIHRoZSBwbGFjZQ==",
        "YW5vdGhlciB0aGUgc3RyYWlnaHQ=",
        "d2FzIG1lIGFkZHJlc3MgcHJvdmlkZXI=",
        "YWJvdXQgdGhlIG1hc3RlciBvZiB0aGUgZGFtYWdl",
        "ZW50aXJlIHRoYXQgYnJvdWdodCBvZiB0aGUgbW9uZXk=",
        "bGVnYWwgc2VjdXJpdHk=",
        "YmFzaWMgZ29vZCBvZiB0aGUgcGFkIHN0cmluZw==",
        "ZGVsZXRlIHN0cmluZyBvZiB0aGUgc3RyYWlnaHQ=",
        "YnJvdWdodCBvZiB0aGUgcGFkIGZvbGRlciBvZiB0aGUgZGFtYWdl",
        "aW50ZXJmYWNlIHN0cmluZw==",
        "Y29uc29sZS1tZS1jb21wYW55",
        "aW5mb3JtYXRpb24tbWVkaWE=",
        "c3RhdHVzLXNlY3VyZQ==",
        "Y3JlYXRlLWNvbXBhbnktc3RyaW5n",
        "b3JkZXItbGVhZGVy",
        "Y2F0YWxvZy1wcm9maWxl",
        "dGVzdC1jb25zdWx0aW5n",
        "YnJvdWdodC1sZWFkZXI=",
        "YXNzaWduLW1lY2hhbmlzbQ==",
        "bGVnYWwtY29udGFpbmVy",
        "ZW1haWwtY29udGFpbmVy",
        "aW5zdGFuY2UtY29udGFpbmVy",
        "dGVzdC1jb21wYW55LWFuZC1wcm9maWxl",
        "YmFzZTY0LWJhc2U=",
        "cGFzc3dvcmQ=",
        "Zm9vYmFy",
        "Y29vbC1iYXNl",
        "YmFzZTY0LXNlY3VyZQ==",
        "aW50ZXJ2YWw=",
        "dGhlLW1hc3Rlci1vZi10aGUtZGFtYWdl",
        "c2FtZS1wbGFjZS1vZi10aGUtZGFtYWdl",
        "aGFzaC1zb21ldGhpbmc="
    };

    for (auto const& b64_string : base64_strings)
    {
        auto const decoded = base64pp::decode(b64_string);
        ASSERT_TRUE(decoded);

        auto const encoded_round_trip = base64pp::encode({begin(*decoded), end(*decoded)});
        ASSERT_EQ(encoded_round_trip, b64_string);
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
