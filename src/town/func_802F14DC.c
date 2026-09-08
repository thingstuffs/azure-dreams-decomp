#include "common.h"

extern void func_8007BEF0(s32 arg0) __attribute__((noreturn));
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_80404DBC(s32 arg0);
extern void func_804077D4(s32 arg0);

extern u8 D_8040086C[];
extern u8 D_80400894[];
extern s32 D_8008DAB4[3];
extern s32 D_8008DAB0[4];

/* Processes the object's two handles and sets the object and global high-bit flags. */
void func_802F14DC(void *object) {
    u16 object_flags;
    s32 global_flags;

    if (object == 0) {
        func_8007C040(D_8040086C, D_80400894, 0x183);
        func_8007BEF0(1);
    }

    func_80404DBC(*(s32 *)((u8 *)object + 0x40));
    func_804077D4(*(s32 *)((u8 *)object + 0x44));

    object_flags = *(u16 *)((u8 *)object + 0x1E);
    global_flags = D_8008DAB4[0];
    object_flags |= 0x8000;
    global_flags |= 0x8000;
    *(u16 *)((u8 *)object + 0x1E) = object_flags;
    D_8008DAB0[1] = global_flags;
}
