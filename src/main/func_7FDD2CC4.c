/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80089C24_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
} S_80089C24_0;   /* temp_v0 in func_80089C24 */

typedef struct S_80089C24_1 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80089C24_1;   /* var_s4 in func_80089C24 */

typedef struct S_80089C24_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80089C24_2;   /* ((S_80089C24_0 *)temp_v0)->unk_08 in func_80089C24 */


typedef struct Sol9Copy8 {
    u8 bytes[8];
} Sol9Copy8;

static inline void sol9_copy8(void *dst, const void *src, s32 ignored_size) {
    *(Sol9Copy8 *)dst = *(const Sol9Copy8 *)src;
    (void)ignored_size;
}

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80053428();                      /* extern */
M2C_UNK func_80053DA8(); /* extern */
M2C_UNK func_80067014();                     /* extern */
M2C_UNK func_800672D8();        /* extern */
M2C_UNK func_8006733C();        /* extern */
M2C_UNK func_8008A98C(); /* extern */
M2C_UNK func_8008ABD4();   /* extern */
M2C_UNK func_8008AE60();            /* extern */
extern u8 D_80013180;
extern u8 D_80013181;
extern u8 D_80013182;
extern u8 D_80013184;
extern u8 D_80013186;
extern M2C_UNK D_800786E8;
extern M2C_UNK D_80078AF0;
extern s8 D_80080A84;
extern s32 D_80080A94;
extern s32 D_80080A98;
extern s32 D_80080A9C;
extern u8 D_800888AC;
extern M2C_UNK D_8008A288;
extern M2C_UNK D_8008A794;
extern M2C_UNK D_8008AA40;
extern M2C_UNK D_8008AA84;
extern M2C_UNK D_8008AAE4;
extern M2C_UNK D_8008AB44;
extern M2C_UNK D_8008AC70;
extern M2C_UNK D_8008ACB4;
extern M2C_UNK D_8008AD58;
extern M2C_UNK D_8008AEEC;
extern M2C_UNK D_8008B030;
extern s32 D_8008B2B0;
extern s32 D_8008B2B4;
extern s32 D_8008B2BC;
extern M2C_UNK D_8008B2C4;
extern M2C_UNK D_8008B2D4;
extern s32 D_8008B2DC;
extern M2C_UNK D_8008B2E4;
extern M2C_UNK D_8008B2F0;
extern M2C_UNK D_8008B2FC;

void func_80089C24(void) {
    u8 frame[0x278];
    s32 unksp12;
    s32 unksp16;
    s32 sp12;
    s32 sp16;
    s32 sp10;
    s32 sp14;
    s16 sp28;
    void *sp2C;
    s32 sp30;
    s16 sp34;
    s16 sp36;
    s16 sp38;
    s16 sp3A;
    s16 sp3C;
    s16 sp3E;
    s32 sp40;
    s16 sp50;
    s16 sp52;
    s32 sp54;
    void *sp5C;
    s32 sp60;
    s16 sp64;
    u16 sp66;
    s16 sp68;
    s16 sp6A;
    s16 sp6C;
    s32 sp70;
    s32 sp74;
    M2C_UNK sp80;
    M2C_UNK sp20E;
    M2C_UNK sp280;
    M2C_UNK sp284;
    u8 *var_a0_3;
    u8 *var_a0_4;
    u8 *var_a0_5;
    u8 *var_a0_6;
    u8 *var_a0_7;
    u8 *var_a0_8;
    u8 *var_a0_9;
    u8 *var_v1;
    register s16 var_s1;
    s16 var_s1_3;
    s16 var_s1_5;
    register s16 var_s3;
    register s32 var_s2_2;
    register u8 *var_s1_2;
    register u8 *var_s2;
    u8 *var_s2_3;
    u8 *var_s2_4;
    u8 *var_s2_5;
    u8 *var_s2_6;
    u8 *var_s2_7;
    s32 temp_v0_10;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 var_a0;
    s32 var_a2;
    s32 msk;
    s32 *cfgp;
    s32 descriptor_color;
    u8 *base_b030;
    register s32 var_s0;
    s32 var_s0_2;
    register s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;
    s32 var_s0_7;
    s32 var_s0_8;
    s32 var_s0_9;
    s32 var_v0;
    u16 var_s1_4;
    u16 var_s1_6;
    u16 var_s1_7;
    register void *temp_v0;
    void *var_a0_2;
    void *var_s4;

#define sp28 (*(s16 *)(frame + 0x18 + 0))
#define sp2C (*(void **)(frame + 0x18 + 4))
#define sp30 (*(s32 *)(frame + 0x18 + 8))
#define sp34 (*(s16 *)(frame + 0x18 + 12))
#define sp36 (*(s16 *)(frame + 0x18 + 14))
#define sp38 (*(s16 *)(frame + 0x18 + 16))
#define sp3A (*(s16 *)(frame + 0x18 + 18))
#define sp3C (*(s16 *)(frame + 0x18 + 20))
#define sp3E (*(s16 *)(frame + 0x18 + 22))
#define sp40 (*(s32 *)(frame + 0x18 + 24))
#define sp50 (((s16 *)(frame + 0x40))[0])
#define sp52 (((s16 *)(frame + 0x40))[1])
#define sp54 (((s32 *)(frame + 0x40))[1])
#define sp5C (*(void **)(frame + 0x40 + 12))
#define sp60 (((s32 *)(frame + 0x40))[4])
#define sp64 (((s16 *)(frame + 0x40))[10])
#define sp66 (((u16 *)(frame + 0x40))[11])
#define sp68 (((s16 *)(frame + 0x40))[12])
#define sp6A (((s16 *)(frame + 0x40))[13])
#define sp6C (((s16 *)(frame + 0x40))[14])
#define sp70 (((s32 *)(frame + 0x40))[8])
#define sp74 (((s32 *)(frame + 0x40))[9])

    var_s4 = NULL;
    sol9_copy8(frame + 0x270, &D_800888AC, 8);
    var_a2 = 0x100;
    D_80080A84 = 1;
    cfgp = (s32 *)&D_8008B2F0;
    if (D_80080A98 != 0x7FFF) {
        var_a2 = (s32) D_80080A98 >> 7;
    }
    var_a0 = 0x100;
    cfgp[0] = var_a2;
    if (D_80080A9C != 0x7FFF) {
        var_a0 = (s32) D_80080A9C >> 7;
    }
    var_v0 = 0x100;
    cfgp[1] = var_a0;
    if (D_80080A94 != 0x7FFF) {
        var_v0 = (s32) D_80080A94 >> 7;
    }
    cfgp[2] = var_v0;
    func_80053DA8(0x200);
    func_8006733C(frame + 0x270, frame + 0x70);
    func_80067014(0);
    var_s0 = 0xFF;
    msk = ~0x7FFF;
    do {
        *(u16 *)(frame + var_s0 * 2 + 0x70) = *(u16 *)(frame + var_s0 * 2 + 0x70) | msk;
        var_s0 -= 1;
    } while (var_s0 >= 0);
    func_800672D8(frame + 0x270, frame + 0x70);
    temp_v0 = func_8003FC64(0x11);
    if (temp_v0 != NULL) {
        ((S_80089C24_0 *)temp_v0)->unk_10 = &D_8008A288;
        func_8004491C(temp_v0, &D_8008A794);
        var_s4 = temp_v0 + 0x20;
        ((S_80089C24_2 *)(((S_80089C24_0 *)temp_v0)->unk_08))->unk_06 = 0xF0;
        (*(s16 *)((u8 *)var_s4 + 4)) = 0x20;
        (*(s16 *)((u8 *)var_s4 + 0x14)) = (s16) ((u8) D_80013184 >> 5);
        var_s0 = 2;
        (*(s16 *)((u8 *)var_s4 + 0xE)) = (s16) D_80013180;
        (*(s16 *)((u8 *)var_s4 + 0x10)) = (s16) D_80013181;
        ((S_80089C24_1 *)var_s4)->unk_12 = (s16) D_80013182;
        do {
            if (*(s16 *)((u8 *)var_s4 + var_s0 * 2 + 14) >= 0xFF) {
                *(s16 *)((u8 *)var_s4 + var_s0 * 2 + 14) = 0x100;
            }
            var_s0 -= 1;
        } while (var_s0 >= 0);
        if ((D_80013186 & 1) == 0) {
            ((S_80089C24_1 *)var_s4)->unk_16 = (u16) (((S_80089C24_1 *)var_s4)->unk_16 | 2);
        } else {
            ((S_80089C24_1 *)var_s4)->unk_16 = (u16) (((S_80089C24_1 *)var_s4)->unk_16 & 0xFFFD);
        }
    }
    func_80053428(var_s4);
    sp10 = 0x400000;
    sp14 = 0xA00000;
    *(s32 *)(frame + 0x0) = sp10;
    *(s32 *)(frame + 0x4) = sp14;
    func_8008A98C(frame, &D_8008AC70, &D_80078AF0, var_s4);
    unksp12 = 0x94;
    unksp16 = 0x44;
    *(s16 *)(frame + 0x2) = unksp12;
    *(s16 *)(frame + 0x6) = unksp16;
    func_8008A98C(frame, &D_8008ACB4, &D_800786E8, var_s4);
    sp66 = 0xD0;
    sp68 = 1;
    sp6C = 0;
    sp6A = 0x7C80;
    sp60 = 0x808080;
    var_s0 = 0x1A;
    sp5C = var_s4;
    sp50 = 0;
    do {
        sp64 = var_s0 * 8 + 48;
        temp_v0_2 = ((s32 *)&D_8008B2FC)[var_s0];
        sp52 = var_s0 * 2 + 30;
        sp54 = temp_v0_2;
        func_8008AE60((u8 *)&D_8008AEEC, &sp50);
            var_s0 -= 1;
    } while (var_s0 >= 0);
    sp64 = 0x74;
    sp66 = 0xC;
    sp54 = D_8008B2B0;
    func_8008AE60((u8 *)&D_8008B030, &sp50);
    var_s0 = 0;
    sp64 = 0x20;
    do {
        sp66 = var_s0 * 0xC + 0x20;
        temp_v0_3 = ((s32 *)&D_8008B2B4)[var_s0];
        sp54 = temp_v0_3;
        func_8008AE60((u8 *)&D_8008B030, &sp50);
        var_s0 += 1;
    } while (var_s0 < 2);
    var_s0_5 = 0;
    sp66 -= 6;
    do {
        sp70 = 0;
        sp74 = var_s0_5;
        sp64 = var_s0_5 * 0x40 + 0xBE;
        temp_v0_4 = ((s32 *)&D_8008B2BC)[var_s0_5];
        sp54 = temp_v0_4;
        func_8008AE60((u8 *)&D_8008AD58, &sp50);
        var_s0_5 += 1;
    } while (var_s0_5 < 2);
    sp64 = 0x20;
    var_s0_5 = 3;
    do {
        sp66 = var_s0_5 * 0xC + 0x40;
        temp_v0_5 = ((s32 *)&D_8008B2C4)[var_s0_5];
        sp54 = temp_v0_5;
        func_8008AE60((u8 *)&D_8008B030, &sp50);
            var_s0_5 -= 1;
    } while (var_s0_5 >= 0);
    var_s0_5 = 1;
    do {
        sp64 = var_s0_5 * 0x40 + 0xBE;
        temp_v0_6 = ((s32 *)&D_8008B2D4)[var_s0_5];
        sp54 = temp_v0_6;
        func_8008AE60((u8 *)&D_8008B030, &sp50);
            var_s0_5 -= 1;
    } while (var_s0_5 >= 0);
    sp64 = 0x20;
    var_s0_5 = 0;
    do {
        sp66 = var_s0_5 * 0xC + 0x78;
        temp_v0_7 = ((s32 *)&D_8008B2DC)[var_s0_5];
        sp54 = temp_v0_7;
        func_8008AE60((u8 *)&D_8008B030, &sp50);
        var_s0_5 += 1;
    } while (var_s0_5 < 2);
    sp64 = 0xB2;
    var_s0_5 = 2;
    do {
        sp66 = var_s0_5 * 0xC + 0x7E;
        temp_v0_8 = ((s32 *)&D_8008B2E4)[var_s0_5];
        sp54 = temp_v0_8;
        func_8008AE60((u8 *)&D_8008B030, &sp50);
            var_s0_5 -= 1;
    } while (var_s0_5 >= 0);
    sp34 = 0x1C;
    sp38 = 0x100;
    sp3C = 2;
    sp3E = 1;
    descriptor_color = 0x202020;
    sp30 = descriptor_color;
    sp28 = 0;
    sp2C = var_s4;
    sp3A = 0x1C;
    sp36 = 0x1C;
    func_8008ABD4(&D_8008AA40, &sp28);
    sp3A = 0x34;
    sp36 = 0x3C;
    func_8008ABD4(&D_8008AA40, &sp28);
    sp3A = 0x2E;
    sp36 = 0x74;
    func_8008ABD4(&D_8008AA40, &sp28);
    sp34 = 0x20;
    sp36 = 0xA6;
    sp38 = 0x40;
    sp3A = 0x18;
    func_8008ABD4(&D_8008AB44, &sp28);
    sp34 = 0xCA;
    sp3A = 8;
    sp38 = 0x40;
    sp3E = 0;
    sp40 = 2;
    do {
        sp30 = 0xFF << (sp40 * 8);
        sp36 = (sp40 * 0xC) + 0x7E;
        func_8008ABD4(&D_8008AA84, &sp28);
        temp_v0_9 = sp40 - 1;
        sp40 = temp_v0_9;
    } while (temp_v0_9 >= 0);
    sp3A = 8;
    sp30 = 0xFFFFFF;
    sp3C = 0;
    sp3E = 0;
    sp40 = 2;
    do {
        sp36 = ((sp40 + 1) * 0xC) + 0x40;
        func_8008ABD4(&D_8008AAE4, &sp28);
        temp_v0_10 = sp40 - 1;
        sp40 = temp_v0_10;
    } while (temp_v0_10 >= 0);
}
