#include "common.h"


extern void func_8004E994();
extern void func_800B0EF4(void);
extern void func_800B0EF8(void);
extern void func_800B0F3C(void);

extern s32 D_800814A0;
extern u8 D_800DDC40[];
extern u8 *D_800E3D7C[];


typedef struct S_800B0D34_0 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x8];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u16 unk_12;
    void * unk_14;
    u8 pad_18[0x44];
    s32 unk_5C;
} S_800B0D34_0;   /* arg0 in func_800B0D34 */

typedef struct S_800B0D34_1_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800B0D34_1_pre;   /* the 0x18 bytes before info in func_800B0D34, addressed as info[-1] */

typedef struct S_800B0D34_1 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x1];
    u8 unk_13;
    u8 pad_14[0x11];
    u8 unk_25;
    u8 pad_26[0x2];
    u8 unk_28;
    u8 unk_29;
} S_800B0D34_1;   /* info in func_800B0D34 */

typedef struct S_800B0D34_2 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_800B0D34_2;   /* out in func_800B0D34 */

typedef struct S_800B0D34_3 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 pad_05[0x13];
    union { u16 u; s16 s; } unk_18;   /* accessed as both */
} S_800B0D34_3;   /* arg2 in func_800B0D34 */

typedef struct S_800B0D34_4 {
    u8 pad_00[0x104];
    void * unk_104;
} S_800B0D34_4;   /* D_800E3D7C[0] in func_800B0D34 */

typedef struct S_800B0D34_5 {
    u8 pad_00[0x28];
    void * unk_28;
} S_800B0D34_5;   /* object in func_800B0D34 */

typedef struct S_800B0D34_6_pre {
    u16 unk_00;
} S_800B0D34_6_pre;   /* the 0x2 bytes before entry in func_800B0D34, addressed as entry[-1] */

typedef struct S_800B0D34_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B0D34_7;   /* arg1 in func_800B0D34 */

typedef struct S_800B0D34_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B0D34_8;   /* source in func_800B0D34 */

void func_800B0D34(void *arg0, void *arg1, void *arg2) {
    u16 packed;
    register s32 base_phase ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 phase;
    register s32 reflected ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    void *out;
    void *info;
    s32 mode;

    packed = ((S_800B0D34_0 *)arg0)->unk_12;
    out = ((S_800B0D34_0 *)arg0)->unk_04;
    info = ((S_800B0D34_0 *)arg0)->unk_14;
    base_phase = packed & 0x1F;
    phase = base_phase;
    if (packed & 0x10) {
        reflected = -base_phase & 0x1F;
        phase = reflected;
        if (reflected == 0) {
            phase = 0x10;
        }
    }

    out = (u8 *)out + 4;
    if ((s32)((S_800B0D34_1 *)info)->unk_29 /
            (s32)((((S_800B0D34_1 *)info)->unk_11 >> 1) + 2) >=
        (s32)((S_800B0D34_1 *)info)->unk_28) {
        ((S_800B0D34_2 *)out)->unk_00 = -0x80 - phase * 8;
        ((S_800B0D34_2 *)out)->unk_02 = 0x10;
        ((S_800B0D34_2 *)out)->unk_01 = 0x10;
    }

    out = (u8 *)out + 4;
    if (((S_800B0D34_1 *)info)->unk_25 < 10) {
        ((S_800B0D34_2 *)out)->unk_00 = -0x80 - phase * 8;
        ((S_800B0D34_2 *)out)->unk_02 = 0x10;
        ((S_800B0D34_2 *)out)->unk_01 = 0x10;
    }

    mode = ((S_800B0D34_0 *)arg0)->unk_10.s;
    ((S_800B0D34_0 *)arg0)->unk_12++;
    if (mode == 0) {
        goto mode_zero;
    }
    if (mode == 1) {
        goto mode_one;
    }
    ((S_800B0D34_3 *)arg2)->unk_04 = 0;
    func_800B0EF8();
    return;

mode_zero:
    {
        u16 value = ((S_800B0D34_3 *)arg2)->unk_18.u;
        if (value != 0) {
            ((S_800B0D34_3 *)arg2)->unk_18.u = value + 0x80;
        }
    }
    if (((S_800B0D34_4 *)(D_800E3D7C[0]))->unk_104 !=
        ((S_800B0D34_0 *)arg0)->unk_14) {
        ((S_800B0D34_0 *)arg0)->unk_10.u++;
        func_800B0EF4();
        return;
    }
    goto finish;

mode_one:
    {
        s16 signed_value = ((S_800B0D34_3 *)arg2)->unk_18.s;
        u16 value = ((S_800B0D34_3 *)arg2)->unk_18.u;
        if (signed_value >= -0x3FF) {
            ((S_800B0D34_3 *)arg2)->unk_18.u = value - 0x100;
            func_800B0EF4();
            return;
        }
    }
    func_8004E994(((S_800B0D34_0 *)arg0)->unk_5C);
    {
        s32 i = 0;
        s32 *global_base = (s32 *)0x80080000;
        void *object = arg0;
        do {
            void *entry = ((S_800B0D34_5 *)object)->unk_28;
            if (entry != 0) {
                ((S_800B0D34_6_pre *)entry)[-1].unk_00 |= 0x8000;
                global_base[0x14A0 / 4] |= 0x8000;
            }
            i++;
            object = (u8 *)object + 4;
        } while (i < 4);
    }
    (*(u16 *)((u8 *)arg0 + (-2))) |= 0x8000;
    D_800814A0 |= 0x8000;
    func_800B0F3C();
    return;

finish:
    ((S_800B0D34_3 *)arg2)->unk_04 = 0;
    {
        void *source = ((S_800B0D34_1_pre *)info)[-1].unk_00;
        s32 adjustment;
        u16 source_value;
        ((S_800B0D34_7 *)arg1)->unk_02 = ((S_800B0D34_8 *)source)->unk_02;
        ((S_800B0D34_7 *)arg1)->unk_06 = ((S_800B0D34_8 *)source)->unk_06;
        adjustment = D_800DDC40[((S_800B0D34_1 *)info)->unk_13] + 0x50;
        source_value = ((S_800B0D34_8 *)source)->unk_0A;
        ((S_800B0D34_7 *)arg1)->unk_0A = source_value - adjustment;
    }
}
