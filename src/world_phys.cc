#include "world_phys.h"
#include "conf.h"

world_phys::world_phys()
    : m_world(NULL), m_space(NULL)
{
    m_world = dWorldCreate();
    m_space = dHashSpaceCreate(0);
    dWorldSetGravity(m_world, 0, GRAVITY, 0);
    dWorldSetCFM(m_world, CFM);
    dWorldSetAutoDisableFlag(m_world, 1);

#if 1
    dWorldSetAutoDisableAverageSamplesCount( m_world, 10 );
#endif

    dWorldSetLinearDamping(m_world, LINEAR_DAMPING);
    dWorldSetAngularDamping(m_world, ANGULAR_DAMPING);
    dWorldSetMaxAngularSpeed(m_world, MAX_ANGULAR);

    dWorldSetContactMaxCorrectingVel (m_world,CONTACT_CORR_VEL);
    dWorldSetContactSurfaceLayer (m_world, CONTACT_SURF_LAY);

    m_2d_plane = dJointCreatePlane2D(m_world, 0);
}

world_phys::~world_phys()
{
    /* delete all objects from list */
    dSpaceDestroy(m_space);
    dWorldDestroy(m_world);
    dCloseODE();
}

void 
world_phys::add(object_phys * op)
{
    dJointAttach(m_2d_plane, op->get_body(), 0);
    m_pobjects.push_back(op);
}

void
world_phys::advance(double delta_t)
{
    dWorldQuickStep(m_world, delta_t);
}


