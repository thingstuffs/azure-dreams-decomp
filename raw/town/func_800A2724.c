#include "common.h"

extern u32 func_8009FD68();
extern void *D_8001029C;

void func_8009FE84(void) {
    void **entry;
    u8 *object;
    s32 expected;
    u32 table_base;

    if (D_8001029C != 0) {
        expected = 0x13;
        
        table_base = 0x800102F0;
        
        entry = (void **)0x8001029C;
        do {
            object = *entry;
            if (object[1] == expected) {
                func_8009FD68((void *)((object[3] & 0x1F) * 84 + table_base));
            }
            entry++;
        } while (*entry != 0);
    }
}

/* MECHANISM: Guarded s2/s1 carriers force the retail preheader order: tag 19, then 0x800102F0.
   A literal 0x8001029C iterator base selects lui/ori, and byte-offset-plus-base preserves addu order.
   The natural s0 iterator retains the 0x20 frame and ra/s2/s1/s0 save contract. */
