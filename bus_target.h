#ifndef BUS_TARGET_H
#define BUS_TARGET_H

#include "platform_common.h"

class bus_target: sc_module
{
public:
  tlm_utils::simple_target_socket<bus_target> socket;

  bus_target(sc_core::sc_module_name name) 
  : sc_module(name), 
    socket("target_socket")
  {
    socket.register_nb_transport_fw(this, &AXISlave::nb_transport_fw);
  }


};

#endif
