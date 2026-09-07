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

void func_80174C64(S_80174C64_0 *arg0, void *arg1, Rec_D_80082E80 *arg2, void *arg3)
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
    temp_a0 = (*(u16 *)((u8 *)arg3 + 0x2A));
    state = arg0->unk_B3;
    direction = (temp_a0 >> 9) & 7;
    if (state != 0) {
        goto state1_test;
    }

    switch (arg0->unk_B1) {
    case 0:
        switch (arg0->unk_B2) {
        case 0:
            if (arg2->unk_14.at00_u16.v & 0x8000) {
                goto set_state2_from_zero;
            }
            if (arg0->unk_B4 >= 7U) {
                if ((temp_a0 & 0x3FF) == 0) {
                    arg0->unk_B1 = 1;
                    arg0->unk_B2 = 0;
                    arg0->unk_96 = 0;
                    goto state0_done;
                }
            } else if ((temp_a0 & 0x3FF) == 0) {
                if (func_800D5F80(arg1, arg3) != 0) {
                    u16 next_state;

                    next_state = 0x1E;
                    arg0->unk_96 = next_state;
                    next_state = arg0->unk_B3;
                    temp_ptr = arg0->unk_AC;
                    arg0->unk_B2 = 0;
                    arg0->unk_B1 = 0;
                    next_state++;
                    arg0->unk_B3 = next_state;
                    if (temp_ptr != 0) {
                        u16 y;

                        base = (u8 *)temp_ptr + 0x20;
                        (*(u16 *)((u8 *)base + 0x62)) = (*(u16 *)((u8 *)arg1 + 2));
                        y = (*(u16 *)((u8 *)arg1 + 6));
                        (*(u16 *)((u8 *)base + 0x68)) = 0;
                        (*(u16 *)((u8 *)base + 0x66)) = 0;
                        (*(u16 *)((u8 *)base + 0x64)) = y;
                    }
                    goto state0_done;
                }
            }
            arg0->unk_B2 = 2;
            goto state0_done;

        case 1:
            {
            u16 timer = arg0->unk_96;

            arg0->unk_96 = timer - 1;
            if ((timer << 16) <= 0) {
                arg0->unk_B2 = 0;
            }
            goto state0_done;
            }

        case 2:
            temp_v0 = temp_a0 + 0x200;
            (*(u16 *)((u8 *)arg3 + 0x2A)) = temp_v0;
            if (((signed short)(temp_v0)) >= 0x1000) {
                (*(u16 *)((u8 *)arg3 + 0x2A)) = 0;
            }
            arg0->unk_B2 = 1;
            arg0->unk_96 = 1;
            arg0->unk_B4++;
            goto state0_done;

        default:
            goto state0_done;
        }

    case 1:
        switch (arg0->unk_B2) {
        case 0:
            if (arg2->unk_14.at00_u16.v & 0x8000) {
set_state2_from_zero:
                arg0->unk_B3 = 2;
                goto state0_done;
            }
            if (func_800D5F80(arg1, arg3) != 0) {
                arg0->unk_96 = 0x1E;
                arg0->unk_B2 = 0;
                arg0->unk_B1 = 0;
                arg0->unk_B3++;
                goto state0_done;
            }
            arg0->unk_96 = 3;
            arg0->unk_B2++;
            /* fall through */

        case 1:
            {
            u16 timer = arg0->unk_96;

            arg0->unk_96 = timer - 1;
            if ((timer << 16) <= 0) {
                arg0->unk_B2 = 0;
            }
            (*(u16 *)((u8 *)arg1 + 2)) = D_800E2468[direction].x * 16 + (*(u16 *)((u8 *)arg1 + 2));
            (*(u16 *)((u8 *)arg1 + 6)) = D_800E2468[direction].y * 16 + (*(u16 *)((u8 *)arg1 + 6));
            goto state0_done;
            }

        default:
            goto state0_done;
        }

    default:
        goto state0_done;
    }

state0_done:
    state = arg0->unk_B3;
state1_test:
    if (state != 1) {
        goto state2_test;
    }
    if (arg2->unk_14.at00_u16.v & 0x8000) {
        arg0->unk_B3 = 2;
        goto state1_done;
    }

    {
        u16 count = arg0->unk_A8;

        arg0->unk_A8 = count + 1;
        if ((signed short)count >= 300) {
            goto set_state3;
        }
    }

    {
        void *check_ptr = arg0->unk_AC;

        if (check_ptr != 0) {
            base = (u8 *)check_ptr + 0x20;
            if (((*(signed short *)((u8 *)base + 0x66)) != 0 ||
                 (*(signed short *)((u8 *)base + 0x68)) != 0) &&
                (*(signed short *)((u8 *)base + 0x62)) == (*(signed short *)((u8 *)arg1 + 2)) &&
                (*(signed short *)((u8 *)base + 0x64)) == (*(signed short *)((u8 *)arg1 + 6))) {
                goto set_state3;
            }

            {
                loaded_addr = (unsigned long)arg0->unk_AC;

                if (loaded_addr != 0) {
                    history_addr = loaded_addr;

                    base = (u8 *)history_addr + 0x20;
            history_x = (*(signed short *)((u8 *)base + 0x66));
            if (history_x != 0 ||
                (loaded_addr = (signed long)(*(signed short *)((u8 *)base + 0x68))) != 0) {
                i = 2;
                do { base = (u8 *)history_addr + 0x20; } while (0);
                do {
                    u8 *cursor = base + (i << 2);

                    if (history_x == (*(signed short *)((u8 *)cursor + 0x62)) &&
                        (*(signed short *)((u8 *)base + 0x68)) == (*(signed short *)((u8 *)cursor + 0x64))) {
                        goto set_state3;
                    }
                    i++;
                } while (i < 6);
            }
                }
            }
        }
    }

    switch (arg0->unk_B1) {
    case 0:
state1_call:
        if (func_800D5F80(arg1, arg3) == 0) {
            arg0->unk_B1 = 2;
            arg0->unk_B2 = 0;
            goto state1_case2;
        }
        arg0->unk_B1 = 1;
        arg0->unk_B2 = 0;
        /* fall through */

    case 1:
        switch (arg0->unk_B2) {
        case 0:
state1_plus_angle:
            temp_v0 = (*(u16 *)((u8 *)arg3 + 0x2A)) + 0x200;
            (*(u16 *)((u8 *)arg3 + 0x2A)) = temp_v0;
            if (((signed short)(temp_v0)) >= 0x1000) {
                (*(u16 *)((u8 *)arg3 + 0x2A)) = 0;
            }
            goto state1_advance_sub;

        case 1:
            {
            u16 timer = arg0->unk_96;

            arg0->unk_96 = timer - 1;
            if ((timer << 16) > 0) {
                goto state1_done;
            }
            if (((*(u16 *)((u8 *)arg3 + 0x2A)) & 0x3FF) != 0) {
                arg0->unk_B2 = 0;
                goto state1_plus_angle;
            }
            arg0->unk_B1 = 0;
            arg0->unk_B2 = 0;
            goto state1_call;
            }

        default:
            goto state1_done;
        }

    case 2:
state1_case2:
        temp_v1 = arg0->unk_B2;
        switch (temp_v1) {
        case 0:
            arg0->unk_B2 = (temp_v1 == 0);
            arg0->unk_96 = 3;
            /* fall through */

        case 1:
            {
            u16 timer;

            (*(u16 *)((u8 *)arg1 + 2)) = D_800E2468[direction].x * 16 + (*(u16 *)((u8 *)arg1 + 2));
            (*(u16 *)((u8 *)arg1 + 6)) = D_800E2468[direction].y * 16 + (*(u16 *)((u8 *)arg1 + 6));

            timer = arg0->unk_96;
            arg0->unk_96 = timer - 1;
            if ((timer << 16) > 0) {
                goto state1_done;
            }

            {
            void *copy_ptr = arg0->unk_AC;

            if (copy_ptr != 0) {
                base = (u8 *)copy_ptr + 0x20;
                for (i = 5; i >= 2; i--) {
                    ((S_80174C64_2 *)((u8 *)((unsigned long)base + (i << 2))))->unk_62 =
                        ((S_80174C64_3 *)((u8 *)((unsigned long)base + ((i - 1) << 2))))->unk_62;
                    ((S_80174C64_2 *)((u8 *)((unsigned long)base + (i << 2))))->unk_64 =
                        ((S_80174C64_3 *)((u8 *)((unsigned long)base + ((i - 1) << 2))))->unk_64;
                }
                (*(u16 *)((u8 *)base + 0x66)) = (*(u16 *)((u8 *)arg1 + 2));
                (*(u16 *)((u8 *)base + 0x68)) = (*(u16 *)((u8 *)arg1 + 6));
            }
            }

            temp_s1 = (*(u16 *)((u8 *)arg3 + 0x2A));
            temp_v0 = temp_s1 - 0x400;
            (*(u16 *)((u8 *)arg3 + 0x2A)) = temp_v0;
            if ((temp_v0 << 16) < 0) {
                (*(u16 *)((u8 *)arg3 + 0x2A)) = temp_s1 + 0xC00;
            }
            if (func_800D5F80(arg1, arg3) != 0) {
                arg0->unk_B2 = 0;
                arg0->unk_B1 = 0;
                (*(u16 *)((u8 *)arg3 + 0x2A)) = temp_s1;
                goto state1_done;
            }
            arg0->unk_B1 = 3;
            arg0->unk_B2 = 0;
            (*(u16 *)((u8 *)arg3 + 0x2A)) = temp_s1;
            goto state1_done;
            }

        default:
            goto state1_done;
        }

    case 3:
        switch (arg0->unk_B2) {
        case 0:
state1_minus_angle:
            temp_v1 = (*(u16 *)((u8 *)arg3 + 0x2A));
            temp_v0 = temp_v1 - 0x200;
            (*(u16 *)((u8 *)arg3 + 0x2A)) = temp_v0;
            if ((temp_v0 << 16) < 0) {
                (*(u16 *)((u8 *)arg3 + 0x2A)) = temp_v1 + 0xE00;
            }
state1_advance_sub:
            temp_v0 = arg0->unk_B2;
            arg0->unk_96 = 0;
            arg0->unk_B2 = temp_v0 + 1;
            goto state1_done;

        case 1:
            {
            u16 timer = arg0->unk_96;

            arg0->unk_96 = timer - 1;
            if ((timer << 16) > 0) {
                goto state1_done;
            }
            if (((*(u16 *)((u8 *)arg3 + 0x2A)) & 0x3FF) != 0) {
                arg0->unk_B2 = 0;
                goto state1_minus_angle;
            }
            arg0->unk_B1 = 2;
            arg0->unk_B2 = 0;
            goto state1_case2;
            }

        default:
            goto state1_done;
        }

    default:
        goto state1_done;
    }

set_state3:
    arg0->unk_B3 = 3;
    arg0->unk_B1 = 0;
    goto state3_test;

state1_done:
    state = arg0->unk_B3;
state2_test:
    if (state != 2) {
        goto state3_test;
    }
    (*(u16 *)((u8 *)arg3 + 0x2A)) &= 0xFC00;
    arg0->unk_9B++;
    arg2->unk_14.at00_u16.v |= 0x80;
    arg0->unk_92 = 0;
    arg0->unk_B1 = 0;
    arg0->unk_96 = 0;
    arg0->unk_A2 = 0;
    func_8009D8A4();
    D_800E296C |= 0x800000;
    func_800A56E0(0x80F);

state3_test:
    if (arg0->unk_B3 != 3) {
        goto done;
    }
    state = arg0->unk_B1;
    if ((u32)state >= 5) {
        goto done;
    }
    (void)state3_keep;
    goto *D_80170888[state];

state3_0:
    {
    u16 next_state = arg0->unk_B1;

    arg0->unk_96 = 10;
    arg0->unk_B1 = next_state + 1;
    }

state3_1:
    {
        u16 timer = arg0->unk_96;

        arg0->unk_96 = timer - 1;
        if ((timer << 16) > 0) {
            goto done;
        }
    }
    arg0->unk_B1++;
    goto done;

state3_2:
    arg2->unk_14.at00_u16.v |= 0x80;
    goto state3_set_timer;

state3_3:
    {
        u16 timer = arg0->unk_96;

        arg0->unk_96 = timer - 1;
        if ((timer << 16) > 0) {
            goto done;
        }
    }

state3_set_timer:
    arg0->unk_96 = 20;
    arg0->unk_B1++;
    goto done;

state3_4:
    {
        u16 timer = arg0->unk_96;

        arg0->unk_96 = timer - 1;
        if ((timer << 16) > 0) {
            goto done;
        }
    }
    (*(u16 *)((u8 *)arg3 + 0x2A)) &= 0xFC00;
    arg0->unk_9B++;
    arg2->unk_14.at00_u16.v |= 0x80;
    arg0->unk_92 = 0;
    arg0->unk_B1 = 0;
    arg0->unk_96 = 0;
    arg0->unk_A2 = 0;
    func_8009D8A4();
    D_800E296C |= 0x800000;
    func_800A56E0(0x80F);

done:
    (*(signed short *)((u8 *)arg3 + 0x88)) = func_800BCB04(
        (*(u16 *)((u8 *)arg1 + 2)), (*(u16 *)((u8 *)arg1 + 6)),
        (signed short)((*(u16 *)((u8 *)arg1 + 0xA)) - 0x20));
}
