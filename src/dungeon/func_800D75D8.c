#include "common.h"

typedef struct {
    u8 pad_00[0x38];
    s32 *field_38;
    u8 field_3C[1];
} ObjectHeader;

extern void *func_8003FC64(s32);
extern s32 func_8004B404(s32);
extern void func_8004491C(void *, void *);
extern void func_800DC988(void *);
extern s32 func_800DCBE4(void *, s32);
extern void func_800DCCF4(void *, s32);
extern s32 D_800133A0[];
extern u8 D_8004CAA0[];
extern s32 D_800814A0;
extern u8 D_800DC8F8[];
extern void *D_800E5910[];

void *func_800DCD38(void) {
    s32 allocation;
    register ObjectHeader *header ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 *statusPage;
    s32 *source;
    u8 *data;
    u8 *object;

    object = func_8003FC64(0);
    if (object != 0) {
        D_800E5910[0] = object;
        allocation = func_8004B404(0x100);
        if (allocation != 0) {
            header = (ObjectHeader *)(object + 0x20);
            ASM_KEEP(header);   /* MATCH pin: retail schedule: same instructions, different order without it */
            data = object + 0x5C;
            func_800DCCF4(data, allocation);
            source = (s32 *)0x800133A0;
            header->field_38 = source;
            *(s32 *)(object + 0xC) = func_800DCBE4(data, source[0]);
            func_800DC988(object);
            *(u8 **)(object + 0x10) = D_800DC8F8;
            func_8004491C(object, D_8004CAA0);
            return object;
        }
        *(u16 *)(object + 0x1E) |= 0x8000;
        statusPage = (s32 *)0x80080000;
        object = 0;
        statusPage[0x528] |= 0x8000;
    }
    return object;
}

/* MECHANISM: The guarded object+0x20 header occupies s2 while object+0x5c
   occupies s0; the 0x80080000 page local retains v1 for the status RMW.
   A literal 0x800133A0 pointer yields retail's v0 lui/ori and delay-slot store.
   The void dispatcher call returns the held object through the tail-j delay. */
