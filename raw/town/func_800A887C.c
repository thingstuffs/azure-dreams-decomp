#include "common.h"

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

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

    FIELD(state, u16, 0xA)--;
    if (FIELD(state, s16, 0xA) <= 0) {
        FIELD(state, u16, 0xA) = func_800374F4(3) + 5;
        value = func_800374F4(2);
        func_80097844(table, (u16)value + 2);
    }

    flags = FIELD(globals, s32, 8);
    if (flags & 0xF000) {
        func_80094C1C(state);
        result = func_80094BC8(FIELD(globals, s32, 8),
                               FIELD(globals, s16, 0xC8));
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
    if (FIELD(table, s16, 0xA) >= result) {
        func_80095A94(table, result, D_800FE488);
        coordinates = D_80083780;
        goto coordinates_ready;
    }

    if (D_800CFCEE[1] != 0) {
        FIELD(table, s32, 0x14) = 0;
        func_800954F4(table);
        coordinates = D_80083780;
        goto coordinates_ready;
    }

    func_80095388(table);
    coordinates = D_80083780;
coordinates_ready:
    value = func_8008C180(FIELD(coordinates, s16, 2),
                          FIELD(coordinates, s16, 6));
    if (func_800C1D44((u16)value) != 0) {
        FIELD(table, s32, 0x14) -= func_800A5894(table);
    }

    value = func_8003BD84(FIELD(table, s32, 0xC),
                          FIELD(table, s32, 0x10));
    if (D_80100E20[0] != 0) {
        delta = abs(D_80100E20[0] - value);
        quotient = (s32)((u32)delta * 7U) / D_80100E20[0];
        if ((FIELD(globals, u16, 4) % (quotient + 2)) == 0) {
            func_80053DA8(0x60A);
        }
    }

    if (value == 0) {
        FIELD(globals, u16, 0xC8) =
            (FIELD(globals, u16, 0xC8) + 8) & 0xFFF0;
    }

    value /= 0x10000;
    if (FIELD(globals, s32, 8) & 4) {
        adjustment = FIELD(globals, u16, 0xC8) + 0x10;
        FIELD(globals, u16, 0xC8) = adjustment + value;
    }
    if (FIELD(globals, s32, 8) & 8) {
        adjustment = FIELD(globals, u16, 0xC8) - 0x10;
        FIELD(globals, u16, 0xC8) = adjustment - value;
    }

    if ((FIELD(globals, s32, 0x10) & 0x10) &&
        (D_800CFCEE[0] == 0)) {
        func_800A55CC(state, table, context);
        goto done;
    }

    if (FIELD(globals, s32, 0x10) & 0x100) {
        FIELD(state, s32, 0) = (s32)&D_800A58CC;
        FIELD(state, s16, 0xA) = 8;
    }
done:
    return;
}
