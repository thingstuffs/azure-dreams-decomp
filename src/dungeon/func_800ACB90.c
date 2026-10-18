#include "common.h"
#include "shared/entity.h"

typedef struct S_800B22F0_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800B22F0_0;   /* arg2 in initialize_entity_sprite_effect */

typedef struct S_800B22F0_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x51];
    u8 unk_71;
    u8 pad_72[0x16];
    s16 unk_88;
    u8 pad_8A[0x23];
    u8 unk_AD;
} S_800B22F0_1;   /* state in initialize_entity_sprite_effect */


extern s8 find_active_rect_containing_point(u8, u8);
extern void set_record_integer_tile_center(void *, u8, u8);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern void clear_entry_flag_and_link_owner(void *);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void create_tracked_effect(void *, s32, void *, void *);

/* Initialize the entity sprite position, scale, color, and active state. */
void initialize_entity_sprite_effect(void *entity, EntityRec *position, void *sprite)
{
    u8 *state = (u8 *)entity + 0x20;

    ((S_800B22F0_0 *)sprite)->unk_26 =
        find_active_rect_containing_point(((S_800B22F0_0 *)sprite)->unk_24, ((S_800B22F0_0 *)sprite)->unk_25);
    set_record_integer_tile_center(position, ((S_800B22F0_0 *)sprite)->unk_24, ((S_800B22F0_0 *)sprite)->unk_25);

    ((S_800B22F0_1 *)state)->unk_88 =
        sample_terrain_surface_height(((u16)position->x.w.i), ((u16)position->y.w.i),
                      (s16)(((u16)position->z.w.i) - 0x20));

    ((S_800B22F0_0 *)sprite)->unk_1E = 0x1000;
    ((S_800B22F0_0 *)sprite)->unk_1C = 0x1000;
    ((S_800B22F0_0 *)sprite)->unk_0C = 0x2C808080;
    ((S_800B22F0_0 *)sprite)->unk_14 |= 0x8000;
    clear_entry_flag_and_link_owner(entity);

    cycle_map_cell_flags(((S_800B22F0_0 *)sprite)->unk_24, ((S_800B22F0_0 *)sprite)->unk_25,
                  (((S_800B22F0_1 *)state)->unk_1C & 0x2000) ? 0x300 : 0x3000);

    ((S_800B22F0_1 *)state)->unk_AD = 1;
    ((S_800B22F0_1 *)state)->unk_71 = 0;
    ((S_800B22F0_1 *)state)->unk_1C |= 0x40000000;
    create_tracked_effect(entity, 0, (u8 *)sprite + 0x2C, (u8 *)entity + 0x4A);
}
