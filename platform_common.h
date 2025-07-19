#ifndef PLATFORM_COMMON_H
#define PLATFORM_COMMON_H

#include <iostream>
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include <tlm_utils/peq_with_cb_and_phase.h>

using namespace sc_core;
using namespace sc_dt;
using namespace std;
using namespace tlm;

#define FIFO_SIZE 16

#endif
