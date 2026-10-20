#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"

typedef struct S_80172438_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172438_1;   /* arg2 in search_ahead_and_start_action */

typedef struct S_80172438_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x16];
    u16 unk_B2;
} S_80172438_2;   /* arg0 in search_ahead_and_start_action */


extern s32 check_layer_offset_height(s32, s32, s16, s32);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern s32 find_eligible_entry_at_coordinates(void *, u16, u16);
extern s32 check_entity_interaction_compatibility(void *, void *);
extern s32 try_claim_dungeon_action_slot(void *);
extern void apply_camera_offset_and_select_target(void *, void *, s32, s32);
extern void select_sprite_entry(void *, u8, s32);
extern void advance_status_timers(void *);

extern u8 D_801764A0[];

/* Searches up to four tiles ahead for a target and starts the actor's action. */
s32 search_ahead_and_start_action(void *action_state, void *action_context, void *sprite, EntityRec *actor) {
    s32 attempt;
    s32 tile_x;
    s32 tile_y;
    s32 direction;
    s32 step_offset;
    s32 next_x;
    s32 next_y;
    u16 call_direction;
    s16 *x_step;
    s16 *y_step;
    s16 floor_height;
    s32 target;

    actor->unk_71 &= 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    attempt = 0;
    direction = ((u16)((u16)actor->facing) >> 9) & 7;
    step_offset = direction << 1;
    tile_x = ((S_80172438_1 *)sprite)->unk_24;
    tile_y = ((S_80172438_1 *)sprite)->unk_25;
    x_step = (s16 *)((u8 *)((s8 *)dir_step_x) + step_offset);
    ((S_80172438_2 *)action_state)->unk_B2 = 0;
    call_direction = direction;

    do {
        s32 try_x = (s16)tile_x;
        s32 try_y = (s16)tile_y;
        s32 floor_x;
        s32 floor_y;

        ((S_80172438_2 *)action_state)->unk_B2++;
        if ((check_layer_offset_height((try_x << 6) & 0xFFC0,
                           (try_y << 6) & 0xFFC0,
                           actor->unk_88, call_direction << 9)
             << 16) != 0) {
            ((S_80172438_2 *)action_state)->unk_B2--;
            return 2;
        }

        floor_y = (s16 *)((s8 *)dir_step_y);
        floor_x = (((try_x + *x_step) << 6) + 0x20) & 0xFFE0;
        y_step = (s16 *)(step_offset + (u8 *)floor_y);
        floor_y = (((try_y + *y_step) << 6) + 0x20) & 0xFFE0;
        floor_height = sample_terrain_surface_height(floor_x,
                              floor_y,
                              (s16)(((u16)actor->unk_88) - 0x20));
        if (floor_height >= 0x201) {
            ((S_80172438_2 *)action_state)->unk_B2--;
            return 3;
        }
        if ((u16)(floor_height - ((u16)actor->unk_88) + 0x3F) >= 0x7F) {
            ((S_80172438_2 *)action_state)->unk_B2--;
            return 3;
        }

        next_x = tile_x + *(u16 *)x_step;
        next_y = tile_y + *(u16 *)y_step;
        target = find_eligible_entry_at_coordinates(actor, (u16)next_x, (u16)next_y);
        actor->target = target;
        if (target != 0) {
            break;
        }

        attempt++;
        tile_x += *(u16 *)x_step;
        tile_y += *(u16 *)y_step;
    } while (attempt < 4);

    if (attempt >= 4) {
        return 3;
    }
    if ((check_entity_interaction_compatibility(actor, (void *)target) << 16) == 0) {
        return 0;
    }
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000) && (g_dungeon_status.flags & 8)) {
        return -1;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    ((S_80172438_2 *)action_state)->unk_9B = 0;
    ((S_80172438_2 *)action_state)->unk_8C = 0;
    ((S_80172438_2 *)action_state)->unk_9A = 0x17;
    (*(void * *)((u8 *)sprite + 0x2C)) = D_801764A0;
    select_sprite_entry(sprite,
                  D_801764A0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                  0);
    advance_status_timers(actor);
    (*(u8 *)&actor->unk_6D)--;
    return 1;
}
