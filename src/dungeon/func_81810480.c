#include "common.h"


typedef s32 (*Func)(s32, s32);

typedef struct S_80025480_0_pre {
    u16 unk_00;
} S_80025480_0_pre;   /* the 0x2 bytes before arg0 in func_80025480, addressed as arg0[-1] */


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
            ((S_80025480_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            D_800814A0.v |= 0x8000;
        }
    }
}
