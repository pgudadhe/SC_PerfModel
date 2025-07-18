#include <iostream>
#include "systemc.h"
#include "platform_top.h"

using namespace std;

int sc_main(int argc, char* argv[])
{
    cout << "Hello World..." << endl;
    platform_top Top("top");
    sc_start();
    return 0;
}