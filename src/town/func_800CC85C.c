#include "common.h"

typedef struct {
    u8 pad0[0x6C];
    u16 timer;
    u16 value;
    u16 pad70;
    u16 output;
} TownObject;

extern void func_800CA60C(void);
extern void func_800CA008(void);

void func_800C9FBC(TownObject *obj) {
    u16 timer;
    u16 value;

    timer = obj->timer - 1;
    obj->timer = timer;
    if ((timer << 16) <= 0) {
        func_800CA60C();
        value = obj->value + 0x800;
        ASM_TAILSLOT_PIN_TIED(value);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        func_800CA008();
        return;
    }
    obj->output += 0x100;
}

/* MECHANISM: The seed's 24-byte frame and s0-held object base were already exact.
   A guarded v0 value plus ASM_TAILSLOT_PIN_TIED lets LEAD 28 sink value+0x800
   into LEAD 22's tail-j delay; the live output RMW uses +0x100. */
