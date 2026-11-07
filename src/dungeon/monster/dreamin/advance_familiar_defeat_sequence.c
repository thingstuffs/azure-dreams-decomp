#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/item/actor_target.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/item/message.h"

void spend_actor_mp(ActorRecord *entity, s32 base_reduction);
extern void try_apply_action_by_chance(void *, s32, s32);

extern void *actor_update_node_cursor;
extern u8 D_80170854[];
extern u8 dreamin_action_continuation_address;
extern u8 D_801738A4[];

/* Run the actor's two-step death sequence: post its message, then spawn the drop and release it. */
void advance_familiar_defeat_sequence(ActorRecord *work, ObjectPosition *part_a, SpriteFrameState *part_b, ActorRecord *actor)
{
    void *first;
    void *result;
    void *saved_first;
    void *object;
    u8 state;

    state = work->action_phase;
    switch (state) {
    case 0:
        result = append_entity_display_text(actor, first = get_unused_text_buffer());
        saved_first = first;
        first = result;
        clear_byte_and_advance(expand_text_control_codes(D_80170854, first));
        display_text_with_fullwidth_adjustment(saved_first);
        object = scan_actor_along_heading(actor, part_b->tile_x, part_b->tile_y,
                               actor->facing, 0x10);
        actor->target = object;
        part_b->frameTable = D_801738A4;
        select_sprite_entry(part_b,
            D_801738A4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x812);
        work->action_phase = work->action_phase + 1;
        part_a->velocity_z = 0;
        part_a->velocity_y = 0;
        part_a->velocity_x = 0;
        return;
    case 1:
        if (!(part_b->flags & 0xE000)) {
            return;
        }
        spend_actor_mp(actor, 0xC00);
        work->unk_8C.address = &dreamin_action_continuation_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->pending_turn_updates == 0) {
            actor->action_flags &= 0x7FFF;
        } else {
            actor_update_node_cursor = (u8 *)actor - 0x20;
        }
        object = actor->target;
        if (object != 0) {
            try_apply_action_by_chance(object, 0x10, 0x10);
        }
        break;
    }
}

/* MECHANISM: True-space advance_familiar_defeat_sequence turns 0x80173780/0x80173798 into local CFG joins
   and orders state-zero before state-one, preserving the 0x30 frame and five held bases.
   Byte-scaled table indexing keeps lbu/shift-nine; distinct result/saved_first lifetimes
   emit retail's a1<-v0 and call-delay s0<-a1 around append_entity_display_text. */
