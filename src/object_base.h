#ifndef __OBJECT_BASE_H__
#define __OBJECT_BASE_H__
#include "object_types.h"

class object_base
{
    public:

        object_base(object::type_t type)
            : m_type(type)
        {
        }
        virtual ~object_base()
        {
        }
    protected:
        object::type_t       m_type;
};

#endif /* __OBJECT_BASE_H__ */
