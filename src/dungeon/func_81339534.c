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


typedef struct S_80170534_0_pre {
    u16 unk_00;
} S_80170534_0_pre;   /* the 0x2 bytes before state in func_80170534, addressed as state[-1] */

typedef struct S_80170534_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x4];
    u16 unk_18;
} S_80170534_0;   /* state in func_80170534 */

typedef struct S_80170534_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    union { s8 s; u8 u; } unk_0D;   /* accessed as both */
    union { s8 s; u8 u; } unk_0E;   /* accessed as both */
} S_80170534_1;   /* input in func_80170534 */

void func_80170534(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = {
        &&state_end, &&state_1, &&state_2, &&state_end, &&state_4
    };
    void *state = arg0;
    void *input;
    void * volatile *table;
    s32 temp_v1;
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v1 = ((S_80170534_0 *)state)->unk_12.s;
    if ((u32) temp_v1 >= 5) {
        goto state_end;
    }
    input = arg2;
    ASM_KEEP(input);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    table = jtbl_80164A38;
    (void)jt_keep;
    goto *table[(u32) temp_v1];

state_1:
    temp_v0 = ((S_80170534_0 *)state)->unk_18 + 1;
    ((S_80170534_0 *)state)->unk_18 = temp_v0;
    if (!(temp_v0 & 3)) {
        func_800419EC(6, 0xC);
        func_800A56E0(0x818);
    }
    if (!(((S_80170534_0 *)state)->unk_18 & 7)) {
        temp_v1 = 0xFF;
        if (((S_80170534_1 *)input)->unk_0C != temp_v1) {
            ((S_80170534_1 *)input)->unk_0E.s = temp_v1;
            ((S_80170534_1 *)input)->unk_0D.s = temp_v1;
            ((S_80170534_1 *)input)->unk_0C = temp_v1;
            func_801705EC();
        }
        temp_v0 = 0x80;
        ((S_80170534_1 *)input)->unk_0E.u = temp_v0;
        ((S_80170534_1 *)input)->unk_0D.u = temp_v0;
        ((S_80170534_1 *)input)->unk_0C = temp_v0;
    }
    if ((s16) ((S_80170534_0 *)state)->unk_18 == 0x28) {
#ifdef NON_MATCHING
        D_801760D8[0] = 1;
#else
        {
            register u8 *flag_page ASM_REG("$3") = (u8 *) 0x80170000;   /* MATCH pin: retail register colouring depends on it */
            ASM_KEEP(flag_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
            *(u16 *)(flag_page + 0x60D8) = 1;
        }
#endif
    }
    if ((s16) ((S_80170534_0 *)state)->unk_18 >= 0x28) {
        temp_v0 = ((S_80170534_0 *)state)->unk_12.u + 1;
        ((S_80170534_0 *)state)->unk_12.u = temp_v0;
        func_801706E8();
    }
    goto state_end;

state_2:
    temp_v0_2 = ((S_80170534_0 *)state)->unk_18 + 1;
    ((S_80170534_0 *)state)->unk_18 = temp_v0_2;
    if (!(temp_v0_2 & 3)) {
        func_800A56E0(0x818);
    }
    if (!(((S_80170534_0 *)state)->unk_18 & 7)) {
        temp_v1 = 0xFF;
        if (((S_80170534_1 *)input)->unk_0C != temp_v1) {
            ((S_80170534_1 *)input)->unk_0E.s = temp_v1;
            ((S_80170534_1 *)input)->unk_0D.s = temp_v1;
            ((S_80170534_1 *)input)->unk_0C = temp_v1;
            func_80170690();
        }
        temp_v0 = 0x80;
        ((S_80170534_1 *)input)->unk_0E.u = temp_v0;
        ((S_80170534_1 *)input)->unk_0D.u = temp_v0;
        ((S_80170534_1 *)input)->unk_0C = temp_v0;
    }
    if ((s16) ((S_80170534_0 *)state)->unk_18 >= 0x3C) {
        ((S_80170534_0 *)state)->unk_18 = 0U;
        ((S_80170534_0 *)state)->unk_12.s = (s16) ((u16) ((S_80170534_0 *)state)->unk_12.s + 1);
        ((S_80170534_1 *)input)->unk_0E.u = 0x80;
        ((S_80170534_1 *)input)->unk_0D.u = 0x80;
        ((S_80170534_1 *)input)->unk_0C = 0x80;
        func_801706E8();
    }
    goto state_end;

state_4:
    {
        u8 *page;
        u16 flags = ((S_80170534_0_pre *)state)[-1].unk_00;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        page = (u8 *) 0x80080000;
        ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        flags = (u16) (flags | 0x8000);
        ((S_80170534_0_pre *)state)[-1].unk_00 = flags;
#ifdef NON_MATCHING
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
#else
        *(s32 *)(page + 0x14A0) |= 0x8000;
#endif
    }

state_end:
    ;
}
