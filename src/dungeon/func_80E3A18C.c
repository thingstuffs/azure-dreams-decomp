#include "common.h"

extern void func_80042710(void *, void *);
extern s32 func_80042900(void *, s32);
extern void func_80099FDC(void *);
extern u8 *func_800A17E8(s32, s32);
extern s32 func_800A1BD0(void *);
extern void func_800A2B04(s32, s32, s32);
extern void func_800ACB98(void *, s32, s32, void *);
extern void func_80173D40(void *, s32, void *, void *);

extern s32 D_80083460;
extern u8 *D_800E3D7C;

/* Copies linked object data and transfers or releases its state. */
void func_8017398C(u8 *owner, s32 object_id, u8 *dest_object, u8 *dest_state)
{
    u8 *linked_object;
    u8 *linked_state;
    u8 *source_object;
    u8 *state_slot;
    u8 *state_table;
    u8 *kind_entry;
    u8 *counter_data;
    u8 *active_data;
    s32 call_result;
    u8 kind_unlisted;
    u8 can_release;
    s32 state_kind;
    u8 kind_byte;
    long slot_address;

    linked_object = *(u8 **)(owner + 0xA4);
    linked_state = linked_object + 0x20;
    source_object = *(u8 **)(linked_object + 0xC);
    dest_object[0x24] = source_object[0x24];
    dest_object[0x25] = source_object[0x25];
    *(u16 *)(dest_state + 0x88) = *(u16 *)(linked_state + 0x88);
    func_800A2B04(object_id, dest_object[0x24], dest_object[0x25]);

    linked_object = *(u8 **)(owner + 0xA4);
    if (*(u16 *)(linked_object + 0x1E) & 0x8000) {
        if ((linked_state[0x13] == 0x1E) && (linked_state[0x28] != 0)) {
            dest_state[0x6D] = 1;
        }

        if (*(s32 *)(dest_state + 0x14) & 0x4000) {
            call_result = func_800A1BD0(linked_state);
            state_table = D_800E3D7C;
            slot_address = (s32)(s16)call_result * 4;
            slot_address += (long)state_table;
            state_slot = (u8 *)slot_address;
            *(u8 **)(state_slot + 0xAC) = dest_state;
            *(s32 *)(state_slot + 0xE4) = 0;
            if (*(u8 **)(state_table + 0x60) == linked_state) {
                *(u8 **)(state_table + 0x60) = dest_state;
            }
        }

        if ((linked_state[0x13] != 0x1E) && (linked_state[0x28] == 0)) {
            counter_data = (u8 *)&D_80083460;
            (*(u16 *)(counter_data + 0xA))++;
        }

        *(s32 *)(dest_state + 0x14) = 0;
        *(s32 *)(dest_state + 0x1C) = 0;
        func_80042710(dest_state, linked_state);
        *(u32 *)(dest_state + 0x14) &= 0xDFFFFFFF;
        call_result = func_80042900(dest_state, 1);
        if ((call_result << 16) != 0) {
            *(u32 *)(dest_state + 0x1C) |= 0x200;
        } else {
            *(u32 *)(dest_state + 0x1C) &= ~0x200;
        }

        dest_state[0x13] = 0x1E;
        func_80099FDC(owner - 0x20);
        *(u32 *)(dest_state + 0x60) = *(u32 *)(linked_state + 0x60);
        func_80173D40(owner, object_id, dest_object, dest_state);
        *(u32 *)(owner + 0xA4) = 0;
        return;
    }

    if ((((s8)linked_state[0x13] - 1) < 0) ||
        (linked_state[0x13] == 0x1E) ||
        (owner[0x9B] != 0)) {
        return;
    }

    state_kind = linked_object[0x33];
    kind_byte = state_kind;
    kind_entry = func_800A17E8(kind_byte, 1);
    if (kind_entry == 0) {
        kind_unlisted = 1;
    } else {
        kind_unlisted = kind_entry[1] != kind_byte;
    }
    can_release = kind_unlisted;
    if (can_release == 0) {
        return;
    }

    kind_entry = func_800A17E8(state_kind, 3);
    if ((kind_entry != 0) && (kind_entry[1] == state_kind)) {
        kind_unlisted = 0;
    }
    can_release = kind_unlisted;
    if (can_release == 0) {
        return;
    }

    active_data = (u8 *)&D_80083460;
    if (*(u8 **)(active_data + 0xC) == linked_state) {
        *(u8 **)(active_data + 0xC) = 0;
    }
    func_800ACB98(linked_state, *(s32 *)(linked_state - 0x18),
                  *(s32 *)(linked_state - 0x14), linked_state);
    owner[0x9B]++;
}
