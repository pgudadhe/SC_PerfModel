#ifndef BUS_TARGET_H
#define BUS_TARGET_H

#include "platform_common.h"

class bus_target : sc_module
{
public:
  tlm_utils::simple_target_socket<bus_target> socket;

  SC_HAS_PROCESS(bus_target);

  bus_target(sc_core::sc_module_name name)
      : sc_module(name),
        socket("target_socket")
  {
    cout << "Target created" << endl;
    socket.register_nb_transport_fw(this, &bus_target::nb_transport_fw);
  }

  virtual tlm_sync_enum nb_transport_fw(tlm_generic_payload &trans,
                                        tlm_phase &phase, sc_time &delay);
};

#endif
