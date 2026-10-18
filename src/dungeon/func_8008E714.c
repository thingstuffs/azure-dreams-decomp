#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80093E74_7 {
    u8 pad_00[0xD0];
    union { void * s; s32 u; } unk_D0;   /* accessed as both */
} S_80093E74_7;   /* ((arg3->unk_8A * 4) + arg0) in store_recalled_familiar */


typedef struct S_80093E74_1 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_80093E74_1;

typedef struct S_80093E74_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x94];
    u8 unk_A8;
} S_80093E74_2;

typedef struct S_80093E74_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80093E74_3;

typedef struct S_80093E74_5 {
    void * unk_00;
    u8 pad_04[0x2C];
    s32 unk_30;
} S_80093E74_5;   /* Pointer addresses record offset 0x14. */




#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

typedef struct {
    s32 words[35];
} Copy140;

s32 func_80042900();                 /* extern */
void update_map_cell_flags_with_item_limit(u8, u8, s32);     /* extern */
s32 play_sound_if_enabled();                     /* extern */
extern void *D_800E3DF0[];
extern u8 D_800E3E48[];

/* Copy the indexed record into storage, clear its owner slot, and trigger an effect. */
void store_recalled_familiar(s32 slot_table, void *unused_arg1, void *unused_arg2, EntityRec *owner) {
    M2C_UNK effect_mask;
    u8 effect_x;
    u8 effect_y;
    s32 record_index;
    s16 saved_index;
    void **record_table;
    void **record_slot;
    S_80093E74_3 *stored_record;
    EntityRec *owner_state;
    S_80093E74_2 *source_record;
    void *unused_ptr;
    void *record_storage;
    void *owner_record;
    MovingTile *position;
    void *unused_ptr2;
    void *unused_ptr3;

    {
        s32 cleared_flags;
        u8 flags_index;
        S_80093E74_1 *slot_entry;
        void **source_table;
        u8 index_byte;

        slot_entry = ((S_80093E74_7 *)(((owner->unk_8A * 4) + slot_table)))->unk_D0.s;
        flags_index = slot_entry->unk_03;
        cleared_flags = flags_index & 0xDF;
        flags_index &= 0x1F;
        index_byte = (u8)flags_index;
        saved_index = index_byte;
        record_index = saved_index;
        source_table = D_800E3DF0;
        slot_entry->unk_03 = (u8) cleared_flags;
        record_slot = source_table + record_index;
        source_record = *record_slot;
    }
    if ((func_80042900(source_record, 0xA) << 0x10) != 0) {
        source_record->unk_13 = (u8) source_record->unk_A8;
    }
    record_storage = &D_800E3E48[((((record_index * 8) + record_index) * 4) - record_index) * 4];
    *record_slot = record_storage;
    *(Copy140 *) record_storage = *(Copy140 *) source_record;
    record_table = D_800E3DF0;
    stored_record = record_table[saved_index];
    stored_record->unk_14 = (s32) (stored_record->unk_14 & ~0x4000);
    ((S_80093E74_7 *)(((owner->unk_8A * 4) + slot_table)))->unk_D0.u = 0;
    owner_state = owner->target;
    owner_state->flags1C = (s32) (owner_state->flags1C | 0x400000);
    owner_record = owner->target;
    position = ((S_80093E74_5 *)((u8 *)owner_record - 0x14))->unk_00;
    effect_x = position->unk_24;
    effect_y = position->unk_25;
    effect_mask = 0x3000;
    if (((S_80093E74_5 *)((u8 *)owner_record - 0x14))->unk_30 & 0x2000) {
        effect_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(effect_x, effect_y, effect_mask);
    play_sound_if_enabled(0x704);
}
