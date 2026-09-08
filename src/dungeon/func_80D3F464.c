#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef struct {
    signed short x;
    signed short y;
} DirectionDelta;

extern signed short func_800D5F80(void *, void *);
extern void func_8009D8A4(void);
extern void func_800A56E0(s32);
extern s32 func_800BCB04(u16, u16, signed short);

extern DirectionDelta D_800E2468[];
extern s32 D_800E296C;
extern void *D_80170888[];


typedef struct S_80174C64_0 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x4];
    u16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
    u8 pad_B0[0x1];
    u8 unk_B1;
    u8 unk_B2;
    u8 unk_B3;
    u8 unk_B4;
} S_80174C64_0;   /* arg0 in func_80174C64 */


typedef struct S_80174C64_2 {
    u8 pad_00[0x62];
    u16 unk_62;
    u16 unk_64;
} S_80174C64_2;   /* (u8 *)((unsigned long)base + (i << 2)) in func_80174C64 */

typedef struct S_80174C64_3 {
    u8 pad_00[0x62];
    u16 unk_62;
    u16 unk_64;
} S_80174C64_3;   /* (u8 *)((unsigned long)base + ((i - 1) << 2)) in func_80174C64 */

/* Updates movement, turning, position history, and timed stop states. */
void func_80174C64(S_80174C64_0 *motion, void *position, Rec_D_80082E80 *record, void *object)
{
    static void *const state3_keep[] = {
        &&state3_0, &&state3_1, &&state3_2, &&state3_3, &&state3_4
    };
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
    state = motion->unk_B3;
    direction = (angle >> 9) & 7;
    if (state != 0) {
        goto state1_test;
    }

    switch (motion->unk_B1) {
    case 0:
        switch (motion->unk_B2) {
        case 0:
            if (record->unk_14.at00_u16.v & 0x8000) {
                goto set_state2_from_zero;
            }
            if (motion->unk_B4 >= 7U) {
                if ((angle & 0x3FF) == 0) {
                    motion->unk_B1 = 1;
                    motion->unk_B2 = 0;
                    motion->unk_96 = 0;
                    goto state0_done;
                }
            } else if ((angle & 0x3FF) == 0) {
                if (func_800D5F80(position, object) != 0) {
                    u16 next_state;

                    next_state = 0x1E;
                    motion->unk_96 = next_state;
                    next_state = motion->unk_B3;
                    history = motion->unk_AC;
                    motion->unk_B2 = 0;
                    motion->unk_B1 = 0;
                    next_state++;
                    motion->unk_B3 = next_state;
                    if (history != 0) {
                        u16 position_y;

                        history_base = (u8 *)history + 0x20;
                        (*(u16 *)((u8 *)history_base + 0x62)) = (*(u16 *)((u8 *)position + 2));
                        position_y = (*(u16 *)((u8 *)position + 6));
                        (*(u16 *)((u8 *)history_base + 0x68)) = 0;
                        (*(u16 *)((u8 *)history_base + 0x66)) = 0;
                        (*(u16 *)((u8 *)history_base + 0x64)) = position_y;
                    }
                    goto state0_done;
                }
            }
            motion->unk_B2 = 2;
            goto state0_done;

        case 1:
            {
                u16 timer = motion->unk_96;

                motion->unk_96 = timer - 1;
                if ((timer << 16) <= 0) {
                    motion->unk_B2 = 0;
                }
                goto state0_done;
            }

        case 2:
            next_angle = angle + 0x200;
            (*(u16 *)((u8 *)object + 0x2A)) = next_angle;
            if (((signed short)(next_angle)) >= 0x1000) {
                (*(u16 *)((u8 *)object + 0x2A)) = 0;
            }
            motion->unk_B2 = 1;
            motion->unk_96 = 1;
            motion->unk_B4++;
            goto state0_done;

        default:
            goto state0_done;
        }

    case 1:
        switch (motion->unk_B2) {
        case 0:
            if (record->unk_14.at00_u16.v & 0x8000) {
set_state2_from_zero:
                motion->unk_B3 = 2;
                goto state0_done;
            }
            if (func_800D5F80(position, object) != 0) {
                motion->unk_96 = 0x1E;
                motion->unk_B2 = 0;
                motion->unk_B1 = 0;
                motion->unk_B3++;
                goto state0_done;
            }
            motion->unk_96 = 3;
            motion->unk_B2++;
            /* fall through */

        case 1:
            {
                u16 timer = motion->unk_96;

                motion->unk_96 = timer - 1;
                if ((timer << 16) <= 0) {
                    motion->unk_B2 = 0;
                }
                (*(u16 *)((u8 *)position + 2)) = D_800E2468[direction].x * 16 + (*(u16 *)((u8 *)position + 2));
                (*(u16 *)((u8 *)position + 6)) = D_800E2468[direction].y * 16 + (*(u16 *)((u8 *)position + 6));
                goto state0_done;
            }

        default:
            goto state0_done;
        }

    default:
        goto state0_done;
    }

state0_done:
    state = motion->unk_B3;
state1_test:
    if (state != 1) {
        goto state2_test;
    }
    if (record->unk_14.at00_u16.v & 0x8000) {
        motion->unk_B3 = 2;
        goto state1_done;
    }

    {
        u16 elapsed_ticks = motion->unk_A8;

        motion->unk_A8 = elapsed_ticks + 1;
        if ((signed short)elapsed_ticks >= 300) {
            goto set_state3;
        }
    }

    {
        void *history_check = motion->unk_AC;

        if (history_check != 0) {
            history_base = (u8 *)history_check + 0x20;
            if (((*(signed short *)((u8 *)history_base + 0x66)) != 0 ||
                 (*(signed short *)((u8 *)history_base + 0x68)) != 0) &&
                (*(signed short *)((u8 *)history_base + 0x62)) == (*(signed short *)((u8 *)position + 2)) &&
                (*(signed short *)((u8 *)history_base + 0x64)) == (*(signed short *)((u8 *)position + 6))) {
                goto set_state3;
            }

            {
                history_load = (unsigned long)motion->unk_AC;

                if (history_load != 0) {
                    history_addr = history_load;

                    history_base = (u8 *)history_addr + 0x20;
                    history_x = (*(signed short *)((u8 *)history_base + 0x66));
                    if (history_x != 0 ||
                        (history_load = (signed long)(*(signed short *)((u8 *)history_base + 0x68))) != 0) {
                        history_index = 2;
                        do { history_base = (u8 *)history_addr + 0x20; } while (0);
                        do {
                            u8 *history_entry = history_base + (history_index << 2);

                            if (history_x == (*(signed short *)((u8 *)history_entry + 0x62)) &&
                                (*(signed short *)((u8 *)history_base + 0x68)) == (*(signed short *)((u8 *)history_entry + 0x64))) {
                                goto set_state3;
                            }
                            history_index++;
                        } while (history_index < 6);
                    }
                }
            }
        }
    }

    switch (motion->unk_B1) {
    case 0:
state1_call:
        if (func_800D5F80(position, object) == 0) {
            motion->unk_B1 = 2;
            motion->unk_B2 = 0;
            goto state1_case2;
        }
        motion->unk_B1 = 1;
        motion->unk_B2 = 0;
        /* fall through */

    case 1:
        switch (motion->unk_B2) {
        case 0:
state1_plus_angle:
            next_angle = (*(u16 *)((u8 *)object + 0x2A)) + 0x200;
            (*(u16 *)((u8 *)object + 0x2A)) = next_angle;
            if (((signed short)(next_angle)) >= 0x1000) {
                (*(u16 *)((u8 *)object + 0x2A)) = 0;
            }
            goto state1_advance_sub;

        case 1:
            {
                u16 timer = motion->unk_96;

                motion->unk_96 = timer - 1;
                if ((timer << 16) > 0) {
                    goto state1_done;
                }
                if (((*(u16 *)((u8 *)object + 0x2A)) & 0x3FF) != 0) {
                    motion->unk_B2 = 0;
                    goto state1_plus_angle;
                }
                motion->unk_B1 = 0;
                motion->unk_B2 = 0;
                goto state1_call;
            }

        default:
            goto state1_done;
        }

    case 2:
state1_case2:
        turn_phase = motion->unk_B2;
        switch (turn_phase) {
        case 0:
            motion->unk_B2 = (turn_phase == 0);
            motion->unk_96 = 3;
            /* fall through */

        case 1:
            {
                u16 timer;

                (*(u16 *)((u8 *)position + 2)) = D_800E2468[direction].x * 16 + (*(u16 *)((u8 *)position + 2));
                (*(u16 *)((u8 *)position + 6)) = D_800E2468[direction].y * 16 + (*(u16 *)((u8 *)position + 6));

                timer = motion->unk_96;
                motion->unk_96 = timer - 1;
                if ((timer << 16) > 0) {
                    goto state1_done;
                }

                {
                    void *history_copy = motion->unk_AC;

                    if (history_copy != 0) {
                        history_base = (u8 *)history_copy + 0x20;
                        for (history_index = 5; history_index >= 2; history_index--) {
                            ((S_80174C64_2 *)((u8 *)((unsigned long)history_base + (history_index << 2))))->unk_62 =
                                ((S_80174C64_3 *)((u8 *)((unsigned long)history_base + ((history_index - 1) << 2))))->unk_62;
                            ((S_80174C64_2 *)((u8 *)((unsigned long)history_base + (history_index << 2))))->unk_64 =
                                ((S_80174C64_3 *)((u8 *)((unsigned long)history_base + ((history_index - 1) << 2))))->unk_64;
                        }
                        (*(u16 *)((u8 *)history_base + 0x66)) = (*(u16 *)((u8 *)position + 2));
                        (*(u16 *)((u8 *)history_base + 0x68)) = (*(u16 *)((u8 *)position + 6));
                    }
                }

                saved_angle = (*(u16 *)((u8 *)object + 0x2A));
                next_angle = saved_angle - 0x400;
                (*(u16 *)((u8 *)object + 0x2A)) = next_angle;
                if ((next_angle << 16) < 0) {
                    (*(u16 *)((u8 *)object + 0x2A)) = saved_angle + 0xC00;
                }
                if (func_800D5F80(position, object) != 0) {
                    motion->unk_B2 = 0;
                    motion->unk_B1 = 0;
                    (*(u16 *)((u8 *)object + 0x2A)) = saved_angle;
                    goto state1_done;
                }
                motion->unk_B1 = 3;
                motion->unk_B2 = 0;
                (*(u16 *)((u8 *)object + 0x2A)) = saved_angle;
                goto state1_done;
            }

        default:
            goto state1_done;
        }

    case 3:
        switch (motion->unk_B2) {
        case 0:
state1_minus_angle:
            old_angle = (*(u16 *)((u8 *)object + 0x2A));
            next_angle = old_angle - 0x200;
            (*(u16 *)((u8 *)object + 0x2A)) = next_angle;
            if ((next_angle << 16) < 0) {
                (*(u16 *)((u8 *)object + 0x2A)) = old_angle + 0xE00;
            }
state1_advance_sub:
            next_phase = motion->unk_B2;
            motion->unk_96 = 0;
            motion->unk_B2 = next_phase + 1;
            goto state1_done;

        case 1:
            {
                u16 timer = motion->unk_96;

                motion->unk_96 = timer - 1;
                if ((timer << 16) > 0) {
                    goto state1_done;
                }
                if (((*(u16 *)((u8 *)object + 0x2A)) & 0x3FF) != 0) {
                    motion->unk_B2 = 0;
                    goto state1_minus_angle;
                }
                motion->unk_B1 = 2;
                motion->unk_B2 = 0;
                goto state1_case2;
            }

        default:
            goto state1_done;
        }

    default:
        goto state1_done;
    }

set_state3:
    motion->unk_B3 = 3;
    motion->unk_B1 = 0;
    goto state3_test;

state1_done:
    state = motion->unk_B3;
state2_test:
    if (state != 2) {
        goto state3_test;
    }
    (*(u16 *)((u8 *)object + 0x2A)) &= 0xFC00;
    motion->unk_9B++;
    record->unk_14.at00_u16.v |= 0x80;
    motion->unk_92 = 0;
    motion->unk_B1 = 0;
    motion->unk_96 = 0;
    motion->unk_A2 = 0;
    func_8009D8A4();
    D_800E296C |= 0x800000;
    func_800A56E0(0x80F);

state3_test:
    if (motion->unk_B3 != 3) {
        goto done;
    }
    state = motion->unk_B1;
    if ((u32)state >= 5) {
        goto done;
    }
    (void)state3_keep;
    goto *D_80170888[state];

state3_0:
    {
        u16 next_state = motion->unk_B1;

        motion->unk_96 = 10;
        motion->unk_B1 = next_state + 1;
    }

state3_1:
    {
        u16 timer = motion->unk_96;

        motion->unk_96 = timer - 1;
        if ((timer << 16) > 0) {
            goto done;
        }
    }
    motion->unk_B1++;
    goto done;

state3_2:
    record->unk_14.at00_u16.v |= 0x80;
    goto state3_set_timer;

state3_3:
    {
        u16 timer = motion->unk_96;

        motion->unk_96 = timer - 1;
        if ((timer << 16) > 0) {
            goto done;
        }
    }

state3_set_timer:
    motion->unk_96 = 20;
    motion->unk_B1++;
    goto done;

state3_4:
    {
        u16 timer = motion->unk_96;

        motion->unk_96 = timer - 1;
        if ((timer << 16) > 0) {
            goto done;
        }
    }
    (*(u16 *)((u8 *)object + 0x2A)) &= 0xFC00;
    motion->unk_9B++;
    record->unk_14.at00_u16.v |= 0x80;
    motion->unk_92 = 0;
    motion->unk_B1 = 0;
    motion->unk_96 = 0;
    motion->unk_A2 = 0;
    func_8009D8A4();
    D_800E296C |= 0x800000;
    func_800A56E0(0x80F);

done:
    (*(signed short *)((u8 *)object + 0x88)) = func_800BCB04(
        (*(u16 *)((u8 *)position + 2)), (*(u16 *)((u8 *)position + 6)),
        (signed short)((*(u16 *)((u8 *)position + 0xA)) - 0x20));
}
