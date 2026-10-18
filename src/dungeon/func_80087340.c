#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"

M2C_UNK func_80042B68();             /* extern */
M2C_UNK func_80048A44(); /* extern */
void clear_player_linked_action_flags();                            /* extern */
s32 generate_random_value();                                /* extern */
extern u8 D_800DCFE0[];
extern u8 D_800DCFE8[];
extern u8 D_800E3E41;

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
        direction_entry = direction_table + (((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7);
        func_80048A44(sprite, *direction_entry, 0, 1);
    }
    ((Rec_func_8008ACDC_arg0 *)action)->unk_9A.as_s8 = 7;
    ((Rec_func_8008ACDC_arg0 *)action)->unk_9B.as_s8 = 0;
    ((Rec_func_8008ACDC_arg0 *)action)->unk_8C.as_s32 = 0;
    clear_player_linked_action_flags();
    if (!(generate_random_value() & 1)) {
        func_80042B68(actor, 1);
        func_80042B68(actor, 4);
        func_80042B68(actor, 2);
    }
    {
        s32 mode_mask = 0x20000000;
        if (actor->flags1C & mode_mask) {
            ((Rec_func_8008ACDC_arg0 *)action)->unk_96.as_s16 = (s16) D_800E3E41;
        }
    }
}
