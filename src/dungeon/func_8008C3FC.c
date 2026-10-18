#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"

M2C_UNK func_80048A44(); /* extern */
s16 get_rounded_facing_and_rounding_flag();       /* extern */
extern u8 D_800DD030[];


typedef struct S_80091B5C_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
} S_80091B5C_1;   /* arg3 in begin_actor_turn_toward_target */


typedef struct S_80091B5C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
    void * unk_0C;
} S_80091B5C_3;   /* base in begin_actor_turn_toward_target */



   /* the 0x14 bytes before ((S_80091B5C_3 *)base)->unk_0C in begin_actor_turn_toward_target, addressed as ((S_80091B5C_3 *)base)->unk_0C[-1] */

/* Initializes the actor's action and turns it toward the current target. */
void begin_actor_turn_toward_target(void *action, void *unused, void *actor, void *motion) {
    M2C_UNK distance;
    void *target;

    if (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x8000) {
        ((S_80091B5C_1 *)motion)->unk_14 &= 0xFFFDFFFF;
        return;
    }
    ((Rec_func_8008ACDC_arg0 *)action)->unk_9A.as_s8 = 0x2A;
    ((Rec_func_8008ACDC_arg0 *)action)->unk_9B.as_s8 = 0;
    (*(s32 *)((u8 *)action + (0x8C))) = 0;
    g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) + 1);
    ((Rec_func_8008ACDC_arg0 *)action)->unk_96.as_s16 = 0x10;
    (*(u8 **)((u8 *)actor + (0x2C))) = D_800DD030;
    func_80048A44(actor, D_800DD030[((s32) (g_game_work.view.viewAngle + ((S_80091B5C_1 *)motion)->unk_2A + 0x100)
        >> 9) & 7], 0, 1);
    target = ((SpriteLinkPrefixView *)(g_dungeon_status.unk_0C))[-1].unk_00;
    ((Rec_func_8008ACDC_arg0 *)action)->unk_11A = (u16) ((S_80091B5C_1 *)motion)->unk_2A;
    ((S_80091B5C_1 *)motion)->unk_2A = get_rounded_facing_and_rounding_flag(((Rec_D_80082E80 *)actor)->unk_24,
        ((Rec_D_80082E80 *)actor)->unk_25, ((MovingTile *)target)->unk_24, ((MovingTile *)target)->unk_25,
        &distance);
}
