#include "common.h"

typedef struct {
    u8 pad0[0xA];
    u16 field_A;
} Obj800AD0E4;

typedef struct {
    u8 pad0[8];
    u32 field_8;
    u8 padC[4];
    u32 field_10;
} State80083160;

extern void func_80093D48(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void func_80093ED8(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void func_800942B0(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void func_80094378(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void func_80095094(Obj800AD0E4 *);
extern s16 func_80095978(Obj800AD0E4 *, void *);
extern void func_80095A94(Obj800AD0E4 *, s16, void *);
extern void func_800A9F14(Obj800AD0E4 *);

extern State80083160 D_80083160;
extern u8 D_800CFCEF[9];
extern u8 D_800FE488[9];

void func_800AA844(Obj800AD0E4 *arg0, Obj800AD0E4 *arg1, s32 arg2) {
    State80083160 *state = &D_80083160;
    s16 value;
    u16 timer;

    func_80095C80(arg1);
    func_80095094(arg1);
    value = func_80095978(arg1, D_800FE488);

    if ((value - (s16)arg1->field_A) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094378(arg0, arg1, arg2);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        func_80095A94(arg1, value, D_800FE488);
    }

    timer = arg0->field_A - 1;
    arg0->field_A = timer;
    if ((s16)timer < 0) {
        func_80093D48(arg0, arg1, arg2);
        return;
    }

    if (state->field_8 & 0xF000) {
        func_80093ED8(arg0, arg1, arg2);
        return;
    }

    if (state->field_10 & 0x10) {
        func_800942B0(arg0, arg1, arg2);
        return;
    }

    func_800A9F14(arg1);
}
