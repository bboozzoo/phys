#include "world_phys.h"
#include "conf.h"
#include "log.h"

world_phys::world_phys()
    : m_world(NULL), m_space(NULL)
{
    LOG(1, "creating world");
    dInitODE();
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
    m_contact_joints = dJointGroupCreate(0);
}

world_phys::~world_phys()
{
    LOG(1, "destroying world");
    /* delete all objects from list */
    dJointDestroy(m_2d_plane);
    dSpaceDestroy(m_space);
    dWorldDestroy(m_world);
    dCloseODE();
}

void 
world_phys::add(object_phys * op)
{
    if (op->get_type() != object::PLANE)
        dJointAttach(m_2d_plane, op->get_body(), 0);
    m_pobjects.push_back(op);
}

void
world_phys::advance(double delta_t)
{
    dSpaceCollide(m_space, this, world_phys::possible_collision_clbk);
    dWorldQuickStep(m_world, delta_t);
    dJointGroupEmpty(m_contact_joints);
}

void
world_phys::possible_collision_clbk(void * data, dGeomID g0, dGeomID g1) 
{
    object_phys * o0 = reinterpret_cast<object_phys *>(dGeomGetData(g0));
    object_phys * o1 = reinterpret_cast<object_phys *>(dGeomGetData(g1));
    world_phys * w = reinterpret_cast<world_phys *>(data);
    LOG(2, "collision? g0: " << (void *) o0 << " g1: " << (void *) o1);
    dContact contacts[1];
    contacts[0].surface.mode = dContactBounce;
    contacts[0].surface.mu = 0;
    contacts[0].surface.mu2 = 0;
    contacts[0].surface.bounce = 0.8;
    contacts[0].surface.bounce_vel = 0.001;
    contacts[0].surface.soft_cfm = 0.01;
    int contact_cnt = dCollide(g0, g1, 1, &contacts[0].geom, sizeof(dContact));
    LOG(2, "contacts: " << contact_cnt);
    if (contact_cnt > 0) 
    {
        dJointID contact_joint = dJointCreateContact(w->m_world, w->m_contact_joints, &contacts[0]);
        dJointAttach(contact_joint, dGeomGetBody(g0), dGeomGetBody(g1));
        o0->set_in_collision(true);
        o1->set_in_collision(true);
    }   
}


