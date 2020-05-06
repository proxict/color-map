#include <constexpr-color/constexpr-color.hpp>

#include <iostream>
#include <sstream>
#include <string>

namespace cc = constexprColor;

static std::string toHex(const cc::Rgb& rgb) {
    std::stringstream ss;
    static constexpr const char* const hex = "0123456789ABCDEF";
    ss << "#";
    ss << (hex[(rgb.r >> 4) & 0xf]) << (hex[rgb.r & 0xf]);
    ss << (hex[(rgb.g >> 4) & 0xf]) << (hex[rgb.g & 0xf]);
    ss << (hex[(rgb.b >> 4) & 0xf]) << (hex[rgb.b & 0xf]);
    return ss.str();
}

static std::string toHex(const cc::Hsl& hsl) {
    return toHex(cc::toRgb(hsl));
}

constexpr bool isHexChar(const char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

bool isValidColor(const char* color) {
    if (*color++ != '#') {
        return false;
    }
    while (*color) {
        if (!isHexChar(*color++)) {
            return false;
        }
    }
    return true;
}

template <typename T>
constexpr T lerp(const T a, const T b, const T d) {
    return ((a * (T(1.0) - d)) + (b * d));
}

constexpr cc::Hsl interpolateColor(const cc::Hsl& from, const cc::Hsl& to, const float f) {
    return cc::Hsl(lerp(static_cast<float>(from.hue), static_cast<float>(to.hue), f),
                   lerp(from.saturation, to.saturation, f),
                   lerp(from.lightness, to.lightness, f));
}

int main(const int argc, const char** argv) {
    if (argc < 4) {
        std::clog << "Usage: " << argv[0] << " <from-color> <to-color> <factor>\n";
        return 1;
    }

    const char* fromColor = argv[1];
    const char* toColor = argv[2];

    if (!isValidColor(fromColor) || !isValidColor(toColor)) {
        std::clog << "Invalid color value. Expected format #rrggbb\n";
        return 1;
    }

    int factor;
    try {
        factor = std::stoi(argv[3]);
    } catch (const std::exception&) {
        factor = -1;
    }
    if (factor < 0 || factor > 100) {
        std::clog << "Invalid factor value. Factor can only be in the range between 0 and 100\n";
        return 1;
    }

    const cc::Hsl interpolated =
        interpolateColor(cc::toHsl(fromColor), cc::toHsl(toColor), static_cast<float>(factor) / 100.0f);
    std::cout << toHex(interpolated) << "\n";
    return 0;
}
