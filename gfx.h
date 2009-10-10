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

};

}
#endif /* __GFX_H__ */
