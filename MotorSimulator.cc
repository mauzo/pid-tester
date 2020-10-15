/* MotorSimulator.cc
 * Simulate a motor.
 */

#include <algorithm>

#include "MotorSimulator.h"

#define EPSILON 0.01f

namespace mauzo::pid {

MotorSimulator::MotorSimulator() :
    pwm(0), speed(0.0), force(0.0),
    pwm_factor(1.0), txn_ratio(50.0), wheel_r(0.1),
    friction(2.0), stiction(3.0), mass(0.5)
{ }

void
MotorSimulator::sim_step(float dt) {
    /* parameters:
        pwm_factor      convert pwm to energy
        txn_ratio       e.g. 50 for 50:1 reduction
        wheel_r         wheel radius
        friction        coeff of rolling friction
        mass            vehicle mass (per wheel)
    */

    /* PWM is energy, broadly speaking. */
    float   E       = float(pwm) * pwm_factor;

    /* Armature angular speed */
    float   oh_ar    = speed;

    /* Armature torque. */
    float   T_ar    = E / std::max(oh_ar, EPSILON);

    /* Wheel torque. */
    float   T_wh    = T_ar * txn_ratio;

    /* Force on tyre. */
    float   F_wh    = T_wh / wheel_r;
    F_wh            = std::min(F_wh, 5.0f);

    /* Linear speed of vehicle */
    float   oh_wh   = oh_ar / txn_ratio;
    float   v_ve    = oh_wh * wheel_r;

    /* Force on vehicle */
    float   F_ve;
    if (v_ve < EPSILON) {
        F_ve        = std::max(0.0f, F_wh - stiction);
    }
    else {
        F_ve        = F_wh - friction;
    }
    force           = F_ve;

    /* Accel of vehicle */
    float   a_ve    = F_ve / mass;

    /* Calculate new speed and convert back */
    v_ve    += a_ve * dt;
    v_ve    = std::max(v_ve, 0.0f);
    oh_wh   = v_ve / wheel_r;
    oh_ar   = oh_wh * txn_ratio;

    speed   = oh_ar;
}

}
