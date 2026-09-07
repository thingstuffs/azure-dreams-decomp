#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((s8 *)(ptr) + (offset)))

typedef s32 (*Func)(s32, s32);

typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
} Entity;

extern void func_800253C0(Entity *);
extern u8 D_80082E6A[];
extern Func D_800294A8[];
extern struct { s32 v; s32 pad[2]; } D_800814A0;

void func_80025480(Entity *arg0) {
    if (arg0) {
        func_800253C0(arg0);
        if (D_80082E6A[0] == 1 || D_800294A8[arg0->field_18](arg0->field_0, arg0->field_10)) {
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0.v |= 0x8000;
        }
    }
}
