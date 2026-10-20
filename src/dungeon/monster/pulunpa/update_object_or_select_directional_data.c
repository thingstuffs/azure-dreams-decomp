#include "common.h"
#include "shared/game_work.h"

extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);
extern s32 check_actor_floor_trap(void *, void *);
extern void select_sprite_entry(void *, u8, s32);

extern u8 D_80170F20[];
extern u8 D_80173B98[];
extern u8 D_801762C8[];
extern u8 D_80176300[];
extern u8 D_80176328[];
extern u8 D_80176360[];

/* Updates object state or selects a source table entry from the target direction. */
void update_object_or_select_directional_data(void *object_arg, void *context, void *source_arg, void *target_arg) {
    void *object = object_arg;
    void *source = source_arg;
    void *target = target_arg;
    void *state_table;

    if (update_actor_transform_from_parent(object_arg, context, source_arg, target_arg) != 0) {
        if ((check_actor_floor_trap(source, target) << 0x10) > 0) {
            if (*(u8 *)((u8 *)object + 0xA7) != 0) {
                *(void **)((u8 *)object + 0x8C) = D_80173B98;
            } else {
                *(void **)((u8 *)object + 0x8C) = D_80170F20;
            }
        }
        return;
    }

    state_table = *(void **)((u8 *)source + 0x2C);
    if (state_table == D_80176300) {
        if (*(s32 *)((u8 *)target + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)source + 0x2C) = D_801762C8;
        select_sprite_entry(source, D_801762C8[((g_game_work.view.viewAngle + *(s16 *)((u8 *)target + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else if (state_table == D_80176360) {
        if (*(s32 *)((u8 *)target + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)source + 0x2C) = D_80176328;
        select_sprite_entry(source, D_80176328[((g_game_work.view.viewAngle + *(s16 *)((u8 *)target + 0x2A) + 0x100) >> 9) & 7],
            0);
    } else {
        return;
    }

}

