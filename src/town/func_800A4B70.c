#include "common.h"

typedef struct Func800A4B70Inner {
    u8 pad_00[0x6e];
    u16 value;
} Func800A4B70Inner;

typedef struct Func800A4B70Object {
    u8 pad_00[0x10];
    Func800A4B70Inner *inner;
    u8 pad_14[0x0c];
    s16 flag;
} Func800A4B70Object;

typedef struct Func800A4B70Output {
    u8 pad_00[0x1a];
    s16 value;
} Func800A4B70Output;

extern void func_800A22FC(void) __attribute__((noreturn));

void func_800A22D0(Func800A4B70Object *arg0, s32 arg1, Func800A4B70Output *arg2) {
    Func800A4B70Inner *inner = arg0->inner;

    if (arg0->flag != 0) {
        arg2->value = inner->value;
        func_800A22FC();
    }
    arg2->value = -inner->value;
}
