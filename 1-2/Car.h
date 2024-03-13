#include "iostream"
#include "CarErrors.h"

class CCar {
public:


    [[nodiscard]] bool IsTurnedOn() const { return m_engineOn; }
    [[nodiscard]] int GetDirection() const { return m_direction; }
    [[nodiscard]] int GetSpeed() const { return m_speed; }
    [[nodiscard]] int GetGear() const { return m_gear; }

    bool TurnOnEngine();
    bool TurnOffEngine();
    void SetSpeed(int speed) noexcept(false);
    void SetGear(int gear) noexcept(false);

private:
    bool m_engineOn;
    int m_direction; // -1 = reverse, 0 = stopped, 1 = forwards
    int m_speed;
    int m_gear;
};
