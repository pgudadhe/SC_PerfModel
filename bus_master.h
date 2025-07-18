#ifndef BUS_MASTER_H
#define BUS_MASTER_H

#include "platform_common.h"

class bus_master: sc_module
{
public:
  tlm_utils::simple_initiator_socket<bus_master> socket;

  SC_HAS_PROCESS(bus_master);

  bus_master(sc_core::sc_module_name name, unsigned int num_transactions, float ratio) 
  : sc_module(name), 
    m_num_transactions(num_transactions),
    m_r_to_wr_ratio(ratio),
    socket("master_socket")
  {
    SC_THREAD(thread_process);
  }

  void thread_process();

private:
  unsigned int    m_data[16];
  unsigned int    m_num_transactions;
  float           m_r_to_wr_ratio;

};

#endif