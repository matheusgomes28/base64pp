#ifndef BASE64PP_H
#define BASE64PP_H

#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace base64pp
{
    std::string encode(std::span<std::uint8_t const> const input);

    std::optional<std::vector<std::uint8_t>> decode(
        std::string_view const encoded_str);
} // namespace base64pp

#endif // BASE64PP_H
