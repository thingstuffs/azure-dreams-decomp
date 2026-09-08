#include "common.h"

typedef struct S_80173B48_0 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    u8 pad_49[0x17];
    void * unk_60;
    u8 pad_64[0x6];
    u16 unk_6A;
    u8 pad_6C[0x1];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x10];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x2];
    s16 unk_88;
} S_80173B48_0;   /* arg3 in func_80173B48 */

typedef struct S_80173B48_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
    s16 unk_AC;
} S_80173B48_1;   /* arg0 in func_80173B48 */

typedef struct S_80173B48_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173B48_2;   /* arg2 in func_80173B48 */

typedef struct S_80173B48_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80173B48_3_pre;   /* the 0x14 bytes before ((S_80173B48_0 *)arg3)->unk_60 in func_80173B48, addressed as ((S_80173B48_0 *)arg3)->unk_60[-1] */



extern void func_8009C12C(void *, void *, s16, s16);
extern void func_8009C93C(void *, void *, s16, s16, void *);
extern s16 func_8009FD40(void *, void *);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern s32 func_800A2B5C(void *);
extern void func_800C78A0(void *, s32, s32, s16, s32, s32);
extern void func_800C7930(void *, s32, s32, s32);

extern u16 D_80083462;
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

/* Resolves action targets, updates the actor position, and sets the follow-up state. */
void func_80173B48(void *action_input, s32 x_offset_input, void *position_input, void *actor_input)
{
    void *action = action_input;
    register s32 x_offset ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *position ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    void *actor = actor_input;
    register s32 remaining_steps ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 next_y ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 saved_x;
    u32 saved_y;
    s32 action_state;
    u8 state_param;
    s32 next_x;

    ASM_KEEP(action);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    x_offset = x_offset_input;
    ((S_80173B48_0 *)actor)->unk_71 &= 0x7F;
    position = position_input;
    if (D_80083462 & 0x2000) {
        goto done;
    }

    if ((func_800A2B5C(actor) << 16) != 0) {
        goto done;
    }

    func_800C7930((u8 *)actor - 0x20, x_offset, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) != 0) {
        goto done;
    }

    ((S_80173B48_1 *)action)->unk_8C = 0;
    ((S_80173B48_1 *)action)->unk_9A = 0x11;
    ((S_80173B48_1 *)action)->unk_9B = 0;
    ((S_80173B48_0 *)actor)->unk_6D--;

    if (((S_80173B48_0 *)actor)->unk_48 == 15) {
        ((S_80173B48_0 *)actor)->unk_60 =
            func_800A05A4(actor, ((S_80173B48_2 *)position)->unk_24,
                          ((S_80173B48_2 *)position)->unk_25, ((S_80173B48_0 *)actor)->unk_2A, 10);
        ((S_80173B48_1 *)action)->unk_AC = 0;
        if (((S_80173B48_0 *)actor)->unk_60 == 0) {
            goto initial_null;
        }

        {
            s16 travel_steps = func_8009FD40(
                ((S_80173B48_3_pre *)(((S_80173B48_0 *)actor)->unk_60))[-1].unk_00, position);
            ((S_80173B48_1 *)action)->unk_AA = travel_steps;
            func_8009C93C(actor, position, ((S_80173B48_0 *)actor)->unk_2A, travel_steps,
                          ((S_80173B48_0 *)actor)->unk_60);
        }

        if (((S_80173B48_0 *)actor)->unk_14 & 0x04000000) {
            remaining_steps = 10;
            saved_x = ((S_80173B48_2 *)position)->unk_24;
            saved_y = ((S_80173B48_2 *)position)->unk_25;

loop:
            next_x = ((S_80173B48_0 *)actor)->unk_72;
            next_y = ((S_80173B48_0 *)actor)->unk_73;
            func_8009C12C(actor, position, ((S_80173B48_0 *)actor)->unk_2A,
                          ((S_80173B48_1 *)action)->unk_AA);
            remaining_steps -= ((S_80173B48_1 *)action)->unk_AA;
            if (remaining_steps == 0) {
                goto restore_coords;
            }

            ((S_80173B48_2 *)position)->unk_24 = next_x;
            ((S_80173B48_2 *)position)->unk_25 = next_y;
            ((S_80173B48_0 *)actor)->unk_60 =
                func_800A05A4(actor, ((S_80173B48_2 *)position)->unk_24,
                              ((S_80173B48_2 *)position)->unk_25,
                              ((S_80173B48_0 *)actor)->unk_2A, (s16)remaining_steps);
            if (((S_80173B48_0 *)actor)->unk_60 == 0) {
                goto loop_null;
            }

            ((S_80173B48_2 *)position)->unk_24 = saved_x;
            ((S_80173B48_2 *)position)->unk_25 = saved_y;
            {
                s16 travel_steps = func_8009FD40(
                    ((S_80173B48_3_pre *)(((S_80173B48_0 *)actor)->unk_60))[-1].unk_00, position);
                ((S_80173B48_1 *)action)->unk_AA = travel_steps;
                func_8009C93C(actor, position, ((S_80173B48_0 *)actor)->unk_2A, travel_steps,
                              ((S_80173B48_0 *)actor)->unk_60);
            }
            if (((S_80173B48_0 *)actor)->unk_14 & 0x04000000) {
                goto loop;
            }
            goto restore_coords;
        }
        goto render;

loop_null:
        func_8009C93C(actor, position, ((S_80173B48_0 *)actor)->unk_2A, 1, 0);
        ((S_80173B48_1 *)action)->unk_AA = 1;

restore_coords:
        ((S_80173B48_2 *)position)->unk_24 = saved_x;
        ((S_80173B48_2 *)position)->unk_25 = saved_y;
        goto render;

initial_null:
        func_8009C93C(actor, position, ((S_80173B48_0 *)actor)->unk_2A, 1, 0);
        ((S_80173B48_1 *)action)->unk_AA = 1;

render:
        {
            u32 direction_offset = (((S_80173B48_0 *)actor)->unk_6A >> 8) & 0xE;
            func_800C78A0(
                (u8 *)actor - 0x20,
                (((S_80173B48_2 *)position)->unk_24 << 6) +
                    ((s16)*(u16 *)((u8 *)D_800DCEAC + direction_offset) >> 1) + 0x20,
                (((S_80173B48_2 *)position)->unk_25 << 6) +
                    ((s16)*(u16 *)((u8 *)D_800DCEBC + direction_offset) >> 1) + 0x20,
                ((S_80173B48_0 *)actor)->unk_88, 8, 0x300);
        }
        goto final_state;
    }

    func_8009C93C(actor, position, ((S_80173B48_0 *)actor)->unk_2A, 1, 0);
    ((S_80173B48_1 *)action)->unk_AA = 1;

final_state:
    action_state = ((S_80173B48_0 *)actor)->unk_48;
    if (action_state == 14) {
        goto state_14;
    }
    if (action_state < 15) {
        if (action_state == 13) {
            goto state_13;
        }
        goto done;
    }
    if (action_state == 15) {
        goto state_15;
    }
    goto done;

state_13:
    ((S_80173B48_0 *)actor)->unk_84 = 0x78;
    state_param = 8;
    goto store_state;

state_14:
    ((S_80173B48_0 *)actor)->unk_84 = 0x70;
    state_param = 2;
    goto store_state;

state_15:
    ((S_80173B48_0 *)actor)->unk_84 = 0x74;
    state_param = 1;

store_state:
    ((S_80173B48_0 *)actor)->unk_85 = state_param;

done:
    return;
}
