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

typedef struct S_8017390C_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017390C_0;   /* arg0 in spawn_appearance_object_and_advance_actor */

typedef struct S_8017390C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x28];
    u8 unk_48;
    u8 unk_49;
} S_8017390C_1;   /* saved_arg3 in spawn_appearance_object_and_advance_actor */

typedef struct S_8017390C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x9C];
    s16 unk_A8;
    s16 unk_AA;
} S_8017390C_3;   /* saved_arg1 in spawn_appearance_object_and_advance_actor */

typedef struct {
    s32 value;
} __attribute__((packed)) Unaligned32;

extern s32 update_actor_defeat_removal();
extern void *create_tracked_effect();

extern M2C_UNK item_effect_descriptor;
void func_80173770(void *actor, void *motion, void *visual);

/* Spawns an object from stored appearance data and advances the actor's state. */
void spawn_appearance_object_and_advance_actor(S_8017390C_0 *actor, void *transform, Rec_func_800AD058_arg2 *render, void *actor_data)
{
    s32 pos_z;
    s32 pos_x;
    s32 state;
    void *work_data;
    ObjectNodeHeader *spawned_obj;
    SpriteFrameState *spawned_render;
    void *spawned_data;
    void *render_asset;
    ObjectPosition *spawned_transform;
    void *init_obj;
    s32 angle;

    state = actor->unk_9B;
    switch (state) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        actor->unk_9B = 1;
    case 1:
        if (((S_8017390C_1 *)actor_data)->unk_49 != 0) {
            spawned_obj = allocate_flagged_object_node(0x12);
            if (spawned_obj != 0) {
                init_obj = spawned_obj;
                spawned_transform = spawned_obj->position;
                pos_x = ((S_8017390C_3 *)transform)->unk_00;
                spawned_render = spawned_obj->sprite;
                spawned_transform->x.v = pos_x;
                spawned_transform->y.v = ((S_8017390C_3 *)transform)->unk_04;
                pos_z = ((S_8017390C_3 *)transform)->unk_08;
                spawned_transform->velocity_y = 0;
                spawned_transform->velocity_x = 0;
                spawned_transform->velocity_z = 0xFFEE0000;
                spawned_transform->z.v = pos_z;
                angle = 0xC90;
                register_node(init_obj, project_sprite_chain);
                spawned_render->color.word = 0x808080;
                spawned_render->scale_y = angle;
                spawned_data = (u8 *)spawned_obj + 0x20;
                spawned_render->scale_x = angle;
                work_data = spawned_data;
                if (((S_8017390C_1 *)actor_data)->unk_49 == 0x12) {
                    render_asset = &item_effect_descriptor;
                    spawned_render->source = render_asset;
                } else {
                    render_asset = (void *)lookup_item_category_mapped_value(
                        ((S_8017390C_1 *)actor_data)->unk_49, ((S_8017390C_1 *)actor_data)->unk_48);
                    spawned_render->source = render_asset;
                }
                ((S_8017390C_3 *)work_data)->unk_A8 = render->unk_24;
                ((S_8017390C_3 *)work_data)->unk_AA = render->unk_25;
                *(Unaligned32 *)((u8 *)spawned_data + 0x48) =
                    *(Unaligned32 *)((u8 *)actor_data + 0x48);
                create_tracked_effect(spawned_obj, 0, 0, 0);
                spawned_obj->update_callback = &func_80173770;
            }
            ((S_8017390C_1 *)actor_data)->unk_48 = 0;
            ((S_8017390C_1 *)actor_data)->unk_49 = 0;
        }

        render->unk_10 = 0x20;
        render->unk_12 -= 0x80;
        render->unk_14 |= 0xC;
        ((S_8017390C_1 *)actor_data)->unk_1C |= 0x10000000;
        render->unk_0C = 0x808080;
        actor->unk_96 = 0x10;
        actor->unk_9B++;
        play_sound_if_enabled(0x805);
        return;
    case 2:
        update_actor_defeat_removal(actor, transform, render, actor_data);
        return;
    }
}
