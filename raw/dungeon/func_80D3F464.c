#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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

void func_80174C64(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const state3_keep[] = {
        &&state3_0, &&state3_1, &&state3_2, &&state3_3, &&state3_4
    };
    u16 temp_a0;
    u16 temp_v0;
    u16 temp_v1;
    s32 state;
    s32 direction;
    s32 temp_s1;
    void *temp_ptr;
    u8 *base;
    unsigned long loaded_addr;
    unsigned long history_addr;
    signed short history_x;
    s32 i;
    temp_a0 = FIELD(arg3, u16, 0x2A);
    state = FIELD(arg0, u8, 0xB3);
    direction = (temp_a0 >> 9) & 7;
    if (state != 0) {
        goto state1_test;
    }

    switch (FIELD(arg0, u8, 0xB1)) {
    case 0:
        switch (FIELD(arg0, u8, 0xB2)) {
        case 0:
            if (FIELD(arg2, u16, 0x14) & 0x8000) {
                goto set_state2_from_zero;
            }
            if (FIELD(arg0, u8, 0xB4) >= 7U) {
                if ((temp_a0 & 0x3FF) == 0) {
                    FIELD(arg0, u8, 0xB1) = 1;
                    FIELD(arg0, u8, 0xB2) = 0;
                    FIELD(arg0, u16, 0x96) = 0;
                    goto state0_done;
                }
            } else if ((temp_a0 & 0x3FF) == 0) {
                if (func_800D5F80(arg1, arg3) != 0) {
                    u16 next_state;

                    next_state = 0x1E;
                    FIELD(arg0, u16, 0x96) = next_state;
                    next_state = FIELD(arg0, u8, 0xB3);
                    temp_ptr = FIELD(arg0, void *, 0xAC);
                    FIELD(arg0, u8, 0xB2) = 0;
                    FIELD(arg0, u8, 0xB1) = 0;
                    next_state++;
                    FIELD(arg0, u8, 0xB3) = next_state;
                    if (temp_ptr != 0) {
                        u16 y;

                        base = (u8 *)temp_ptr + 0x20;
                        FIELD(base, u16, 0x62) = FIELD(arg1, u16, 2);
                        y = FIELD(arg1, u16, 6);
                        FIELD(base, u16, 0x68) = 0;
                        FIELD(base, u16, 0x66) = 0;
                        FIELD(base, u16, 0x64) = y;
                    }
                    goto state0_done;
                }
            }
            FIELD(arg0, u8, 0xB2) = 2;
            goto state0_done;

        case 1:
            {
            u16 timer = FIELD(arg0, u16, 0x96);

            FIELD(arg0, u16, 0x96) = timer - 1;
            if ((timer << 16) <= 0) {
                FIELD(arg0, u8, 0xB2) = 0;
            }
            goto state0_done;
            }

        case 2:
            temp_v0 = temp_a0 + 0x200;
            FIELD(arg3, u16, 0x2A) = temp_v0;
            if (((signed short)(temp_v0)) >= 0x1000) {
                FIELD(arg3, u16, 0x2A) = 0;
            }
            FIELD(arg0, u8, 0xB2) = 1;
            FIELD(arg0, u16, 0x96) = 1;
            FIELD(arg0, u8, 0xB4)++;
            goto state0_done;

        default:
            goto state0_done;
        }

    case 1:
        switch (FIELD(arg0, u8, 0xB2)) {
        case 0:
            if (FIELD(arg2, u16, 0x14) & 0x8000) {
set_state2_from_zero:
                FIELD(arg0, u8, 0xB3) = 2;
                goto state0_done;
            }
            if (func_800D5F80(arg1, arg3) != 0) {
                FIELD(arg0, u16, 0x96) = 0x1E;
                FIELD(arg0, u8, 0xB2) = 0;
                FIELD(arg0, u8, 0xB1) = 0;
                FIELD(arg0, u8, 0xB3)++;
                goto state0_done;
            }
            FIELD(arg0, u16, 0x96) = 3;
            FIELD(arg0, u8, 0xB2)++;
            /* fall through */

        case 1:
            {
            u16 timer = FIELD(arg0, u16, 0x96);

            FIELD(arg0, u16, 0x96) = timer - 1;
            if ((timer << 16) <= 0) {
                FIELD(arg0, u8, 0xB2) = 0;
            }
            FIELD(arg1, u16, 2) = D_800E2468[direction].x * 16 + FIELD(arg1, u16, 2);
            FIELD(arg1, u16, 6) = D_800E2468[direction].y * 16 + FIELD(arg1, u16, 6);
            goto state0_done;
            }

        default:
            goto state0_done;
        }

    default:
        goto state0_done;
    }

state0_done:
    state = FIELD(arg0, u8, 0xB3);
state1_test:
    if (state != 1) {
        goto state2_test;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0xB3) = 2;
        goto state1_done;
    }

    {
        u16 count = FIELD(arg0, u16, 0xA8);

        FIELD(arg0, u16, 0xA8) = count + 1;
        if ((signed short)count >= 300) {
            goto set_state3;
        }
    }

    {
        void *check_ptr = FIELD(arg0, void *, 0xAC);

        if (check_ptr != 0) {
            base = (u8 *)check_ptr + 0x20;
            if ((FIELD(base, signed short, 0x66) != 0 ||
                 FIELD(base, signed short, 0x68) != 0) &&
                FIELD(base, signed short, 0x62) == FIELD(arg1, signed short, 2) &&
                FIELD(base, signed short, 0x64) == FIELD(arg1, signed short, 6)) {
                goto set_state3;
            }

            {
                loaded_addr = (unsigned long)FIELD(arg0, void *, 0xAC);

                if (loaded_addr != 0) {
                    history_addr = loaded_addr;

                    base = (u8 *)history_addr + 0x20;
            history_x = FIELD(base, signed short, 0x66);
            if (history_x != 0 ||
                (loaded_addr = (signed long)FIELD(base, signed short, 0x68)) != 0) {
                i = 2;
                do { base = (u8 *)history_addr + 0x20; } while (0);
                do {
                    u8 *cursor = base + (i << 2);

                    if (history_x == FIELD(cursor, signed short, 0x62) &&
                        FIELD(base, signed short, 0x68) == FIELD(cursor, signed short, 0x64)) {
                        goto set_state3;
                    }
                    i++;
                } while (i < 6);
            }
                }
            }
        }
    }

    switch (FIELD(arg0, u8, 0xB1)) {
    case 0:
state1_call:
        if (func_800D5F80(arg1, arg3) == 0) {
            FIELD(arg0, u8, 0xB1) = 2;
            FIELD(arg0, u8, 0xB2) = 0;
            goto state1_case2;
        }
        FIELD(arg0, u8, 0xB1) = 1;
        FIELD(arg0, u8, 0xB2) = 0;
        /* fall through */

    case 1:
        switch (FIELD(arg0, u8, 0xB2)) {
        case 0:
state1_plus_angle:
            temp_v0 = FIELD(arg3, u16, 0x2A) + 0x200;
            FIELD(arg3, u16, 0x2A) = temp_v0;
            if (((signed short)(temp_v0)) >= 0x1000) {
                FIELD(arg3, u16, 0x2A) = 0;
            }
            goto state1_advance_sub;

        case 1:
            {
            u16 timer = FIELD(arg0, u16, 0x96);

            FIELD(arg0, u16, 0x96) = timer - 1;
            if ((timer << 16) > 0) {
                goto state1_done;
            }
            if ((FIELD(arg3, u16, 0x2A) & 0x3FF) != 0) {
                FIELD(arg0, u8, 0xB2) = 0;
                goto state1_plus_angle;
            }
            FIELD(arg0, u8, 0xB1) = 0;
            FIELD(arg0, u8, 0xB2) = 0;
            goto state1_call;
            }

        default:
            goto state1_done;
        }

    case 2:
state1_case2:
        temp_v1 = FIELD(arg0, u8, 0xB2);
        switch (temp_v1) {
        case 0:
            FIELD(arg0, u8, 0xB2) = (temp_v1 == 0);
            FIELD(arg0, u16, 0x96) = 3;
            /* fall through */

        case 1:
            {
            u16 timer;

            FIELD(arg1, u16, 2) = D_800E2468[direction].x * 16 + FIELD(arg1, u16, 2);
            FIELD(arg1, u16, 6) = D_800E2468[direction].y * 16 + FIELD(arg1, u16, 6);

            timer = FIELD(arg0, u16, 0x96);
            FIELD(arg0, u16, 0x96) = timer - 1;
            if ((timer << 16) > 0) {
                goto state1_done;
            }

            {
            void *copy_ptr = FIELD(arg0, void *, 0xAC);

            if (copy_ptr != 0) {
                base = (u8 *)copy_ptr + 0x20;
                for (i = 5; i >= 2; i--) {
                    FIELD((u8 *)((unsigned long)base + (i << 2)), u16, 0x62) =
                        FIELD((u8 *)((unsigned long)base + ((i - 1) << 2)), u16, 0x62);
                    FIELD((u8 *)((unsigned long)base + (i << 2)), u16, 0x64) =
                        FIELD((u8 *)((unsigned long)base + ((i - 1) << 2)), u16, 0x64);
                }
                FIELD(base, u16, 0x66) = FIELD(arg1, u16, 2);
                FIELD(base, u16, 0x68) = FIELD(arg1, u16, 6);
            }
            }

            temp_s1 = FIELD(arg3, u16, 0x2A);
            temp_v0 = temp_s1 - 0x400;
            FIELD(arg3, u16, 0x2A) = temp_v0;
            if ((temp_v0 << 16) < 0) {
                FIELD(arg3, u16, 0x2A) = temp_s1 + 0xC00;
            }
            if (func_800D5F80(arg1, arg3) != 0) {
                FIELD(arg0, u8, 0xB2) = 0;
                FIELD(arg0, u8, 0xB1) = 0;
                FIELD(arg3, u16, 0x2A) = temp_s1;
                goto state1_done;
            }
            FIELD(arg0, u8, 0xB1) = 3;
            FIELD(arg0, u8, 0xB2) = 0;
            FIELD(arg3, u16, 0x2A) = temp_s1;
            goto state1_done;
            }

        default:
            goto state1_done;
        }

    case 3:
        switch (FIELD(arg0, u8, 0xB2)) {
        case 0:
state1_minus_angle:
            temp_v1 = FIELD(arg3, u16, 0x2A);
            temp_v0 = temp_v1 - 0x200;
            FIELD(arg3, u16, 0x2A) = temp_v0;
            if ((temp_v0 << 16) < 0) {
                FIELD(arg3, u16, 0x2A) = temp_v1 + 0xE00;
            }
state1_advance_sub:
            temp_v0 = FIELD(arg0, u8, 0xB2);
            FIELD(arg0, u16, 0x96) = 0;
            FIELD(arg0, u8, 0xB2) = temp_v0 + 1;
            goto state1_done;

        case 1:
            {
            u16 timer = FIELD(arg0, u16, 0x96);

            FIELD(arg0, u16, 0x96) = timer - 1;
            if ((timer << 16) > 0) {
                goto state1_done;
            }
            if ((FIELD(arg3, u16, 0x2A) & 0x3FF) != 0) {
                FIELD(arg0, u8, 0xB2) = 0;
                goto state1_minus_angle;
            }
            FIELD(arg0, u8, 0xB1) = 2;
            FIELD(arg0, u8, 0xB2) = 0;
            goto state1_case2;
            }

        default:
            goto state1_done;
        }

    default:
        goto state1_done;
    }

set_state3:
    FIELD(arg0, u8, 0xB3) = 3;
    FIELD(arg0, u8, 0xB1) = 0;
    goto state3_test;

state1_done:
    state = FIELD(arg0, u8, 0xB3);
state2_test:
    if (state != 2) {
        goto state3_test;
    }
    FIELD(arg3, u16, 0x2A) &= 0xFC00;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u16, 0x14) |= 0x80;
    FIELD(arg0, u16, 0x92) = 0;
    FIELD(arg0, u8, 0xB1) = 0;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u16, 0xA2) = 0;
    func_8009D8A4();
    D_800E296C |= 0x800000;
    func_800A56E0(0x80F);

state3_test:
    if (FIELD(arg0, u8, 0xB3) != 3) {
        goto done;
    }
    state = FIELD(arg0, u8, 0xB1);
    if ((u32)state >= 5) {
        goto done;
    }
    (void)state3_keep;
    goto *D_80170888[state];

state3_0:
    {
    u16 next_state = FIELD(arg0, u8, 0xB1);

    FIELD(arg0, u16, 0x96) = 10;
    FIELD(arg0, u8, 0xB1) = next_state + 1;
    }

state3_1:
    {
        u16 timer = FIELD(arg0, u16, 0x96);

        FIELD(arg0, u16, 0x96) = timer - 1;
        if ((timer << 16) > 0) {
            goto done;
        }
    }
    FIELD(arg0, u8, 0xB1)++;
    goto done;

state3_2:
    FIELD(arg2, u16, 0x14) |= 0x80;
    goto state3_set_timer;

state3_3:
    {
        u16 timer = FIELD(arg0, u16, 0x96);

        FIELD(arg0, u16, 0x96) = timer - 1;
        if ((timer << 16) > 0) {
            goto done;
        }
    }

state3_set_timer:
    FIELD(arg0, u16, 0x96) = 20;
    FIELD(arg0, u8, 0xB1)++;
    goto done;

state3_4:
    {
        u16 timer = FIELD(arg0, u16, 0x96);

        FIELD(arg0, u16, 0x96) = timer - 1;
        if ((timer << 16) > 0) {
            goto done;
        }
    }
    FIELD(arg3, u16, 0x2A) &= 0xFC00;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u16, 0x14) |= 0x80;
    FIELD(arg0, u16, 0x92) = 0;
    FIELD(arg0, u8, 0xB1) = 0;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u16, 0xA2) = 0;
    func_8009D8A4();
    D_800E296C |= 0x800000;
    func_800A56E0(0x80F);

done:
    FIELD(arg3, signed short, 0x88) = func_800BCB04(
        FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
        (signed short)(FIELD(arg1, u16, 0xA) - 0x20));
}
