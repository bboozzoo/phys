#ifndef __GFX_H__
#define __GFX_H__

namespace phys 
{
class gfx 
{
	public:
		gfx() {}
		virtual ~gfx() {};
		virtual void init() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual uint32_t get_width() = 0;
        virtual uint32_t get_height() = 0;

};

}
#endif /* __GFX_H__ */
