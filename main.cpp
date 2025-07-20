#include <iostream>
#include "systemc.h"
#include "platform_top.h"

using namespace std;

int sc_main(int argc, char *argv[])
{
    cout << "Interconnect Bus Performance Model running..." << endl;
    platform_top Top("top");
    sc_start(4, SC_SEC);
    return 0;
}