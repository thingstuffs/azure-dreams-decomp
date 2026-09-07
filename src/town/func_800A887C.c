#include "common.h"

typedef struct S_800A5FDC_0 {
    s32 unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5FDC_0;   /* state in func_800A5FDC */

typedef struct S_800A5FDC_1 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xB4];
    union { s16 s; u16 u; } unk_C8;   /* accessed as both */
} S_800A5FDC_1;   /* globals in func_800A5FDC */

typedef struct S_800A5FDC_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A5FDC_2;   /* table in func_800A5FDC */

typedef struct S_800A5FDC_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A5FDC_3;   /* coordinates in func_800A5FDC */


extern s32 func_800374F4();
extern s32 func_8003BD84();
extern void func_80053DA8();
extern s32 func_8008C180();
extern s16 func_80094BC8();
extern void func_80094C1C();
extern void func_80094F58();
extern void func_80095094();
extern void func_80095388();
extern void func_800954F4();
extern s16 func_80095978();
extern void func_80095A94();
extern void func_80095C80();
extern void func_80097844();
extern void func_800A55CC();
extern s32 func_800A5894();
extern s32 func_800C1D44();
extern int abs(int);

extern u8 D_80083160[];
extern u8 D_80083780[];
extern s32 D_800A58CC;
extern u8 D_800CFCEE[];
extern u8 D_800FE488[];
extern s32 D_80100E20[];


void func_800A5FDC(u8 *state, u8 *table, void *arg2)
{
    u8 *context;
    u8 *globals;
    u8 *coordinates;
    s32 value;
    s32 delta;
    s32 quotient;
    s32 flags;
    s32 adjustment;
    s16 result;

    context = arg2;
    globals = D_80083160;
    func_80095C80(table);

    ((S_800A5FDC_0 *)state)->unk_0A.s--;
    if (((S_800A5FDC_0 *)state)->unk_0A.u <= 0) {
        ((S_800A5FDC_0 *)state)->unk_0A.s = func_800374F4(3) + 5;
        value = func_800374F4(2);
        func_80097844(table, (u16)value + 2);
    }

    flags = ((S_800A5FDC_1 *)globals)->unk_08;
    if (flags & 0xF000) {
        func_80094C1C(state);
        result = func_80094BC8(((S_800A5FDC_1 *)globals)->unk_08,
                               ((S_800A5FDC_1 *)globals)->unk_C8.s);
        if (result != -1) {
            func_80094F58(result, D_80100E20[0], table);
        }
        value = func_800374F4(1);
        func_80097844(table, (u16)value);
        goto after_updates;
    }

    if (flags & 0x10) {
        func_80095094(table);
    }
    func_80095094(table);

after_updates:
    result = func_80095978(table, D_800FE488);
    if (((S_800A5FDC_2 *)table)->unk_0A >= result) {
        func_80095A94(table, result, D_800FE488);
        coordinates = D_80083780;
        goto coordinates_ready;
    }

    if (D_800CFCEE[1] != 0) {
        ((S_800A5FDC_2 *)table)->unk_14 = 0;
        func_800954F4(table);
        coordinates = D_80083780;
        goto coordinates_ready;
    }

    func_80095388(table);
    coordinates = D_80083780;
coordinates_ready:
    value = func_8008C180(((S_800A5FDC_3 *)coordinates)->unk_02,
                          ((S_800A5FDC_3 *)coordinates)->unk_06);
    if (func_800C1D44((u16)value) != 0) {
        ((S_800A5FDC_2 *)table)->unk_14 -= func_800A5894(table);
    }

    value = func_8003BD84(((S_800A5FDC_2 *)table)->unk_0C,
                          ((S_800A5FDC_2 *)table)->unk_10);
    if (D_80100E20[0] != 0) {
        delta = abs(D_80100E20[0] - value);
        quotient = (s32)((u32)delta * 7U) / D_80100E20[0];
        if ((((S_800A5FDC_1 *)globals)->unk_04 % (quotient + 2)) == 0) {
            func_80053DA8(0x60A);
        }
    }

    if (value == 0) {
        ((S_800A5FDC_1 *)globals)->unk_C8.u =
            (((S_800A5FDC_1 *)globals)->unk_C8.u + 8) & 0xFFF0;
    }

    value /= 0x10000;
    if (((S_800A5FDC_1 *)globals)->unk_08 & 4) {
        adjustment = ((S_800A5FDC_1 *)globals)->unk_C8.u + 0x10;
        ((S_800A5FDC_1 *)globals)->unk_C8.u = adjustment + value;
    }
    if (((S_800A5FDC_1 *)globals)->unk_08 & 8) {
        adjustment = ((S_800A5FDC_1 *)globals)->unk_C8.u - 0x10;
        ((S_800A5FDC_1 *)globals)->unk_C8.u = adjustment - value;
    }

    if ((((S_800A5FDC_1 *)globals)->unk_10 & 0x10) &&
        (D_800CFCEE[0] == 0)) {
        func_800A55CC(state, table, context);
        goto done;
    }

    if (((S_800A5FDC_1 *)globals)->unk_10 & 0x100) {
        ((S_800A5FDC_0 *)state)->unk_00 = (s32)&D_800A58CC;
        ((S_800A5FDC_0 *)state)->unk_0A.u = 8;
    }
done:
    return;
}
