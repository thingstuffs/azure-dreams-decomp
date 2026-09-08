#include "common.h"

extern void func_8003B0B8(void *, void *);
extern void *func_800373DC(s32);

extern u8 D_8052664C[];
extern u8 D_80526640[];
extern u8 D_8052B2A4[];

/* Runs setup and attaches D_8052B2A4 to the returned object, if present. */
s32 func_80810650(void) {
    void *object;

    func_8003B0B8(D_8052664C, D_80526640);
    object = func_800373DC(2);
    if (object == 0) {
        return 0;
    }
    *(void **)((u8 *)object + 0x10) = D_8052B2A4;
    return 0;
}
