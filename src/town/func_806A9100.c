#include "common.h"
#include "shared/town_root.h"
#include "shared/record_ptrs.h"


typedef void (*Callback)(u32);




extern u8 D_80017420[];
extern void *D_800174D4[];

/* Sets D_800174D4[0] to D_80017420 and invokes both object callbacks with 1. */
void func_806A9100(void) {
    Callback firstCallback;

    firstCallback = ((Callback)D_80016000->unk_20->callback_28C);
    D_800174D4[0] = D_80017420;
    firstCallback(1);
    ((Callback)D_80016000->unk_20->callback_290)(1);
}
