#pragma once

namespace FGE {

    class Timestep {

    public:
        Timestep( float time = 0.0f ) : m_Time( time ) {}

        // Use Timestep As Float
        operator float() const  { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMilliSeconds() { return m_Time * 1000.0f; }

    private:
        float m_Time;

    };

}