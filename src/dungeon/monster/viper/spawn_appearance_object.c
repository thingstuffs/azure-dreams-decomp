#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AD058_arg2.h"
#include "engine/menu.h"
#include "dungeon/system.h"
#include "engine/node.h"
#include "dungeon/actor/state.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#include "dungeon/monster/viper.h"


typedef struct S_8017390C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x9C];
    s16 unk_A8;
    s16 unk_AA;
} S_8017390C_3;   /* saved_arg1 in spawn_appearance_object */

typedef struct {
    s32 value;
} __attribute__((packed)) Unaligned32;

extern M2C_UNK item_effect_descriptor;
void func_80173770(void *actor, ObjectPosition *motion, SpriteFrameState *visual);

/* Spawns an object from stored appearance data and advances the actor's state. */
void spawn_appearance_object(ActorRecord *actor, ObjectPosition *transform, struct SpriteFrameState *render, ActorRecord *actor_data)
{
    s32 pos_z;
    s32 pos_x;
    s32 state;
    S_8017390C_3 *work_data;
    ObjectNodeHeader *spawned_obj;
    SpriteFrameState *spawned_render;
    void *spawned_data;
    void *render_asset;
    ObjectPosition *spawned_transform;
    void *init_obj;
    s32 angle;

    state = actor->action_phase;
    switch (state) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        actor->action_phase = 1;
    case 1:
        if (actor_data->unk_49 != 0) {
            spawned_obj = allocate_flagged_object_node(0x12);
            if (spawned_obj != 0) {
                init_obj = spawned_obj;
                spawned_transform = spawned_obj->position;
                pos_x = transform->x.v;
                spawned_render = spawned_obj->sprite;
                spawned_transform->x.v = pos_x;
                spawned_transform->y.v = transform->y.v;
                pos_z = transform->z.v;
                spawned_transform->velocity_y = 0;
                spawned_transform->velocity_x = 0;
                spawned_transform->velocity_z = 0xFFEE0000;
                spawned_transform->z.v = pos_z;
                angle = 0xC90;
                register_node(init_obj, project_sprite_chain);
                spawned_render->color.word = 0x808080;
                spawned_render->scale_y = angle;
                spawned_data = NODE_BODY(spawned_obj);
                spawned_render->scale_x = angle;
                work_data = spawned_data;
                if (actor_data->unk_49 == 0x12) {
                    render_asset = &item_effect_descriptor;
                    spawned_render->source = render_asset;
                } else {
                    render_asset = (void *)lookup_item_category_mapped_value(
                        actor_data->unk_49, actor_data->unk_48);
                    spawned_render->source = render_asset;
                }
                work_data->unk_A8 = render->tile_x;
                work_data->unk_AA = render->tile_y;
                *(Unaligned32 *)((u8 *)spawned_data + 0x48) =
                    *(Unaligned32 *)((u8 *)actor_data + 0x48);
                create_tracked_effect(spawned_obj, 0, 0, 0);
                spawned_obj->update_callback = &func_80173770;
            }
            actor_data->unk_48 = 0;
            actor_data->unk_49 = 0;
        }

        render->tpage_abr = 0x20;
        render->clut -= 0x80;
        render->flags |= 0xC;
        actor_data->flags1C |= 0x10000000;
        render->color.word = 0x808080;
        actor->action_timer = 0x10;
        actor->action_phase++;
        play_sound_if_enabled(0x805);
        return;
    case 2:
        update_actor_defeat_removal(actor, transform, render, actor_data);
        return;
    }
}
