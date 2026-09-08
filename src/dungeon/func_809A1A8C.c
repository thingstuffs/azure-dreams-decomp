#include "common.h"

#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80173420(void) __attribute__((noreturn));
extern void func_80173438(void) __attribute__((noreturn));
extern void func_801734E8(void) __attribute__((noreturn));

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228[];
extern s32 D_8008346C[];
extern u8 D_801710EC[];
extern u8 D_80175E88[];
extern u8 D_80175EB8[];

void func_8017328C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 delta_x;
    s32 delta_y;
    s32 table_off;
    s32 table_idx;
    s32 object_type;
    register s32 count ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    s32 next_count;
    u16 flags;
    s32 state;

    state = U8(arg0, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state >= 2) {
        goto state_two_test;
    }
    if (state == 0) {
        goto state_zero;
    }
    return;

state_two_test:
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
{
    u8 *byte_table;
    u8 *phase_page;

    flags = U16(arg2, 0x14);
    if (flags & 0x8000) {
        U16(arg2, 0x14) = flags | 0x6000;
        U8(arg0, 0x9B) = 2;
        func_8009C12C(arg3, arg2, S16(arg3, 0x2A), 1);
        return;
    }
       /* MATCH pin: retail basic-block layout depends on it */
    if ((flags & 0x6000) == 0) {
        goto done;
    }
    byte_table = (u8 *)0x80170000;
    if (S16(arg0, 0x92) != 0) {
        goto done;
    }
    ASM_KEEP_NV(byte_table);   /* MATCH pin: keeps a constant in a register as retail does */
    byte_table += 0x5E88;
    phase_page = (u8 *)0x80080000;
    ASM_KEEP(phase_page);   /* MATCH pin: retail schedule: same instructions, different order without it */
    PTR(arg2, 0x2C) = byte_table;
    table_idx = (*(s16 *)(phase_page + 0x3228) + S16(arg3, 0x2A) + 0x100) >> 9;
    table_idx &= 7;
    phase_page = (u8 *)(table_idx + (s32)byte_table);
    func_80047784(arg2, *phase_page, 0);
    U16(arg0, 0x96) = 0;
    func_800A56E0(0x808);
    func_801734E8();
}

state_one:
{
    register u8 *direction_base ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 active_x;
    s32 active_y;
    s32 limit;
    s32 raw_y;

    direction_base = (u8 *)0x80070000;
    ASM_KEEP_NV(direction_base);   /* MATCH pin: load-bearing for the whole function shape */
    count = U16(arg0, 0x96);
    direction_base -= 0x3328;
    next_count = count + 1;
    count -= 3;
    U16(arg0, 0x96) = next_count;
    table_off = (U16(arg3, 0x2A) >> 8) & 0xE;
    count = (u32)count < 8U;
    direction_base = (u8 *)(table_off + (s32)direction_base);
    ASM_KEEP_NV(direction_base);   /* MATCH pin: load-bearing for the whole function shape */
    delta_x = *(s16 *)direction_base;
    direction_base = (u8 *)0x80070000;
    ASM_KEEP_NV(direction_base);   /* MATCH pin: load-bearing for the whole function shape */
    direction_base -= 0x3318;
    table_off = table_off + (s32)direction_base;
    raw_y = *(s16 *)table_off;
    delta_x = -delta_x;
    delta_x <<= 16;
    raw_y = -raw_y;
    delta_y = raw_y << 16;
    if (count) {
        active_x = S32(arg1, 0xC) - delta_x;
        active_y = S32(arg1, 0x10) - delta_y;
        ASM_KEEP(active_x);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ASM_TAILSLOT_PIN_TIED(active_y);   /* MATCH pin: load-bearing for the whole function shape */
        func_80173420();
    }
    limit = (s16)next_count;
    if (limit < 0x12) {
        S32(arg1, 0xC) += delta_x;
        S32(arg1, 0x10) += delta_y;
        func_80173438();
    }
    ASM_CLOBBER("$5");   /* MATCH pin: load-bearing for the whole function shape */
    S32(arg1, 0x14) = 0;
    S32(arg1, 0x10) = 0;
    S32(arg1, 0xC) = 0;
    object_type = S8(arg2, 4);
    if (object_type == 5) {
        if (U16(arg2, 0x14) & 0x1000) {
            goto call_c12c;
        }
    }
    if ((U16(arg2, 0x14) & 0x8000) == 0) {
        goto after_c12c;
    }
call_c12c:
    func_8009C12C(arg3, arg2, S16(arg3, 0x2A), 1);
after_c12c:
    {
        u8 *byte_table;
        u8 *phase_page;

        byte_table = (u8 *)0x80170000;
        if ((U16(arg2, 0x14) & 0xE000) == 0) {
            goto done;
        }
        ASM_KEEP_NV(byte_table);   /* MATCH pin: keeps a constant in a register as retail does */
        byte_table += 0x5EB8;
        phase_page = (u8 *)0x80080000;
        ASM_KEEP(phase_page);   /* MATCH pin: retail schedule: same instructions, different order without it */
        PTR(arg2, 0x2C) = byte_table;
        table_idx = (*(s16 *)(phase_page + 0x3228) + S16(arg3, 0x2A) + 0x100) >> 9;
        table_idx &= 7;
        phase_page = (u8 *)(table_idx + (s32)byte_table);
        func_80047784(arg2, *phase_page, 0);
    }
    S32(arg1, 0x14) = 0;
    S32(arg1, 0x10) = 0;
    S32(arg1, 0xC) = 0;
    func_800A2B04(arg1, U8(arg2, 0x24), U8(arg2, 0x25));
    U8(arg0, 0x9B)++;
    return;
}

state_two:
{
    u8 *global_page;

    if ((U16(arg2, 0x14) & 0xE000) == 0) {
        goto done;
    }
    func_800AD594(arg3, 0x100);
    PTR(arg0, 0x8C) = D_801710EC;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    global_page = (u8 *)0x80080000;
    ASM_KEEP(global_page);   /* MATCH pin: retail register colouring depends on it */
    S32(global_page, 0x346C) = 0;
    U16(arg3, 0x46) &= 0x7FFF;
    func_800A4ACC(arg3);
}

done:
    return;
}
