#include "common.h"

s32 func_8006A084(void);
s32 func_8006A094(void);
s32 func_8006A248(u32);

/* Bracket command 0xF2000002 with setup and completion calls. */
void card_boot_start_hardware_counter(void) {
    func_8006A084();
    func_8006A248(0xF2000002);
    func_8006A094();
}
