#include "common.h"

extern void func_80018B58(s32);
extern void func_80018BD0(s32);
extern s32 func_80018C50(s32);

typedef void (*Callback)(s32, s32);

typedef struct Inner {
    u8 pad[0x2F8];
    Callback callback;
} Inner;

typedef struct Outer {
    u8 pad[0x20];
    Inner *inner;
} Outer;

extern Outer *D_80016000;

/* Runs the conditional action or invokes the fallback callback. */
s32 func_800169B4(void) {
    Outer *callback_owner;

    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);

    if (func_80018C50(0x679) == 0) {
        goto fallback;
    }
    if (func_80018C50(0x67A) != 0) {
        goto fallback;
    }

    func_80018B58(0x67E);
    return 1;

fallback:
    callback_owner = D_80016000;
    callback_owner->inner->callback(0x10, 0x200);
    return 0;
}
