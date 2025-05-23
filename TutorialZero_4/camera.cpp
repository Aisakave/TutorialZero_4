#include "camera.h"

void Camera::reset()
{

    position.x = 0;
    position.y = 0;
}

void Camera::on_updata(int runTimeMs)
{
    timer_shake.on_updata(runTimeMs);

    if (is_shaking)
    {
        position.x = ((rand() / (float)RAND_MAX) * 2.0f - 1.0f) * shaking_strength;
        position.y = ((rand() / (float)RAND_MAX) * 2.0f - 1.0f) * shaking_strength;
    }
}

const Vector2& Camera::get_postion() const 
{

    return position;
}

Camera::Camera()
{
    timer_shake.set_one_shot(true);
    timer_shake.set_callback(
        [&]()
        {
            is_shaking = false;
            reset();
        }
    );
}

void Camera::shake(float strength, int duration)
{
    is_shaking = true;
    shaking_strength = strength;

    timer_shake.set_wait_time(duration);
    timer_shake.restart();
}