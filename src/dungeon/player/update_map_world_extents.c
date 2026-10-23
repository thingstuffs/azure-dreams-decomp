#include "shared/actor_status_flags.h"
#include "shared/dungeon_actor_callbacks.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

extern s32 resolve_record_orientation_or_fallback();
extern void set_sprite_animation_frame();
extern void begin_deferred_player_item_effect();
extern s32 get_unused_text_buffer();
extern s32 expand_text_control_codes();
extern s32 clear_byte_and_advance();
extern s32 write_text_byte_and_advance();
extern s32 append_typed_formatted_value();
extern s32 process_eligible_object_value();
extern s32 append_entity_display_text();
extern void process_unflagged_linked_entries();
extern void process_unflagged_linked_entries_alt();
extern void display_text_with_fullwidth_adjustment();
extern void *create_item_render_object(s32 parent, s32 sprite_source, s16 x, s32 y, s16 z);

extern u8 D_8008D470[12];
extern u8 player_carry_frames[8];
extern u8 D_800E06EE[9];
extern u8 D_800E06F7[9];

typedef struct S_800927E4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x74];
    void * unk_110;
} S_800927E4_0;   /* arg0 in func_800927E4 */

typedef struct S_800927E4_1 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_800927E4_1;   /* callArg in func_800927E4 */

typedef struct S_800927E4_5 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_800927E4_5;   /* (void *)coordUnsigned in func_800927E4 */

typedef struct S_800927E4_9 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    void * unk_9C;
    u8 pad_A0[0x8];
    s16 unk_A8;
    s16 unk_AA;
    u8 pad_AC[0x2];
    s16 unk_AE;
} S_800927E4_9;   /* effect in func_800927E4 */

typedef struct S_800927E4_10 {
    u8 pad_00[0x1];
    u8 unk_01;
    s8 unk_02;
} S_800927E4_10;   /* entity in func_800927E4 */

/* Advances a directional animation, spawns its effect and message, and handles completion. */
void animate_and_display_item_use(void *action, s32 actor_id, Rec_D_80082E80 *sprite, EntityRec *actor) {
    u16 offset[3];
    ObjectNodeHeader *effect_obj;
    ObjectPosition *effect_prim;
    S_800927E4_9 *effect;
    S_800927E4_10 *entity;
    s32 text;
    s32 text_root;
    s32 state_or_text;
    u16 timer;
    s32 tail_value; /* MATCH: keep the shared-tail store value in retail's v0. */

    state_or_text = ((S_800927E4_0 *)action)->unk_9B;
    switch (state_or_text) {
    case 0:
        if (((S_800927E4_0 *)action)->unk_9A == 0x2C) {
            void *anim_sprite = sprite;   /* Pin: removal reorders the instructions (same instructions, different order). */
            u8 *anim_table = player_carry_frames;

                           /* Pin: removal changes a delay-slot fill. */
            ((S_800927E4_1 *)anim_sprite)->unk_2C = anim_table;
            set_sprite_animation_frame(
                anim_sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle +
                        actor->facing + 0x100) >> 9) & 7],
                0,
                1);
            ((S_800927E4_0 *)action)->unk_9B = ((S_800927E4_0 *)action)->unk_9B + 1;
            return;
        }

                   /* Pin: removal changes a delay-slot fill. */
        {
            s32 base_angle = g_game_work.view.camera_rotation.parts.viewAngle;
            s32 signed_angle = actor->facing;
            s32 angle_or_sprite;
            s32 next_angle;

                           /* Pin: removal changes the callee-saved set / frame layout. */
            angle_or_sprite = ((u16)actor->facing);
            if ((((base_angle + signed_angle + 0x100) >> 9) & 7) == 2) {
                angle_or_sprite = (s32)sprite;
                {
                    u8 *anim_table = player_carry_frames;   /* Pin: removal changes the instruction count (a copy retail keeps is dropped or added). */

                    ((S_800927E4_5 *)((void *)angle_or_sprite))->unk_2C = anim_table;
                    set_sprite_animation_frame(
                        (void *)angle_or_sprite,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle +
                                actor->facing + 0x100) >> 9) & 7],
                        0,
                        1);
                    ((S_800927E4_0 *)action)->unk_9B = ((S_800927E4_0 *)action)->unk_9B + 1;
                    return;
                }
            }

            next_angle = angle_or_sprite + 0x200;
            actor->facing = next_angle;
        }
        return;
    case 1:
        if (resolve_record_orientation_or_fallback(sprite->unk_08, sprite, offset, 0) == 0 &&
            !(sprite->unk_14.at00_u16.v & 0x8000)) {
            return;
        }

        if (!(actor->flags1C & ACTOR_CARRYING)) {
            void *owner_obj = (u8 *)action - 0x20;
            s32 zero = 0;   /* Pin: removal changes the whole function shape. */
                           /* Pin: removal reorders the instructions (same instructions, different order). */
                           /* Pin: removal changes the register colouring. */
            effect_obj = create_item_render_object(
                owner_obj, ((S_800927E4_0 *)action)->unk_110, zero, zero, 0);
            if (effect_obj != 0) {

                effect_obj->unk_10 = D_8008D470;
                effect_prim = effect_obj->position;
                effect_prim->x.w.i = (sprite->unk_24 << 6) + 0x20;
                effect_prim->y.w.i = (sprite->unk_25 << 6) + 0x20;

                effect = (u8 *)effect_obj + 0x20;
                if (sprite->unk_14.at00_u16.v & 0x8000) {
                    effect_prim->z.w.i = ((u16)actor->unk_88) - 0x50;
                } else {
                    *(u16 *)&effect_prim->x.w.i += offset[0];
                    *(u16 *)&effect_prim->y.w.i += offset[1];
                    tail_value = offset[2];
                    tail_value += ((u16)actor->unk_88);
                    effect_prim->z.w.i = tail_value;
                }
                effect->unk_A8 = 0x1E;
                effect->unk_AA = 2;
                effect->unk_90 = sprite;
                effect->unk_8C = actor_id;
                effect->unk_9C = (u8 *)action + 0x108;

                entity = ((S_800927E4_0 *)action)->unk_110;
                if (entity != 0 && entity->unk_01 == 4 &&
                    entity->unk_02 != 0) {
                    effect->unk_AE = 1;
                    effect->unk_A8 = 0x3C;
                }
            }

            text_root = get_unused_text_buffer();
            state_or_text = append_entity_display_text(actor, write_text_byte_and_advance(8, text_root));
            state_or_text = expand_text_control_codes(D_800E06EE, state_or_text);
            state_or_text = append_typed_formatted_value(((S_800927E4_0 *)action)->unk_110, state_or_text);
            text = expand_text_control_codes(D_800E06F7, state_or_text);
            entity = ((S_800927E4_0 *)action)->unk_110;
            if (entity->unk_01 != 4) {
                text = process_eligible_object_value(entity, text);
            }
            clear_byte_and_advance(text);
            display_text_with_fullwidth_adjustment(text_root);
        }

        ((S_800927E4_0 *)action)->unk_96 = 0x1E;
        ((S_800927E4_0 *)action)->unk_9B = ((S_800927E4_0 *)action)->unk_9B + 1;
        return;
    case 2:
        if ((sprite->unk_14.at00_u16.v & 0x8000) ||
            (timer = ((S_800927E4_0 *)action)->unk_96 - 1,
             ((S_800927E4_0 *)action)->unk_96 = timer,
             (s32)(timer << 16) <= 0)) {
            if (((S_800927E4_0 *)action)->unk_110 != 0) {
                begin_deferred_player_item_effect(action, actor_id, sprite, actor);
                return;
            }
            process_unflagged_linked_entries_alt(actor->unk_5C);
            process_unflagged_linked_entries(actor->unk_5C);
                           /* Pin: removal changes the whole function shape. */
            g_dungeon_status.flags |= 0x812;
            ((S_800927E4_0 *)action)->unk_8C =handle_player_input;
        }
        return;
    }
}
