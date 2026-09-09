#include "common.h"
#include "records/Rec_D_80082D58.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_800BCE78_1 {
    s32 unk_00;
    u8 pad_04[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    union { s32 s; volatile s32 u; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    s32 unk_14;
} S_800BCE78_1;   /* arg1 in func_800BCE78 */




extern s32 func_800352FC(void *, void *, void *, s32);
extern s32 func_800C2AB4(void *);
extern void SD_Call(s32);
extern s32 rand(void);
extern s16 func_800C2AE8(void *);
extern void func_8008F134(void *, s32, s32);
extern void func_80033D08(void *);
extern void func_800478B8(void *);
extern void func_8003DB94(void *, void *, s32);

extern s32 D_800814A0;
extern s32 D_800E9E14[];
extern s32 D_800E9E34[];
extern s32 D_800E9E54[];
extern u8 D_800E9E7C[];
extern s32 D_800E9ECC[];

/* Updates randomized movement, animation, and landing states for a town actor. */
void func_800BCE78(void *actor, void *motion, void *sprite, s32 update_mode)
{
    register s32 *sequence;
    register s32 state;
    register s32 wait_state;
    register s32 glide_state ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 settle_state ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    sequence = 0;
    if ((func_800352FC(actor, motion, sprite, update_mode) != 0) && (func_800C2AB4(actor) != 0)) {
        if (!(((Rec_D_80082D58 *)actor)->unk_AC & 1)) {
            SD_Call(0x60B);
            ((Rec_D_80082D58 *)actor)->unk_AC |= 1;
        }
    } else {
        ((Rec_D_80082D58 *)actor)->unk_AC &= ~1;
    }

    state = ((Rec_D_80082D58 *)actor)->unk_68;
    glide_state = 0x31;
    if (state == glide_state) {
        goto case_31;
    }
    if (state >= 0x32) {
        goto dispatch_high;
    }
    wait_state = 0x10;
    if (state == wait_state) {
        goto case_10;
    }
    if (state < 0x11) {
        if (state == 0) {
            goto case_0;
        }
        goto tail;
    }
    if (state == 0x20) {
        goto case_20;
    }
    if (state == 0x30) {
        goto case_30;
    }
    goto tail;

dispatch_high:
    settle_state = 0x34;
    if (state == settle_state) {
        goto case_34;
    }
    if (state < 0x35) {
        if (state == 0x32) {
            goto case_32;
        }
        if (state == 0x33) {
            goto case_33;
        }
        goto tail;
    }
    if (state == 0x40) {
        goto case_40;
    }
    if (state == 0xFF) {
        goto case_FF;
    }
    goto tail;

case_0: {
        s32 action_choice;
        s32 random_value;
        register s32 quotient;
        register s32 home_dx;
        s32 home_distance;
        register s32 vx;

        ((S_800BCE78_1 *)motion)->unk_08.at02.v = func_800C2AE8(motion);
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            goto tail;
        }
        random_value = rand();
        action_choice = random_value;
        ASM_KEEP(random_value);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        quotient = random_value >> 2;
        if (action_choice < 0) {
            quotient = (action_choice + 3) >> 2;
        }
        action_choice = action_choice - (quotient * 4);
        if (action_choice == 1) {
            goto random_case_1;
        }
        if (action_choice >= 2) {
            goto random_high;
        }
        if (action_choice == 0) {
            goto random_case_0;
        }
        goto random_done;

random_high:
        if (action_choice == 2) {
            goto random_case_2;
        }
        if (action_choice == 4) {
            goto random_case_4;
        }
        goto random_done;

random_case_0:
            sequence = (s32 *)D_800E9E7C;
            ((Rec_D_80082D58 *)actor)->unk_68 = wait_state;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = (rand() % 2) + 2;
            goto random_done;

random_case_1: {
            s32 limit;
            s32 hop_vx;

            ((Rec_D_80082D58 *)actor)->unk_68 = 0x20;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = (rand() & 1) + 2;
            limit = 0x1FFFFF;
            ((S_800BCE78_1 *)motion)->unk_14 = -0x30000;
            home_dx = ((S_800BCE78_1 *)motion)->unk_00;
            home_dx -= ((Rec_D_80082D58 *)actor)->unk_A0;
            home_distance = __builtin_abs(home_dx);
            limit = limit < home_distance;
            if (!limit) {
                ((S_800BCE78_1 *)motion)->unk_0C.s = 0x10000;
                if (!(rand() & 1)) {
                    goto case_1_after_store;
                }
                hop_vx = -((S_800BCE78_1 *)motion)->unk_0C.s;
                goto case_1_store;
            } else {
                hop_vx = -0x10000;
                if (home_dx < 0) {
                    hop_vx = 0x10000;
                }
            }
case_1_store:
            ((S_800BCE78_1 *)motion)->unk_0C.s = hop_vx;
case_1_after_store:
            if (((S_800BCE78_1 *)motion)->unk_0C.s > 0) {
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 1;
            } else {
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xFFFE;
            }
            goto random_done;
        }

random_case_2: {
            s32 limit;
            s32 random_speed;
            s32 *launch_sequence;

            launch_sequence = D_800E9ECC;
            sequence = launch_sequence;
            ((Rec_D_80082D58 *)actor)->unk_68 = 0x30;
            random_speed = rand();
            limit = 0xFFFFF;
            vx = (random_speed & 0x1FF) << 8;
            ((S_800BCE78_1 *)motion)->unk_0C.s = vx;
            home_dx = ((S_800BCE78_1 *)motion)->unk_00;
            home_dx -= ((Rec_D_80082D58 *)actor)->unk_A0;
            home_distance = __builtin_abs(home_dx);
            limit = limit < home_distance;
            if (!limit) {
                if (rand() & 1) {
                    ((S_800BCE78_1 *)motion)->unk_0C.u = ((S_800BCE78_1 *)motion)->unk_0C.s;
                } else {
                    ((S_800BCE78_1 *)motion)->unk_0C.s = -((S_800BCE78_1 *)motion)->unk_0C.s;
                }
            } else if (home_dx > 0) {
                ((S_800BCE78_1 *)motion)->unk_0C.s = -vx;
            }
            if (((S_800BCE78_1 *)motion)->unk_0C.s > 0) {
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 1;
            } else {
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xFFFE;
            }
            ((S_800BCE78_1 *)motion)->unk_14 = -0x20000;
            goto random_done;
        }

random_case_4:
            ((Rec_D_80082D58 *)actor)->unk_68 = 0x40;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = 0x14;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
random_done:
        goto tail;
    }

case_10: {
        register u16 timer;

        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
            if ((s16)timer <= 0) {
                ((Rec_D_80082D58 *)actor)->unk_68 = 0;
            }
            sequence = (s32 *)D_800E9E7C;
        }
        goto tail;
    }

case_20: {
        void *floor_motion;
        register s32 x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 vx ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        s32 y;
        register s32 vy ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        register s32 floor ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 below_floor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u16 timer;

        floor_motion = motion;
        ASM_KEEP(floor_motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C.s;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        x += vx;
        y += vy;
        ((S_800BCE78_1 *)motion)->unk_00 = x;
        {
            register s32 new_vy ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            new_vy = vy;
            ASM_KEEP(new_vy);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            ((S_800BCE78_1 *)motion)->unk_08.at00.v = y;
            y = 0x10000;
            new_vy += y;
            ((S_800BCE78_1 *)motion)->unk_14 = new_vy;
        }
        floor = func_800C2AE8(floor_motion);
        below_floor = floor < ((S_800BCE78_1 *)motion)->unk_08.at02.v;
        if (below_floor) {
            ((S_800BCE78_1 *)motion)->unk_08.at02.v = floor;
            timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
            if ((s16)timer <= 0) {
                ((S_800BCE78_1 *)motion)->unk_14 = 0;
                ((S_800BCE78_1 *)motion)->unk_0C.s = 0;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
                ((Rec_D_80082D58 *)actor)->unk_68 = 0;
            } else {
                ((S_800BCE78_1 *)motion)->unk_14 = -0x30000;
            }
        }
        goto tail;
    }

case_30: {
        s32 vy;
        s32 new_vy;

        {
            register s32 x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 vx;

            x = ((S_800BCE78_1 *)motion)->unk_00;
            vx = ((S_800BCE78_1 *)motion)->unk_0C.s;
            vy = ((S_800BCE78_1 *)motion)->unk_14;
            x += vx;
            new_vy = vy;
            ASM_KEEP(new_vy);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            ((S_800BCE78_1 *)motion)->unk_00 = x;
        }
        {
            register s32 y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
            new_vy -= 0x4000;
            ((S_800BCE78_1 *)motion)->unk_14 = new_vy;
            y += vy;
            ((S_800BCE78_1 *)motion)->unk_08.at00.v = y;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            sequence = D_800E9E34;
            ((Rec_D_80082D58 *)actor)->unk_68 = glide_state;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = 3;
        }
        goto tail;
    }

case_31: {
        register s32 x;
        register s32 vx;
        register s32 y;
        register s32 vy;
        register u16 timer;

        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C.s;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        ((S_800BCE78_1 *)motion)->unk_00 = x + vx;
        ((S_800BCE78_1 *)motion)->unk_08.at00.v = y + vy;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
            if ((s16)timer <= 0) {
                sequence = D_800E9E34;
                ((S_800BCE78_1 *)motion)->unk_14 = -0x10000;
                ((S_800BCE78_1 *)motion)->unk_0C.s >>= 1;
                ((Rec_D_80082D58 *)actor)->unk_68 = 0x32;
                ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = (rand() & 3) + 3;
            }
        }
        goto tail;
    }

case_32: {
        register s32 x;
        register s32 vx;
        register s32 y;
        register s32 vy;
        register s32 new_vx;
        s32 height;
        s32 floor_fixed;
        register s16 floor;
        register u16 timer;

        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C.s;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        ((S_800BCE78_1 *)motion)->unk_00 = x + vx;
        ((S_800BCE78_1 *)motion)->unk_08.at00.v = y + vy;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
            if ((s16)timer <= 0) {
                ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = 8;
                new_vx = -((S_800BCE78_1 *)motion)->unk_0C.s;
                ((S_800BCE78_1 *)motion)->unk_0C.s = new_vx;
                if (new_vx > 0) {
                    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 1;
                } else {
                    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xFFFE;
                }
                floor = func_800C2AE8(motion);
                floor_fixed = (s32)floor << 16;
                height = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
                ASM_KEEP(height);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                height = height + 0x100000;
                ((S_800BCE78_1 *)motion)->unk_14 =
                    (floor_fixed - height) /
                    (s16)((Rec_D_80082D58 *)actor)->unk_6C.as_u16;
                sequence = D_800E9E14;
                ((Rec_D_80082D58 *)actor)->unk_68 = 0x33;
            }
        }
        goto tail;
    }

case_33: {
        register s32 x;
        register s32 vx;
        register s32 y;
        register s32 vy;
        register u16 timer;

        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C.s;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        ((S_800BCE78_1 *)motion)->unk_00 = x + vx;
        ((S_800BCE78_1 *)motion)->unk_08.at00.v = y + vy;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            sequence = D_800E9E14;
        }
        timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
        ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
        if ((s16)timer <= 0) {
            sequence = D_800E9E54;
            ((S_800BCE78_1 *)motion)->unk_14 = 0;
            ((S_800BCE78_1 *)motion)->unk_0C.s = 0;
            ((Rec_D_80082D58 *)actor)->unk_68 = settle_state;
        }
        goto tail;
    }

case_34: {
        register s16 floor;

        ((S_800BCE78_1 *)motion)->unk_00 += ((S_800BCE78_1 *)motion)->unk_0C.s;
        floor = func_800C2AE8(motion);
        ((S_800BCE78_1 *)motion)->unk_08.at02.v =
            (u16)((S_800BCE78_1 *)motion)->unk_08.at02.v + ((floor - ((S_800BCE78_1 *)motion)->unk_08.at02.v) >> 1);
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            sequence = (s32 *)D_800E9E7C;
            ((Rec_D_80082D58 *)actor)->unk_68 = 0;
        }
        goto tail;
    }

case_40: {
        register u16 timer;

        timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
        ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
        if ((s16)timer <= 0) {
            ((Rec_D_80082D58 *)actor)->unk_68 = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        goto tail;
    }

case_FF:
        func_8008F134(actor, glide_state, settle_state);
        func_80033D08(actor);
        (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto tail;

tail:
    func_800478B8(sprite);
    if (sequence != 0) {
        func_8003DB94(sprite, sequence, 0);
    }
}
