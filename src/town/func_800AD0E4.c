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

/* Update the object and dispatch actions based on its value, timer, and state flags. */
void func_800AA844(Obj800AD0E4 *timer_obj, Obj800AD0E4 *object, s32 action_arg) {
    State80083160 *state = &D_80083160;
    s16 next_value;
    u16 timer;

    func_80095C80(object);
    func_80095094(object);
    next_value = func_80095978(object, D_800FE488);

    if ((next_value - (s16)object->field_A) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094378(timer_obj, object, action_arg);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        func_80095A94(object, next_value, D_800FE488);
    }

    timer = timer_obj->field_A - 1;
    timer_obj->field_A = timer;
    if ((s16)timer < 0) {
        func_80093D48(timer_obj, object, action_arg);
        return;
    }

    if (state->field_8 & 0xF000) {
        func_80093ED8(timer_obj, object, action_arg);
        return;
    }

    if (state->field_10 & 0x10) {
        func_800942B0(timer_obj, object, action_arg);
        return;
    }

    func_800A9F14(object);
}
