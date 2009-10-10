#ifndef __POINT_H__
#define __POINT_H__
namespace phys {

class point 
{
	public:
		point(float mass, float x, float y, float z) 
			: m_mass(mass), m_x(x), m_y(y), m_z(0) 
		{
		}
		point(float mass, float x, float y)
			: m_mass(mass), m_x(x), m_y(y), m_z(0)
		{
		}
		point(const point & orig)
		{	
			this->m_x = orig.m_x;
			this->m_y = orig.m_y;
			this->m_z = orig.m_z;
			this->m_mass = orig.m_mass;
		}
		virtual ~point() 
		{
		}
	private:
		float m_mass;
		float m_x;
		float m_y;
		float m_z;
};

}
#endif /* __POINT_H__ */
