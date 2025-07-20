#ifndef PLATFORM_TOP_H
#define PLATFORM_TOP_H

#include "systemc.h"
#include <iostream>
#include "bus_master.h"
#include "bus_target.h"

using namespace std;

SC_MODULE(platform_top)
{
public:
    SC_CTOR(platform_top)
    {
        cout << "top created" << endl;
        m_master = new bus_master("bus_master", 1000, 0.5);
        m_target = new bus_target("bus_target");

        m_master->socket.bind(m_target->socket);
    }
    ~platform_top(){};

private:
    bus_master *m_master;
    bus_target *m_target;
};

#endif