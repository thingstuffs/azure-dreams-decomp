#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();    /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800BB2E4(); /* extern */
M2C_UNK func_800C77D0(); /* extern */
extern M2C_UNK D_80083498;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800BB55C;
extern M2C_UNK D_800BBA20;
extern M2C_UNK D_800DF3C0;

typedef struct S_800BBA40_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800BBA40_0;   /* temp_v0 in func_800BBA40 */

typedef struct S_800BBA40_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BBA40_1;   /* temp_v1 in func_800BBA40 */

typedef struct S_800BBA40_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800BBA40_2;   /* temp_v1_2 in func_800BBA40 */

typedef struct S_800BBA40_3 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0xC];
    s16 unk_28;
    s16 unk_2A;
    u8 pad_2C[0x10];
    s16 unk_3C;
    u8 pad_3E[0x1E];
    s32 unk_5C;
    s32 unk_60;
} S_800BBA40_3;   /* var_v1 in func_800BBA40 */

void *func_800BBA40(s32 arg0, s32 arg1, s16 arg2, M2C_UNK arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 call_data[2];
    s16 var_a1;
    void *temp_v0;
    S_800BBA40_1 *temp_v1;
    S_800BBA40_2 *temp_v1_2;
    s32 held_arg0 = arg0;
    register s32 held_arg1 ASM_REG("$20") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 held_arg2 ASM_REG("$21") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register M2C_UNK held_arg3 ASM_REG("$22") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *setup_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    call_data[0] = 0x01000340;
    call_data[1] = 0x01000080;
    func_800BB2E4(0, 0, call_data, 1, 0);
    temp_v0 = func_8003FD64(0x12, &D_80083498);
    if (temp_v0 != NULL) {
        s32 var_a0;
        void *var_v1;

        func_800A56E0(0x704);
        ((S_800BBA40_0 *)temp_v0)->unk_10 = &D_800BB55C;
        func_8004491C(temp_v0, &D_800BBA20);
        temp_v1 = ((S_800BBA40_0 *)temp_v0)->unk_08;
        temp_v1->unk_02 = (s16) (((s32) (held_arg0 << 0x10) >> 0xA) + 0x20);
        temp_v1->unk_06 = (s16) (((s32) (held_arg1 << 0x10) >> 0xA) + 0x20);
        temp_v1->unk_0A = held_arg2;
        temp_v1_2 = ((S_800BBA40_0 *)temp_v0)->unk_0C;
        temp_v1_2->unk_08 = &D_800DF3C0;
        temp_v1_2->unk_1E = 0x1000;
        temp_v1_2->unk_1C = 0x1000;
        temp_v1_2->unk_0C = 0x808080;
        temp_v1_2->unk_06 = 8;
        func_8003DB94(temp_v0 + 0x2C, held_arg3, 0);
        ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg3);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        setup_base = temp_v0 + 0x20;
        ASM_KEEP(setup_base);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        var_v1 = setup_base;
        ((S_800BBA40_3 *)var_v1)->unk_2A = (s16) arg4;
        ((S_800BBA40_3 *)var_v1)->unk_28 = (s16) arg4;
        ((S_800BBA40_3 *)var_v1)->unk_18 = 0x808080;
        var_a1 = -0x400;
        ((S_800BBA40_3 *)var_v1)->unk_5C = arg5;
        var_a0 = 0;
        ((S_800BBA40_3 *)var_v1)->unk_60 = arg6;
        do {
            ((S_800BBA40_3 *)var_v1)->unk_3C = var_a1;
            var_a1 += 0x999;
            var_a0 += 1;
            ASM_KEEP(var_a0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            var_v1 += 2;
        } while (var_a0 < 5);
        ASM_KEEP(var_v1);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        func_800C77D0(&D_80083498, &D_80083780, 8, 0x300);
    }
    return temp_v0;
}

/* MECHANISM: A two-word stack array preserves both call-data initializers in the 0x40 frame.
   Guarded s2/s4/s5/s6 argument holds reproduce the callee-saved prologue order.
   A pinned v0 split base copies into v1; the pinned a0 counter blocks countdown strength reduction. */
