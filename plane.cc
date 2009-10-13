#include "plane.h"
#include "log.h"

namespace phys
{

plane::plane()
	: m_p1(2), m_p2(2), m_normal(2), m_c(0), m_n(2), m_p(0)
{
	for (size_t i = 0 ; i < m_normal.size(); i++)
	{
		m_p1(i) = 0;
		m_p2(i) = 0;
		m_normal(i) = 0;
	}
}

void
plane::init(ublas::vector<double> p1, ublas::vector<double> p2)
{
	m_p1 = p1;
	m_p2 = p2;

    ublas::vector<double> pv(2);
    pv = p2 - p1;
    m_normal(0) = -pv(1);
    m_normal(1) = pv(0);
    m_c = -ublas::inner_prod(m_normal, p1);
	LOG(1, "plane, p1: " << m_p1 << " p2: " << m_p2 << " normal: " << m_normal << " C: " << m_c);
    double norm_sqrt = ublas::norm_2(m_normal);
    m_n = m_normal / norm_sqrt;
    m_p = m_c / norm_sqrt;
    LOG(1, "plane: normalized normal: " << m_n << " p: " << m_p);

    if (m_p1(0) <= m_p2(0))
    {
        m_start_x = &m_p1;
        m_end_x = &m_p2;
    } 
    else
    {
        m_start_x = &m_p2;
        m_end_x = &m_p1;
    }

    if (m_p1(1) <= m_p2(1))
    {
        m_start_y = &m_p1;
        m_end_y = &m_p2;
    } 
    else
    {
        m_start_y = &m_p2;
        m_end_y = &m_p1;
    }

}

plane::~plane()
{

}

ublas::vector<double> & 
plane::get_normal()
{
	return m_normal;
}

ublas::vector<double> & 
plane::get_nn()
{
	return m_n;
}

double
plane::get_p()
{
	return m_p;
}

ublas::vector<double> & 
plane::get_p1()
{
	return m_p1;
}

ublas::vector<double> & 
plane::get_p2()
{
	return m_p2;
}

bool
plane::is_inside(ublas::vector<double> & p) 
{
    if ((p(0) >= (*m_start_x)(0) && p(0) <= (*m_end_x)(0)) || 
        (p(1) >= (*m_start_y)(1) && p(1) <= (*m_end_y)(1)))
            return true;
    return false;           
}

}

