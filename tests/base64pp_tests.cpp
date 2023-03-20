#include <array>
#include <base64pp/base64pp.h>
#include <cstdint>
#include <gtest/gtest.h>
#include <string>

TEST(Base64Encode, EncodesEmpty)
{
    std::string const expected{};
    std::string const actual{base64pp::encode({})};
    ASSERT_EQ(expected, actual);
}

TEST(Base64Encode, EncodesThreeBytesZeros)
{
    std::array<std::uint8_t, 3> const input{0x00, 0x00, 0x00};
    auto const expected{"AAAA"};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(expected, actual);
}

TEST(Base64Encode, EncodesThreeBytesRandom)
{
    std::array<std::uint8_t, 3> const input{0xFE, 0xE9, 0x72};
    auto const expected{"/uly"};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(expected, actual);
}

TEST(Base64Encode, EncodesTwoBytes)
{
    std::array<std::uint8_t, 2> const input{0x00, 0x00};
    auto const expected{"AAA="};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(expected, actual);
}

TEST(Base64Encode, EncodesOneByte)
{
    std::array<std::uint8_t, 1> const input{0x00};
    auto const expected{"AA=="};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(expected, actual);
}

TEST(Base64Encode, EncodesFourBytes)
{
    std::array<std::uint8_t, 4> const input{0x74, 0x68, 0x65, 0x20};
    auto const expected{"dGhlIA=="};
    auto actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(expected, actual);
}

TEST(Base64Encode, EncodesFiveBytes)
{
    std::array<std::uint8_t, 5> const input{0x20, 0x62, 0x72, 0x6f, 0x77};
    auto const expected{"IGJyb3c="};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(actual, expected);
}

TEST(Base64Encode, EncodesSixBytes)
{
    std::array<std::uint8_t, 6> const input{0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73};
    auto const expected{"IGp1bXBz"};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(actual, expected);
}

TEST(Base64Encode, EncodesBrownFox)
{
    std::array<std::uint8_t, 43> const input{0x74, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6b, 0x20, 0x62, 0x72,
        0x6f, 0x77, 0x6e, 0x20, 0x66, 0x6f, 0x78, 0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73, 0x20, 0x6f, 0x76, 0x65, 0x72,
        0x20, 0x74, 0x68, 0x65, 0x20, 0x6c, 0x61, 0x7a, 0x79, 0x20, 0x64, 0x6f, 0x67};

    auto const expected{"dGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw=="};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(actual, expected);
}

TEST(Base64Encode, EncodesBrownFastFoxNullInMiddle)
{
    std::array<std::uint8_t, 45> const input{0x74, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6b, 0x21, 0x20, 0x62,
        0x72, 0x6f, 0x77, 0x6e, 0x20, 0x66, 0x6f, 0x78, 0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73, 0x20, 0x6f, 0x76, 0x65,
        0x72, 0x20, 0x74, 0x68, 0x65, 0x00, 0x20, 0x6c, 0x61, 0x7a, 0x79, 0x20, 0x64, 0x6f, 0x67};

    auto const expected{"dGhlIHF1aWNrISBicm93biBmb3gganVtcHMgb3ZlciB0aGUAIGxhenkgZG9n"};
    auto const actual{base64pp::encode({begin(input), end(input)})};
    ASSERT_EQ(actual, expected);
}

TEST(Base64Decode, FailDecodeOneString)
{
    std::string const input{"1"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

TEST(Base64Decode, FailDecodeOneStringPadded)
{
    std::string const input{"1==="};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

TEST(Base64Decode, FailDecodeTwoString)
{
    std::string const input{"12"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

TEST(Base64Decode, FailDecodeThreeString)
{
    std::string const input{"12a"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

TEST(Base64Decode, FailDecodeNonSize4)
{
    std::string const input{"something"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

TEST(Base64Decode, FailDecodeNonSize4Bigger)
{
    std::string const input{"SomethingEntirelyDifferent"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

TEST(Base64Decode, FailDecodeNonBase64Short)
{
    std::string const input{"a aa"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}

TEST(Base64Decode, FailDecodeNonBase64Longer)
{
    std::string const input{"aaa`"};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, std::nullopt);
}
TEST(Base64Decode, DecodesEmptyString)
{
    std::string const input{};
    std::vector<std::uint8_t> expected{};
    auto const actual{base64pp::decode("")};

    ASSERT_EQ(expected, actual);
}

TEST(Base64Decode, DecodesZeroArray)
{
    std::string const input{"AAAA"};
    std::vector<std::uint8_t> const expected{0x00, 0x00, 0x00};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, expected);
}

TEST(Base64Decode, DecodesZeroArrayTwice)
{
    std::string const input{"AAAAAAAA"};
    std::vector<std::uint8_t> const expected{0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, expected);
}

TEST(Base64Decode, DecodesZeroArrayOneByte)
{
    std::string const input{"AA=="};
    std::vector<std::uint8_t> const expected{0x00};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, expected);
}

TEST(Base64Decode, DecodesZeroArrayTwoBytes)
{
    std::string const input{"AAA="};
    std::vector<std::uint8_t> const expected{0x00, 0x00};
    auto const actual{base64pp::decode(input)};

    ASSERT_EQ(actual, expected);
}

TEST(Base64Decode, DecodesQuickFox)
{
    std::string const input{"VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw=="};
    std::vector<std::uint8_t> const expected{0x54, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6b, 0x20, 0x62, 0x72,
        0x6f, 0x77, 0x6e, 0x20, 0x66, 0x6f, 0x78, 0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73, 0x20, 0x6f, 0x76, 0x65, 0x72,
        0x20, 0x74, 0x68, 0x65, 0x20, 0x6c, 0x61, 0x7a, 0x79, 0x20, 0x64, 0x6f, 0x67};
    auto const actual{base64pp::decode(input)};
    ASSERT_EQ(actual, expected);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
