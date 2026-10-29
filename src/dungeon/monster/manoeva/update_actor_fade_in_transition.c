#include "shared/sprite_frame_state.h"
#include "shared/actor_status_flags.h"
#include "dungeon/effect.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/level.h"
#include "shared/object_node.h"
#include "dungeon/actor/status.h"
#include "engine/entity.h"
#include "engine/node.h"
#include "dungeon/monster/manoeva.h"
#include "dungeon/actor.h"



typedef struct S_8017427C_4 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_8017427C_4;   /* D_800E3D7C + index * 4 in update_actor_fade_in_transition */

extern s8 func_80042518(void *, s32);
extern s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern void resolve_familiar_deployment_request(void *, void *, void *, s32);
extern s32 find_entity_slot_by_field_ac(void *);

extern u8 manoeva_action_resume_address[];
extern u8 manoeva_frame_set[];

/* Advances an actor's fade-in sequence and applies its completion updates. */
void update_actor_fade_in_transition(ActorRecord *actor_state, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor_data) {
    void *actor_base;
    s32 actor_flags;
    s32 entry_index;
    s32 tile_mask;
    u8 brightness;
    u8 fade_delay;
    u8 state;
    u8 tile_x;
    u8 tile_y;
    s16 fade_ticks;

    state = actor_state->action_phase.u;
    switch (state) {
    case 0:
        actor_base = (u8 *)actor_state - 0x20;
        actor_state->action_timer.s = 0x10;
        register_node(actor_base, process_linked_states_mode_zero);
        sprite->color.word = 0x08000000;
        sprite->tpage_abr = 0x20;
        sprite->clut -= 0x80;
        sprite->flags |= 0xC;
        (*(u32 *)&actor_data->flags1C) |= ACTOR_REFRESH_GROUND;
        actor_state->action_phase.u++;
                        /* fall through */

    case 1:
        fade_ticks = actor_state->action_timer.s;
        if (fade_ticks == 0) {
            actor_state->action_phase.u++;
            break;
        }
        brightness = sprite->color.c.r;
        brightness += (0x80 - brightness) / fade_ticks;
        sprite->color.c.r = brightness;
        sprite->color.c.b = brightness;
        sprite->color.c.g = brightness;
        actor_state->action_timer.u--;
        break;

    case 2:
        actor_base = (u8 *)actor_state - 0x20;
        fade_delay = sprite->color.c.code;
        if (fade_delay >= 2) {
            sprite->color.c.code = fade_delay - 1;
            break;
        }
        unlink_node(actor_base);
        register_node(actor_base, project_sprite_chain);
        sprite->color.word = 0x00808080;
        sprite->tpage_abr = 0;
        sprite->clut += 0x80;
        sprite->flags &= 0xFFF3;
        create_terrain_scaled_actor_effect(actor_base, &actor_data->facing,
                      &actor_state->action_id.u, &actor_state->action_state_flags);
        actor_state->action_phase.u++;
        break;

    case 3:
        actor_state->unk_8C.address = manoeva_action_resume_address;
        actor_flags = actor_data->flags1C;
        actor_data->flags1C = actor_flags & 0xEFFFFFFF;
        if (!(actor_data->flags1C & 0x00400000)) {
            tile_x = sprite->tile_x;
            tile_y = sprite->tile_y;
            tile_mask = 0x3000;
            if (actor_flags & 0x2000) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(tile_x, tile_y, tile_mask);
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        if (actor_data->hp == 0) {
            g_dungeon_status.pending_display_owner = (u8 *)actor_data - 0x20;
            begin_actor_display_action(actor_state, context, sprite, manoeva_frame_set);
            break;
        }
        if ((actor_data->flags14 & ACTOR_PARTY_MEMBER) &&
            (actor_data->flags1C & 0x10000)) {
            entry_index = (s16)find_entity_slot_by_field_ac(actor_data);
            if (entry_index < 0) {
                break;
            }
            resolve_familiar_deployment_request(((u8 *)dungeon_actor_ring_anchor), ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)),
                          ((S_8017427C_4 *)(((u8 *)dungeon_actor_ring_anchor) + entry_index * 4))->unk_D0);
            actor_data->flags1C &= 0xFFFEFFFF;
            break;
        }
        if ((get_entity_effect_value(actor_data, STATUS_FROG) << 0x10) != 0) {
            set_or_clear_actor_status_slot(actor_data, STATUS_FROG, func_80042518(actor_data, 0xA));
        }
        break;
    }
}
