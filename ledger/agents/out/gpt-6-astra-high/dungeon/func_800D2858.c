#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u32 word0;
    u32 word1;
} Copy8 __attribute__((packed));

typedef struct {
    u8 pad0[8];
    void *child;
    void *sub;
    u8 *d81d4;
} Entry;

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800DEC00[];
extern s32 D_80083460[3];
extern s32 D_800814A0[];
extern s32 D_800D81D4;

extern void *func_8003FD64(void *, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A56E0(s32);

/* Spawns effect entries and marks the controller finished after two delays. */
void func_800D7FB8(void *controller) {
    u8 *entry_data;
    s16 state;
    s32 spawn_index;
    u16 finish_timer;
    u16 effect_timer;
    s32 resource_word;
    void *sub_data;
    Entry *entry;
    u8 *counter_base;

    state = FIELD(controller, s16 *, 0);
    if (state == 1) {
        goto timer_state;
    }
    if (state >= 2) {
        goto check_ff;
    }
    if (state == 0) {
        goto init_state;
    }
    goto done;

check_ff:
    if (state == 0xFF) {
        goto ff_state;
    }
    goto done;

init_state:
    FIELD(controller, s16 *, 2) = 0x3C;
    FIELD(controller, s16 *, 0) = (s16)((u16)FIELD(controller, s16 *, 0) + 1);
    func_800A56E0(0x600);
    spawn_index = 0x96;
    do {
        entry = func_8003FD64((void *)0x312, D_80083498);
        if (entry != NULL) {
            entry_data = (u8 *)entry + 0x20;
            FIELD(entry, void **, 0x10) = &D_800D81D4;
            func_8004491C(entry, D_80045340);
            sub_data = entry->sub;
            FIELD(entry->child, u16 *, 2) = FIELD(controller, u16 *, 4);
            FIELD(entry->child, u16 *, 6) = FIELD(controller, u16 *, 6);
            FIELD(entry->child, u16 *, 0xA) = FIELD(controller, u16 *, 8);
            FIELD(sub_data, s16 *, 0x1E) = 0x400;
            FIELD(sub_data, s16 *, 0x1C) = 0x400;
            FIELD(sub_data, s16 *, 0x10) = 0x20;
            FIELD(sub_data, u8 **, 0) = D_800DEC00;
            FIELD(sub_data, u16 *, 0x14) = (u16)(FIELD(sub_data, u16 *, 0x14) | 0xC);
            resource_word = FIELD(D_800DEC00, s32 *, 4);
            FIELD(sub_data, s8 *, 4) = 0;
            FIELD(sub_data, s8 *, 5) = 0;
            FIELD(sub_data, s32 *, 0xC) = 0;
            FIELD(sub_data, s32 *, 8) = resource_word;
            __builtin_memcpy((u8 *)entry + 0x2C, (u8 *)controller + 4, 8);
            FIELD(entry_data, s16 *, 0x4A) = (spawn_index & 1) ? 1 : -1;
            FIELD(entry->child, u16 *, 0xA) = FIELD(controller, u16 *, 8);
        }
        spawn_index -= 1;
    } while (spawn_index >= 0);

timer_state:
    effect_timer = (u16)(FIELD(controller, u16 *, 2) - 1);
    FIELD(controller, u16 *, 2) = effect_timer;
    if ((effect_timer << 0x10) <= 0) {
        FIELD(controller, u16 *, 2) = 8U;
        FIELD(controller, s16 *, 0) = (s16)0xFF;
    }
    goto done;

ff_state:
    finish_timer = (u16)(FIELD(controller, u16 *, 2) - 1);
    FIELD(controller, u16 *, 2) = finish_timer;
    if ((finish_timer << 0x10) <= 0) {
        counter_base = (u8 *)D_80083460;
        FIELD(counter_base, u16 *, 0xA) = (u16)(FIELD(counter_base, u16 *, 0xA) - 1);
        FIELD(controller, u16 *, -2) = (u16)(FIELD(controller, u16 *, -2) | 0x8000);
        FIELD(D_800814A0, s32 *, 0) = FIELD(D_800814A0, s32 *, 0) | 0x8000;
    }

done:
    return;
}
