/* Item entry copy and its file-private helper. */
#include "common.h"
#include "town/shop/item_lookup.h"
typedef struct S_800422DC_Other S_800422DC_Other;
typedef struct S_800422DC_Self S_800422DC_Self;
typedef struct S_800423C0_Obj S_800423C0_Obj;
typedef struct S_800423C0_Src S_800423C0_Src;
void *runtime_get_mode_indexed_value();
/* extern */
void build_entity_slot_snapshot(S_800422DC_Self *snapshot, S_800422DC_Other *source);
void apply_actor_template_and_direction(S_800423C0_Obj *obj, s16 unused, S_800423C0_Src *source);
void func_80042640(void *obj, s16 monsterId);
void *memset(void *, s32, u32);
/* extern */
void *find_unused_default_pool_slot();
void *func_800B2344();
/* extern */
extern s32 town_actor_scratch;
typedef struct {
    s32 words[0x15];
} Record84;
extern Record84 town_slot_snapshot;
typedef struct Copy10 {
    s8 bytes[10];
} __attribute__((packed)) Copy10;
typedef struct S_8009FB2C_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_8009FB2C_0;
typedef struct S_8009FB2C_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_8009FB2C_1;
/* arg1 in copy_an_entry_slot_creating_associated_type_hex_13 */

typedef struct S_8009FB2C_2 {
    u8 pad_00[0x29C];
    void * unk_29C;
    s32 unk_2A0;
} S_8009FB2C_2;
extern s32 func_8009F6E4(void);

/* Copies an item into a slot and creates a saved actor record for type 0x13 entries. */
static void *copy_an_entry_slot_creating_associated_type_hex_13(s32 slot_index, S_8009FB2C_1 *source_entry) {
    u8 *copy_dst;
    u8 *copy_src;
    s32 record_index;
    void *detail_dst;
    S_8009FB2C_0 *entry;
    void *detail_src;
    S_8009FB2C_2 *slot;
    void *slot_base;

    entry = find_unused_default_pool_slot();
    entry->unk_00 = (u8) source_entry->unk_00;
    entry->unk_01 = (u8) source_entry->unk_01;
    entry->unk_02 = (u8) source_entry->unk_02;
    entry->unk_03 = (u8) source_entry->unk_03;
    if (entry->unk_01 == 0x13) {
        memset(&town_actor_scratch, 0, 0x54);
        func_80042640(&town_actor_scratch, entry->unk_00);
        apply_actor_template_and_direction(&town_actor_scratch, entry->unk_00, 0);
        {
            u8 *record_buffer;
            record_buffer = (u8 *)&town_slot_snapshot;
            copy_src = record_buffer;
            build_entity_slot_snapshot(record_buffer, &town_actor_scratch);
        }
        record_index = find_first_vacant_record((void *)0x800102F0, 0x14);
        copy_dst = (record_index * 0x54) + (u8 *)0x800102F0;
        *(Record84 *)copy_dst = *(Record84 *)copy_src;
        detail_dst = (record_index * 0x54) + (u8 *)0x80010324;
        detail_src = runtime_get_mode_indexed_value(entry->unk_00);
        *(Copy10 *)detail_dst = *(Copy10 *)detail_src;
        entry->unk_03 = (u8) ((entry->unk_03 & 0xC0) | record_index);
    }
    slot_base = (void *)0x80010000;
    slot = (slot_index * 4) + slot_base;
    slot->unk_29C = entry;
    slot->unk_2A0 = 0;
    return entry;
}

/* Creates an item from four parameter bytes in a free slot, returning NULL when no slot is available. */
void *set_item_w0(s8 item_byte_0, s8 item_byte_1, s8 item_byte_2, s8 item_byte_3) {
    s8 item_bytes[4];
    s32 slot;
    void *result;
    s8 *item_bytes_ptr;

    slot = func_8009F6E4();
    item_bytes_ptr = item_bytes;
    if (slot == -1) {
        result = 0;
    } else {
        item_bytes[0] = item_byte_0;
        item_bytes[1] = item_byte_1;
        item_bytes[2] = item_byte_2;
        item_bytes[3] = item_byte_3;
        result = copy_an_entry_slot_creating_associated_type_hex_13(slot, item_bytes_ptr);
    }
    return result;
}
