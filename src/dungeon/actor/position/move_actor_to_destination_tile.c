#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"

void begin_player_trap_trigger(); /* extern */
void set_record_integer_tile_center();              /* extern */
extern M2C_UNK D_80096384;

/* Move the actor toward the destination tile and finish movement when the timer expires. */
void move_actor_to_destination_tile(Rec_func_8008ACDC_arg0 *actor, EntityRec *motion, SpriteFrameState *destination, s32 context) {
    s16 frames_left;
    u16 actor_flags;
    s32 saved_context;
    saved_context = context;

    if (g_dungeon_status.flags & 0x80) {
        g_dungeon_status.unk_04 = 0;
    }
    if (g_dungeon_status.unk_04 != 0) {
        motion->unk_0C = (s32) ((s32) ((((destination->unk_24 << 6) + 0x20) << 0x10)
            - motion->x.v) / (s16) g_dungeon_status.unk_04);
        motion->unk_10 = (s32) ((s32) ((((destination->unk_25 << 6) + 0x20) << 0x10)
            - motion->y.v) / (s16) g_dungeon_status.unk_04);
    }
    actor_flags = actor->unk_A2;
    if (!(actor_flags & 0x10)) {
        actor->unk_A2 = (u16) (actor_flags | 1);
    }
    frames_left = (u16) g_dungeon_status.unk_04 - 1;
    g_dungeon_status.unk_04 = frames_left;
    if ((frames_left << 0x10) <= 0) {
        g_dungeon_status.unk_04 = 0;
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, destination->unk_24, destination->unk_25);
        destination->flags = (u16) (destination->flags | 0x4000);
        if (actor->unk_100 >= 0) {
            begin_player_trap_trigger(actor, motion, destination, saved_context);
            return;
        }
        actor->unk_8C.as_pm = &D_80096384;
    }
}
