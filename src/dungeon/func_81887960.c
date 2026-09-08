#include "common.h"

typedef struct S_80025160_0_pre {
    u16 unk_00;
} S_80025160_0_pre;   /* the 0x2 bytes before arg0 in func_80025160, addressed as arg0[-1] */

typedef struct S_80025160_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0xA];
    s16 unk_16;
    union { volatile u16 s; u16 u; s16 p; } unk_18;   /* accessed as both */
    u16 unk_1A;
    union { volatile u16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x4];
    s16 unk_22;
} S_80025160_0;   /* arg0 in func_80025160 */

typedef struct S_80025160_1 {
    u8 pad_00[0x6];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80025160_1;   /* arg2 in func_80025160 */

typedef struct S_80025160_2 {
    u8 pad_00[0x6328];
    s16 unk_6328;
} S_80025160_2;   /* flag_page in func_80025160 */

typedef struct S_80025160_3 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80025160_3;   /* flags_page in func_80025160 */


#define COUNTER D_80026326.counter

typedef struct Global26326 {
    u16 counter;
    s16 flag;
    u16 unused[3];
} Global26326;

typedef struct Global26328 {
    s16 flag;
    u16 unused[4];
} Global26328;

typedef struct Global814A0 {
    s32 flags;
    s32 unused[2];
} Global814A0;

extern void func_8002530C(void) __attribute__((noreturn));
extern void func_80025314(void) __attribute__((noreturn));
extern void func_8002569C(s32, s32, s32, s32, void *);
extern u8 D_80020000[0x10000];
extern Global26326 D_80026326;
extern Global26328 D_80026328;
extern Global814A0 D_800814A0;

void func_80025160(void *arg0, s32 arg1, S_80025160_1 *arg2) {
    s16 state;
    s32 one;
    u16 value;
    u16 angle;
    u16 next;
    s32 call_a1;
    s32 signed_angle;
    void *call_arg5;
    u8 *flag_page;
    u8 *flags_page;

    one = 1;
    COUNTER = COUNTER + 1;
    state = ((S_80025160_0 *)arg0)->unk_0A.s;

    if (state == one) {
        goto state_1;
    }
    value = state < 2;
    if (value == 0) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    arg2->unk_0C = 0x20;
    func_80025314();

state_ge_2:
    value = 2;
    if (state == value) {
        goto state_2;
    }
    value = 3;
    if (state == value) {
        goto state_3;
    }
    arg2->unk_0C = 0x20;
    func_80025314();

state_0:
    value = arg2->unk_06.s + 0x80;
    arg2->unk_06.s = value;
    if ((s16)value <= 0x100) {
        goto set_colors;
    }
    arg2->unk_06.s = 0x100;
    if (((S_80025160_0 *)arg0)->unk_22 < 0x61) {
        next = ((S_80025160_0 *)arg0)->unk_18.s;
        angle = ((S_80025160_0 *)arg0)->unk_1C.s;
        call_a1 = ((S_80025160_0 *)arg0)->unk_16;
        next = next - ((s32)(next << 16) >> 19);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        angle = angle + 0x80;
        call_arg5 = (u8 *)arg0 - 0x20;
        ((S_80025160_0 *)arg0)->unk_1C.u = angle;
        signed_angle = angle << 16;
        ((S_80025160_0 *)arg0)->unk_18.u = next;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_8002569C(arg1, call_a1, ((S_80025160_0 *)arg0)->unk_18.p,
                     signed_angle >> 16, call_arg5);
    }
    ((S_80025160_0 *)arg0)->unk_0A.u++;
    if (((S_80025160_0 *)arg0)->unk_22 == 0x6F) {
        D_80026328.flag = one;
        func_8002530C();
    }
    goto set_colors;

state_1:
    flag_page = (u8 *)0x80020000;
    if (((S_80025160_2 *)flag_page)->unk_6328 == 0) {
        goto state_1_zero;
    }
    arg2->unk_06.u = -0x100;
    ((S_80025160_0 *)arg0)->unk_1A = 0x10;
    ((S_80025160_0 *)arg0)->unk_0A.u++;
    func_8002530C();

state_2:
    value = ((S_80025160_0 *)arg0)->unk_1A - 1;
    ((S_80025160_0 *)arg0)->unk_1A = value;
    if ((value << 16) > 0) {
        goto set_colors;
    }
    ((S_80025160_0 *)arg0)->unk_0A.u++;

state_3:
    value = arg2->unk_06.s + 0x80;
    arg2->unk_06.s = value;
    if ((value << 16) >= 0) {
        flags_page = (u8 *)0x80080000;
        ((S_80025160_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        ((S_80025160_3 *)flags_page)->unk_14A0 |= 0x8000;
    }

state_1_zero:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
set_colors:
    arg2->unk_0C = 0x20;
    arg2->unk_0D = 0x40;
    arg2->unk_0E = 0xE0;
}
