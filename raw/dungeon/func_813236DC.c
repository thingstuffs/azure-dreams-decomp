#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FD64();
extern void func_80042640();
extern void func_8004491C();
extern void func_800A152C();
extern s8 func_800A6DA4();
extern void func_800A9C18();
extern void func_800AA36C();
extern void func_8016AFCC() __attribute__((noreturn));
extern void *func_8016F160();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8016B0E8[];
extern s32 D_8016B778;
extern u8 D_8017467C[];
extern u8 *D_80174704;

void *func_8016AEDC(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    register s32 held_arg0 ASM_REG("$22");
    register u8 *work_copy ASM_REG("$21");
    register s32 one ASM_REG("$2");
    register s32 reload ASM_REG("$8");
    s32 held_arg1;
    register s32 held_arg2 ASM_REG("$23");
    u8 *object;
    register u8 *work ASM_REG("$17");
    u8 *part_a;
    u8 *part_b;
    u8 *callback;
    u8 *spawned;
    s32 mode;
    volatile u16 saved_arg3;

    work = 0;
    held_arg1 = arg1;
    held_arg2 = arg2;
    object = func_8003FD64(0x112, D_80083498);
    held_arg0 = arg0;
    *(u16 *)&saved_arg3 = arg3;
    if (object != 0) {
        work = object + 0x20;
        ASM_KEEP_NV(work);
        D_80174704 = object;
        FIELD(object, u8 *, 0x10) = D_8016B0E8;
        FIELD(work, s8, 0x13) = 0x31;
        func_8004491C(object, &D_80045340);

        callback = D_8017467C;
        do { part_a = FIELD(object, u8 *, 8); } while (0);
        do { work_copy = work; } while (0);
        ASM_KEEP_NV(work_copy);
        FIELD(part_a, s16, 0xA) = arg3;
        do { part_b = FIELD(object, u8 *, 0xC); } while (0);
        do { mode = arg0 & 3; } while (0);
        FIELD(part_b, u8 *, 0x2C) = callback;
        FIELD(part_b, s8, 0x24) = held_arg1;

        one = 1;
        ASM_KEEP_NV(one);
        FIELD(part_b, s8, 0x25) = held_arg2;
        if (mode == one) {
            register u32 tail_v0 ASM_REG("$2") = FIELD(work, u32, 0x14) | 0x6000;
            register u32 tail_v1 ASM_REG("$3") = FIELD(work, u32, 0x1C) | 0x6000;
            ASM_KEEP(tail_v0);
            ASM_TAILSLOT_PIN(tail_v1);
            func_8016AFCC();
        }
        if (mode >= 2) {
            FIELD(work, u32, 0x14) |= 0x2000;
            FIELD(work, u32, 0x1C) |= 0x2000;
        }

        func_800A9C18(object, part_a, part_b, (s16)held_arg0);
        {
            register u8 *a0_copy ASM_REG("$4") = work_copy;
            register u8 *a1_copy ASM_REG("$5") = part_a;
            register u8 *a2_copy ASM_REG("$6") = part_b;
            ASM_KEEP_NV(a0_copy);
            ASM_KEEP_NV(a1_copy);
            ASM_KEEP_NV(a2_copy);
            FIELD(a0_copy, u8, 0x9A) = 0xFF;
            FIELD(a0_copy, s8, 0x9C) = -1;
            FIELD(a0_copy, s32 *, 0x8C) = &D_8016B778;
            FIELD(a0_copy, s16, 0xAE) = 0;
            FIELD(a0_copy, s8, 0xB4) = 0;
            FIELD(a0_copy, s8, 0xB0) = 0;
            FIELD(a2_copy, u16, 0x14) |= 0x80;
            func_800AA36C(a0_copy, a1_copy, a2_copy, work);
        }
        FIELD(work, s8, 0x49) = 0xE;
        FIELD(work, s8, 0x48) = 3;
        FIELD(work, s8, 0x4A) = func_800A6DA4(0x10, 0x18);
        FIELD(work, s8, 0x4B) = 1;
    }

    {
        register s32 spawn_arg0 ASM_REG("$4");
        register s32 spawn_arg1 ASM_REG("$5");
        register s32 spawn_arg2 ASM_REG("$6");

        spawn_arg0 = (s16)held_arg0;
        spawn_arg1 = (s16)(held_arg1 + 1);
        ASM_SCHED_BARRIER();
        spawn_arg2 = (s32)((u32)held_arg2 << 16);
        reload = saved_arg3;
        ASM_KEEP_NV(reload);
        spawn_arg2 >>= 16;
        spawned = func_8016F160(spawn_arg0, spawn_arg1, spawn_arg2, (s16)reload);
    }
    ASM_KEEP(held_arg0);
    func_800A152C(FIELD(spawned, u8, 0x13), 1);
    func_80042640(spawned, FIELD(spawned, u8, 0x13));
    FIELD(spawned, u8, 0x43) = 0xFF;
    FIELD(spawned, s8, 0x12) = 0;
    return work;
}
