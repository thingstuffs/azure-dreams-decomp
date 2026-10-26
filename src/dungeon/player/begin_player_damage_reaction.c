#include "shared/actor_status_ids.h"
#include "shared/actor_status.h"
#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "dungeon/player.h"



void clear_slots_of_type(ActorRecord *owner, s8 match_type);             /* extern */
void set_sprite_animation_frame(struct SpriteFrameState *obj, s16 frame_group, s16 frame_index, s32 slot_index); /* extern */
s32 generate_random_value(void);                                /* extern */
extern u8 player_damage_frames_2[];
extern u8 player_damage_frames[];
extern u8 pending_player_damage_kind;

/* Initialize directional animation and reset the actor action state. */
void begin_player_damage_reaction(void *action, void *unused, void *sprite, EntityRec *actor) {
    u8 *direction_table;
    ((Rec_func_8008ACDC_arg0 *)action)->unk_10C = (s16) (((Rec_func_8008ACDC_arg0 *)action)->unk_10C & 0xFFFE);
    {
        s32 mode_mask = 0x20000000;
        if (actor->flags1C & mode_mask) {
            direction_table = player_damage_frames_2;
        } else {
            direction_table = player_damage_frames;
        }
    }
    (*(u8 **)((u8 *)sprite + 0x2C)) = direction_table;
    {
        u8 *direction_entry;
        direction_entry = direction_table + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7);
        set_sprite_animation_frame(sprite, *direction_entry, 0, 1);
    }
    ((Rec_func_8008ACDC_arg0 *)action)->unk_9A.as_s8 = 7;
    ((Rec_func_8008ACDC_arg0 *)action)->unk_9B.as_s8 = 0;
    ((Rec_func_8008ACDC_arg0 *)action)->unk_8C.as_s32 = 0;
    clear_player_linked_action_flags();
    if (!(generate_random_value() & 1)) {
        clear_slots_of_type(actor, STATUS_SLEEP);
        clear_slots_of_type(actor, STATUS_PARALYSIS);
        clear_slots_of_type(actor, STATUS_CONFUSION);
    }
    {
        s32 mode_mask = 0x20000000;
        if (actor->flags1C & mode_mask) {
            ((Rec_func_8008ACDC_arg0 *)action)->unk_96.as_s16 = (s16) pending_player_damage_kind;
        }
    }
}
