#include "common.h"

typedef struct {
    u8 pad[0x12];
    s16 value;
    u8 pad14[4];
    s16 timer;
} Obj;

extern Obj *D_80175D58[];
extern Obj *D_80175D5C[];

void func_8016F96C(s32 arg0, s16 arg1) {
    register u32 page ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
    Obj *obj;

    page = 0x80170000;
    if (arg0 == 0) {
        obj = (Obj *)((u8 *)D_80175D58[0] + 0x20);
    } else {
        obj = (Obj *)((u8 *)*(Obj **)(page + 0x5D5C) + 0x20);
    }
    obj->value = arg1;
    obj->timer = 0;
}
