#ifndef __SIMOBJECT_H__
#define __SIMOBJECT_H__
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/array.hpp>

namespace phys 
{

typedef boost::numeric::ublas::vector<double> vertex_t;
typedef boost::numeric::ublas::vector<double> vector_t;
typedef boost::numeric::ublas::vector<double> pos_t;

typedef enum
{
    SIMOBJECT_POINT,
    SIMOBJECT_PLANE,
} simobject_type_t;

template <simobject_type_t obj_type, size_t vertex_cnt>
class simobject
{
    public:

        simobject()
            : m_type(obj_type)
        {
        }
        ~simobject()
        {
        }
        virtual double distance(const pos_t & p) = 0;
        virtual bool is_collision(const pos_t & p) = 0;
    protected:
        boost::array<vertex_t, vertex_cnt>  m_vertices;
        simobject_type_t                    m_type;
};

}


#endif /* __SIMOBJECT_H__ */
