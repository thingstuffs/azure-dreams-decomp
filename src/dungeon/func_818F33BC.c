#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80024BBC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_80024BBC_0;   /* object in func_80024BBC */

typedef struct S_80024BBC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80024BBC_1;   /* arg0 in func_80024BBC */

typedef struct S_80024BBC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80024BBC_2;   /* dest1 in func_80024BBC */

typedef struct S_80024BBC_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80024BBC_3;   /* dest2 in func_80024BBC */

typedef struct S_80024BBC_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80024BBC_4;   /* dest3 in func_80024BBC */

typedef struct S_80024BBC_5 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0x1C];
    s32 unk_50;
} S_80024BBC_5;   /* base in func_80024BBC */

typedef struct S_80024BBC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024BBC_6;   /* ((S_80024BBC_1 *)arg0)->unk_08 in func_80024BBC */



extern void *func_8003FD64(s32, void *);
extern s32 rand(void);
extern void func_8004491C(void *, void *);
extern void func_80024B6C(void);
extern void func_800248EC(void);

void func_80024BBC(
    S_80024BBC_1 *arg0, s16 arg1, void *arg2, s16 arg3,
    s32 arg4, s32 arg5, s32 arg6)
{
    register s32 held_arg4 ASM_REG("$18") = arg4;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 held_arg5 ASM_REG("$19") = arg5;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 held_arg6 ASM_REG("$20") = arg6;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *object;
    S_80024BBC_5 *base;

    object = func_8003FD64(0x211, arg0);
    if (object != NULL) {
        s32 random1;
        s32 random2;
        s32 random3;
        s32 offset1;
        s32 offset2;
        s32 offset3;
        s32 value1;
        s32 value2;
        s32 value3;
        S_80024BBC_2 *dest1;
        S_80024BBC_3 *dest2;
        S_80024BBC_4 *dest3;

        ((S_80024BBC_0 *)object)->unk_10 = func_80024B6C;

        random1 = rand() & 0x1F;
        value1 = ((S_80024BBC_6 *)(arg0->unk_08))->unk_02;
        dest1 = ((S_80024BBC_0 *)object)->unk_08;
        value1 += random1;
        offset1 = held_arg4 - 0x10;
        value1 += offset1;
        dest1->unk_02 = value1;
        random2 = rand() & 0x1F;
        value2 = ((S_80024BBC_6 *)(arg0->unk_08))->unk_06;
        dest2 = ((S_80024BBC_0 *)object)->unk_08;
        value2 += random2;
        offset2 = held_arg5 - 0x10;
        value2 += offset2;
        dest2->unk_06 = value2;

        base = (u8 *)object + 0x20;
        random3 = rand() & 0x1F;
        value3 = ((S_80024BBC_6 *)(arg0->unk_08))->unk_0A;
        dest3 = ((S_80024BBC_0 *)object)->unk_08;
        value3 += random3;
        offset3 = held_arg6 - 0x10;
        value3 += offset3;
        dest3->unk_0A = value3;
        base->unk_14 = arg1;
        base->unk_32 = arg3;
        func_8004491C(object, func_800248EC);
        base->unk_50 = -0x2000;
        base->unk_08 = arg2;
        ASM_KEEP(held_arg4);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_KEEP(held_arg5);   /* MATCH pin: keeps a statement from moving across a call/branch */
        ASM_KEEP(held_arg6);   /* MATCH pin: load-bearing for the whole function shape */
    }
}

/* MECHANISM: The 0x38 frame and s2/s3/s4 stack-argument holds fall out of guarded pins.
   Separate random/value/destination/offset names give v1/a0/v0 one live range per field.
   Tail ASM_KEEPs prevent destructive saved-register updates without fencing call slots. */
