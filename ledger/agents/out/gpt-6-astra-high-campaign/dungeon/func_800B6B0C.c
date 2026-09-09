#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BC26C_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800BC26C_0;   /* result in func_800BC26C */

typedef struct S_800BC26C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
} S_800BC26C_1;   /* fields in func_800BC26C */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern u8 D_800BC388[9];
extern u8 D_800BC3E4[9];

/* Creates an object and initializes its owner, parameter, and mode-dependent fields. */
void *func_800BC26C(s32 owner, s32 mode, s32 param)
{
    void *object;
    u8 *fields;
    s32 initial_value;
    register s32 saved_mode ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    object = func_8003FD64(0x110, (void *)owner);
    if (object != NULL) {
        do { saved_mode = mode; } while (0);
        ASM_KEEP(saved_mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_800BC26C_0 *)object)->unk_10 = D_800BC388;
        func_8004491C(object, D_800BC3E4);
        fields = (u8 *)object + 0x20;
        ((S_800BC26C_0 *)object)->unk_20 = owner;
        ((S_800BC26C_1 *)fields)->unk_04 = param;
        if ((mode << 16) != 0) {
            initial_value = 0x7F80;
        } else {
            ASM_SCHED_BARRIER();
            initial_value = 0x7FC0;
        }
        ((S_800BC26C_1 *)fields)->unk_0C = initial_value;
        ((S_800BC26C_1 *)fields)->unk_0E = saved_mode;
    }
    return object;
}
