#include "bus_target.h"

    tlm_sync_enum bus_target::nb_transport_fw(tlm_generic_payload& trans, tlm_phase& phase, sc_time& delay) {
        if (phase == BEGIN_REQ)
        {
            // This is for WRITE command
            delay += sc_time(10, SC_PS); 
            wait(delay);

           trans.set_response_status(TLM_OK_RESPONSE);

            phase = BEGIN_RESP;
            return TLM_UPDATED;
        } else if (phase == END_RESP) 
        {
            return TLM_COMPLETED;
        }
        return TLM_ACCEPTED;
    }
