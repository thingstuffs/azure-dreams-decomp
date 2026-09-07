#include "common.h"

/* S_80082E60: shared global state struct; field_16 (u16) has bit 0x2 set here.
 * Same struct family as src/code2.c / src/w_80041818.c's D_80082E60. */
struct S_80082E60 {
    char pad0[0x16];
    u16 field_16;
};
extern struct S_80082E60 D_80082E60;

extern void func_80025D34();
extern void func_80027BF4(void);
extern void func_80040AA0();
extern void func_800439F8(void);

/* Selects object and global modes, sets the shared state flag, and runs updates. */
void func_800251A4(void *object) {
    s16 object_mode;
    s32 global_mode;
    u16 state_flags;
    /* D_80013714 and D_80010208 sit on the same 64K page; retail keeps ONE
     * lui (0x8001) live in a callee-saved reg ($s1) across both accesses and
     * across the two intervening calls. Pin the page base to a saved hard
     * register so it survives the calls instead of being rematerialized. */
    u8 *global_page = (u8 *)0x80010000;

    func_80027BF4();
    object_mode = 1;
    if (*(s32 *)((char *)object + 0x44) == 0) {
        object_mode = 3;
    }
    state_flags = D_80082E60.field_16;
    *(s16 *)(global_page + 0x3714) = object_mode;
    D_80082E60.field_16 = state_flags | 2;
    func_80025D34(object - 0x20, object_mode);
    func_800439F8();
    global_mode = 6;
    if (*(u16 *)(global_page + 0x208) != 0) {
        global_mode = 5;
    }
    func_80040AA0(global_mode);
}
