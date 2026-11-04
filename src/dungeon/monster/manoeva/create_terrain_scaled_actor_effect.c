#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "engine/graphics.h"
#include "engine/node/allocation.h"
#include "dungeon/monster/manoeva.h"

   /* arg0 in create_terrain_scaled_actor_effect */


   /* ((S_80174B90_6 *)arg0)->unk_08 in create_terrain_scaled_actor_effect */

s32 register_node(ObjectNodeHeader *entry, void *registration_id);           /* extern */
void update_terrain_scaled_actor_effect(ManoevaTerrainEffectBody *effect, MovingPosition *out_position, void *out_render);
extern M2C_UNK D_80175540;



/* Create an effect using the source object's rendering and transform data. */
void create_terrain_scaled_actor_effect(ObjectNodeHeader *source, s16 *facing, u8 *action, u16 *flags) {
    void *allocation_head_address;
    ObjectNodeHeader **allocation_head;
    SpriteFrameState *render_data;
    ManoevaTerrainEffectBody *effect_state;
    ObjectNodeHeader *effect;

    allocation_head_address = source;
    allocation_head = allocation_head_address;
    effect = allocate_list_node(0x100,allocation_head);
    if (effect != NULL) {
        render_data = effect->sprite;
        effect_state = NODE_BODY(effect);
        effect->update_callback = &update_terrain_scaled_actor_effect;
        effect_state->unk_14 =  source->sprite;
        effect_state->unk_18 =  source->position;
        render_data->scale_y = 0x1000;
        render_data->scale_x = 0x1000;
        render_data->color.word = 0x808080;
        render_data->animation_resource = (s32) effect_state->unk_14->animation_resource;
        render_data->clut = (u16) effect_state->unk_14->clut;
        effect->position->x.unsigned_parts.integer =
            (u16) source->position->x.unsigned_parts.integer;
        effect->position->y.unsigned_parts.integer =
            (u16) source->position->y.unsigned_parts.integer;
        effect->position->z.unsigned_parts.integer =
            (u16) source->position->z.unsigned_parts.integer;
        select_sprite_entry(render_data, 0x46, 0);
        register_node(effect, &D_80175540);
        ((ManoevaTerrainEffectBody *)NODE_BODY(effect))->unk_00 = facing;
        effect_state->unk_04 = action;
        effect_state->unk_08 = flags;
        effect_state->unk_0C = source;
        effect_state->unk_1C.s = 0x1000;
    }
}
