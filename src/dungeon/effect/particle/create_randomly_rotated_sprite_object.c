/* Rotating sprites, vertical motion, ring rendering, and staged particle bursts and impacts. */
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/system.h"
void (*const dungeon_18b2800_entry)(B22_81893474_EffectState *, B22_81893474_Motion *, B22_81893474_ColorPart *) = update_effect_launch_travel_impact_cleanup;
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "shared/object_flags.h"

/* Advance motion and rotation, then set completion flags when the timer exceeds its limit. */
void advance_accelerating_spin_effect(B22_81892800_Entity *entity, B22_81892800_Motion *motion, B22_81892800_Aux *aux) {
    s16 timer;

    entity->link->counter++;
    motion->x += motion->dx;
    motion->y += motion->dy;
    if (entity->timer < 8) {
        motion->dz *= 2;
    }
    motion->z += motion->dz;
    aux->angle += 0x300;
    timer = (u16)entity->timer + 1;
    entity->timer = timer;
    if (entity->limit < timer) {
        entity[-1].limit |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "shared/object_node.h"
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "shared/slus_callbacks.h"

   /* fields in create_randomly_rotated_sprite_object */

extern s32 rand(void);

extern u8 D_80025308[];

/* Create an object with a randomly rotated sprite and initialize its copied data. */
void *create_randomly_rotated_sprite_object(void *context, B22_818928F8_Copy24 *src_data, s16 state_value)
{
    ObjectNodeHeader *obj;
    B22_818928F8_S_818928F8_0 *state;
    SpriteFrameState *sprite;
    B22_818928F8_Copy24 *dst_data;
    s32 random_rotation;
    B22_818928F8_Object *sprite_obj;

    obj = (B22_818928F8_Object *)allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->unk_10 = advance_accelerating_spin_effect;
        state = (u8 *)obj + 0x20;
        state->unk_0C = context;
        state->unk_10 = 0;
        state->unk_12 = state_value;

        sprite = *(B22_818928F8_Sprite * *)&obj->sprite;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->source = D_80025308;
        random_rotation = rand();
        sprite_obj = obj;
        sprite->angle_z = random_rotation % 0x1000;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;

        register_node(sprite_obj, project_sprite_chain);
        dst_data = *(B22_818928F8_Copy24 * *)&obj->position;
        *dst_data = *src_data;
        dst_data->word[5] = (s32)0xFFFF0000;
        return obj;
    }
    return 0;
}
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "shared/object_flags.h"

/* Advance the accumulation step, update the target, and flag completion past the final step. */
void accelerate_and_expire_animated_sprite(void *step_state, void *accumulator, SpriteFrameState *target)
{
    void *owner;
    s32 total;
    s32 increment;

    owner = *(void **)step_state;
    *(u16 *)((u8 *)owner + 0x14) += 1;
    *(u16 *)((u8 *)step_state + 4) += 1;

    total = *(s32 *)((u8 *)accumulator + 8);
    increment = *(s32 *)((u8 *)accumulator + 0x14);
    *(s32 *)((u8 *)accumulator + 8) = total + increment;
    if (*(s16 *)((u8 *)step_state + 4) < 8) {
        *(s32 *)((u8 *)accumulator + 0x14) *= 2;
    }

    if (*(s16 *)((u8 *)step_state + 4) == *(s16 *)((u8 *)step_state + 6)) {
        target->scale_y >>= 1;
    }

    advance_sprite_animation_and_textures(target);

    if (*(s16 *)((u8 *)step_state + 4) > *(s16 *)((u8 *)step_state + 6)) {
        *(u16 *)((u8 *)step_state - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "shared/object_node.h"
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 D_800E2178;

/* Creates a sprite object with initialized state and a copied, adjusted transform. */
void *create_vertical_acceleration_sprite(s32 state_value, B22_81892AF0_Copy24 *source_transform, s16 variant) {
    B22_81892AF0_Copy24 *transform;
    SpriteFrameState *sprite;
    ObjectNodeHeader *object;
    B22_81892AF0_S_81892AF0_1 *state;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->unk_10 = accelerate_and_expire_animated_sprite;
        state = ((void *)object) + 0x20;
        ((B22_81892AF0_S_81892AF0_0 *)object)->unk_20 = state_value;
        state->unk_04 = 0;
        state->unk_06 = variant;
        sprite = object->sprite;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        select_record_entry_and_value(sprite, &D_800E2178, 0);
        sprite->scale_y = 0x1800;
        sprite->scale_x = 0x1800;
        register_node(object, project_sprite_chain);
        transform = *(B22_81892AF0_Copy24 * *)&object->position;
        *transform = *source_transform;
        ((B22_81892AF0_S_81892AF0_3 *)transform)->unk_14 = 0x10000;
        ((B22_81892AF0_S_81892AF0_3 *)transform)->unk_08 += 0xFD010000;
        return object;
    }
    return NULL;
}
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

   /* the 0x2 bytes before arg0 in func_800243F8, addressed as arg0[-1] */

   /* arg0 in func_800243F8 */

/* Increment both counters and set completion flags when the count reaches its limit. */
void expire_counted_child_effect(void *counterState) {
    u16 incrementedCount;
    B22_81892BF8_S_81892BF8_1 *linkedCounter;

    linkedCounter = ((B22_81892BF8_S_81892BF8_0 *)counterState)->unk_00;
    linkedCounter->unk_14 = (u16) (linkedCounter->unk_14 + 1);
    incrementedCount = ((B22_81892BF8_S_81892BF8_0 *)counterState)->unk_04 + 1;
    ((B22_81892BF8_S_81892BF8_0 *)counterState)->unk_04 = incrementedCount;
    if ((s16) incrementedCount >= ((B22_81892BF8_S_81892BF8_0 *)counterState)->unk_06) {
        ((B22_81892BF8_S_81892BF8_0_pre *)counterState)[-1].unk_00 = (u16) (((B22_81892BF8_S_81892BF8_0_pre *)counterState)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "shared/game_work.h"

   /* scratch in draw_red */

   /* the 0x8 bytes before arg0 in draw_red, addressed as arg0[-1] */

   /* arg0 in draw_red */

   /* arg1 in draw_red */

   /* context in draw_red */

   /* prim in draw_red */

   /* context2 in draw_red */

   /* next in draw_red */

#define setaddr(p, _addr) (((B22_81892C5C_P_TAG *)(p))->addr = (u32)(_addr))
#define getaddr(p) (u32)(((B22_81892C5C_P_TAG *)(p))->addr)
#define addPrim(ot, p) setaddr(p, getaddr(ot)), setaddr(ot, p)

/* Draw a red ring around the effect center using eight projected polylines. */
s32 draw_red(void *effect, B22_81892C5C_S_81892C5C_2 *center)
{
    u8 *scratch = (u8 *)0x1F800000;
    void *initial_context;
    s32 base_height;
    s32 radius;
    s32 segment;
    s32 angle_step;
    GameWork *ot_ctx;

    ot_ctx = &g_game_work;
    initial_context = ot_ctx->draw_buffer;
    ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_18.s = (u8 *)initial_context + 0xB0;
    for (;;) {
        base_height = ((B22_81892C5C_S_81892C5C_1 *)effect)->unk_04;
        ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_68 = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_70 =
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_78 = center->unk_0A;
        radius = (s16)((base_height + 1) << 5);

        angle_step = 0x100;

        for (segment = 0; segment < 8; segment++) {
            void *render_context;
            s32 end_y_scaled;
            void *polyline;
            s32 start_angle;
            s32 angle_base;
            s32 mid_angle;
            s32 end_angle;
            s32 height;
            s32 x_trig;

            render_context = ot_ctx->draw_buffer;
            polyline = ((B22_81892C5C_S_81892C5C_3 *)render_context)->unk_8D0;
            ((B22_81892C5C_S_81892C5C_3 *)render_context)->unk_8D0 = (u8 *)polyline + 0x18;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_00.at03.v = 5;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_07 = 0x48;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_14 = 0x55555555;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_07 |= 2;
            angle_base = angle_step << 1;
            start_angle = segment * angle_base;
            height = ((B22_81892C5C_S_81892C5C_1 *)effect)->unk_04;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_05 = 0;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_06 = 0;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_04 =
                (s8)(-0x80 - (height << 4));

            x_trig = rsin(start_angle);

            angle_base = segment * 2;
            mid_angle = (angle_base + 1) * angle_step;
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_64 = (s16)(center->unk_02 +
                (((x_trig >> 4) * radius) >> 8));
            x_trig = rsin(mid_angle);

            end_angle = (angle_base + 2) * angle_step;
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_6C = (s16)(center->unk_02 +
                (((x_trig >> 4) * radius) >> 8));
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_74 = (s16)(center->unk_02 +
                (((rsin(end_angle) >> 4) * radius) >> 8));
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_66 = (s16)(center->unk_06 +
                (((rcos(start_angle) >> 4) * radius) >> 8));
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_6E = (s16)(center->unk_06 +
                (((rcos(mid_angle) >> 4) * radius) >> 8));
            {

                end_y_scaled = (rcos(end_angle) >> 4) * radius;
                base_height = end_y_scaled >> 8;
                ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_76 = (s16)(center->unk_06 + base_height);
            }

            {
                u8 *start_vertex = scratch + 0x64;
                u8 *mid_vertex = scratch + 0x6C;
                u8 *end_vertex = scratch + 0x74;
                u8 *screen_start = scratch + 0xD8;
                ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_B4.s = func_80065530(
                    start_vertex, mid_vertex, end_vertex, screen_start, scratch + 0xDC, scratch + 0xE0,
                    scratch + 0x84, scratch + 0x88);
            }

            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_08 = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_D8;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_0A = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_DA;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_0C = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_DC;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_0E = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_DE;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_10 = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_E0;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_12 = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_E2;

            {
                u32 otz = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_B4.u;

                if (otz < 0x1E0) {
                    void *tpage;

                    addPrim(((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_18.u + ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_B4.u, polyline);

                    {
                        B22_81892C5C_S_81892C5C_5 *draw_context;

                        draw_context = ot_ctx->draw_buffer;
                        tpage = draw_context->unk_8D0;
                        draw_context->unk_8D0 = (u8 *)tpage + 0xC;
                    }
                    SetDrawMode(tpage, 0, 0, GetTPage(0, 1, 0, 0) & 0xFFFF, 0);

                    addPrim(((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_18.u + ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_B4.u, tpage);
                }
            }

        }

        {
            void *next_effect = ((B22_81892C5C_S_81892C5C_1_pre *)effect)[-1].unk_00;
            if (next_effect == 0) {
                break;
            }
            effect = (u8 *)next_effect + 0x20;
            center = ((B22_81892C5C_S_81892C5C_7 *)next_effect)->unk_08;
        }
    }
    {
        s32 result = 0;
        return result;
    }
}
#include "shared/object_node.h"
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "m2c_compat.h"

/* Creates an object with copied data, an adjusted field, and initialized arguments. */
void *create_timed_transform_copy_effect(s32 object_arg, void *source_data, s16 initial_value, s16 field_delta) {
    B22_81893024_M2C_BLOCK *src;
    B22_81893024_M2C_OBJECT *object;
    s32 *object_args;
    ObjectPosition *data;

    object = allocate_flagged_object_node(0x212);

    if (object != NULL) {
        src = (B22_81893024_M2C_BLOCK *)source_data;
        object->callback = expire_counted_child_effect;
        object_args = &object->params;
        object->params = object_arg;
        ((s16 *)object_args)[2] = 0;
        ((s16 *)object_args)[3] = initial_value;
        data = object->data;
        *(B22_81893024_M2C_BLOCK *)data = *src;
        data->z.w.i = (s16) (*(u16 *)&data->z.w.i + field_delta);
        register_node(object, draw_red);
    } else {
        return NULL;
    }
    return object;
}
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "shared/object_flags.h"
   /* the 0x2 bytes before arg0 in func_800248F8, addressed as arg0[-1] */

   /* arg0 in func_800248F8 */

/* Advance the object counters, apply the initial frame offset, and flag completion. */
void func_800248F8(void *state, s32 draw_context, s32 update_context) {
    s16 frame;
    B22_818930F8_S_818930F8_1 *object;

    object = ((B22_818930F8_S_818930F8_0 *)state)->unk_00;
    object->unk_14 = (u16) (object->unk_14 + 1);
    ((B22_818930F8_S_818930F8_0 *)state)->unk_04 = (u16) (((B22_818930F8_S_818930F8_0 *)state)->unk_04 + 1);
    advance_sprite_animation_and_textures(update_context);
    frame = (s16) ((B22_818930F8_S_818930F8_0 *)state)->unk_04;
    if (frame < 5) {
        create_timed_transform_copy_effect(((B22_818930F8_S_818930F8_0 *)state)->unk_00, draw_context, 8, (s16) ((frame * 0x10) - 0x40));
    }
    if ((s16) ((B22_818930F8_S_818930F8_0 *)state)->unk_04 > ((B22_818930F8_S_818930F8_0 *)state)->unk_06) {
        ((B22_818930F8_S_818930F8_0_pre *)state)[-1].unk_00 = (u16) (((B22_818930F8_S_818930F8_0_pre *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

   /* the 0x2 bytes before arg0 in func_800249B8, addressed as arg0[-1] */

   /* arg0 in func_800249B8 */

   /* arg1 in func_800249B8 */

/* Increment the linked counter, reduce the source value by four, and process and flag the target status. */
void step_sprite_height_and_animation(void *entry, B22_818931B8_S_818931B8_2 *source, SpriteFrameState *target) {
    B22_818931B8_S_818931B8_1 *counter_state;

    counter_state = ((B22_818931B8_S_818931B8_0 *)entry)->unk_00;
    counter_state->unk_14 = (u16) (counter_state->unk_14 + 1);
    source->unk_0A = (u16) (source->unk_0A - 4);
    advance_sprite_animation_and_textures(target);
    if (target->flags & 0x6000) {
        ((B22_818931B8_S_818931B8_0_pre *)entry)[-1].unk_00 = (u16) (((B22_818931B8_S_818931B8_0_pre *)entry)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
#include "shared/object_node.h"
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

extern s32 D_800E2178;
s32 rand(void);
extern s32 D_800253BC;
/* Spawns a primary effect and eight randomly offset particles from the supplied data. */
void create_animated_sprite_burst(s32 source, B22_81893244_Func81893244Data *initial_data, s16 status_param) {
    SpriteFrameState *sprite;
    ObjectPosition *payload;
    B22_81893244_Func81893244Object *effect;
    B22_81893244_Func81893244Status *status;
    s32 brightness;
    s32 particle_index;
    effect = (B22_81893244_Func81893244Object *)allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        status = &effect->status;
        effect->field10 = func_800248F8;
        status->field20 = source;
        status->field24 = 0;
        status->field26 = status_param;
        sprite = effect->fieldC;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        select_record_entry_and_value(sprite, &D_800E2178, 0);
        sprite->scale_y = 0x1800;
        sprite->scale_x = 0x1800;
        register_node(effect, project_sprite_chain);
        payload = effect->field8;
        *(B22_81893244_Func81893244Data *)payload = *initial_data;
        create_timed_transform_copy_effect(source, payload, 8, -0x40);
    }
    particle_index = 0;
    do {
        effect = (B22_81893244_Func81893244Object *)allocate_flagged_object_node(0x212);
        status = &effect->status;
        if (effect != NULL) {
            effect->field10 = step_sprite_height_and_animation;
            brightness = 0x80;
            status->field20 = source;
            status->field24 = 0;
            status->field26 = status_param;
            sprite = effect->fieldC;
            sprite->color.c.b = brightness;
            sprite->color.c.g = brightness;
            sprite->color.c.r = brightness;
            select_record_entry_and_value(sprite, &D_800253BC, 0);
            sprite->scale_y = 0x800;
            sprite->scale_x = 0x800;
            sprite->flags = (u16) (sprite->flags | 0xC);
            sprite->tpage_abr = (u16) (sprite->tpage_abr | 0x60);
            register_node(effect, project_sprite_chain);
            payload = effect->field8;
            *(B22_81893244_Func81893244Data *)payload = *initial_data;
            payload->x.w.i = (u16) (*(u16 *)&payload->x.w.i + ((s32) (rsin(rand()) * 2) >> 8));
            payload->y.w.i = (u16) (*(u16 *)&payload->y.w.i + ((s32) (rcos(rand()) * 2) >> 8));
        }
        particle_index += 1;
    } while (particle_index < 8);
}
#include "dungeon/effect/particle/create_randomly_rotated_sprite_object.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
extern int abs(int);

#define U8_AT(p, n) (*(u8 *)((u8 *)(p) + (n)))
#define S8_AT(p, n) (*(s8 *)((u8 *)(p) + (n)))
#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))
#define probe scratch.probe
#define result scratch.result
#define map_flags scratch.map_flags

/* Updates the effect's launch, travel, impact, and cleanup states. */
void update_effect_launch_travel_impact_cleanup(B22_81893474_EffectState *effect_state, B22_81893474_Motion *effect_motion, B22_81893474_ColorPart *color_part)
{
    B22_81893474_EffectState *state;
    B22_81893474_Motion *motion;
    B22_81893474_ColorPart *part;
    void *owner;
    void *owner_data;
    void *owner_node;
    void *owner_motion;
    B22_81893474_Scratch scratch;
    register TileObject *origin;
    s32 target_z;
    s32 direction_bits;
    s32 state_id;
    s32 source_z;
    s32 adjusted_z;
    s16 *target_pos;
    void *spawned_effect;

    state = effect_state;
    motion = effect_motion;
    state->timer++;
    state_id = state->state;
    owner = state->owner;
    part = color_part;
    switch (state_id) {
    case 0:
        origin = &reference_tile_object;
        {
            u8 *node = PTR_AT((u8 *)owner - 0x20, 0xC);
            u32 offset = (U16_AT(primary_actor_record, 0x2A) >> 8) & 0xE;

            U16_AT(owner, 0x2A) = get_rounded_facing_and_rounding_flag(
                node[0x24], node[0x25],
                origin->tile_position.parts.tile_x + U16_AT((u8 *)dir_step_x + offset, 0),
                origin->tile_position.parts.tile_y + U16_AT((u8 *)dir_step_y + offset, 0), &result);
        }
        state->timer = 0;
        state->state++;
        state->direction = (U16_AT(owner, 0x2A) >> 9) & 7;
        state->status = 0;
        part->color = 0x00808080;

    case 1:
        owner_data = (u8 *)owner - 0x20;
        owner_node = PTR_AT(owner_data, 0xC);
        if (resolve_record_orientation_or_fallback(PTR_AT(owner_node, 8), owner_node, probe, 0) == 0) {
            if (!(U16_AT(PTR_AT(owner_data, 0xC), 0x14) & 0x8000)) {
                break;
            }
        }
        owner_motion = PTR_AT(owner_data, 8);
        U16_AT(motion, 2) = U16_AT(owner_motion, 2);
        U16_AT(motion, 6) = U16_AT(owner_motion, 6);
        source_z = U16_AT(owner_motion, 0xA);
        U16_AT(motion, 0xA) = source_z;
        if (!(U16_AT(PTR_AT(owner_data, 0xC), 0x14) & 0x8000)) {
            U16_AT(motion, 2) += probe[0];
            U16_AT(motion, 6) += probe[1];
            U16_AT(motion, 0xA) += probe[2];
        } else {
            U16_AT(motion, 0xA) = source_z - 0x40;
        }
        if (!(U16_AT(state->image, 0) & 0x80)) {
            break;
        }
        target_pos = scratch.work;
                        /* This expression is intentionally kept in its retail form. */
        if ((U16_AT(owner_data, 0x1E) | 0x2000) != 0) {
            TileObject *position_base = &reference_tile_object;
            void *direction_node = primary_actor_record;

            {
                u8 *x_table = (u8 *)dir_step_x;
                direction_bits = U16_AT(direction_node, 0x2A);
                state->x = position_base->tile_position.parts.tile_x +
                    ((s16 *)(x_table + (((u32)direction_bits >> 8) & 0xE)))[0];
            }
            {
                u8 *y_table = (u8 *)dir_step_y;
                direction_bits = U16_AT(direction_node, 0x2A);
                state->y = position_base->tile_position.parts.tile_y +
                    ((s16 *)(y_table + (((u32)direction_bits >> 8) & 0xE)))[0];
            }
        } else {
            state->x = reference_tile_object.tile_position.parts.tile_x + dir_step_x[state->direction];
            state->y = reference_tile_object.tile_position.parts.tile_y + dir_step_y[state->direction];
        }
        {
            ActorRecord *height_node;
            s32 tile_coord;

            tile_coord = state->x;
            S16_AT(target_pos, 2) = tile_coord * 64 + 0x20;
            tile_coord = state->y;
            height_node = primary_actor_record;
            S16_AT(target_pos, 6) = tile_coord * 64 + 0x20;
            S16_AT(target_pos, 0xA) = height_node->ground_height - 0x20;
        }
        S16_AT(target_pos, 0xA) = get_surface_height_at_record(target_pos);
        state->z = S16_AT(target_pos, 0xA);
        get_offset_map_cell_value_and_flags(state->x - 1, state->y, 0, &map_flags);
        if ((map_flags & 0x3300) != 0 ||
            (target_z = S16_AT(target_pos, 0xA)) > 0x200 ||
            (check_left_tile_and_center_height(U16_AT(target_pos, 2), U16_AT(target_pos, 6), target_z) << 16) != 0 ||
            (increment_bounded_counter() << 16) == 0) {
            state->state = 7;
        } else {
            if ((U16_AT(owner_data, 0x1E) | 0x2000) == 0) {
                state->status = 2;
            } else {
                state->status = 1;
            }
            state->state++;
        }
        {
            s32 delta_x;
            s32 delta_y;
            s32 delta_z;

            delta_x = S16_AT(target_pos, 2) - S16_AT(motion, 2);
            delta_x = abs(delta_x);
            probe[0] = delta_x;
            delta_y = S16_AT(target_pos, 6) - S16_AT(motion, 6);
            delta_y = abs(delta_y);
            probe[1] = delta_y;
            {
                s32 motion_z;

                delta_z = S16_AT(target_pos, 0xA);
                motion_z = S16_AT(motion, 0xA);
                delta_z -= motion_z;
            }
            delta_z = abs(delta_z);
            probe[2] = delta_z;
        }
        state->duration = 12;
        S32_AT(motion, 0xC) = (S32_AT(target_pos, 0) - S32_AT(motion, 0)) / state->duration;
        S32_AT(motion, 0x10) = (S32_AT(target_pos, 4) - S32_AT(motion, 4)) / state->duration;
        S32_AT(motion, 0x14) = (S32_AT(target_pos, 8) - S32_AT(motion, 8)) / state->duration;
        create_randomly_rotated_sprite_object(state, motion, state->duration);
        create_randomly_rotated_sprite_object(state, motion, state->duration);
        create_randomly_rotated_sprite_object(state, motion, state->duration);
        state->timer = 0;
        break;

    case 2:
        S32_AT(motion, 0) += S32_AT(motion, 0xC);
        S32_AT(motion, 4) += S32_AT(motion, 0x10);
        S32_AT(motion, 8) += S32_AT(motion, 0x14);
        if (state->timer < state->duration) {
            break;
        }
        create_vertical_acceleration_sprite(state, motion, 12);
        state->timer = 0;
        state->state++;
        break;

    case 3:
        if (state->timer < 8) {
            break;
        }
        play_sound_if_enabled(0x300);
        state->timer = 0;
        state->state++;
        break;

    case 4:
        if (state->timer < 5) {
            break;
        }
        create_animated_sprite_burst(state, motion, 16);
        initialize_timed_motion_step(8, 36);
        state->timer = 0;
        state->state++;
        break;

    case 5:
        if (state->timer < 0x11) {
            break;
        }
        if (state->status != 0) {
            s32 strength;
            s16 clamped_strength;
            u32 effect_id;
            s32 variation;

            spawned_effect = create_actor_at_tile(state->status, state->x, state->y, state->z);
            func_80042640(spawned_effect, 51);
            variation = generate_random_value();
            effect_id = U8_AT(state, 9);
            strength = effect_id >> 1;
            strength += effect_id << 1;
            strength += variation & 3;
            strength += 16;
            clamped_strength = strength;
            if (strength >= 256) {
                clamped_strength = 255;
            }
            U8_AT(spawned_effect, 0x28) = clamped_strength;
            U8_AT(spawned_effect, 0x29) = clamped_strength;
        }
        state->timer = 0;
        state->state++;
        break;

    case 6:
        if (state->field_14 != 0) {
            break;
        }
        g_dungeon_status.active_actor = 0;
        U16_AT(state, -2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;

    case 7:
        S32_AT(motion, 0) += S32_AT(motion, 0xC);
        S32_AT(motion, 4) += S32_AT(motion, 0x10);
        if (state->timer >= state->duration) {
            state->state = 6;
            state->timer = 0;
        }
    }

    state->field_14 = 0;
}
