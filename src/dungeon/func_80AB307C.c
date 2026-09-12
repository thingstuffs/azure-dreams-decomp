#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_8015887C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8015887C_0;   /* obj in func_8015887C */

typedef struct S_8015887C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015887C_1;   /* work in func_8015887C */

typedef struct S_8015887C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015887C_2;   /* part_a in func_8015887C */

typedef struct S_8015887C_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8015887C_3;   /* part_b in func_8015887C */

typedef struct S_8015887C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8015887C_4;   /* actor in func_8015887C */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_80158A50[];
extern M2C_UNK D_80158E7C;
extern u8 D_8015CC3C[];
extern u8 D_8015CC8C[];

void *func_8015887C(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    s32 kind;
    void *obj;
    S_8015887C_2 *part_a;
    S_8015887C_3 *part_b;
    S_8015887C_1 *work;
    S_8015887C_4 *actor;
    s32 left;
    s32 right;
    s8 saved_arg1;
    s16 saved_arg3;
    s8 saved_arg2;
    void *call_a0;
    void *call_a1;

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8015887C_0 *)obj)->unk_10 = D_80158A50;
        work->unk_13 = 0x8;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_8015887C_0 *)obj)->unk_08;
        part_a->unk_0A = saved_arg3;
        part_b = ((S_8015887C_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->unk_2C = D_8015CC3C;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = work->unk_14 | 0x2000;
        right = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = left;
        work->unk_1C = right;
        goto post_kind;

normal_kind:
        call_a0 = obj;
        if (((arg0 & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                call_a1 = part_a;
                ASM_KEEP(call_a0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_8015CC8C;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
        call_a0 = obj;
call_a1_setup:
        func_800A9C18(call_a0, part_a, part_b, arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80158E7C;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}

/* MECHANISM: Preserve the seed's exact 0x38 frame, s0-s7 holds, CFG, and true-base name.
   The work pointer is the retail object subobject at +0x20; part_b's byte field is +0x24. */
