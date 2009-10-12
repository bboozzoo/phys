#include "plane.h"
#include "log.h"

namespace phys
{

plane::plane()
	: m_p1(3), m_p2(3), m_normal(3)
{
	for (int i = 0 ; i < m_normal.size(); i++)
	{
		m_p1(i) = 0;
		m_p2(i) = 0;
		m_normal(i) = 0;
	}
}

void
plane::init(ublas::vector<double> p1, ublas::vector<double> p2)
{
	ublas::vector<double> plane(3);
	m_p1 = p1;
	m_p2 = p2;
	plane = m_p1 - m_p2;	
	if (plane(1) == 0)
	{
		m_normal(1) = 1;
	}
	else if (plane(0) == 0)
	{
		m_normal(0) = 1;
	}
	else
	{
		double slope = plane(1) / plane(0);
		double tslope = -1/slope;
		m_normal.assign(plane);
		m_normal(1) = tslope * m_normal(0);	
	}
	LOG(1, "plane, p1: " << m_p1 << " p2: " << m_p2 << " pl: " << plane << " normal: " << m_normal);
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
plane::get_p()
{
	return m_p1;
}


}

