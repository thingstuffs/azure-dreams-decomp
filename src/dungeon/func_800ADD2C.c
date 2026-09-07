#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_80099F04();                         /* extern */
s32 func_8009C12C();    /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B341C();        /* extern */
void func_800B357C() __attribute__((noreturn)); /* extern */
void func_800B3744() __attribute__((noreturn)); /* extern */
void func_800B3998() __attribute__((noreturn)); /* extern */
void func_800B3A40() __attribute__((noreturn)); /* extern */
M2C_UNK func_800B3D10();          /* extern */
M2C_UNK func_800B4194();             /* extern */
M2C_UNK func_800C77D0(); /* extern */
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008ACDC;
extern u8 D_800DD030[];
extern u8 D_800DD068[];
extern u8 D_800DD070[];
extern u8 D_800DD078[];
extern u8 D_800DD080[];
extern u8 D_800DD088[];
extern u8 D_800DD090[];
extern u8 D_800DD098[];
extern u8 D_800DD0A0[];
extern u8 D_800DD0A8[];
extern u8 D_800DD0B0[];
extern s32 D_800DF244[];
extern s16 D_800DF248[];
extern void *D_800891C0[];


typedef struct S_800B348C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x2];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x23];
    u8 * unk_CC;
    u8 pad_D0[0x24];
    s32 unk_F4;
    u8 pad_F8[0xA];
    u8 unk_102;
} S_800B348C_0;   /* arg0 in func_800B348C */

typedef struct S_800B348C_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x20];
    s32 unk_4C;
    u8 pad_50[0xC];
    s32 unk_5C;
    void * unk_60;
} S_800B348C_1;   /* arg3 in func_800B348C */

typedef struct S_800B348C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800B348C_2;   /* arg2 in func_800B348C */

typedef struct S_800B348C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B348C_3;   /* arg1 in func_800B348C */

typedef struct S_800B348C_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800B348C_4_pre;   /* the 0x14 bytes before temp_a2 in func_800B348C, addressed as temp_a2[-1] */

typedef struct S_800B348C_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800B348C_4;   /* temp_a2 in func_800B348C */

typedef struct S_800B348C_5 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800B348C_5;   /* temp_a0 in func_800B348C */

typedef struct S_800B348C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800B348C_6;   /* end_base in func_800B348C */

typedef struct S_800B348C_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800B348C_7;   /* ((S_800B348C_4_pre *)temp_a2)[-1].unk_00 in func_800B348C */

void func_800B348C(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *held_arg1;
    register void *held_arg2 ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_a1_4;
    M2C_UNK var_a0;
    s32 temp_a1_3;
    s32 temp_v0_3;
    s32 temp_v1_2;
    s32 temp_v1_3;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u8 jt_index;
    u8 state_9b;

    static void *const jt_keep[] = {
        &&jt_0, &&jt_1, &&jt_2, &&jt_3,
        &&jt_4, &&jt_5, &&jt_6, &&jt_7,
        &&jt_8, &&jt_9, &&jt_10, &&jt_default,
        &&jt_default, &&jt_default, &&jt_default, &&jt_15
    };

    held_arg1 = arg1;
    held_arg2 = arg2;
#define arg1 held_arg1
#define arg2 held_arg2
    jt_index = ((S_800B348C_0 *)arg0)->unk_9B;
    (void)jt_keep;
    if (jt_index >= 16) {
        goto jt_default;
    }
    goto *D_800891C0[jt_index];
    switch (((S_800B348C_0 *)arg0)->unk_9B) {
    case 0:
jt_0:
        ((S_800B348C_1 *)arg3)->unk_14 = (s32) (((S_800B348C_1 *)arg3)->unk_14 & ~7);
        ((S_800B348C_0 *)arg0)->unk_9B = (u8) (((S_800B348C_0 *)arg0)->unk_9B + 1);
        D_800DF248[0] = 0;
        return;
    case 1:
jt_1:
        if (((S_800B348C_0 *)arg0)->unk_A6 != 0) {
            (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD030;
            func_80048A44(arg2, D_800DD030[((s32) (D_80083228 + ((S_800B348C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
            ((S_800B348C_0 *)arg0)->unk_CC = NULL;
            if ((u16) ((S_800B348C_0 *)arg0)->unk_A6 < 2U) {
                func_800B357C();
                return;
            }
        } else {
            ((S_800B348C_0 *)arg0)->unk_F4 = 0;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
block_7:
            ((S_800B348C_0 *)arg0)->unk_98 = (u16) (((S_800B348C_0 *)arg0)->unk_98 & 0xDFFF);
            ((S_800B348C_0 *)arg0)->unk_9B = (u8) (((S_800B348C_0 *)arg0)->unk_9B + 1);
        case 2:
jt_2:
            if (((S_800B348C_0 *)arg0)->unk_A6 == 0) {
                func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
                (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD068;
                func_80048A44(arg2, D_800DD068[((s32) (D_80083228 + ((S_800B348C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
                state_9b = ((S_800B348C_0 *)arg0)->unk_9B;
                ((S_800B348C_0 *)arg0)->unk_CC = NULL;
                goto bump_state_9b;
            }
        }
        break;
    case 3:
jt_3:
        if (((S_800B348C_2 *)arg2)->unk_14 & 0xE000) {
            temp_v1_2 = ((u16) ((S_800B348C_1 *)arg3)->unk_2A >> 8) & 0xE;
            ((S_800B348C_3 *)arg1)->unk_0C = (s32) (*(s16 *)((u8 *)&D_8006CCD8 + temp_v1_2) << 0x11);
            ((S_800B348C_3 *)arg1)->unk_10 = (s32) (*(s16 *)((u8 *)&D_8006CCE8 + temp_v1_2) << 0x11);
            ((S_800B348C_3 *)arg1)->unk_14 = 0xFFEBC000;
            (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD070;
            func_80048A44(arg2, D_800DD070[((s32) (D_80083228 + ((S_800B348C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
            {
                u8 *next_v0;

                if (((S_800B348C_1 *)arg3)->unk_4C != 0) {
                    next_v0 = D_800DD078;
                } else {
                    next_v0 = D_800DD0A8;
                }
                ((S_800B348C_0 *)arg0)->unk_CC = next_v0;
            }
            ((S_800B348C_0 *)arg0)->unk_98 = (u16) (((S_800B348C_0 *)arg0)->unk_98 & 0xFFF7);
            ((S_800B348C_0 *)arg0)->unk_9B = (u8) (((S_800B348C_0 *)arg0)->unk_9B + 1);
            return;
        }
        break;
    case 4:
jt_4:
        if (((S_800B348C_2 *)arg2)->unk_14 & 0xE000) {
            temp_a1 = ((S_800B348C_0 *)arg0)->unk_CC;
            (*(u8 **)((u8 *)arg2 + 0x2C)) = temp_a1;
            func_80048A44(arg2, *(temp_a1 + (((s32) (D_80083228 + ((S_800B348C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7)), 0, 1);
            if (((S_800B348C_1 *)arg3)->unk_4C != 0) {
                register u32 page_v0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
                register u8 *next_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

                page_v0 = 0x800E0000;
                ASM_KEEP(page_v0);   /* MATCH pin: load-bearing for the whole function shape */
                next_v1 = (u8 *)page_v0 - 0x2F80;
                ASM_TAILSLOT_PIN(next_v1);   /* MATCH pin: retail delay-slot contents depend on it */
                func_800B3744();
                return;
            }
            {
                register u32 page_v0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
                register u8 *next_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

                ASM_CLOBBER("$2");   /* MATCH pin: retail basic-block layout depends on it */
                page_v0 = 0x800E0000;
                ASM_KEEP(page_v0);   /* MATCH pin: load-bearing for the whole function shape */
                next_v1 = (u8 *)page_v0 - 0x2F50;
                ASM_KEEP(next_v1);   /* MATCH pin: load-bearing for the whole function shape */
                state_9b = ((S_800B348C_0 *)arg0)->unk_9B;
                ((S_800B348C_0 *)arg0)->unk_CC = next_v1;
            }
            goto bump_state_9b;
        }
        break;
    case 5:
jt_5:
        if (((S_800B348C_2 *)arg2)->unk_14 & 0xE000) {
            if (((S_800B348C_0 *)arg0)->unk_A8 != 0) {
                D_800DF248[0] = 1;
                goto load_state_9b;
            }
            ((S_800B348C_0 *)arg0)->unk_96.u = 4U;
            ((S_800B348C_0 *)arg0)->unk_9B = (u8) (((S_800B348C_0 *)arg0)->unk_9B + 0xA);
            return;
        }
        break;
    case 15:
jt_15:
        temp_v0 = ((S_800B348C_0 *)arg0)->unk_96.u - 1;
        ((S_800B348C_0 *)arg0)->unk_96.u = temp_v0;
        if (((temp_v0 << 0x10) <= 0) || (((S_800B348C_2 *)arg2)->unk_14 & 0x8000)) {
            var_a0 = 0x606;
            if (((S_800B348C_1 *)arg3)->unk_4C != 0) {
                var_a0 = 0x605;
            }
            func_800A56E0(var_a0);
            temp_a1_2 = ((S_800B348C_0 *)arg0)->unk_CC;
            (*(u8 **)((u8 *)arg2 + 0x2C)) = temp_a1_2;
            func_80048A44(arg2, *(temp_a1_2 + (((s32) (D_80083228 + ((S_800B348C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7)), 0, 1);
            ((S_800B348C_0 *)arg0)->unk_CC = D_800DD088;
            ((S_800B348C_0 *)arg0)->unk_96.u = 2U;
            ((S_800B348C_0 *)arg0)->unk_9B = 7U;
            return;
        }
        break;
    case 6:
jt_6:
        ((S_800B348C_2 *)arg2)->unk_14 = (u16) (((S_800B348C_2 *)arg2)->unk_14 | 0x800);
        ((S_800B348C_0 *)arg0)->unk_98 = (u16) (((S_800B348C_0 *)arg0)->unk_98 | 8);
        temp_a1_3 = ((S_800B348C_3 *)arg1)->unk_14;
        ((S_800B348C_3 *)arg1)->unk_0C = 0;
        ((S_800B348C_3 *)arg1)->unk_10 = 0;
        ((S_800B348C_3 *)arg1)->unk_14 = 0;
        temp_v0_2 = ((S_800B348C_0 *)arg0)->unk_96.u - 1;
        ((S_800B348C_0 *)arg0)->unk_96.u = temp_v0_2;
        D_800DF244[0] = temp_a1_3;
        if ((s16)temp_v0_2 < 0) {
            temp_v1_3 = ((u16) ((S_800B348C_1 *)arg3)->unk_2A >> 8) & 0xE;
            ((S_800B348C_3 *)arg1)->unk_0C = (s32) (*(s16 *)((u8 *)&D_8006CCD8 + temp_v1_3) << 0x11);
            ((S_800B348C_3 *)arg1)->unk_10 = (s32) (*(s16 *)((u8 *)&D_8006CCE8 + temp_v1_3) << 0x11);
            ((S_800B348C_3 *)arg1)->unk_14 = temp_a1_3;
            ((S_800B348C_2 *)arg2)->unk_14 = (u16) (((S_800B348C_2 *)arg2)->unk_14 & 0xF7FF);
            ((S_800B348C_0 *)arg0)->unk_96.u = 4U;
            ((S_800B348C_0 *)arg0)->unk_98 = (u16) (((S_800B348C_0 *)arg0)->unk_98 & 0xFFF7);
            ((S_800B348C_0 *)arg0)->unk_9B = (u8) (((S_800B348C_0 *)arg0)->unk_9B + 1);
            func_800B341C(arg0 - 0x20, ((S_800B348C_0 *)arg0)->unk_F4, 0x40);
            temp_a1_4 = ((S_800B348C_0 *)arg0)->unk_CC;
            (*(u8 **)((u8 *)arg2 + 0x2C)) = temp_a1_4;
            func_80048A44(arg2, *(temp_a1_4 + (((s32) (D_80083228 + ((S_800B348C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7)), 0, 1);
            ((S_800B348C_0 *)arg0)->unk_CC = D_800DD088;
            func_800B3D10(((S_800B348C_0 *)arg0)->unk_A8, ((S_800B348C_1 *)arg3)->unk_60, arg3);
            return;
        }
        break;
    case 7:
jt_7:
        if (((S_800B348C_2 *)arg2)->unk_14 & 0x8000) {
            ((S_800B348C_0 *)arg0)->unk_96.u = 0U;
            func_800B3998();
            return;
        } else {
            ((S_800B348C_0 *)arg0)->unk_96.u = (u16) (((S_800B348C_0 *)arg0)->unk_96.u - 1);
        }
        ASM_MEM_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
        if (((S_800B348C_0 *)arg0)->unk_96.s == 0) {
            if (((S_800B348C_0 *)arg0)->unk_102 == 0) {
                register s32 temp_a2 ASM_REG("$6");   /* MATCH pin: retail keeps a computation the compiler would drop */

                temp_a2 = func_8009C12C(arg3, arg2, ((S_800B348C_1 *)arg3)->unk_2A, 1);
                if (temp_a2 != 0) {
                    func_800B4194(((S_800B348C_0 *)arg0)->unk_A8, temp_a2, arg3);
                    ((S_800B348C_0 *)arg0)->unk_A8 = 0U;
                    func_800B3A40();
                    return;
                } else {
                    register void *temp_a2 ASM_REG("$6");   /* MATCH pin: retail keeps a computation the compiler would drop */

                    temp_a2 = ((S_800B348C_1 *)arg3)->unk_60;
                    if (temp_a2 != NULL) {
                        ((S_800B348C_1 *)arg3)->unk_60 = NULL;
                        ((S_800B348C_4 *)temp_a2)->unk_1C = (s32) (((S_800B348C_4 *)temp_a2)->unk_1C & 0xEFFFFFFF);
                        ((S_800B348C_7 *)(((S_800B348C_4_pre *)temp_a2)[-1].unk_00))->unk_0C = 0x808080;
                        func_800B3A40();
                        return;
                    }
                }
            } else {
                void *temp_a0;

                temp_a0 = ((S_800B348C_1 *)arg3)->unk_60;
                if (temp_a0 != NULL) {
                    ((S_800B348C_5 *)temp_a0)->unk_14 = (s32) (((S_800B348C_5 *)temp_a0)->unk_14 | 0x01000000);
                }
            }
        }
        if (((s16) ((S_800B348C_0 *)arg0)->unk_96.u <= 0) && (((S_800B348C_2 *)arg2)->unk_14 & 0xE000)) {
            (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD088;
            func_80048A44(arg2, D_800DD088[((s32) (D_80083228 + ((S_800B348C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
            ((S_800B348C_0 *)arg0)->unk_CC = D_800DD090;
            ((S_800B348C_0 *)arg0)->unk_9B = (u8) (((S_800B348C_0 *)arg0)->unk_9B + 1);
        }
        /* fallthrough */
    case 8:
jt_8:
        if (((S_800B348C_0 *)arg0)->unk_A2 & 0x10) {
            ((S_800B348C_3 *)arg1)->unk_14 = 0;
            ((S_800B348C_3 *)arg1)->unk_10 = 0;
            ((S_800B348C_3 *)arg1)->unk_0C = 0;
            if (((S_800B348C_0 *)arg0)->unk_A8 != 0) {
                ((S_800B348C_0 *)arg0)->unk_A8 = 0U;
            }
            if ((s16) ((S_800B348C_0 *)arg0)->unk_96.u <= 0) {
                (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD090;
                func_80048A44(arg2, D_800DD090[((s32) (D_80083228 + ((S_800B348C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
                ((S_800B348C_0 *)arg0)->unk_CC = D_800DD098;
                ((S_800B348C_0 *)arg0)->unk_9B = 9U;
                return;
            }
        }
        break;
    case 9: {
        s32 delta_x;
        s32 delta_y;

jt_9:
        if (((S_800B348C_2 *)arg2)->unk_14 & 0xE000) {
            ((S_800B348C_3 *)arg1)->unk_14 = 0;
            (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD098;
            func_80048A44(arg2, D_800DD098[((s32) (D_80083228 + ((S_800B348C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
            ((S_800B348C_0 *)arg0)->unk_96.u = 2U;
            delta_x = ((S_800B348C_2 *)arg2)->unk_24 << 6;
            delta_y = ((S_800B348C_3 *)arg1)->unk_02;
            delta_y -= 0x20;
            delta_x -= delta_y;
            ((S_800B348C_3 *)arg1)->unk_0C = (s32) ((delta_x << 0x10) / (s16) ((S_800B348C_0 *)arg0)->unk_96.u);
            delta_y = ((S_800B348C_3 *)arg1)->unk_06 - 0x20;
            ((S_800B348C_3 *)arg1)->unk_10 = (s32) ((s32) (((((S_800B348C_2 *)arg2)->unk_25 << 6) - delta_y) << 0x10) / (s16) ((S_800B348C_0 *)arg0)->unk_96.u);
load_state_9b:
            state_9b = ((S_800B348C_0 *)arg0)->unk_9B;
bump_state_9b:
            ((S_800B348C_0 *)arg0)->unk_9B = (u8) (state_9b + 1);
            return;
        }
        break;
    }
    case 10: {
        u32 end_page;
        s32 *end_base;
        s32 end_mask;
        s32 end_timer_state;
        s32 end_flags;

jt_10:
        temp_v0_4 = ((S_800B348C_0 *)arg0)->unk_96.u - 1;
        ((S_800B348C_0 *)arg0)->unk_96.u = temp_v0_4;
        if (((temp_v0_4 << 0x10) <= 0) || (((S_800B348C_2 *)arg2)->unk_14 & 0x8000)) {
            ((S_800B348C_3 *)arg1)->unk_14 = 0;
            ((S_800B348C_3 *)arg1)->unk_10 = 0;
            ((S_800B348C_3 *)arg1)->unk_0C = 0;
            func_800A2B04(arg1, ((S_800B348C_2 *)arg2)->unk_24, ((S_800B348C_2 *)arg2)->unk_25);
            {
                register void *case10_arg2 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
                case10_arg2 = arg2;
                (*(u8 **)((u8 *)case10_arg2 + 0x2C)) = D_800DD0A0;
                func_80048A44(case10_arg2, D_800DD0A0[((s32) (D_80083228 + ((S_800B348C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
            }
            func_80099F04(((S_800B348C_1 *)arg3)->unk_5C);
            end_page = 0x80080000;
            ASM_KEEP(end_page);   /* MATCH pin: load-bearing for the whole function shape */
            end_base = (s32 *)(end_page + 0x3460);
            end_mask = -8;
            ((S_800B348C_6 *)end_base)->unk_02 = (u16) (((S_800B348C_6 *)end_base)->unk_02 | 0x412);
            end_timer_state = 0x800E0000;
            ASM_KEEP(end_timer_state);   /* MATCH pin: keeps a constant in a register as retail does */
            ((S_800B348C_0 *)arg0)->unk_8C = &D_8008ACDC;
            end_flags = ((S_800B348C_1 *)arg3)->unk_14;
            end_timer_state = *(s16 *)((u8 *)end_timer_state - 0xDB8);
            end_flags &= end_mask;
            ((S_800B348C_1 *)arg3)->unk_14 = end_flags;
            if (end_timer_state == 0) {
                ((S_800B348C_6 *)end_base)->unk_0C = 0;
            }
            ((S_800B348C_0 *)arg0)->unk_96.u = 0U;
        }
        break;
    }
    default:
jt_default:
        break;
    }
    ASM_KEEP(held_arg1);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(held_arg2);   /* MATCH pin: keeps a statement from moving across a call/branch */
}
#undef arg1
#undef arg2
