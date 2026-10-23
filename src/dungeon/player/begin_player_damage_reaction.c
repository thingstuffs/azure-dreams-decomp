#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "dungeon/player.h"

typedef struct S_80048A44_Obj S_80048A44_Obj;
typedef struct {
    s8 type;
    s8 value;
} Slot;
typedef struct {
    u8 pad[0x2C];
    Slot slots[4];
} SlotOwner;

void clear_slots_of_type(SlotOwner *owner, s8 match_type);             /* extern */
void set_sprite_animation_frame(S_80048A44_Obj *obj, s16 frame_group, s16 frame_index, s32 slot_index); /* extern */
s32 generate_random_value();                                /* extern */
extern u8 D_800DCFE0[];
extern u8 D_800DCFE8[];
extern u8 pending_player_damage_kind;

/* Initialize directional animation and reset the actor action state. */
void begin_player_damage_reaction(void *action, s32 unused, void *sprite, EntityRec *actor) {
    u8 *direction_table;
    ((Rec_func_8008ACDC_arg0 *)action)->unk_10C = (s16) (((Rec_func_8008ACDC_arg0 *)action)->unk_10C & 0xFFFE);
    {
        s32 mode_mask = 0x20000000;
        if (actor->flags1C & mode_mask) {
            direction_table = D_800DCFE0;
        } else {
            direction_table = D_800DCFE8;
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
