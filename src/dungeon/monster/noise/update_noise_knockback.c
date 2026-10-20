/* Relinked copy of dungeon/func_80AF200C (func_80AF200C.c); retail differs only at relocation sites. */
#include "modules/dungeon_resource10_slot0.h"

/* r121_nodonor relink of dungeon/func_80AF200C: symbols this copy binds at other addresses. */
extern u8 D_80156ED8[];
extern u8 D_80156E98[];
extern u8 D_80156E88[];
void func_80153760(void *actor_arg, void *context_arg, void *sprite_arg, EntityRec *entity_arg);

void update_noise_knockback(void *action, EntityRec *motion, void *entity, EntityRec *actor)
{
    s32 state;

    state = ((R10_8017380C_S_8017380C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        ((R10_8017380C_S_8017380C_0 *)action)->unk_96.s = 4;
        ((R10_8017380C_S_8017380C_0 *)action)->unk_9B++;
        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(action, motion, entity, ((u8 *)D_80156ED8));
            return;
        }
        if (!(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
            return;
        }
        ((R10_8017380C_S_8017380C_0 *)action)->unk_96.s = 0;
        ((R10_8017380C_S_8017380C_0 *)action)->unk_9B = 3;
        return;

    case 1:
    {
        s16 frames_left;

        frames_left = ((R10_8017380C_S_8017380C_0 *)action)->unk_96.u - 1;
        ((R10_8017380C_S_8017380C_0 *)action)->unk_96.s = frames_left;
        if (frames_left > 0) {
            motion->unk_0C =
                *(s16 *)((u8 *)((s8 *)dir_step_x) +
                    ((actor->unk_6A >> 8) & 0xE)) << 19;
            motion->unk_10 =
                *(s16 *)((u8 *)((s8 *)dir_step_y) +
                    ((actor->unk_6A >> 8) & 0xE)) << 19;
            return;
        }
        if (frames_left != 0) {
            return;
        }
        motion->unk_0C =
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                ((actor->unk_6A >> 8) & 0xE)) << 18;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                ((actor->unk_6A >> 8) & 0xE)) << 18;
        ((R10_8017380C_S_8017380C_0 *)action)->unk_96.s = 6;
        ((R10_8017380C_S_8017380C_0 *)action)->unk_9B++;
        return;
    }

    case 2:
        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(action, motion, entity, ((u8 *)D_80156ED8));
            return;
        }
        {
            s16 return_frames;
            s32 origin_y;
            u16 previous_frames;

            return_frames = ((R10_8017380C_S_8017380C_0 *)action)->unk_96.s;
            if (return_frames != 0) {
                motion->unk_0C =
                    (((((Rec_D_80082E80 *)entity)->unk_24 << 6) - ({ motion->x.w.i - 0x20; })) << 16) / return_frames;
                origin_y = motion->y.w.i - 0x20;
                motion->unk_10 =
                    (((((Rec_D_80082E80 *)entity)->unk_25 << 6) - origin_y) << 16) /
                    ((R10_8017380C_S_8017380C_0 *)action)->unk_96.s;
            }
            previous_frames = ((R10_8017380C_S_8017380C_0 *)action)->unk_96.u;
            ((R10_8017380C_S_8017380C_0 *)action)->unk_96.s = previous_frames - 1;
            if ((s32)(previous_frames << 16) > 0) {
                return;
            }
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            ((R10_8017380C_S_8017380C_0 *)action)->unk_9B++;
            return;
        }

    case 3:
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25);
        if (((Rec_D_80082E80 *)entity)->unk_2C.as_pv == ((u8 *)D_80156E98)) {
            u8 *direction_table;

            direction_table = ((u8 *)D_80156E88);
            (*(void * *)((u8 *)entity + 0x2C)) = direction_table;
            select_sprite_entry(entity,
                direction_table[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        {
            s32 entity_ref;

            entity_ref = ((s32)g_dungeon_status.unk_10);
            if (entity_ref == (s32)((u8 *)actor - 0x20)) {
                g_dungeon_status.unk_10 = entity_ref & 0x7FFFFFFF;
            }
        }
        ((R10_8017380C_S_8017380C_0 *)action)->unk_8C = ((void *)func_80153760);
        return;
    }
}
