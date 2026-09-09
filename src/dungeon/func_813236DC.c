#include "common.h"

typedef struct S_8016AEDC_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    u8 * unk_10;
} S_8016AEDC_0;   /* object in func_8016AEDC */

typedef struct S_8016AEDC_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x28];
    s8 unk_48;
    s8 unk_49;
    s8 unk_4A;
    s8 unk_4B;
} S_8016AEDC_1;   /* work in func_8016AEDC */

typedef struct S_8016AEDC_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016AEDC_2;   /* part_a in func_8016AEDC */

typedef struct S_8016AEDC_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8016AEDC_3;   /* part_b in func_8016AEDC */

typedef struct S_8016AEDC_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    s16 unk_AE;
    s8 unk_B0;
    u8 pad_B1[0x3];
    s8 unk_B4;
} S_8016AEDC_4;   /* a0_copy in func_8016AEDC */

typedef struct S_8016AEDC_5 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016AEDC_5;   /* a2_copy in func_8016AEDC */

typedef struct S_8016AEDC_6 {
    u8 pad_00[0x12];
    s8 unk_12;
    u8 unk_13;
    u8 pad_14[0x2F];
    u8 unk_43;
} S_8016AEDC_6;   /* spawned in func_8016AEDC */



extern void *func_8003FD64();
extern void func_80042640();
extern void func_8004491C();
extern void func_800A152C();
extern s8 func_800A6DA4();
extern void func_800A9C18();
extern void func_800AA36C();
extern void *func_8016F160();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8016B0E8[];
extern s32 D_8016B778;
extern u8 D_8017467C[];
extern u8 *D_80174704;

/* Initialize an actor and its companion, then return the actor work area. */
void *func_8016AEDC(s32 mode_flags, s32 config_24, s32 config_25, s32 config_0a)
{
    register s32 saved_mode ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u8 *work_copy;
    register s32 spawn_config_0a ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 saved_config_24;
    register s32 saved_config_25 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *object;
    u8 *work;
    u8 *part_a;
    u8 *part_b;
    u8 *callback;
    u8 *spawned;
    s32 mode_kind;
    volatile u16 saved_config_0a;

    work = 0;
    saved_config_24 = config_24;
    saved_config_25 = config_25;
    object = func_8003FD64(0x112, D_80083498);
    saved_mode = mode_flags;
    *(u16 *)&saved_config_0a = config_0a;
    if (object != 0) {
        work = object + 0x20;
        D_80174704 = object;
        ((S_8016AEDC_0 *)object)->unk_10 = D_8016B0E8;
        ((S_8016AEDC_1 *)work)->unk_13 = 0x31;
        func_8004491C(object, &D_80045340);

        callback = D_8017467C;
        do { part_a = ((S_8016AEDC_0 *)object)->unk_08; } while (0);
        work_copy = work;
        ((S_8016AEDC_2 *)part_a)->unk_0A = config_0a;
        part_b = ((S_8016AEDC_0 *)object)->unk_0C;
        do { mode_kind = mode_flags & 3; } while (0);
        ((S_8016AEDC_3 *)part_b)->unk_2C = callback;
        ((S_8016AEDC_3 *)part_b)->unk_24 = saved_config_24;

        ((S_8016AEDC_3 *)part_b)->unk_25 = saved_config_25;
        if (mode_kind == 1) {
            ((S_8016AEDC_1 *)work)->unk_14 |= 0x6000;
            ((S_8016AEDC_1 *)work)->unk_1C |= 0x6000;
        } else if (mode_kind >= 2) {
            ((S_8016AEDC_1 *)work)->unk_14 |= 0x2000;
            ((S_8016AEDC_1 *)work)->unk_1C |= 0x2000;
        }

        func_800A9C18(object, part_a, part_b, (s16)saved_mode);
        {

            ((S_8016AEDC_4 *)work_copy)->unk_9A = 0xFF;
            ((S_8016AEDC_4 *)work_copy)->unk_9C = -1;
            ((S_8016AEDC_4 *)work_copy)->unk_8C = &D_8016B778;
            ((S_8016AEDC_4 *)work_copy)->unk_AE = 0;
            ((S_8016AEDC_4 *)work_copy)->unk_B4 = 0;
            ((S_8016AEDC_4 *)work_copy)->unk_B0 = 0;
            ((S_8016AEDC_5 *)part_b)->unk_14 |= 0x80;
            func_800AA36C(work_copy, part_a, part_b, work);
        }
        ((S_8016AEDC_1 *)work)->unk_49 = 0xE;
        ((S_8016AEDC_1 *)work)->unk_48 = 3;
        ((S_8016AEDC_1 *)work)->unk_4A = func_800A6DA4(0x10, 0x18);
        ((S_8016AEDC_1 *)work)->unk_4B = 1;
    }

    {
        s32 spawn_mode;
        s32 spawn_config_24;
        s32 spawn_config_25;

        spawn_mode = (s16)saved_mode;
        spawn_config_24 = (s16)(saved_config_24 + 1);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        spawn_config_25 = (s32)((u32)saved_config_25 << 16);
        spawn_config_0a = saved_config_0a;
        ASM_KEEP_NV(spawn_config_0a);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        spawn_config_25 >>= 16;
        spawned = func_8016F160(spawn_mode, spawn_config_24, spawn_config_25, (s16)spawn_config_0a);
    }
    ASM_KEEP(saved_mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    func_800A152C(((S_8016AEDC_6 *)spawned)->unk_13, 1);
    func_80042640(spawned, ((S_8016AEDC_6 *)spawned)->unk_13);
    ((S_8016AEDC_6 *)spawned)->unk_43 = 0xFF;
    ((S_8016AEDC_6 *)spawned)->unk_12 = 0;
    return work;
}
