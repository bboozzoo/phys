#ifndef __SIMOBJECT_H__
#define __SIMOBJECT_H__
#include <boost/array.hpp>

#if 0
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
    protected:
        boost::array<vertex_t, vertex_cnt>  m_vertices;
        simobject_type_t                    m_type;
};
#endif

#endif /* __SIMOBJECT_H__ */
