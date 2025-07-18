#ifndef BUS_TARGET_H
#define BUS_TARGET_H

#include "platform_common.h"

class bus_target: sc_module
{
public:
  tlm_utils::simple_target_socket<bus_target> socket;

  SC_CTOR(bus_target) : socket("target_socket")
  {
  }

};

#endif