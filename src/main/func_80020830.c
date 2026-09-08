#include "common.h"

extern void func_8007BEF0(s32 arg0) __attribute__((noreturn));
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_80407160(s32 arg0);

extern s32 D_804007A4[];
extern s32 D_804007CC[];

/* Assert a valid card slot, store its value, and process its embedded state. */
void func_80020830(s32 slot_addr, s32 slot_value) {
    s32 slot_state_addr;

    slot_state_addr = slot_addr + 0x20;
    if (slot_addr == 0) {
        func_8007C040(D_804007A4, D_804007CC, 0x153);
        func_8007BEF0(1);
        slot_addr = 1;
    }
    *(s32 *)(slot_addr + 0x44) = slot_value;
    func_80407160(slot_state_addr);
}
