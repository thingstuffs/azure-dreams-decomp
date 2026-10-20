#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_8008E700_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008E700_0;   /* entity in update_player_jump */

extern void set_sprite_animation_frame(void *a0, u8 a1, s32 a2, s32 a3);
extern void process_unflagged_linked_entries(s32 a0);
extern void process_unflagged_linked_entries_alt(s32 a0);
extern s16 measure_directional_stopping_distance(s16 a0, void *a1, void *a2, s32 a3);
extern void append_packed_action_record(void *a0, s32 a1, s16 a2, s32 a3);
extern void play_sound_if_enabled(s32 a0);

extern s32 D_80081484;
extern u8 D_8008EAC8[];
extern u8 D_800DCFD0[8];
extern u8 D_800DD048[8];
extern u8 D_800DD060[8];
extern u8 D_800DD0C8[8];
extern s32 D_800E3540[3];

/* Advance the entity action through its motion, animation, and linked-child effects. */
void update_player_jump(u8 *action, u8 *motion, u8 *sprite, u8 *entity) {
    s16 effect_id;
    s32 entity_flags;
    s32 direction;
    u16 ticks;
    s32 phase;
    u8 *child;
    u8 *anim_sprite;

    phase = action[0x9B];
    switch (phase) {
    case 0:
        if (*(u16 *)(sprite + 0x14) & 0x6000) {
            *(s32 *)(motion + 0x14) = 0xFFEA0000;
            if (*(s32 *)(entity + 0x1C) & 0x100000) {
                *(u8 **)(sprite + 0x2C) = D_800DD0C8;
            } else {
                *(u8 **)(sprite + 0x2C) = D_800DD048;
            }
            anim_sprite = sprite;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)(entity + 0x2A) + 0x100) >> 9) & 7;
            set_sprite_animation_frame(anim_sprite, (*(u8 **)(anim_sprite + 0x2C))[direction], 0, 1);
            action[0x9B]++;
        }
        return;
    case 1:
        ticks = *(u16 *)(action + 0x96) + 1;
        *(u16 *)(action + 0x96) = ticks;
        if ((*(u16 *)(action + 0xA2) & 0x10) && ((s16)ticks >= 4)) {
            u8 *animations;
            s32 heading;
            s32 update_direction;

            *(s32 *)(motion + 0x14) = 0;
            if (*(s32 *)(entity + 0x1C) & 0x100000) {
                *(u8 **)(action + 0x8C) = D_8008EAC8;
            } else {
                anim_sprite = sprite;
                animations = D_800DD060;
                *(u8 **)(anim_sprite + 0x2C) = animations;
                update_direction = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)(entity + 0x2A) + 0x100) >> 9) & 7;
                set_sprite_animation_frame(anim_sprite, animations[update_direction], 0, 1);
            }
            action[0x9B]++;
            return;
        }

        if ((*(s32 *)(entity + 0x1C) & 0x300000) == 0x100000) {
            if (!((*(u16 *)0x80013714) & 1)) {
                effect_id = measure_directional_stopping_distance(*(s16 *)(entity + 0x2A), motion, sprite, 8);
                if ((effect_id << 16) != 0) {
                    child = *(u8 **)(action + 0x124);
                    *(s32 *)(child + 0x1C) |= 0x200000;
                    *(s32 *)(entity + 0x1C) |= 0x200000;
                    *(s16 *)(*(u8 **)(action + 0x124) + 0x8A) = effect_id;
                    *(u8 *)(*(u8 **)(action + 0x124) + 0x84) = 0x78;
                    *(u8 *)(*(u8 **)(action + 0x124) + 0x85) = 2;
                    append_packed_action_record(entity, 0x30, *(s16 *)(action + 0x96), 0);

                    {
                        s32 saved_state;
                        s32 angle;
                        s32 heading;

                        ((S_8008E700_0 *)entity)->unk_1C &= 0xFFEFFFFF;
                        saved_state = D_80081484;
                        D_80081484 = 0;
                        g_dungeon_status.activity_counts.parts.pending_action_count++;
                        *(u8 **)(sprite + 0x2C) = D_800DCFD0;
                        angle = g_game_work.view.camera_rotation.parts.viewAngle;
                        heading = *(s16 *)(entity + 0x2A);
                        D_800E3540[0] = saved_state;
                        set_sprite_animation_frame(sprite, D_800DCFD0[((angle + heading + 0x100) >> 9) & 7], 5, 1);
                    }
                    play_sound_if_enabled(0x512);
                    return;
                }
            }
        }
        return;
    case 2:
        anim_sprite = sprite;
        if ((*(u16 *)(anim_sprite + 0x14) & 0x6000) &&
            (g_dungeon_status.activity_counts.parts.pending_action_count == 0)) {
            entity_flags = *(s32 *)(entity + 0x1C);
            if (entity_flags & 0x200000) {
                *(s32 *)(entity + 0x1C) = entity_flags & 0xFFDFFFFF;
                g_dungeon_status.flags |= 0x412;
                process_unflagged_linked_entries_alt(*(s32 *)(entity + 0x5C));
                process_unflagged_linked_entries(*(s32 *)(entity + 0x5C));
            }
            *(s32 **)(action + 0x8C) = handle_player_input;
        }
    }
}
