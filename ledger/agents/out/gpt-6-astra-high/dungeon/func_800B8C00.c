#include "common.h"

extern void func_8008D344(void *arg0, void *arg1, void *arg2, void *arg3);
extern s32 func_80098864(void *arg0, s32 arg1);
extern s32 func_80098B38(void *arg0);
extern s32 func_800997FC(void *arg0, s32 arg1, s32 arg2);
extern s32 func_800A5F38(void *arg0, void *arg1);
extern s32 func_800A6480(void *arg0, void *arg1, s32 arg2);
extern s32 func_800AD6FC(void *arg0, s32 arg1, void *arg2);

typedef struct {
    s16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[12];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern DungeonGroup D_80073414[];
extern u8 D_80082E80[];
extern u8 D_80083460[];
extern s32 D_80083780[];
extern u16 D_800DDE84[];
extern s32 D_800E3D7C[];

/* Dispatch an item action using its flags and the target selector, then update the counter. */
s32 func_800BE360(void *target, void *item, s16 action_type, s32 action_value) {
    s32 item_index;
    s32 group_index;
    DungeonItem *entries;
    u16 *selector_table;
    u8 *counter_base;
    u8 *fallback_page;
    u8 *selector_page;
    s32 selector_index;
    s32 selector;
    s16 item_flags;
    u16 selector_bits;

    if (action_type == 0xD) {
        return func_80098864(item, action_value);
    }
    if ((s32) target == D_800E3D7C[0]) {
        *(void **)((u8 *)target + 0x110) = item;
        func_8008D344(target, D_80083780, D_80082E80, target);
        return 0;
    }
    if ((u32)target <= 0x9FFFFFFFU) {
        func_800A6480(target, item, action_type);
        group_index = *((u8 *)item + 1);
        item_index = *((u8 *)item + 0);
        entries = D_80073414[group_index].entries;
        item_flags = entries[item_index].flags;
        if (!(item_flags & 0x8000)) {
            selector_page = (u8 *)0x800E0000;
            ASM_KEEP(selector_page);   /* MATCH pin: retail immediate-load split depends on it */
            selector_index = *((u8 *)target + 0x13);
            ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
            selector_page -= 0x217C;
            ASM_KEEP(selector_page);   /* MATCH pin: retail immediate-load split depends on it */
            selector_bits = ((u16 *)selector_page)[selector_index];
            selector = selector_bits & 3;
        } else {
            selector_table = D_800DDE84;
            selector_bits = selector_table[*((u8 *)target + 0x13)];
            selector = (selector_bits >> 4) & 3;
        }
        if (func_800AD6FC(target, selector, item) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
        func_80098B38(item);
    } else {
        fallback_page = (u8 *)0x800E0000;
        ASM_KEEP(fallback_page);   /* MATCH pin: load-bearing for the whole function shape */
        func_800997FC(fallback_page + 0x101C, action_value, action_type);
    }
    counter_base = D_80083460;
    *(u16 *)(counter_base + 0xA) = *(u16 *)(counter_base + 0xA) - 1;
    return 1;
}
