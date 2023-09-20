#ifndef MAPTOOL__DUMMY_DECLARATIONS_H
#define MAPTOOL__DUMMY_DECLARATIONS_H

// **This file is not subject to the code assessment.**
// It merely contains declarations to make the `map_gug.*` files compile.

#include <memory>

#define EXPORT
#ifdef _MSC_VER
#  define PACKED_STRUCT(...) __pragma(pack(push, 1)); \
                           __VA_ARGS__;             \
                           __pragma(pack(pop));
#else
#  define PACKED_STRUCT(...) __VA_ARGS__  __attribute__((packed));
#endif


static const double RAD_to_DEG = 57.29577951308232;
static const double DEG_to_RAD = .0174532925199432958;
static const char* PATH_SEP = "/";


class EXPORT PixelBufCoord {
    public:
        PixelBufCoord() : x(0), y(0) {};
        PixelBufCoord(int x_, int y_) : x(x_), y(y_) {};

        PixelBufCoord& operator+=(const class PixelBufDelta &rhs);
        PixelBufCoord& operator-=(const class PixelBufDelta &rhs);

        int x, y;
};

class EXPORT MapPixelCoordInt {
    public:
        MapPixelCoordInt() : x(0), y(0) {};
        MapPixelCoordInt(int x_, int y_) : x(x_), y(y_) {};
        MapPixelCoordInt(const class MapPixelCoordInt &coord, int tile_size);
        MapPixelCoordInt(const class MapPixelCoord &coord, int tile_size);
        MapPixelCoordInt& operator+=(const class MapPixelDeltaInt &rhs);
        MapPixelCoordInt& operator-=(const class MapPixelDeltaInt &rhs);
        int x, y;
};

class EXPORT MapPixelDeltaInt {
    public:
        MapPixelDeltaInt() : x(0), y(0) {};
        MapPixelDeltaInt(int x_, int y_) : x(x_), y(y_) {};
        MapPixelDeltaInt& operator+=(const class MapPixelDeltaInt &rhs);
        MapPixelDeltaInt& operator-=(const class MapPixelDeltaInt &rhs);
        MapPixelDeltaInt& operator*=(int factor);
        MapPixelDeltaInt& operator/=(int divisor);

        int x, y;
};

class RasterMap {};

class PixelBuf {
    public:
        PixelBuf();
        PixelBuf(int width, int height);
        std::shared_ptr<unsigned int> &GetData();
        void Insert(const class PixelBufCoord &pos, const PixelBuf &source);
};


EXPORT PixelBuf decompress_jpeg(const std::string &buf, bool swap_rb=false);
void replace_all(std::string& str, const std::string& from, const std::string& to);
std::string string_format(const std::string fmt, ...);
long long int  GetFilesize(const std::string &filename);
bool stobool(const std::string &s);
unsigned long int hextoul(const std::string &s);
MapPixelCoordInt operator+(MapPixelCoordInt lhs, const MapPixelDeltaInt &rhs);

/** Return a white background tile if pos/size are out-of-bounds for the map.
 *
 * Checks if pos and size are within bounds and crops the region if necessary.
 * It may call `map.GetRegion()` again with updated `pos` and `size`!
 * If the return value is valid, it can be returned directly from `GetRegion()`.
 */
PixelBuf EXPORT bg_tile_if_out_of_bounds(const RasterMap &map,
                                         const MapPixelCoordInt &pos,
                                         const MapPixelDeltaInt &size);

#endif
