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
    register u32 page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    Obj *obj;

    page = 0x80170000;
    if (state_selector == 0) {
        obj = (Obj *)((u8 *)D_80175D58[0] + 0x20);
    } else {
        obj = (Obj *)((u8 *)*(Obj **)(page + 0x5D5C) + 0x20);
    }
    obj->value = value;
    obj->timer = 0;
}
