#include "header.h"


#define double LL
namespace kody_ll {
#include "geom.cpp"
#include "anglecmp.cpp"
#include "do_test.cpp"
}; // ns
#undef double

namespace kody_double {
#include "geom.cpp"
#include "anglecmp.cpp"
#include "do_test.cpp"
}; // ns


int main() {
    assert(kody_ll::EPS == 0);
    assert(kody_double::EPS > 1e-10 && kody_double::EPS < 1e-4);
    kody_ll::doTest();
    kody_double::doTest();
}
