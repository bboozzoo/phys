#ifndef __GFX_H__
#define __GFX_H__
#include <cstdint>
#include <string>

namespace sys
{

class color
{
    public:
        typedef enum
        {
            WHITE   = 0xffffffff,
            BLACK   = 0x000000ff,
            RED     = 0xff0000ff,
            GREEN   = 0x00ff00ff,
            BLUE    = 0x0000ffff,
            YELLOW  = 0xffff00ff,
            ORANGE  = 0xffa500ff,
        } color_val_t;

        color(uint32_t col);
        ~color();
        uint32_t get_value();
        std::string to_str();
    private:
        uint32_t    m_color;
};

class gfx 
{
	public:
		gfx() {}
		virtual ~gfx() {};
		virtual void init() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void clear() = 0;
        virtual uint32_t get_width() = 0;
        virtual uint32_t get_height() = 0;

};

}
#endif /* __GFX_H__ */
