#include "shared/dungeon_item_entries.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef unsigned int u32;

typedef struct {
    u8 first;
    u8 second;
    u8 unk_02[10];
} DungeonRecord;

extern u8 D_80081470[];
extern u8 D_80081484[];
extern DungeonRecord D_800E36C8[];

extern s16 find_table_value_index(s32 *);
extern void compact_item_entry_table(s16);
extern s16 get_bounded_stride_index(s32 *, u8 *, s32, s32);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);

/* Clears a slot and updates its associated entry or dungeon state. */
void clear_slot_and_update_linked_state(s32 *slot) {
    s16 lookup_result;
    if (slot != 0) {
        *slot = 0;
        lookup_result = find_table_value_index(slot);
        if (lookup_result >= 0) {
            compact_item_entry_table(lookup_result);
            return;
        }
        if ((u8 *)slot == D_80081484) {
            EntityRec *state = D_800E3D7C;
            state->unk_124 = 0;
            state->flags1C &= 0xFFEFFFFF;
            return;
        }
        if ((u8 *)slot == D_80081470 || slot == ((s32 *)D_800E3D7C->unk_F0)) {
            s16 record_index;
            *(s32 *)D_80081470 = 0;
            record_index = get_bounded_stride_index(((s32 *)D_800E3D7C->unk_F0), ((u8 *)D_800E3548), 4, 0x40);
            if (record_index >= 0) {
                update_map_cell_flags_with_item_limit(D_800E36C8[record_index].first, D_800E36C8[record_index].second, 0x800);
            }
            *(s32 *)D_800E3D7C->unk_F0 = 0;
        }
    }
}
