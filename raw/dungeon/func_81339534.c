/* cfail-repair: recovered external dispatch table */
#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800419EC(s32, s32);
extern void func_800A56E0(u32);
extern void func_801705EC(void) __attribute__((noreturn));
extern void func_80170690(void) __attribute__((noreturn));
extern void func_801706E8(void) __attribute__((noreturn));
extern void *jtbl_80164A38[];
__asm__(".set jtbl_80164A38, 0x80164A38");
extern s32 D_800814A0[3];
extern s16 D_801760D8[5];

void func_80170534(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = {
        &&state_end, &&state_1, &&state_2, &&state_end, &&state_4
    };
    register void *state ASM_REG("$17") = arg0;
    register void *input ASM_REG("$16");
    void * volatile *table;
    s32 temp_v1;
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v1 = M2C_FIELD(state, s16 *, 0x12);
    if ((u32) temp_v1 >= 5) {
        goto state_end;
    }
    input = arg2;
    ASM_KEEP(input);
    table = jtbl_80164A38;
    (void)jt_keep;
    goto *table[(u32) temp_v1];

state_1:
    temp_v0 = M2C_FIELD(state, u16 *, 0x18) + 1;
    M2C_FIELD(state, u16 *, 0x18) = temp_v0;
    if (!(temp_v0 & 3)) {
        func_800419EC(6, 0xC);
        func_800A56E0(0x818);
    }
    if (!(M2C_FIELD(state, u16 *, 0x18) & 7)) {
        temp_v1 = 0xFF;
        if (M2C_FIELD(input, u8 *, 0xC) != temp_v1) {
            M2C_FIELD(input, s8 *, 0xE) = temp_v1;
            M2C_FIELD(input, s8 *, 0xD) = temp_v1;
            M2C_FIELD(input, u8 *, 0xC) = temp_v1;
            func_801705EC();
        }
        temp_v0 = 0x80;
        M2C_FIELD(input, u8 *, 0xE) = temp_v0;
        M2C_FIELD(input, u8 *, 0xD) = temp_v0;
        M2C_FIELD(input, u8 *, 0xC) = temp_v0;
    }
    if ((s16) M2C_FIELD(state, u16 *, 0x18) == 0x28) {
#ifdef NON_MATCHING
        D_801760D8[0] = 1;
#else
        {
            register u8 *flag_page ASM_REG("$3") = (u8 *) 0x80170000;
            ASM_KEEP(flag_page);
            *(u16 *)(flag_page + 0x60D8) = 1;
        }
#endif
    }
    if ((s16) M2C_FIELD(state, u16 *, 0x18) >= 0x28) {
        temp_v0 = M2C_FIELD(state, u16 *, 0x12) + 1;
        M2C_FIELD(state, u16 *, 0x12) = temp_v0;
        func_801706E8();
    }
    goto state_end;

state_2:
    temp_v0_2 = M2C_FIELD(state, u16 *, 0x18) + 1;
    M2C_FIELD(state, u16 *, 0x18) = temp_v0_2;
    if (!(temp_v0_2 & 3)) {
        func_800A56E0(0x818);
    }
    if (!(M2C_FIELD(state, u16 *, 0x18) & 7)) {
        temp_v1 = 0xFF;
        if (M2C_FIELD(input, u8 *, 0xC) != temp_v1) {
            M2C_FIELD(input, s8 *, 0xE) = temp_v1;
            M2C_FIELD(input, s8 *, 0xD) = temp_v1;
            M2C_FIELD(input, u8 *, 0xC) = temp_v1;
            func_80170690();
        }
        temp_v0 = 0x80;
        M2C_FIELD(input, u8 *, 0xE) = temp_v0;
        M2C_FIELD(input, u8 *, 0xD) = temp_v0;
        M2C_FIELD(input, u8 *, 0xC) = temp_v0;
    }
    if ((s16) M2C_FIELD(state, u16 *, 0x18) >= 0x3C) {
        M2C_FIELD(state, u16 *, 0x18) = 0U;
        M2C_FIELD(state, s16 *, 0x12) = (s16) ((u16) M2C_FIELD(state, s16 *, 0x12) + 1);
        M2C_FIELD(input, u8 *, 0xE) = 0x80;
        M2C_FIELD(input, u8 *, 0xD) = 0x80;
        M2C_FIELD(input, u8 *, 0xC) = 0x80;
        func_801706E8();
    }
    goto state_end;

state_4:
    {
        register u8 *page ASM_REG("$3");
        u16 flags = M2C_FIELD(state, u16 *, -2);
        ASM_SCHED_BARRIER();
        page = (u8 *) 0x80080000;
        ASM_KEEP(page);
        flags = (u16) (flags | 0x8000);
        M2C_FIELD(state, u16 *, -2) = flags;
#ifdef NON_MATCHING
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
#else
        *(s32 *)(page + 0x14A0) |= 0x8000;
#endif
    }

state_end:
    ;
}
