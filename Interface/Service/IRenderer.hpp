#ifndef PHOTOSHOP_IRENDERER_HPP
#define PHOTOSHOP_IRENDERER_HPP

#include <cstdint>

struct Color_t;
struct BoxF;
struct Vec2f;

class IRenderer
{
public:
    using ResourceID = uint64_t;

    virtual ~IRenderer() = default;

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
