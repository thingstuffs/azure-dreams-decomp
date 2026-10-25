#include "shared/entity_height_offsets.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 words[3];
} TableEntry;

extern s32 create_visual_object();
extern s32 create_offset_sprite_object_with_z();
extern s32 resolve_record_orientation_or_fallback();
extern void *allocate_list_node();
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */

extern s32 D_80026680[3];
extern TableEntry linked_effect_direction_entries[];
extern s32 linked_mesh_processor_address[3];

typedef struct S_80026A84_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80026A84_1;

   /* arg0 in create_six_offset_effects */


typedef struct S_80026A84_5 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    u8 pad_0C[0x5A];
    s16 unk_66;
    u8 pad_68[0x6];
    s16 unk_6E;
} S_80026A84_5;

typedef struct S_80026A84_6 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
} S_80026A84_6;

typedef struct S_80026A84_7 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80026A84_7;   /* arg1 in create_six_offset_effects */

/* Creates six linked effects at an offset from the origin and initializes their points. */
void *create_six_offset_effects(MovingPosition *origin, S_80026A84_7 *target_pos, s32 effect_param, Rec_D_80082E80 *source)
{
    u16 offset[3];
    s32 *callback;
    TableEntry *effect_entry;
    s32 effect_index;
    s32 point_index;
    u16 coord_xz;
    u16 coord_y;
    SpriteFrameState *render_data;
    ObjectPosition *effect_pos;
    S_80026A84_5 *effect_data;
    ObjectNodeHeader *effect;
    void *chain_head;

    chain_head = NULL;
    offset[0] = offset[1] = 0;
    if (resolve_record_orientation_or_fallback(source->unk_08, source, offset, 0) == 0) {
        offset[2] = (0 - entity_height_offsets[0]) + 0x10;
    }
    effect_index = 0;
    callback = D_80026680;
    effect_entry = linked_effect_direction_entries;
    do {
        effect = allocate_list_node(0x12, ((s32 *)(&scene_object_list_anchor)));
        if (effect != NULL) {
            effect->update_callback = callback;
            register_node(effect, linked_mesh_processor_address);
            effect_pos = effect->position;
            coord_xz = origin->x + offset[0];
            effect_pos->x.w.i = coord_xz;
            *((u16 *)&effect_pos->velocity_x + 1) = coord_xz;
            point_index = 0;
            coord_y = origin->y + offset[1];
            effect_pos->y.w.i = coord_y;
            *((u16 *)&effect_pos->velocity_y + 1) = coord_y;
            effect_data = ((void *)effect) + 0x20;
            coord_xz = origin->z + offset[2];
            effect_pos->z.w.i = coord_xz;
            *((u16 *)&effect_pos->velocity_z + 1) = coord_xz;
            render_data = effect->sprite;
            render_data->source = effect_entry;
            render_data->scale_y = 0x1000;
            render_data->scale_x = 0x1000;
            render_data->flags = render_data->flags | 0xC;
            ((S_80026A84_1 *)effect)->unk_20 = target_pos;
            effect_data->unk_04 = effect_param;
            effect_data->unk_66 = 0x20;
            effect_data->unk_6E = effect_index;
            do {
                ((S_80026A84_6 *)((u8 *)effect_data + point_index * 8))->unk_24 = *(u16 *)&effect_pos->x.w.i;
                ((S_80026A84_6 *)((u8 *)effect_data + point_index * 8))->unk_26 = *(u16 *)&effect_pos->y.w.i;
                ((S_80026A84_6 *)((u8 *)effect_data + point_index * 8))->unk_28 = *(u16 *)&effect_pos->z.w.i;
                point_index += 1;
            } while (point_index < 8);
            effect_data->unk_08 = chain_head;
            chain_head = effect;
        }
        effect_index += 1;
        effect_entry += 1;
    } while (effect_index < 6);
    create_visual_object((s16)(origin->x + offset[0]),
                  (s16)(origin->y + offset[1]),
                  (s16)(origin->z + offset[2]), 0x800);
    create_offset_sprite_object_with_z(target_pos->unk_02, target_pos->unk_06,
                  target_pos->unk_0A, effect_param);
    return effect;
}
