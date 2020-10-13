#ifndef _MotorSimulator_h
#define _MotorSimulator_h

namespace mauzo::pid {

class MotorSimulator {
  public:
    MotorSimulator();

    void    set_pwm(int p)  { pwm = p; }
    int     get_pwm()       { return pwm; }    
    float   get_speed()     { return speed; }

    void    sim_step(float dt);

  private:
    int     pwm;
    float   speed;

    float   pwm_factor;      //convert pwm to energy
    float   txn_ratio;       //e.g. 50 for 50:1 reduction
    float   wheel_r;         //wheel radius
    float   friction;        //coeff of rolling friction
    float   mass;            //vehicle mass (per wheel)
};

}

#endif
