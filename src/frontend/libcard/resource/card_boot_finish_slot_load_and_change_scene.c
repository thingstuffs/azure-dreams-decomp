#include "shared/runtime_dispatch.h"
#include "common.h"

/* S_80082E60: shared global state struct; field_16 (u16) has bit 0x2 set here.
 * Same struct family as src/code2.c / src/w_80041818.c's D_80082E60. */


struct UnkStruct1E; void card_boot_destroy_slot_selection_menu(struct UnkStruct1E *);
#include "frontend/libcard/interfaces.h"
void func_80040AA0(s16);
extern void runtime_save_or_restore_state(void);

/* Selects object and global modes, sets the shared state flag, and runs updates. */
void card_boot_finish_slot_load_and_change_scene(void *object) {
    s16 object_mode;
    s32 global_mode;
    u16 state_flags;
            /* D_80013714 and D_80010208 sit on the same 64K page; retail keeps ONE
     * lui (0x8001) live in a callee-saved reg ($s1) across both accesses and
     * across the two intervening calls. Pin the page base to a saved hard
     * register so it survives the calls instead of being rematerialized. */
    u8 *global_page = (u8 *)0x80010000;

    card_boot_close_events_and_resume_timer();
    object_mode = 1;
    if (*(s32 *)((char *)object + 0x44) == 0) {
        object_mode = 3;
    }
    state_flags = D_80082E60.flags16;
    *(s16 *)(global_page + 0x3714) = object_mode;
    D_80082E60.flags16 = state_flags | 2;
    card_boot_destroy_slot_selection_menu(object - 0x20);
    runtime_save_or_restore_state();
    global_mode = 6;
    if (*(u16 *)(global_page + 0x208) != 0) {
        global_mode = 5;
    }
    func_80040AA0(global_mode);
}
