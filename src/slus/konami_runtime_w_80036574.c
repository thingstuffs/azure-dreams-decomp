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

/* Decrement the countdown, restoring the callback on expiry or updating the selection from state flags. */
void func_80036574(Object *object) {
    u16 ticks_left;
    u8 *state;

    state = D_80083160;
    ticks_left = object->unk64 - 1;
    object->unk64 = ticks_left;
    if ((s16)ticks_left <= 0) {
        object->unk4d = 0xff;
        object->unk51 = 0;
        object->child->unk27 = object->child->unk26;
        object->unk68 = func_800364BC;
    } else {
        if ((*(u32 *)(state + 0x10)) & 0x20) {
            object->unk4d = object->child->unk26 - 1;
            func_8003661C(object);
        } else if ((*(u32 *)(state + 0x10)) & 0x40) {
            object->unk4d = 0;
            func_8003661C(object);
        }
    }
}
