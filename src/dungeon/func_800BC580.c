#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern u8 D_800E1532[];

extern void func_8008D344(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern void func_800A56E0(s32);
extern void func_800A5720(s8 *text);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, u16, s32);
extern void func_800C1F28(s32, s16);
extern s32 func_8003FA44(s32);

/* Applies a target action or processes occupied player slots and updates the action count. */
s32 func_800C1CE0(void *target, s32 action, s16 action_type, s32 action_arg) {
    s32 slot;
    s32 message_end;
    s32 message_start;
    s32 slot_entry;
    u8 *global_page;

    if (action_type == 0xD) {
        return func_80098864(action, action_arg);
    }

    global_page = (u8 *)0x800E0000;
    if (target == *(u8 **)(global_page + 0x3D7C)) {
        *(s32 *)((u8 *)target + 0x110) = action;
        func_8008D344(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFFU) {
        func_800A6480(target, action, action_type);
        if (func_800AD6FC(target, D_800DDE84[((u8 *)target)[0x13]] & 3, action) == 0) {
            func_800A5F38(target, action);
            return 1;
        }
    } else {
        message_start = func_800990FC();
        message_end = message_start;
        if ((*(s32 *)((u8 *)*(u8 **)(global_page + 0x3D7C) + 0xAC) != 0) ||
            (*(s32 *)((u8 *)*(u8 **)(global_page + 0x3D7C) + 0xB0) != 0)) {
            if (func_8003FA44(4) == 0) {
                return 0;
            }
            slot = 0;
            do {
                slot_entry = *(s32 *)((u8 *)*(u8 **)(global_page + 0x3D7C) + 0xAC + slot * 4);
                if (slot_entry != 0) {
                    func_800C1F28(slot_entry, (s16)slot);
                }
                slot += 1;
            } while (slot < 2);
            message_end = func_80099194(D_800E1532, message_end);
            func_800A56E0(0x501);
        } else {
            message_end = func_80099194(D_800E1532 + 0x17, message_start);
        }
        func_80099290(message_end);
        func_800A5720(message_start);
    }

    (((u16)dungeonStatus.unk_0A))--;
    func_80098B38(action);
    return 1;
}
