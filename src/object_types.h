#ifndef __OBJECT_TYPES_H__
#define __OBJECT_TYPES_H__
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef boost::numeric::ublas::vector<double> vertex_t;
typedef boost::numeric::ublas::vector<double> vector_t;
typedef boost::numeric::ublas::vector<double> pos_t;
typedef boost::numeric::ublas::vector<double> dimensions_t;

namespace object
{
    typedef enum
    {
       BOX,
       SPHERE,
    } type_t;
}

#endif /* __OBJECT_TYPES_H__ */
