#include "common.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "dungeon/player.h"

typedef struct S_80048A44_Obj S_80048A44_Obj;

extern void set_sprite_animation_frame(S_80048A44_Obj *obj, s16 frame_group, s16 frame_index, s32 slot_index); /* extern */
s16 get_rounded_facing_and_rounding_flag();       /* extern */
extern u8 actor_attack_frames[];

   /* the 0x14 bytes before ((S_80091B5C_3 *)base)->unk_0C in begin_actor_turn_toward_target, addressed as ((S_80091B5C_3 *)base)->unk_0C[-1] */

/* Initializes the actor's action and turns it toward the current target. */
void begin_actor_turn_toward_target(void *action, void *unused, void *actor, void *motion) {
    s32 distance;
    void *target;

    if (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x8000) {
        ((ActorRecord *)motion)->flags14 &= 0xFFFDFFFF;
        return;
    }
    ((Rec_func_8008ACDC_arg0 *)action)->unk_9A.as_s8 = 0x2A;
    ((Rec_func_8008ACDC_arg0 *)action)->unk_9B.as_s8 = 0;
    (*(s32 *)((u8 *)action + (0x8C))) = 0;
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    ((Rec_func_8008ACDC_arg0 *)action)->unk_96.as_s16 = 0x10;
    (*(u8 **)((u8 *)actor + (0x2C))) = actor_attack_frames;
    set_sprite_animation_frame(actor, actor_attack_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)motion)->facing + 0x100)
        >> 9) & 7], 0, 1);
    target = ((SpriteLinkPrefixView *)(g_dungeon_status.active_actor))[-1].sprite;
    ((Rec_func_8008ACDC_arg0 *)action)->unk_11A = (u16) ((ActorRecord *)motion)->facing;
    ((ActorRecord *)motion)->facing = get_rounded_facing_and_rounding_flag(((Rec_D_80082E80 *)actor)->unk_24,
        ((Rec_D_80082E80 *)actor)->unk_25, ((MovingTile *)target)->tile_x, ((MovingTile *)target)->tile_y,
        &distance);
}
