#ifndef PHOTOSHOP_IRENDERER_HPP
#define PHOTOSHOP_IRENDERER_HPP

#include <cstdint>

struct BoxF;
struct Vec2f;

struct Color_t
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    // Color_t(Color color);
    Color_t( uint8_t r1, uint8_t g1, uint8_t b1, uint8_t a1 );
    // Color_t(double r1, double g1, double b1, double a1) {r = static_cast<uint8_t>(r1); g = static_cast<uint8_t>(g1);
    // b = static_cast<uint8_t>(b1); a = static_cast<uint8_t>(a1); }
    Color_t dark_version() const
    {
        return Color_t{ static_cast< uint8_t >( 0.7 * r ), static_cast< uint8_t >( 0.7 * g ),
                        static_cast< uint8_t >( 0.7 * b ), a };
    }
    Color_t transp_version() const
    {
        return Color_t{ r, g, b, static_cast< uint8_t >( a * 0.5 ) };
    }
};

class IRenderer
{
public:
    using ResourceID = uint64_t;

    virtual ~IRenderer() = default;

    virtual ResourceID loadTexture( const char* path )                                           = 0;
    virtual void renderRect( const Color_t& color, const BoxF& box, const float& angle )         = 0;
    virtual void renderRectLines( const Color_t& color, const BoxF& box, const float& angle )    = 0;
    virtual void renderTexture( const ResourceID& texture, const BoxF& box, const float& angle ) = 0;
    virtual void renderCircle( const Color_t& color, const BoxF& box )                           = 0;
    virtual void renderEllipse( const Color_t& color, const BoxF& box )                          = 0;
    virtual void renderEllipseLines( const Color_t& color, const BoxF& box )                     = 0;
    virtual void renderLine( const Vec2f& origin, const Vec2f& end, const Color_t& color )       = 0;
    virtual void renderVector( const Vec2f& origin, const Vec2f& vector, const Color_t& color )  = 0;
    virtual void renderPixel( const Vec2f& pos, const Color_t& color )                           = 0;

    virtual void update()                                                                             = 0;
    virtual void clear()                                                                              = 0;
    virtual void renderText( const char* text, const Color_t& color, const BoxF& box, int font_size ) = 0;
};

#endif
