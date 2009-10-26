#include <boost/numeric/ublas/vector.hpp>
#include "plane.h"
#include "log.h"

using namespace boost::numeric;

namespace phys
{

plane::plane()
	: m_normal(2), m_c(0.0), m_n(2), m_p(0.0)
{
    m_vertices[0].resize(2);
    m_vertices[1].resize(2);
	for (size_t i = 0 ; i < m_normal.size(); i++)
	{
		m_vertices[0](i) = 0;
		m_vertices[1](i) = 0;
		m_normal(i) = 0;
	}
}

void
plane::init(vertex_t p1, vertex_t p2)
{
	m_vertices[0] = p1;
	m_vertices[1] = p2;

    /* find normal to plane */
    vector_t pv(2);
    pv = p2 - p1;
    m_normal(0) = -pv(1);
    m_normal(1) = pv(0);
    m_c = -ublas::inner_prod(m_normal, p1);
	LOG(1, "plane, p1: " << p1 << " p2: " << p2 << " normal: " << m_normal << " C: " << m_c);

    /* find normalized normal */
    double norm_sqrt = ublas::norm_2(m_normal);
    m_n = m_normal / norm_sqrt;
    m_p = m_c / norm_sqrt;
    LOG(1, "plane: normalized normal: " << m_n << " p: " << m_p);

    if (p1(0) <= p2(0))
    {
        m_start_x = &m_vertices[0];
        m_end_x = &m_vertices[1];
    } 
    else
    {
        m_start_x = &m_vertices[1];
        m_end_x = &m_vertices[0];
    }

    if (p1(1) <= p2(1))
    {
        m_start_y = &m_vertices[0];
        m_end_y = &m_vertices[1];
    } 
    else
    {
        m_start_y = &m_vertices[1];
        m_end_y = &m_vertices[0];
    }

}

plane::~plane()
{

}

vector_t & 
plane::get_normal()
{
	return m_normal;
}

vector_t & 
plane::get_nn()
{
	return m_n;
}

double
plane::get_p()
{
	return m_p;
}

vertex_t & 
plane::get_p1()
{
	return m_vertices[0];
}

vertex_t & 
plane::get_p2()
{
	return m_vertices[1];
}

bool
plane::is_inside(const pos_t & p) 
{
    if ((p(0) >= (*m_start_x)(0) && p(0) <= (*m_end_x)(0)) || 
        (p(1) >= (*m_start_y)(1) && p(1) <= (*m_end_y)(1)))
            return true;
    return false;           
}

}

