#include "common.h"

extern void func_8007BEF0(s32 arg0) __attribute__((noreturn));
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);

extern s32 D_804007A4[];
extern s32 D_804007CC[];

extern s32 D_8008DAB4;

/* Asserts a valid card slot and sets its local and global status flags. */
void func_800207D4(s32 card_slot) {
    u16 slot_flags;
    s32 global_flags;
    if (card_slot == 0) {
        func_8007C040(D_804007A4, D_804007CC, 0x14B);
        func_8007BEF0(1);
        card_slot = 1;
    }
    slot_flags = *(u16 *)(card_slot + 0x1E);
    global_flags = D_8008DAB4;
    slot_flags |= 0x8000;
    global_flags |= 0x8000;
    *(u16 *)(card_slot + 0x1E) = slot_flags;
    D_8008DAB4 = global_flags;
}
