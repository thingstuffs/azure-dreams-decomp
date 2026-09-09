#include "common.h"

typedef struct {
    u8 pad[0x12];
    s16 value;
    u8 pad14[4];
    s16 timer;
} Obj;

extern Obj *D_80175D58[];
extern Obj *D_80175D5C[];

/* Sets the selected object value and clears its timer. */
void func_8016F96C(s32 state_selector, s16 value) {
    u32 page;
    Obj *obj;

    do {
        page = 0x80170000;
    } while (0);
    if (state_selector == 0) {
        obj = (Obj *)((u8 *)D_80175D58[0] + 0x20);
    } else {
        obj = (Obj *)((u8 *)*(Obj **)(page + 0x5D5C) + 0x20);
    }
    obj->value = value;
    obj->timer = 0;
}
