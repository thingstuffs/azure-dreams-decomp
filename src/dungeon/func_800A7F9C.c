#include "common.h"

typedef struct {
    u8 pad00[0x1C];
    s32 unk1C;
    u8 pad20[4];
    u16 unk24;
    u8 pad26[0x40];
    u8 unk66;
} DungeonState;

extern s32 func_800990FC(DungeonState *, s32, u8 *, s32);
extern s32 func_80042900(DungeonState *arg0, s32 arg1);
extern s32 func_80099194(const void *arg0, s32 arg1);
extern s32 func_80099734(DungeonState *arg0, s32 arg1);
extern void func_80099290(s32 arg0);
extern void func_800A56E0(s32 arg0);
extern void func_800A5720(s32 arg0);

extern u8 D_80089084[];
extern u8 D_800E0CAE[];
extern u8 D_800E0CDC[];
extern u8 D_800E0CF3[];
extern u8 D_800E0D1B[];
extern u8 D_800E0D36[];

s32 func_800AD6FC(DungeonState *arg0, s32 arg1, u8 *arg2, s32 arg3) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s5;
    s32 var_s6;

    var_s5 = func_800990FC(arg0, arg1, arg2, arg3);
    var_s0 = var_s5;
    if ((func_80042900(arg0, 0x19) << 16) != 0) {
        func_80099290(func_80099194(D_80089084,
                                    func_80099734(arg0,
                                                  func_80099194(D_800E0CAE, var_s5))));
        func_800A5720(var_s5);
        return 0;
    }

    if ((arg1 == 3) && (arg2 != 0)) {
        if ((arg2[1] == 2) && (arg2[0] == 1)) {
            arg1 = 2;
        } else if ((arg2[1] == 0xC) && (arg2[0] == 6)) {
            arg1 = 2;
        }
    }

    var_s1 = arg0->unk24;
    var_s6 = var_s1;
    if (arg1 == 1) {
        goto mode_one;
    }
    if (arg1 < 2) {
        if (arg1 == 0) {
            goto mode_zero;
        }
        goto dispatch_done;
    }
    if (arg1 == 2) {
        goto mode_two;
    }
    if (arg1 == 3) {
        goto mode_three;
    }
    goto dispatch_done;

mode_zero:
    var_s0 = func_80099194(D_80089084,
                           func_80099734(arg0,
                                         func_80099194(D_800E0CDC, var_s0)));
    goto dispatch_done;

mode_one:
    var_s0 = func_80099194(D_800E0CF3, func_80099734(arg0, var_s0));
    var_s1 += 0x300;
    goto dispatch_done;

mode_two:
    ASM_USE2_NV(var_s0, var_s0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    var_s0 = func_80099194(D_800E0D1B, func_80099734(arg0, var_s0));
    if ((arg2 != 0) && (arg2[1] == 0xC) && (arg2[0] == 6)) {
        var_s1 += 0xA00;
    } else {
        var_s1 += 0x3200;
    }
    goto dispatch_done;

mode_three:
    var_s0 = func_80099194(D_800E0D36, func_80099734(arg0, var_s0));
    var_s1 += 0x6400;

dispatch_done:
    ASM_USE2_NV(var_s0, var_s0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    if ((arg2 != 0) || (arg1 == 0)) {
        func_80099290(var_s0);
        func_800A5720(var_s5);
    }
    if (var_s6 != var_s1) {
        func_800A56E0(0x51E);
    }
    if (var_s1 > 0x10000) {
        var_s1 = 0xFFFF;
    }
    arg0->unk24 = (u16)var_s1;
    if (((u8 *)arg0)[0x25] != 0) {
        arg0->unk1C &= ~8;
    }
    if (arg0->unk66 < ((u8 *)arg0)[0x25]) {
        ((u8 *)arg0)[0x25] = arg0->unk66;
        ((u8 *)arg0)[0x24] = 0xFF;
    }
    return arg1;
}
