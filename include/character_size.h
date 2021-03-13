#pragma once
#include <unordered_map>

namespace local{
    enum class CharacterSize{
        kSmall,
        kMedium,
        kLarge
    };

    std::unordered_map<local::CharacterSize, const char *> charSizeToString({
        {CharacterSize::kSmall, "small"},
        {CharacterSize::kMedium, "medium"},
        {CharacterSize::kLarge, "large"},
    });
}
