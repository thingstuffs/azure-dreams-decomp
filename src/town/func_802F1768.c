#include "common.h"

s32 func_804087B8(void);
s32 func_804087C8(void);
s32 func_80408958(void);

/* Run the three callbacks in sequence. */
void run_memory_callbacks(void) {
    func_804087B8();
    func_80408958();
    func_804087C8();
}
