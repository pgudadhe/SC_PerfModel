#ifndef BUS_MASTER_H
#define BUS_MASTER_H

#include "platform_common.h"

class bus_master : sc_module
{
public:
  tlm_utils::simple_initiator_socket<bus_master> socket;
  tlm_utils::peq_with_cb_and_phase<bus_master> peq;

  SC_HAS_PROCESS(bus_master);

  bus_master(sc_core::sc_module_name name, unsigned int num_transactions, float ratio)
      : sc_module(name),
        m_num_transactions(num_transactions),
        m_r_to_wr_ratio(ratio),
        m_num_trans_in_progress(0),
        socket("master_socket"),
        peq(this, &bus_master::peq_cb)
  {
    cout << "Master created" << endl;
#pragma warning(push)
#pragma warning(disable : 4407)
    SC_METHOD(traffic_gen_method);
    //sensitive << traffic_gen_event;
#pragma warning(pop)
  }

  void peq_cb(tlm_generic_payload &trans, const tlm_phase &phase);
  tlm_sync_enum nb_transport_bw(tlm_generic_payload &trans, tlm_phase &phase, sc_time &delay);

private:
  void traffic_gen_method();
  //sc_event traffic_gen_event;

  unsigned int m_data[16];
  unsigned int m_num_transactions;
  float m_r_to_wr_ratio;
  unsigned int m_num_trans_in_progress;
};

#endif
