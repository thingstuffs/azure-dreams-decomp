#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_801724B0_arg0.h"
#include "shared/entity.h"

typedef struct S_80047784 S_80047784;


void select_sprite_entry(S_80047784 *object, s16 table_index, s16 entry_index);         /* extern */
extern u8 D_800E2360;

/* Initializes state and configures the target using an angle-indexed table entry. */
void initialize_angle_indexed_target(void *state, s32 unused, void *target, EntityRec *angleSource) {
    ((Rec_func_801724B0_arg0 *)state)->unk_9A = 0x10;
    ((Rec_func_801724B0_arg0 *)state)->unk_9B = 0;
    (*(s32 **)((u8 *)target + 0x2C)) = &D_800E2360;
    select_sprite_entry(target, *((((s32) (g_game_work.view.viewAngle + angleSource->facing + 0x100) >> 9) & 7) + &D_800E2360),
        0);
    ((Rec_func_801724B0_arg0 *)state)->unk_AA = 0;
}
