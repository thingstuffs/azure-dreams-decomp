#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_8017427C_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017427C_0;   /* arg0 in update_actor_fade_in_transition */

typedef struct S_8017427C_1 {
    u8 pad_00[0xC];
    union {
        struct { u32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8017427C_1;   /* arg2 in update_actor_fade_in_transition */

typedef struct S_8017427C_4 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_8017427C_4;   /* D_800E3D7C + index * 4 in update_actor_fade_in_transition */


extern s8 func_80042518(void *, s32);
extern s32 get_entity_effect_value(void *, s32);
extern void register_node(void *, void *);
extern void unlink_node(void *);
extern void resolve_familiar_deployment_request(void *, void *, void *, s32);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern s32 find_entity_slot_by_field_ac(void *);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void create_terrain_scaled_actor_effect(void *, void *, void *, void *);

extern s32 D_800C6AEC;
extern u8 D_80170EE4[];
extern u8 D_80176640[];

/* Advances an actor's fade-in sequence and applies its completion updates. */
void update_actor_fade_in_transition(void *actor_state, void *context, S_8017427C_1 *sprite, EntityRec *actor_data) {
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

    state = ((S_8017427C_0 *)actor_state)->unk_9B;
    switch (state) {
    case 0:
        actor_base = (u8 *)actor_state - 0x20;
        ((S_8017427C_0 *)actor_state)->unk_96.s = 0x10;
        register_node(actor_base, &D_800C6AEC);
        sprite->unk_0C.at00.v = 0x08000000;
        sprite->unk_10 = 0x20;
        sprite->unk_12 -= 0x80;
        sprite->unk_14 |= 0xC;
        (*(u32 *)&actor_data->flags1C) |= 0x40000000;
        ((S_8017427C_0 *)actor_state)->unk_9B++;
                        /* fall through */

    case 1:
        fade_ticks = ((S_8017427C_0 *)actor_state)->unk_96.s;
        if (fade_ticks == 0) {
            ((S_8017427C_0 *)actor_state)->unk_9B++;
            break;
        }
        brightness = sprite->unk_0C.at00u.v;
        brightness += (0x80 - brightness) / fade_ticks;
        sprite->unk_0C.at00u.v = brightness;
        sprite->unk_0C.at02.v = brightness;
        sprite->unk_0C.at01.v = brightness;
        ((S_8017427C_0 *)actor_state)->unk_96.u--;
        break;

    case 2:
        actor_base = (u8 *)actor_state - 0x20;
        fade_delay = sprite->unk_0C.at03.v;
        if (fade_delay >= 2) {
            sprite->unk_0C.at03.v = fade_delay - 1;
            break;
        }
        unlink_node(actor_base);
        register_node(actor_base, project_sprite_chain);
        sprite->unk_0C.at00.v = 0x00808080;
        sprite->unk_10 = 0;
        sprite->unk_12 += 0x80;
        sprite->unk_14 &= 0xFFF3;
        create_terrain_scaled_actor_effect(actor_base, (u8 *)actor_data + 0x2A,
                      (u8 *)actor_state + 0x9A, (u8 *)actor_state + 0x98);
        ((S_8017427C_0 *)actor_state)->unk_9B++;
        break;

    case 3:
        ((S_8017427C_0 *)actor_state)->unk_8C = D_80170EE4;
        actor_flags = actor_data->flags1C;
        actor_data->flags1C = actor_flags & 0xEFFFFFFF;
        if (!(actor_data->flags1C & 0x00400000)) {
            tile_x = sprite->unk_24;
            tile_y = sprite->unk_25;
            tile_mask = 0x3000;
            if (actor_flags & 0x2000) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(tile_x, tile_y, tile_mask);
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        if (actor_data->unk_28 == 0) {
            g_dungeon_status.pending_display_owner = (u8 *)actor_data - 0x20;
            begin_actor_display_action(actor_state, context, sprite, D_80176640);
            break;
        }
        if ((actor_data->flags14 & 0x4000) &&
            (actor_data->flags1C & 0x10000)) {
            entry_index = (s16)find_entity_slot_by_field_ac(actor_data);
            if (entry_index < 0) {
                break;
            }
            resolve_familiar_deployment_request(((u8 *)D_800E3D7C), ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)),
                          ((S_8017427C_4 *)(((u8 *)D_800E3D7C) + entry_index * 4))->unk_D0);
            actor_data->flags1C &= 0xFFFEFFFF;
            break;
        }
        if ((get_entity_effect_value(actor_data, 0xA) << 0x10) != 0) {
            set_or_clear_actor_status_slot(actor_data, 0xA, func_80042518(actor_data, 0xA));
        }
        break;
    }
}
