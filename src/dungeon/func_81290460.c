/* Relink of matched dungeon/dungeonProcessGlobalEffectSlotsAfterReset at file 0x1274460; imports and data use paired retail relocations. */
#include "common.h"

extern void func_80098E28(s32 node);
extern s32 D_80161714;
extern s32 D_80161710;
extern s16 D_80161718;
extern s32 D_80160F90;
extern s32 D_80160FBC;

typedef struct FlagsPage {
    u8 pad_00[0x3714];
    u16 unk_3714;
    s16 unk_3716;
    s16 unk_3718;
    s16 unk_371A;
    s32 unk_371C;
} FlagsPage;

typedef struct ActiveState {
    u8 pad_00[0xB8];
    s16 unk_B8;
    s8 unk_BA;
} ActiveState;

/* Resets state and processes occupied entries in the two-slot object table. */
void func_80160C60(void) {
    s16 slot_index;
    s16 next_slot;
    s32 object_addr;
    s32 slot_offset;
    s32 saved_state;
    s32 saved_value;
    ActiveState *active_state;
    void *object_header;
    u8 *table_page;
    u32 high_bit;
    FlagsPage *flags_base;
    u16 state_flags;

    slot_index = 0;
    table_page = (u8 *)0x800E0000;
    high_bit = 0x80000000;
    flags_base = (FlagsPage *)0x80010000;
    active_state = (ActiveState *)(D_80161710 + 0x20);
    active_state->unk_BA = 1;
    state_flags = flags_base->unk_3714;
    D_80161718 = 0;
    *(s16 *)((u8 *)flags_base + 0x371A) = 0;
    *(s16 *)((u8 *)flags_base + 0x3718) = 0;
    *(s16 *)((u8 *)flags_base + 0x3716) = 0;
    state_flags = (state_flags | 9) & 0xFFEF;
    flags_base->unk_3714 = state_flags;
    saved_state = D_80160F90;
    flags_base->unk_371C = saved_state;
    saved_value = D_80160FBC;
    active_state->unk_B8 = 0;
    D_80161714 = saved_value;

    do {
        slot_offset = (slot_index << 16) >> 14;
        object_addr = *(s32 *)(slot_offset + *(s32 *)(table_page + 0x397C) + 0xAC);
        if (object_addr != 0) {
            func_80098E28(object_addr);
            object_header = (void *)(*(s32 *)(slot_offset + *(s32 *)(table_page + 0x397C) + 0xAC) - 0x20);
            *(u32 *)((u8 *)object_header + 0x10) |= high_bit;
        }
        next_slot = slot_index + 1;
        slot_index = next_slot;
    } while (next_slot < 2);
}
