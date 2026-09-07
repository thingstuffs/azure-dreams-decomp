#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800353F4(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_80164BA4(void *);
extern void func_8016BEFC() __attribute__((noreturn));
extern void func_8016C048(void) __attribute__((noreturn));
extern void func_8016C0E0(void) __attribute__((noreturn));

extern u16 D_80013714;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_800E3D7C[];
extern u8 D_8016A36C[];
extern u8 D_801739B8[];
extern u8 D_80173A40[];
extern u8 D_80175392[];
extern u8 D_80175DC0;
extern u8 D_80175DC1;
extern void *D_80164948[];

void func_8016BE20(void *arg0, void *arg1, void *arg2, void *arg3)
{
    void *state = arg0;
    void *work = arg1;
    void *actor = arg2;
    void *ctx = arg3;
    u8 *world;
    u8 *table;
    u8 *control;
    u8 *header;
    void *object;
    register void *setup ASM_REG("$4");
    register u32 mask ASM_REG("$20");
    register s32 i ASM_REG("$17");
    u16 timer;
    u16 flags;
    u16 control_count;
    u8 state_index;

    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5
    };

    (void)jt_keep;
    state_index = FIELD(state, u8, 0x9B);
    if ((u32)state_index >= 6) {
        return;
    }
    goto *D_80164948[(u32)state_index];

jt_c0:
        FIELD(work, s32, 0x14) = 0;
        FIELD(work, s32, 0x10) = 0;
        FIELD(work, s32, 0x0C) = 0;
        FIELD(state, s16, 0x96) = 0;
        FIELD(state, u8, 0x9B)++;
        D_80175DC1 = 0;
        return;

jt_c1:
        if (D_80175DC1 == 0) {
            FIELD(state, s16, 0x96) = 0;
            FIELD(state, u8, 0x9B)++;
            func_8016BEFC(arg0, D_80173A40);
        }
        if (D_80175DC0 == 0) {
            return;
        }
        FIELD(state, s16, 0x96) = 0;
        FIELD(state, u8, 0x9B)++;
        func_800A56E0(0x300);
        FIELD(actor, u8 *, 0x2C) = D_80173A40;
        func_80047784(actor,
            D_80173A40[((D_80083228 + FIELD(ctx, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        return;

jt_c2:
        timer = FIELD(state, u16, 0x96) + 1;
        FIELD(state, u16, 0x96) = timer;
        if ((s16)timer == 0x11) {
            func_8009C12C(ctx, actor, FIELD(ctx, s16, 0x2A), 1);
            FIELD(state, s16, 0x96) = 0;
            FIELD(state, u8, 0x9B)++;
        }
        if (FIELD(state, s16, 0x96) != 0xF) {
            return;
        }
        func_800A56E0(0x804);
        return;

jt_c3:
        if (!(FIELD(actor, u16, 0x14) & 0xE000)) {
            return;
        }
        table = D_801739B8;
        if (FIELD(actor, u8 *, 0x2C) != table) {
            FIELD(actor, u8 *, 0x2C) = table;
            func_80047784(actor,
                table[((D_80083228 + FIELD(ctx, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }
        if (D_80175DC1 != 0) {
            (void)FIELD(state, volatile u8, 0x9B);
            FIELD(state, s16, 0x96) = 0;
            func_8016C048();
        }
        FIELD(state, u8, 0x9B) += 2;
        return;

jt_c4:
        timer = FIELD(state, u16, 0x96) + 1;
        FIELD(state, u16, 0x96) = timer;
        if ((s16)timer < 0x28) {
            return;
        }
        FIELD(state, u8, 0x9B)++;
        return;

jt_c5:
        world = *(u8 **)D_800E3D7C;
        if (FIELD(world, u8, 0x28) >= 2) {
            goto case5_failure;
        }
        if (FIELD(ctx, void *, 0x60) != world) {
            goto case5_failure;
        }

        setup = D_80175392;
        FIELD(state, u8 *, 0x8C) = D_8016A36C;
        control = (u8 *)&D_80083460;
        control_count = FIELD(control, u16, 0x0A);
        ASM_SCHED_BARRIER();
        i = 0;
        ASM_KEEP_NV(i);
        FIELD(control, s32, 0x0C) = 0;
        control_count++;
        FIELD(control, u16, 0x0A) = control_count;
        FIELD(ctx, u16, 0x46) &= 0x7FFF;
        flags = D_80013714;
        ASM_SCHED_BARRIER();
        mask = 0x80000000;
        ASM_USE(mask);
        D_80013714 = flags | 8;
        func_800353F4(setup, work);
        FIELD(ctx, u8, 0x6D) = 0;
        FIELD(state, u8, 0x9B) = 0;

        object = FIELD(*(u8 **)D_800E3D7C, void *, 0xAC + i * 4);
        if (object != 0) {
            func_80164BA4(object);
            header = (u8 *)FIELD(*(u8 **)D_800E3D7C,
                void *, 0xAC + i * 4) - 0x20;
            FIELD(header, u32, 0x10) |= mask;
        }
        ASM_SET(mask);
        i++;
        if (i >= 2) {
            return;
        }
        ASM_USE_NV(i);
        func_8016C0E0();

case5_failure:
        FIELD(state, u8 *, 0x8C) = D_8016A36C;
        D_8008346C = 0;
        func_800A4ACC(ctx);
        FIELD(ctx, u16, 0x46) &= 0x7FFF;
        return;
}
