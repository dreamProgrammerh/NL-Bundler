#define NLC_IMPLEMENTATION 1
#include "nlc.h"

i32 main(i32 argc, ch* args[]) {
    // Silence unused warning
    (void)argc;
    (void)args;
    
    log_info("NL", "Hi to the World, im here!!!!");
    log_info("NL", "Version: %s", NLC_VERSION);
    log_info("NL", "Arch: %d-bit", ARCH_bits);
    return 0;
}