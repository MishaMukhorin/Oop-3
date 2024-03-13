#include "Car.h"

static int GetMaxSpeed(int gear)
{
    switch (gear)
    {
        case -1: return 20;
        case 0: return INT_MAX; // no m_speed limit for neutral
        case 1: return 30;
        case 2: return 50;
        case 3: return 60;
        case 4: return 90;
        case 5: return 150;
        default: return 0;
    }
}

static int GetMinSpeed(int gear)
{
    switch (gear)
    {
        case 2: return 20;
        case 3: return 30;
        case 4: return 40;
        case 5: return 50;
        default: return 0;
    }
}

bool CCar::TurnOnEngine()
{
    if (m_engineOn) return true;
    if (m_speed != 0 || m_gear != 0) return false; // can't turn on if moving or not in neutral
    m_engineOn = true;
    return true;
}

bool CCar::TurnOffEngine()
{
    if (!m_engineOn) return true;
    if (m_speed != 0 || m_gear != 0) return false; // can't turn off if moving or not in neutral
    m_engineOn = false;
    return true;
}

void CCar::SetSpeed(int speed)
{
    if (speed < 0)
        throw NegativeSpeedError();
    if (!m_engineOn)
        throw EngineOffError();
    if (m_gear == 0 && speed > m_speed)
        throw IncreaseSpeedError();
    int maxSpeed = GetMaxSpeed(m_gear);
    if (speed > maxSpeed)
        throw MaxSpeedError();

    this->m_speed = speed;
    if (speed == 0)
        m_direction = 0; // stopped
    else
        m_direction = (m_gear == -1) ? -1 : (m_gear == 1) ? 1 : m_direction;
}

void CCar::SetGear(int gear)
{
    if (!m_engineOn)
        throw EngineOffError();
    if (gear < -1 || gear > 5)
        throw GearRangeError();
    if (m_direction == -1 && gear > 0)
        throw ReverseToForwardError();
    if (gear == -1 && m_speed > 0)
        throw ReverseSpeedError();
    if (m_speed < GetMinSpeed(gear) || m_speed > GetMaxSpeed(gear))
        throw GearSpeedRangeError();
    this->m_gear = gear;
}


