#include "common.h"
#include "shared/object_flags.h"
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


extern s32 func_800352FC(void);
extern s32 func_800C2AB4(void *);
extern void SD_Call(s32);
extern s32 rand(void);
extern s16 func_800C2AE8(void *);
extern void func_8008F134(void *);
extern void func_80033D08(void *);
extern void func_800478B8(void *);
extern void func_8003DB94(void *, void *, s32);

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
    s32 glide_state;
    s32 home_dx;

    sequence = 0;
    if ((func_800352FC() != 0) && (func_800C2AB4(actor) != 0)) {
        if (!(((Rec_D_80082D58 *)actor)->unk_AC & 1)) {
            SD_Call(0x60B);
            ((Rec_D_80082D58 *)actor)->unk_AC |= 1;
        }
    } else {
        ((Rec_D_80082D58 *)actor)->unk_AC &= ~1;
    }

    state = ((Rec_D_80082D58 *)actor)->unk_68;
    glide_state = 0x31;
    glide_state = 0x31;
    switch (state) {
case 0:
    {
        s32 action_choice;
        s32 random_value;
        register s32 quotient;
        s32 home_distance;
        register s32 vx;

        ((S_800BCE78_1 *)motion)->unk_08.at02.v = func_800C2AE8(motion);
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        action_choice = rand();
        quotient = action_choice / 4;
        action_choice -= quotient * 4;
        switch (action_choice) {
        case 0:
            sequence = (s32 *)D_800E9E7C;
            ((Rec_D_80082D58 *)actor)->unk_68 = 0x10;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = (rand() % 2) + 2;
            break;

        case 1:
        {
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
                if (rand() & 1) {
                    hop_vx = -((S_800BCE78_1 *)motion)->unk_0C.s;
                    ((S_800BCE78_1 *)motion)->unk_0C.s = hop_vx;
                }
            } else {
                hop_vx = -0x10000;
                if (home_dx < 0) {
                    hop_vx = 0x10000;
                }
                ((S_800BCE78_1 *)motion)->unk_0C.s = hop_vx;
            }
            if (((S_800BCE78_1 *)motion)->unk_0C.s > 0) {
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 1;
            } else {
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xFFFE;
            }
            break;
        }

        case 2:
        {
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
            break;
        }

        case 4:
            ((Rec_D_80082D58 *)actor)->unk_68 = 0x40;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = 0x14;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        }
        break;
    }

case 0x10:
    {
        register u16 timer;

        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
            if ((s16)timer <= 0) {
                ((Rec_D_80082D58 *)actor)->unk_68 = 0;
            }
            sequence = (s32 *)D_800E9E7C;
        }
        break;
    }

case 0x20:
    {
        s32 x;
        s32 vy;
        s32 vx;
        s32 y;
        register u16 timer;

        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C.s;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        ((S_800BCE78_1 *)motion)->unk_00 = x + vx;
        ((S_800BCE78_1 *)motion)->unk_08.at00.v = y + vy;
        ((S_800BCE78_1 *)motion)->unk_14 += 0x10000;
        home_dx = func_800C2AE8(motion);
        state = home_dx < ((S_800BCE78_1 *)motion)->unk_08.at02.v;
        if (state) {
            ((S_800BCE78_1 *)motion)->unk_08.at02.v = home_dx;
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
        break;
    }

case 0x30:
    {
        s32 x;
        s32 vx;
        s32 vy;
        s32 y;

        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C.s;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        ((S_800BCE78_1 *)motion)->unk_00 = x + vx;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        ((S_800BCE78_1 *)motion)->unk_08.at00.v = y + vy;
        ((S_800BCE78_1 *)motion)->unk_14 -= 0x4000;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            sequence = D_800E9E34;
            ((Rec_D_80082D58 *)actor)->unk_68 = glide_state;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = 3;
        }
        break;
    }

case 0x31:
    {
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
        break;
    }

case 0x32:
    {
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
                height = ((S_800BCE78_1 *)motion)->unk_08.at00.v + 0x100000;
                ((S_800BCE78_1 *)motion)->unk_14 =
                    (floor_fixed - height) /
                    (s16)((Rec_D_80082D58 *)actor)->unk_6C.as_u16;
                sequence = D_800E9E14;
                ((Rec_D_80082D58 *)actor)->unk_68 = 0x33;
            }
        }
        break;
    }

case 0x33:
    {
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
            ((Rec_D_80082D58 *)actor)->unk_68 = 0x34;
        }
        break;
    }

case 0x34:
    {
        register s16 floor;

        ((S_800BCE78_1 *)motion)->unk_00 += ((S_800BCE78_1 *)motion)->unk_0C.s;
        floor = func_800C2AE8(motion);
        ((S_800BCE78_1 *)motion)->unk_08.at02.v =
            (u16)((S_800BCE78_1 *)motion)->unk_08.at02.v + ((floor - ((S_800BCE78_1 *)motion)->unk_08.at02.v) >> 1);
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            sequence = (s32 *)D_800E9E7C;
            ((Rec_D_80082D58 *)actor)->unk_68 = 0;
        }
        break;
    }

case 0x40:
    {
        register u16 timer;

        timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
        ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
        if ((s16)timer <= 0) {
            ((Rec_D_80082D58 *)actor)->unk_68 = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        break;
    }

case 0xFF:
    func_8008F134(actor);
    func_80033D08(actor);
    (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
    objectFlagBlock.flags |= 0x8000;

    }

    func_800478B8(sprite);
    if (sequence != 0) {
        func_8003DB94(sprite, sequence, 0);
    }
}
