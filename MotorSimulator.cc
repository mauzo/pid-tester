/* MotorSimulator.cc
 * Simulate a motor.
 */

#include <algorithm>

#include "MotorSimulator.h"

#define ε 0.01f

namespace mauzo::pid {

MotorSimulator::MotorSimulator() :
    pwm(0), speed(0.0),
    pwm_factor(1.0), txn_ratio(50.0), wheel_r(0.1),
    friction(1.0), mass(0.5)
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
    float   ω_ar    = speed;

    /* Armature torque. */
    float   T_ar    = E / std::max(ω_ar, ε);

    /* Wheel torque. */
    float   T_wh    = T_ar * txn_ratio;

    /* Force on tyre. */
    float   F_wh    = T_wh / wheel_r;
    F_wh            = std::min(F_wh, 100.0f);

    /* Linear speed of vehicle */
    float   ω_wh    = ω_ar / txn_ratio;
    float   v_ve    = ω_wh * wheel_r;

    /* Force on vehicle */
    float   F_ve    = F_wh - (friction * mass * v_ve);

    /* Accel of vehicle */
    float   a_ve    = F_ve / mass;

    /* Calculate new speed and convert back */
    v_ve    += a_ve * dt;
    ω_wh    = v_ve / wheel_r;
    ω_ar    = ω_wh * txn_ratio;

    speed   = ω_ar;
}

}
