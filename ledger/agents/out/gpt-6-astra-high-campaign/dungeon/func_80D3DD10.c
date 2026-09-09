#include "common.h"
#include "records/Rec_D_80082E80.h"


extern void func_80047784(void *, u8, s32);
extern s32 rand(void);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_800D5DCC(void *, s16, s32, s32);
extern void func_801708B8(void *, void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_800E23E0[];
extern u8 D_800E2400[];
extern void *D_80170850[];
extern u8 D_80171A80[];


typedef struct S_80173510_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x14];
    u8 unk_B0;
} S_80173510_0;   /* arg0 in func_80173510 */


typedef struct S_80173510_2 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80173510_2;   /* arg3 in func_80173510 */

typedef struct S_80173510_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173510_3;   /* arg1 in func_80173510 */

/* Updates a staged movement animation and returns the entity to its tile center. */
void func_80173510(void *action, void *motion, void *record, void *actor)
{
    static void *const state_labels[] = { &&init, &&wait_start, &&move, &&stop, &&wait_return, &&return_to_tile };
    u8 state;
    u32 next_timer;

    state = ((S_80173510_0 *)action)->unk_9B.n;
    if ((u32)state >= 6) {
        return;
    }
    (void)state_labels;
    goto *D_80170850[state];

init:
    if (((Rec_D_80082E80 *)record)->unk_14.at00_u16.v & 0x8000) {
        u8 *animation_ids;

        ((S_80173510_0 *)action)->unk_9B.n = 5;
        ((S_80173510_0 *)action)->unk_96.u = 0;
        ((Rec_D_80082E80 *)record)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(actor, record, ((S_80173510_2 *)actor)->unk_2A.s, 1);

        animation_ids = D_800E23E0;
        (*(u8 * *)((u8 *)record + (0x2C))) = animation_ids;
        func_80047784(record,
            animation_ids[((D_80083228 + ((S_80173510_2 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        if (((S_80173510_0 *)action)->unk_B0 != 0) {
            return;
        }
        func_801708B8(action, motion, record);
        return;
    }

    ((S_80173510_3 *)motion)->unk_14 = 0;
    ((S_80173510_3 *)motion)->unk_10 = 0;
    ((S_80173510_3 *)motion)->unk_0C = 0;
    ((S_80173510_0 *)action)->unk_96.u = 2;
    ((S_80173510_0 *)action)->unk_98 &= 0xFFF7;
    ((S_80173510_0 *)action)->unk_9B.n++;
    return;

wait_start:
    {
        s16 *direction_x;
        s16 *direction_y;
        u16 timer;

        timer = ((S_80173510_0 *)action)->unk_96.u;
        ((S_80173510_0 *)action)->unk_96.u = timer - 1;
        if ((s16)timer > 0 && !(((Rec_D_80082E80 *)record)->unk_14.at00_u16.v & 0x8000)) {
            return;
        }

        ((S_80173510_0 *)action)->unk_96.u = 0x12;
        direction_x = (s16 *)&D_8006CCD8;
        ((S_80173510_0 *)action)->unk_9B.n++;
        direction_y = (s16 *)&D_8006CCE8;
        ((S_80173510_3 *)motion)->unk_0C =
            -*(s16 *)((u8 *)direction_x +
              ((((S_80173510_2 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
        ((S_80173510_3 *)motion)->unk_10 =
            -*(s16 *)((u8 *)direction_y +
              ((((S_80173510_2 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
        return;
    }

move:
    {
        s16 *direction_x;
        s16 *direction_y;
        s32 eight;
        s8 entity_kind;
        u16 timer;

        if (((S_80173510_0 *)action)->unk_96.s == 0xB) {
            ((S_80173510_3 *)motion)->unk_0C = 0;
            ((S_80173510_3 *)motion)->unk_10 = 0;
        }

        eight = 8;
        if (((S_80173510_0 *)action)->unk_96.s == eight) {
            u8 *animation_ids;

            animation_ids = D_800E2400;
            (*(u8 * *)((u8 *)record + (0x2C))) = animation_ids;
            func_80047784(record,
                animation_ids[((D_80083228 + ((S_80173510_2 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
                1);

            direction_x = (s16 *)&D_8006CCD8;
            direction_y = (s16 *)&D_8006CCE8;
            ((S_80173510_3 *)motion)->unk_0C =
                *(s16 *)((u8 *)direction_x +
                  ((((S_80173510_2 *)actor)->unk_2A.u >> 8) & 0xE)) << 19;
            ((S_80173510_3 *)motion)->unk_10 =
                *(s16 *)((u8 *)direction_y +
                  ((((S_80173510_2 *)actor)->unk_2A.u >> 8) & 0xE)) << 19;
        }

        entity_kind = ((Rec_D_80082E80 *)record)->unk_04.as_s8;
        if (entity_kind == 4 || entity_kind == eight) {
            s32 particles_left;

            func_800A56E0(0x706);
            particles_left = 0x14;
            do {
                s32 particle_random;

                particles_left--;
                particle_random = rand();
                func_800D5DCC((u8 *)action - 0x20,
                    ((S_80173510_2 *)actor)->unk_2A.s, 0x8080FF,
                    (particle_random & 0xFF) | 0x80);
            } while (particles_left >= 0);
        }

        timer = ((S_80173510_0 *)action)->unk_96.u;
        ((S_80173510_0 *)action)->unk_96.u = timer - 1;
        if ((s16)timer <= 0 || (((Rec_D_80082E80 *)record)->unk_14.at00_u16.v & 0x8000)) {
            ((S_80173510_0 *)action)->unk_96.u = 4;
            ((S_80173510_0 *)action)->unk_9B.n++;
        }

        if (((Rec_D_80082E80 *)record)->unk_2C.as_pu8 != D_800E2400) {
            return;
        }
        ((Rec_D_80082E80 *)record)->unk_05.as_u8 = 0;
        return;
    }

stop:
    {
        s16 timer;

        timer = ((S_80173510_0 *)action)->unk_96.u - 1;
        ((S_80173510_0 *)action)->unk_96.u = timer;
        if (timer == 3 || (((Rec_D_80082E80 *)record)->unk_14.at00_u16.v & 0x8000)) {
            u8 *animation_ids;

            ((S_80173510_3 *)motion)->unk_14 = 0;
            ((S_80173510_3 *)motion)->unk_10 = 0;
            ((S_80173510_3 *)motion)->unk_0C = 0;
            func_8009C12C(actor, record, ((S_80173510_2 *)actor)->unk_2A.s, 1);

            animation_ids = D_800E23E0;
            (*(u8 * *)((u8 *)record + (0x2C))) = animation_ids;
            func_80047784(record,
                animation_ids[((D_80083228 + ((S_80173510_2 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
                0);
            ((S_80173510_0 *)action)->unk_92 = -0x20;
            if (((S_80173510_0 *)action)->unk_B0 == 0) {
                func_801708B8(action, motion, record);
            }
        }

        if (((S_80173510_0 *)action)->unk_96.s > 0 &&
            !(((Rec_D_80082E80 *)record)->unk_14.at00_u16.v & 0x8000)) {
            return;
        }
        state = ((S_80173510_0 *)action)->unk_9B.n;
        next_timer = 2;
        goto advance_state;
    }

wait_return:
    {
        u16 timer;

        timer = ((S_80173510_0 *)action)->unk_96.u;
        ((S_80173510_0 *)action)->unk_96.u = timer - 1;
        if ((s16)timer > 0 && !(((Rec_D_80082E80 *)record)->unk_14.at00_u16.v & 0x8000)) {
            return;
        }
        state = ((S_80173510_0 *)action)->unk_9B.n;
        next_timer = 6;
advance_state:
        ((S_80173510_0 *)action)->unk_96.u = next_timer;
        ASM_SCHED_BARRIER(); /* MATCH: Keep the timer store before the shared state increment. */
        ((S_80173510_0 *)action)->unk_9B.n = state + 1;
        return;
    }

return_to_tile:
    {
        s32 distance;
        s32 axis_position;
        s16 timer;

        timer = ((S_80173510_0 *)action)->unk_96.s;
        if (timer != 0) {
            distance = ((Rec_D_80082E80 *)record)->unk_24 << 6;
            axis_position = ((S_80173510_3 *)motion)->unk_02;
            axis_position -= 0x20;
            distance -= axis_position;
            ((S_80173510_3 *)motion)->unk_0C = (distance << 16) / timer;

            axis_position = ((S_80173510_3 *)motion)->unk_06;
            distance = ((Rec_D_80082E80 *)record)->unk_25 << 6;
            axis_position -= 0x20;
            distance -= axis_position;
            ((S_80173510_3 *)motion)->unk_10 =
                (distance << 16) / ((S_80173510_0 *)action)->unk_96.s;
        }

        ((S_80173510_0 *)action)->unk_96.u--;
        if (((S_80173510_0 *)action)->unk_96.s > 0 &&
            !(((Rec_D_80082E80 *)record)->unk_14.at00_u16.v & 0x8000)) {
            return;
        }

        func_800AD594(actor, 0x100);
        ((S_80173510_0 *)action)->unk_8C = D_80171A80;
        D_8008346C = 0;
        func_800A4ACC(actor);
        ((S_80173510_3 *)motion)->unk_0C = 0;
        ((S_80173510_3 *)motion)->unk_10 = 0;
        ((S_80173510_3 *)motion)->unk_02 = ((Rec_D_80082E80 *)record)->unk_24 * 0x40 + 0x20;
        ((S_80173510_3 *)motion)->unk_06 = ((Rec_D_80082E80 *)record)->unk_25 * 0x40 + 0x20;
        ((S_80173510_2 *)actor)->unk_46 &= 0x7FFF;
    }
}
