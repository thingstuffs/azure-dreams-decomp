#include "common.h"

typedef struct Child {
    u8 unk00[0x22];
    u8 unk22[2];
    u8 unk24[2];
    u8 unk26;
    u8 unk27;
} Child;

typedef struct Object Object;

struct Object {
    u8 unk00[0x4d];
    u8 unk4d;
    u8 unk4e[3];
    u8 unk51;
    u8 unk52[0x12];
    u16 unk64;
    u8 unk66[2];
    void (*unk68)(Object *);
    u8 unk6c[8];
    Child *child;
};

extern u8 D_80083160[];
extern void func_800364BC(Object *arg0);
extern void func_8003661C(Object *arg0);

void func_80036574(Object *arg0) {
    u16 value;
    u8 *state;

    state = D_80083160;
    value = arg0->unk64 - 1;
    arg0->unk64 = value;
    if ((s16)value <= 0) {
        arg0->unk4d = 0xff;
        arg0->unk51 = 0;
        arg0->child->unk27 = arg0->child->unk26;
        arg0->unk68 = func_800364BC;
    } else {
        if ((*(u32 *)(state + 0x10)) & 0x20) {
            arg0->unk4d = arg0->child->unk26 - 1;
            func_8003661C(arg0);
        } else if ((*(u32 *)(state + 0x10)) & 0x40) {
            arg0->unk4d = 0;
            func_8003661C(arg0);
        }
    }
}
