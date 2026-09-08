#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8002466C_0 {
    void * unk_00;
    u8 pad_04[0x18];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_1C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_20;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_24;   /* overlapping accesses */
    u8 pad_28[0x18];
    s16 unk_40;
    s16 unk_42;
    s16 unk_44;
    s16 unk_46;
    union { u16 s; s16 u; } unk_48;   /* accessed as both */
    u16 unk_4A;
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
} S_8002466C_0;   /* arg0 in func_8002466C */

typedef struct S_8002466C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8002466C_1;   /* owner in func_8002466C */

typedef struct S_8002466C_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8002466C_2;   /* ctx1 in func_8002466C */

typedef struct S_8002466C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8002466C_3;   /* coords1 in func_8002466C */

typedef struct S_8002466C_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8002466C_4;   /* ctx2 in func_8002466C */

typedef struct S_8002466C_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8002466C_5;   /* coords2 in func_8002466C */

typedef struct S_8002466C_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8002466C_6;   /* obj in func_8002466C */

typedef struct S_8002466C_7 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002466C_7;   /* draw in func_8002466C */

typedef struct S_8002466C_8 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8002466C_8;   /* disp in func_8002466C */

typedef struct S_8002466C_9 {
    u8 pad_00[0x4C];
    s16 unk_4C;
} S_8002466C_9;   /* ent in func_8002466C */

typedef struct S_8002466C_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8002466C_10;   /* ((S_8002466C_6 *)obj)->unk_08 in func_8002466C */



extern s16 GetTPage(s32, s32, s32, s32);
extern s16 GetClut(s32, s32);
extern s32 func_8003DE58(void *, void *, s16 *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern s32 rand(void);

extern u8 D_80024ACC[];
extern u8 D_80045340[];
extern s32 D_800814A0;
extern u8 D_80082E80[];
extern u8 D_80083498[];
extern u8 D_80083780[];
extern u8 D_800DEA68[];

/* Update the animated effect, track its target, and spawn scattered particles. */
void func_8002466C(void *effect)
{
    s16 target_pos[3];
    s16 state;
    s32 last_particle;
    s32 particle_index;
    s32 display_link;
    u16 frames_left;
    void *owner;
    void *approach_target;
    void *follow_target;
    void *approach_origin;
    void *follow_origin;
    void *particle;
    void *particle_state;
    void *sprite;
    void *particle_data;
    void *display;

    owner = ((S_8002466C_0 *)effect)->unk_00;
    ((S_8002466C_0 *)effect)->unk_48.s = ((S_8002466C_0 *)effect)->unk_48.s + 1;
    ((S_8002466C_1 *)owner)->unk_52 |= 0x8000;
    last_particle = -1;
    state = ((S_8002466C_0 *)effect)->unk_4C.s;
    switch (state) {
        case 0:
            ((S_8002466C_0 *)effect)->unk_50 = GetTPage(0, 1, 0x2C0, 0x100);
            ((S_8002466C_0 *)effect)->unk_52 = GetClut(0xC0, 0x1F7);
            ((S_8002466C_0 *)effect)->unk_46 = 0x1F;
            ((S_8002466C_0 *)effect)->unk_44 = 0x1F;
            ((S_8002466C_0 *)effect)->unk_48.s = 0;
            ((S_8002466C_0 *)effect)->unk_4E = 0x30;
            ((S_8002466C_0 *)effect)->unk_4C.s = ((S_8002466C_0 *)effect)->unk_4C.u + 1;
        case 1:
            last_particle = 0xE;
            approach_target = D_80082E80;
            if (func_8003DE58(((S_8002466C_2 *)approach_target)->unk_08, approach_target, target_pos, 0) != 0) {
                approach_origin = D_80083780;
                ((S_8002466C_0 *)effect)->unk_1C.at00.v +=
                    ((target_pos[0] + ((S_8002466C_3 *)approach_origin)->unk_02) -
                     ((S_8002466C_0 *)effect)->unk_1C.at02.v) << 14;
                ((S_8002466C_0 *)effect)->unk_20.at00.v +=
                    ((target_pos[1] + ((S_8002466C_3 *)approach_origin)->unk_06) -
                     ((S_8002466C_0 *)effect)->unk_20.at02.v) << 14;
                ((S_8002466C_0 *)effect)->unk_24.at00.v +=
                    ((target_pos[2] + ((S_8002466C_3 *)approach_origin)->unk_0A) -
                     ((S_8002466C_0 *)effect)->unk_24.at02.v) << 14;
                ((S_8002466C_0 *)effect)->unk_24.at00.v -=
                    func_800644B8((((S_8002466C_0 *)effect)->unk_48.u << 11) / 10) << 9;
            }
            if (((S_8002466C_0 *)effect)->unk_48.u >= 0xA) {
                ((S_8002466C_0 *)effect)->unk_4A = 0x10;
                ((S_8002466C_0 *)effect)->unk_4C.s = ((S_8002466C_0 *)effect)->unk_4C.u + 1;
            }
            break;

        case 2:
            last_particle = 9;
            if (((S_8002466C_0 *)effect)->unk_48.u >= 0xB) {
                last_particle = 4;
            }
            ((S_8002466C_0 *)effect)->unk_4E += 2;
            follow_target = D_80082E80;
            if (func_8003DE58(((S_8002466C_4 *)follow_target)->unk_08, follow_target, target_pos, 0) != 0) {
                follow_origin = D_80083780;
                ((S_8002466C_0 *)effect)->unk_1C.at00.v +=
                    ((target_pos[0] + ((S_8002466C_5 *)follow_origin)->unk_02) -
                     ((S_8002466C_0 *)effect)->unk_1C.at02.v) << 15;
                ((S_8002466C_0 *)effect)->unk_20.at00.v +=
                    ((target_pos[1] + ((S_8002466C_5 *)follow_origin)->unk_06) -
                     ((S_8002466C_0 *)effect)->unk_20.at02.v) << 15;
                ((S_8002466C_0 *)effect)->unk_24.at00.v +=
                    ((target_pos[2] + ((S_8002466C_5 *)follow_origin)->unk_0A) -
                     ((S_8002466C_0 *)effect)->unk_24.at02.v) << 15;
            }
            if (((S_8002466C_0 *)effect)->unk_48.u >= 0xD) {
                ((S_8002466C_0 *)effect)->unk_48.s = 8;
            }
            frames_left = ((S_8002466C_0 *)effect)->unk_4A - 1;
            ((S_8002466C_0 *)effect)->unk_4A = frames_left;
            if (((s32)(frames_left << 16) <= 0) &&
                (((S_8002466C_0 *)effect)->unk_48.u == 0xC)) {
                ((S_8002466C_0 *)effect)->unk_4C.s = ((S_8002466C_0 *)effect)->unk_4C.u + 1;
            }
            break;

        case 3:
            last_particle = 5;
            if (((S_8002466C_0 *)effect)->unk_48.u == 0xF) {
                (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
                D_800814A0 |= 0x8000;
            }
            break;
    }
    particle_index = last_particle;

    ((S_8002466C_0 *)effect)->unk_40 = ((((S_8002466C_0 *)effect)->unk_48.s & 3) << 5) + 0x80;
    ((S_8002466C_0 *)effect)->unk_42 =
        (((s32)(((S_8002466C_0 *)effect)->unk_48.s << 16) >> 18) << 5) + 0x80;
    if (particle_index >= 0) {
        particle_data = D_80024ACC;
        display = D_800DEA68;
        do {
            particle = func_8003FD64(0x312, D_80083498);
            if (particle != NULL) {
                ((S_8002466C_6 *)particle)->unk_10 = particle_data;
                func_8004491C(particle, D_80045340);
                sprite = ((S_8002466C_6 *)particle)->unk_0C;
                ((S_8002466C_10 *)(((S_8002466C_6 *)particle)->unk_08))->unk_00 =
                    ((S_8002466C_0 *)effect)->unk_1C.at00.v +
                    (((rand() & 0x3FF) - 0x1FF) << 12);
                ((S_8002466C_10 *)(((S_8002466C_6 *)particle)->unk_08))->unk_04 =
                    ((S_8002466C_0 *)effect)->unk_20.at00.v +
                    (((rand() & 0x3FF) - 0x1FF) << 12);
                ((S_8002466C_10 *)(((S_8002466C_6 *)particle)->unk_08))->unk_08 =
                    ((S_8002466C_0 *)effect)->unk_24.at00.v +
                    (((rand() & 0x3FF) - 0x1FF) << 11);
                ((S_8002466C_7 *)sprite)->unk_1E = 0x1000;
                ((S_8002466C_7 *)sprite)->unk_1C = 0x1000;
                ((S_8002466C_7 *)sprite)->unk_10 = 0x60;
                ((S_8002466C_7 *)sprite)->unk_00 = display;
                ((S_8002466C_7 *)sprite)->unk_14 |= 0xC;
                display_link = ((S_8002466C_8 *)display)->unk_04;
                ((S_8002466C_7 *)sprite)->unk_04 = 0;
                ((S_8002466C_7 *)sprite)->unk_05 = 0;
                ((S_8002466C_7 *)sprite)->unk_0C = 0x808080;
                ((S_8002466C_7 *)sprite)->unk_08 = display_link;
                ((S_8002466C_6 *)particle)->unk_20 = ((S_8002466C_0 *)effect)->unk_00;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                particle_state = (u8 *)particle + 0x20;
                ASM_KEEP(particle_state);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                ((S_8002466C_9 *)particle_state)->unk_4C = 0;
            }
            particle_index -= 1;
        } while (particle_index >= 0);
    }
}

/* MECHANISM: (1) held-base locals approach_target/follow_target for D_80082E80 keep retail's
   lui/addiu/lw 8(a1) triple instead of gcc folding D+8 into one %lo; (2) the
   /10 divide is written inline off the s16 field so gcc emits lh + sll 11, not
   lhu + sll 16 / sra 5 (an s16 temp costs an extra word); (3) the sprite-tail
   order puts the two sb 0 stores after the display link load; (4) particle+0x20:
   gcc always folds (particle+0x20)+0x4c into one 0x6c displacement, so the
   materialisation is forced with ASM_KEEP(particle_state) and the preceding
   ASM_SCHED_BARRIER keeps the addiu below the sw, leaving retail's load-delay
   nop (both devices measured: dropping the barrier costs a word, 4 -> 11).
   RESIDUE: 276/280 words byte-identical; the only 4 diffs are this function's
   OWN local j words, all solving true link base 0x8002466C vs the synthetic
   0x819B2E6C - a rowbase base shift, not a C or compiler gap. */

