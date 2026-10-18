#include "modules/trap_effects_candidate.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"

#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))

extern s16 D_8006CCD8[], D_8006CCE8[];
extern s32 find_object_near_tile_height();
extern void apply_attack_power_and_element_effects();
extern s16 find_entry_at_tile_coordinates();
extern s16 find_floor_item_at_world_position();
extern s32 take_map_item_slot(void *object, s16 slot);


/* Advance the effect, process collisions, and mark it finished when its steps run out. */
void advance_trap_effect_and_process_collisions(void *effect)
{
    s32 target;
    s16 entry_index;

    U16(effect, 0) += D_8006CCD8[U8(effect, 6)];
    U16(effect, 2) += D_8006CCE8[U8(effect, 6)];
    target = find_object_near_tile_height(U16(effect, 0), U16(effect, 2), S16(effect, 4));
    if (target) {
        apply_attack_power_and_element_effects(target, 6, U8(((u8 *)D_800E3D7C), 0x11), 9,
                      (s16)(U8(effect, 6) << 9), 0, 3);
    }
    entry_index = find_entry_at_tile_coordinates(S16(effect, 0), S16(effect, 2), S16(effect, 4));
    if (entry_index >= 0) {
        if (((u8 *)D_800E3648)[entry_index * 4] == 7) {
            take_map_item_slot(0, entry_index);
        } else {
            U32(D_800E3648, entry_index * 4) = 0;
        }
    }
    entry_index = find_floor_item_at_world_position(S16(effect, 0), S16(effect, 2), S16(effect, 4));
    if (entry_index >= 0) {
        U32(((u8 *)D_800E3548), entry_index * 4) = 0;
    }
    U8(effect, 7)--;
    if (!U8(effect, 7)) {
        U16(effect, -2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
