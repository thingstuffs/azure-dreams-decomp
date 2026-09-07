#include "common.h"

typedef struct S_80025A14_0 {
    u8 pad_00[0x46];
    s16 unk_46;
    u8 pad_48[0x10];
    void * unk_58;
    u8 pad_5C[0x16];
    union { s8 s; u8 u; } unk_72;   /* accessed as both */
    union { s8 s; u8 u; } unk_73;   /* accessed as both */
} S_80025A14_0;   /* state in func_80025A14 */

typedef struct S_80025A14_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_80025A14_1;   /* buffer in func_80025A14 */

typedef struct S_80025A14_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
    void * unk_2C;
} S_80025A14_2;   /* obj in func_80025A14 */

typedef struct S_80025A14_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x12];
    s32 unk_28;
} S_80025A14_3;   /* template in func_80025A14 */

typedef struct S_80025A14_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80025A14_4_pre;   /* the 0x14 bytes before p in func_80025A14, addressed as p[-1] */

typedef struct S_80025A14_4 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80025A14_4;   /* p in func_80025A14 */



extern void func_80025BD8() __attribute__((noreturn));
extern void func_80025C78(void) __attribute__((noreturn));
extern void func_80025C7C() __attribute__((noreturn));
extern void func_800489F4(void *, u8, s8, s32);
extern void func_80048AC8(void *, s32);
extern s16 D_8002715A;
extern u16 D_8002715C;
extern u8 D_8006CCF8[];
extern u8 D_80082E80[];
extern u8 D_800DD008[];

void func_80025A14(void *arg0, void *arg1, void *arg2)
{
    register void *obj ASM_REG("$17") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *state ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    u16 counter;
    register void *var_a0 ASM_REG("$4") = arg0;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register void *buffer ASM_REG("$5") = arg1;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    u16 tail_value;
    u8 *template;
    s8 phase;
    u8 fade_in_value;
    u8 fade_out_value;
    u8 phase_value;
    s16 init_value;
    s16 index;
    void *p;

    counter = D_8002715C;
    state = arg0;
    counter++;
    D_8002715C = counter;
    phase = ((S_80025A14_0 *)state)->unk_72.s;
    if (phase == 1) {
        goto fade_in;
    }
    if (phase < 2) {
        init_value = 0x1000;
        if (phase != 0) {
            func_80025C7C(var_a0);
        }
        goto init;
    }
    if (phase == 2) {
        goto check_stop;
    }
    if (phase == 3) {
        goto fade_out;
    }
    func_80025C7C(var_a0);

init:
    ((S_80025A14_1 *)buffer)->unk_02 = 0;
    ((S_80025A14_1 *)buffer)->unk_06 = 0;
    ((S_80025A14_1 *)buffer)->unk_0A = 0;
    ((S_80025A14_2 *)obj)->unk_1E = init_value;
    ((S_80025A14_2 *)obj)->unk_1C = init_value;
    ((S_80025A14_2 *)obj)->unk_0E = 0;
    ((S_80025A14_2 *)obj)->unk_0D = 0;
    ((S_80025A14_2 *)obj)->unk_0C = 0;
    template = D_80082E80;
    ((S_80025A14_2 *)obj)->unk_28 = ((S_80025A14_3 *)template)->unk_28;
    ((S_80025A14_2 *)obj)->unk_14 = ((S_80025A14_3 *)template)->unk_14 & 0xFFFC;
    ((S_80025A14_2 *)obj)->unk_2C = D_800DD008;
    ((S_80025A14_2 *)obj)->unk_14 |= 0x200;
    ((S_80025A14_0 *)state)->unk_73.s = 8;
    ((S_80025A14_0 *)state)->unk_72.s = ((S_80025A14_0 *)state)->unk_72.u + 1;

fade_in:
    var_a0 = (void *)(s32)((S_80025A14_0 *)state)->unk_73.s;
    if (var_a0 != 0) {
        fade_in_value = ((S_80025A14_2 *)obj)->unk_0E;
        fade_in_value += (0x40 - fade_in_value) / (s32)var_a0;
        ((S_80025A14_2 *)obj)->unk_0E = fade_in_value;
        ((S_80025A14_2 *)obj)->unk_0D = fade_in_value;
        ((S_80025A14_2 *)obj)->unk_0C = fade_in_value;
    }
    fade_in_value = ((S_80025A14_0 *)state)->unk_73.u - 1;
    ((S_80025A14_0 *)state)->unk_73.u = fade_in_value;
    if ((s8)fade_in_value > 0) {
        goto check_stop;
    }
    ((S_80025A14_2 *)obj)->unk_0E = 0x40;
    ((S_80025A14_2 *)obj)->unk_0D = 0x40;
    ((S_80025A14_2 *)obj)->unk_0C = 0x40;
    phase_value = ((S_80025A14_0 *)state)->unk_72.u;
    ((S_80025A14_0 *)state)->unk_73.u = 0;
    ((S_80025A14_0 *)state)->unk_72.u = phase_value + 1;

check_stop:
    if (D_8002715A != 0) {
        ((S_80025A14_0 *)state)->unk_73.u = 8;
        ((S_80025A14_1 *)buffer)->unk_16 = 8;
        func_80025BD8(var_a0, buffer);
    }
    goto final_update;

fade_out:
    var_a0 = (void *)(s32)((S_80025A14_0 *)state)->unk_73.s;
    if (var_a0 != 0) {
        fade_out_value = ((S_80025A14_2 *)obj)->unk_0E;
        fade_out_value += (0 - fade_out_value) / (s32)var_a0;
        ((S_80025A14_2 *)obj)->unk_0E = fade_out_value;
        ((S_80025A14_2 *)obj)->unk_0D = fade_out_value;
        ((S_80025A14_2 *)obj)->unk_0C = fade_out_value;
    }
    fade_out_value = ((S_80025A14_0 *)state)->unk_73.u - 1;
    ((S_80025A14_0 *)state)->unk_73.u = fade_out_value;
    if ((s8)fade_out_value <= 0) {
        phase_value = ((S_80025A14_0 *)state)->unk_72.u;
        ((S_80025A14_0 *)state)->unk_72.u = phase_value + 1;
    }

final_update:
    p = ((S_80025A14_0 *)state)->unk_58;
    p = ((S_80025A14_4_pre *)p)[-1].unk_00;
    index = ((((S_80025A14_4 *)p)->unk_1A + 0x500) >> 9) & 7;
    if (((S_80025A14_0 *)state)->unk_46 != index) {
        ((S_80025A14_0 *)state)->unk_46 = index;
        func_800489F4(obj, ((u8 *)((S_80025A14_2 *)obj)->unk_2C)[index],
                       ((S_80025A14_2 *)obj)->unk_04, 2);
    }
    func_80048AC8(obj, 2);
    if (D_8006CCF8[index] != 0) {
        tail_value = ((S_80025A14_2 *)obj)->unk_14 | 1;
        ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80025C78();
    }
    ((S_80025A14_2 *)obj)->unk_14 &= 0xFFFE;
}
