#include "common.h"

extern s32 func_80044144(s32 a0, s32 a1, void *a2, void *a3);
extern void func_8004EC20(void *a0);
extern void func_8004ED00(void *a0);

typedef struct S_8004ED5C {
    void (*unk18)(void *);
} S_8004ED5C;

/* Registers the object's input handler and installs its update callback on success. */
void func_8004ED5C(void *object)
{
    void *handler_object = object;

    if (func_80044144(1, 0x1E, (void *)func_8004EC20, handler_object) != 0) {
        ((S_8004ED5C *)((u8 *)handler_object - 0x10))->unk18 = func_8004ED00;
    }
}
