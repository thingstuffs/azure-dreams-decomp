#include "dungeon/level/floor_flags.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/effect/screen.h"
#include "dungeon/level.h"
#include "dungeon/effect/shade.h"

typedef struct {
    signed short x;
    signed short y;
} DirectionDelta;

extern void play_sound_if_enabled(s32);

extern DirectionDelta actor_direction_step_pairs[];

typedef struct S_80174C64_2 {
    u8 pad_00[0x62];
    u16 unk_62;
    u16 unk_64;
} S_80174C64_2;   /* (u8 *)((unsigned long)base + (i << 2)) in update_actor_movement_history */

typedef struct S_80174C64_3 {
    u8 pad_00[0x62];
    u16 unk_62;
    u16 unk_64;
} S_80174C64_3;   /* (u8 *)((unsigned long)base + ((i - 1) << 2)) in update_actor_movement_history */

/* Updates movement, turning, position history, and timed stop states. */
/* Steers around obstacles while recording positions; stops on repeated positions, timeout, or the sprite
 * flag. */
void update_actor_movement_history(ActorRecord *motion, ObjectPosition *position, SpriteFrameState *record, void *object)
{
    u16 angle;
    u16 next_angle;
    u16 turn_phase;
    u16 old_angle;
    u16 next_phase;
    s32 state;
    s32 direction;
    s32 saved_angle;
    void *history;
    u8 *history_base;
    unsigned long history_load;
    unsigned long history_addr;
    signed short history_x;
    s32 history_index;
    angle = (*(u16 *)((u8 *)object + 0x2A));
    state = motion->unk_B0.bytes[3];
    direction = (angle >> 9) & 7;
    if (state == 0) {
    switch (motion->unk_B0.bytes[1]) {
    case 0:
        switch (motion->unk_B0.bytes[2]) {
        case 0:
            if (record->flags & 0x8000) {
                motion->unk_B0.bytes[3] = 2;
                break;
            }
            if (motion->unk_B4.bytes[0] >= 7U) {
                if ((angle & 0x3FF) == 0) {
                    motion->unk_B0.bytes[1] = 1;
                    motion->unk_B0.bytes[2] = 0;
                    motion->action_timer.u = 0;
                    break;
                }
            } else if ((angle & 0x3FF) == 0) {
                if (check_forward_collision_and_height(position, object) != 0) {
                    u16 next_state;

                    next_state = 0x1E;
                    motion->action_timer.u = next_state;
                    next_state = motion->unk_B0.bytes[3];
                    history = motion->unk_AC.address;
                    motion->unk_B0.bytes[2] = 0;
                    motion->unk_B0.bytes[1] = 0;
                    next_state++;
                    motion->unk_B0.bytes[3] = next_state;
                    if (history != 0) {
                        u16 position_y;

                        history_base = (u8 *)history + 0x20;
                        (*(u16 *)(history_base + 0x62)) = (*(u16 *)&position->x.w.i);
                        position_y = (*(u16 *)&position->y.w.i);
                        (*(u16 *)(history_base + 0x68)) = 0;
                        (*(u16 *)(history_base + 0x66)) = 0;
                        (*(u16 *)(history_base + 0x64)) = position_y;
                    }
                    break;
                }
            }
            motion->unk_B0.bytes[2] = 2;
            break;

        case 1:
        {
            u16 timer = motion->action_timer.u;

            motion->action_timer.u = timer - 1;
            if ((timer << 16) <= 0) {
                motion->unk_B0.bytes[2] = 0;
            }
            break;
        }

        case 2:
            next_angle = angle + 0x200;
            (*(u16 *)((u8 *)object + 0x2A)) = next_angle;
            if (((signed short)(next_angle)) >= 0x1000) {
                (*(u16 *)((u8 *)object + 0x2A)) = 0;
            }
            motion->unk_B0.bytes[2] = 1;
            motion->action_timer.u = 1;
            motion->unk_B4.bytes[0]++;
            break;

        default:
            break;
        }
        break;

    case 1:
        switch (motion->unk_B0.bytes[2]) {
        case 0:
            if (record->flags & 0x8000) {
                motion->unk_B0.bytes[3] = 2;
                break;
            }
            if (check_forward_collision_and_height(position, object) != 0) {
                motion->action_timer.u = 0x1E;
                motion->unk_B0.bytes[2] = 0;
                motion->unk_B0.bytes[1] = 0;
                motion->unk_B0.bytes[3]++;
                break;
            }
            motion->action_timer.u = 3;
            motion->unk_B0.bytes[2]++;
                                    /* fall through */

        case 1:
        {
            u16 timer = motion->action_timer.u;

            motion->action_timer.u = timer - 1;
            if ((timer << 16) <= 0) {
                motion->unk_B0.bytes[2] = 0;
            }
            (position->x.w.i) = actor_direction_step_pairs[direction].x * 16 + (*(u16 *)&position->x.w.i);
            (position->y.w.i) = actor_direction_step_pairs[direction].y * 16 + (*(u16 *)&position->y.w.i);
            break;
        }

        default:
            break;
        }
        break;

    default:
        break;
    }
    state = motion->unk_B0.bytes[3];
    }

    if (state == 1) {
        if (record->flags & 0x8000) {
            motion->unk_B0.bytes[3] = 2;
        } else {
            {
                u16 elapsed_ticks = motion->unk_A8.u;

                motion->unk_A8.u = elapsed_ticks + 1;
                if ((signed short)elapsed_ticks >= 300) {
                    motion->unk_B0.bytes[3] = 3;
                    motion->unk_B0.bytes[1] = 0;
                    goto state3_test;
                }
            }

            {
                void *history_check = motion->unk_AC.address;

                if (history_check != 0) {
                    history_base = (u8 *)history_check + 0x20;
                    if (((*(signed short *)(history_base + 0x66)) != 0 ||
                         (*(signed short *)(history_base + 0x68)) != 0) &&
                        (*(signed short *)(history_base + 0x62)) == (position->x.w.i) &&
                        (*(signed short *)(history_base + 0x64)) == (position->y.w.i)) {
                        motion->unk_B0.bytes[3] = 3;
                        motion->unk_B0.bytes[1] = 0;
                        goto state3_test;
                    }

                    {
                        history_load = (unsigned long)motion->unk_AC.address;

                        if (history_load != 0) {
                            history_addr = history_load;

                            history_base = (u8 *)history_addr + 0x20;
                            history_x = (*(signed short *)(history_base + 0x66));
                            if (history_x != 0 ||
                                (history_load = (signed long)(*(signed short *)(history_base + 0x68))) != 0) {
                                history_index = 2;
                                history_base = (u8 *)history_addr + 0x20;
                                do {
                                    u8 *history_entry = history_base + (history_index << 2);

                                    if (history_x == (*(signed short *)(history_entry + 0x62)) &&
                                        (*(signed short *)(history_base + 0x68))
                                        == (*(signed short *)(history_entry + 0x64))) {
                                        motion->unk_B0.bytes[3] = 3;
                                        motion->unk_B0.bytes[1] = 0;
                                        goto state3_test;
                                    }
                                    history_index++;
                                } while (history_index < 6);
                            }
                        }
                    }
                }
            }

            switch (motion->unk_B0.bytes[1]) {
            case 0:
state1_call:
                if (check_forward_collision_and_height(position, object) == 0) {
                    motion->unk_B0.bytes[1] = 2;
                    motion->unk_B0.bytes[2] = 0;
                    goto state1_case2;
                }
                motion->unk_B0.bytes[1] = 1;
                motion->unk_B0.bytes[2] = 0;
                                /* fall through */

            case 1:
                switch (motion->unk_B0.bytes[2]) {
                case 0:
                    next_angle = (*(u16 *)((u8 *)object + 0x2A)) + 0x200;
                    (*(u16 *)((u8 *)object + 0x2A)) = next_angle;
                    if (((signed short)(next_angle)) >= 0x1000) {
                        (*(u16 *)((u8 *)object + 0x2A)) = 0;
                    }
                    next_phase = motion->unk_B0.bytes[2];
                    motion->action_timer.u = 0;
                    motion->unk_B0.bytes[2] = next_phase + 1;
                    break;

                case 1:
                {
                    u16 timer = motion->action_timer.u;

                    motion->action_timer.u = timer - 1;
                    if ((timer << 16) > 0) {
                        break;
                    }
                    if (((*(u16 *)((u8 *)object + 0x2A)) & 0x3FF) != 0) {
                        motion->unk_B0.bytes[2] = 0;
                        next_angle = (*(u16 *)((u8 *)object + 0x2A)) + 0x200;
                        (*(u16 *)((u8 *)object + 0x2A)) = next_angle;
                        if (((signed short)(next_angle)) >= 0x1000) {
                            (*(u16 *)((u8 *)object + 0x2A)) = 0;
                        }
                        next_phase = motion->unk_B0.bytes[2];
                        motion->action_timer.u = 0;
                        motion->unk_B0.bytes[2] = next_phase + 1;
                        break;
                    }
                    motion->unk_B0.bytes[1] = 0;
                    motion->unk_B0.bytes[2] = 0;
                    goto state1_call;
                }

                default:
                    break;
                }
                break;

            case 2:
state1_case2:
                turn_phase = motion->unk_B0.bytes[2];
                switch (turn_phase) {
                case 0:
                    motion->unk_B0.bytes[2] = (turn_phase == 0);
                    motion->action_timer.u = 3;
                                            /* fall through */

                case 1:
                {
                    u16 timer;

                    (position->x.w.i) = actor_direction_step_pairs[direction].x * 16 + (*(u16 *)&position->x.w.i);
                    (position->y.w.i) = actor_direction_step_pairs[direction].y * 16 + (*(u16 *)&position->y.w.i);

                    timer = motion->action_timer.u;
                    motion->action_timer.u = timer - 1;
                    if ((timer << 16) > 0) {
                        break;
                    }

                    {
                        void *history_copy = motion->unk_AC.address;

                        if (history_copy != 0) {
                            history_base = (u8 *)history_copy + 0x20;
                            for (history_index = 5; history_index >= 2; history_index--) {
                                ((S_80174C64_2 *)((u8 *)((unsigned long)history_base + (history_index << 2))))->unk_62 =
                                    ((S_80174C64_3 *)((u8 *)((unsigned long)history_base
                                        + ((history_index - 1) << 2))))->unk_62;
                                ((S_80174C64_2 *)((u8 *)((unsigned long)history_base + (history_index << 2))))->unk_64 =
                                    ((S_80174C64_3 *)((u8 *)((unsigned long)history_base
                                        + ((history_index - 1) << 2))))->unk_64;
                            }
                            (*(u16 *)(history_base + 0x66)) = (*(u16 *)&position->x.w.i);
                            (*(u16 *)(history_base + 0x68)) = (*(u16 *)&position->y.w.i);
                        }
                    }

                    saved_angle = (*(u16 *)((u8 *)object + 0x2A));
                    next_angle = saved_angle - 0x400;
                    (*(u16 *)((u8 *)object + 0x2A)) = next_angle;
                    if ((next_angle << 16) < 0) {
                        (*(u16 *)((u8 *)object + 0x2A)) = saved_angle + 0xC00;
                    }
                    if (check_forward_collision_and_height(position, object) != 0) {
                        motion->unk_B0.bytes[2] = 0;
                        motion->unk_B0.bytes[1] = 0;
                        (*(u16 *)((u8 *)object + 0x2A)) = saved_angle;
                        break;
                    }
                    motion->unk_B0.bytes[1] = 3;
                    motion->unk_B0.bytes[2] = 0;
                    (*(u16 *)((u8 *)object + 0x2A)) = saved_angle;
                    break;
                }

                default:
                    break;
                }
                break;

            case 3:
                switch (motion->unk_B0.bytes[2]) {
                case 0:
state1_minus_angle:
                    old_angle = (*(u16 *)((u8 *)object + 0x2A));
                    next_angle = old_angle - 0x200;
                    (*(u16 *)((u8 *)object + 0x2A)) = next_angle;
                    if ((next_angle << 16) < 0) {
                        (*(u16 *)((u8 *)object + 0x2A)) = old_angle + 0xE00;
                    }
                    next_phase = motion->unk_B0.bytes[2];
                    motion->action_timer.u = 0;
                    motion->unk_B0.bytes[2] = next_phase + 1;
                    break;

                case 1:
                {
                    u16 timer = motion->action_timer.u;

                    motion->action_timer.u = timer - 1;
                    if ((timer << 16) > 0) {
                        break;
                    }
                    if (((*(u16 *)((u8 *)object + 0x2A)) & 0x3FF) != 0) {
                        motion->unk_B0.bytes[2] = 0;
                        goto state1_minus_angle;
                    }
                    motion->unk_B0.bytes[1] = 2;
                    motion->unk_B0.bytes[2] = 0;
                    goto state1_case2;
                }

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }
        state = motion->unk_B0.bytes[3];
    }
    if (state == 2) {
        (*(u16 *)((u8 *)object + 0x2A)) &= 0xFC00;
        motion->action_phase.u++;
        record->flags |= 0x80;
        motion->unk_90.parts.high.u = 0;
        motion->unk_B0.bytes[1] = 0;
        motion->action_timer.u = 0;
        motion->unk_A0.parts.high = 0;
        pack_and_submit_cell_height_levels();
        dungeon_floor_flags |= FLOOR_MAP_VIEW_HOLD;
        play_sound_if_enabled(0x80F);
    }
state3_test:
    if (motion->unk_B0.bytes[3] == 3) {
        state = motion->unk_B0.bytes[1];
        switch (state) {

        case 0:
        {
            u16 next_state = motion->unk_B0.bytes[1];

            motion->action_timer.u = 10;
            motion->unk_B0.bytes[1] = next_state + 1;
        }

        case 1:
        {
            u16 timer = motion->action_timer.u;

            motion->action_timer.u = timer - 1;
            if ((timer << 16) > 0) {
                break;
            }
        }
            motion->unk_B0.bytes[1]++;
            break;

        case 2:
            record->flags |= 0x80;
            motion->action_timer.u = 20;
            motion->unk_B0.bytes[1]++;
            break;

        case 3:
        {
            u16 timer = motion->action_timer.u;

            motion->action_timer.u = timer - 1;
            if ((timer << 16) > 0) {
                break;
            }
        }

            motion->action_timer.u = 20;
            motion->unk_B0.bytes[1]++;
            break;

        case 4:
        {
            u16 timer = motion->action_timer.u;

            motion->action_timer.u = timer - 1;
            if ((timer << 16) > 0) {
                break;
            }
        }
            (*(u16 *)((u8 *)object + 0x2A)) &= 0xFC00;
            motion->action_phase.u++;
            record->flags |= 0x80;
            motion->unk_90.parts.high.u = 0;
            motion->unk_B0.bytes[1] = 0;
            motion->action_timer.u = 0;
            motion->unk_A0.parts.high = 0;
            pack_and_submit_cell_height_levels();
            dungeon_floor_flags |= FLOOR_MAP_VIEW_HOLD;
            play_sound_if_enabled(0x80F);

        }

    }
    (*(signed short *)((u8 *)object + 0x88)) = sample_terrain_surface_height(
        (*(u16 *)((u8 *)position + 2)), (*(u16 *)&position->y.w.i),
        (signed short)((*(u16 *)&position->z.w.i) - 0x20));
}
