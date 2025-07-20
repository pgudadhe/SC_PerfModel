#include "bus_master.h"
// Master
void bus_master::traffic_gen_method()
{
    cout << "Thread running" << endl;

    tlm::tlm_generic_payload *trans;
    tlm::tlm_phase phase;
    sc_time delay;
    uint64_t addr = 0;

    //for (unsigned int i = 0; i < m_num_transactions; i++)
    {
        trans = new tlm::tlm_generic_payload();

        // Is it going to be a READ or WRITE command?
        // 0 = READ, 1 = WRITE
        tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);

        // trans->acquire();  Do we need this???
        trans->set_command(cmd);
        trans->set_address(addr);
        // trans->set_data_ptr(reinterpret_cast<unsigned char *>(&m_data[i % 16]));
        trans->set_data_length(4);
        trans->set_streaming_width(4);                            // = data_length to indicate no streaming
        trans->set_byte_enable_ptr(0);                            // 0 indicates unused
        trans->set_dmi_allowed(false);                            // Mandatory initial value
        trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE); // Mandatory initial value

        // Check for FIFO backpressure
        //if (m_num_trans_in_progress >= FIFO_SIZE)
        //{
            //wait(end_request_event);
        //}

        assert(m_num_trans_in_progress < FIFO_SIZE);

        m_num_trans_in_progress++;
        phase = tlm::BEGIN_REQ;

        // Request delay is 3 pico secs
        delay = sc_time(3, SC_PS);

        cout << "Issueing new " << (cmd ? "WRITE" : "READ") << " request for addr: 0x" << hex << addr << " at time=" << sc_time_stamp() << " PS" << endl;

        tlm::tlm_sync_enum status = socket->nb_transport_fw(*trans, phase, delay);

        if (status == TLM_UPDATED)
        {
            peq.notify(*trans, phase, delay);
        }
        else if (status == TLM_COMPLETED)
        {
            trans->release();
        }

        wait(10, SC_NS); // Simulate processing delay
    }

    next_trigger(1, SC_SEC);
}

tlm_sync_enum bus_master::nb_transport_bw(tlm_generic_payload &trans, tlm_phase &phase, sc_time &delay)
{
    peq.notify(trans, phase, delay);
    return TLM_ACCEPTED;
}

void bus_master::peq_cb(tlm_generic_payload &trans, const tlm_phase &phase)
{
    if (phase == BEGIN_RESP)
    {
        tlm_phase fw_phase = END_RESP;
        sc_time delay = SC_ZERO_TIME;
        socket->nb_transport_fw(trans, fw_phase, delay);

        trans.release();
    }
}
