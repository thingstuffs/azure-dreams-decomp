#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_800B23F8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800B23F8_0;   /* obj in func_800B23F8 */

typedef struct S_800B23F8_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_800B23F8_1;   /* work in func_800B23F8 */

typedef struct S_800B23F8_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B23F8_2;   /* part_a in func_800B23F8 */

typedef struct S_800B23F8_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x18];
    s8 unk_24;
    s8 unk_25;
} S_800B23F8_3;   /* (void *)reg_s2 in func_800B23F8 */

typedef struct S_800B23F8_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_800B23F8_4;   /* (void *)reg_s3 in func_800B23F8 */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800B22F0(void *, void *, void *, s16);
extern u8 D_80045340;
extern s32 D_80083498;
extern M2C_UNK D_800B274C;
extern M2C_UNK D_800B2A60;

void *func_800B23F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                    volatile s32 arg4)
{
    s32 saved_arg0;
    register s32 saved_arg1 ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    long reg_s2;
    long reg_s3;
    register s32 call_a0 ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *call_a1 ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 kind;
    s32 test_v0;
    s32 left;
    s32 right;
    void *part_a;
    void *obj;
    void *work;
    s16 call_arg3;

    saved_arg0 = arg0;
    work = 0;
    call_a0 = 0x112;
    saved_arg1 = arg1;
    call_a1 = &D_80083498;
    reg_s2 = arg3;
    reg_s3 = arg2;
    ASM_KEEP_NV(call_a0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_NV(call_a1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    obj = func_8003FD64(call_a0, call_a1);
    if (obj != 0) {
        call_arg3 = saved_arg0;
        work = (u8 *)obj + 0x20;
        ASM_KEEP(work);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ((S_800B23F8_0 *)obj)->unk_10 = &D_800B274C;
        ((S_800B23F8_1 *)work)->unk_13 = 0x1E;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_800B23F8_0 *)obj)->unk_08;
        kind = saved_arg0 & 3;
        ((S_800B23F8_2 *)part_a)->unk_0A = (s16)reg_s2;
        ASM_KEEP(kind);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        reg_s2 = (long)((S_800B23F8_0 *)obj)->unk_0C;
        test_v0 = 1;
        ((S_800B23F8_3 *)((void *)reg_s2))->unk_25 = (s8)reg_s3;
        reg_s3 = (long)work;
        ((S_800B23F8_3 *)((void *)reg_s2))->unk_24 = saved_arg1;

        if (kind == test_v0) {
            left = ((S_800B23F8_1 *)work)->unk_14 | 0x6000;
            right = ((S_800B23F8_1 *)work)->unk_1C | 0x6000;
            goto write_kind;
        }
        test_v0 = kind < 2;
        if (test_v0) {
            goto post_kind;
        }
        left = ((S_800B23F8_1 *)work)->unk_14 | 0x2000;
        right = ((S_800B23F8_1 *)work)->unk_1C | 0x2000;
write_kind:
        ((S_800B23F8_1 *)work)->unk_14 = left;
        ((S_800B23F8_1 *)work)->unk_1C = right;

post_kind:
        func_800B22F0(obj, part_a, (void *)reg_s2, call_arg3);
        ((S_800B23F8_4 *)((void *)reg_s3))->unk_9A = 0xFF;
        ((S_800B23F8_4 *)((void *)reg_s3))->unk_9C = -1;
        (*(M2C_UNK * *)((u8 *)((void *)reg_s3) + 0x8C)) = &D_800B2A60;
        ((S_800B23F8_3 *)((void *)reg_s2))->unk_08 = arg4;
    }
    return work;
}

/* MECHANISM: Guarded a0/a1 entry locals order retail's s4/s1/s5/s2/s3 saves;
   carrier pins split s2 arg3-to-part_b and s3 arg2-to-actor lifetimes.
   The u8 0xFF then s8 -1 stores preserve retail's distinct constant loads. */
