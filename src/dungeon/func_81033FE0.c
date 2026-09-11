#include "common.h"


typedef struct {
    s16 x;
    s16 y;
} Pair16;

typedef s32 M2C_UNK;

extern void func_8003DB94(void *, void *, s32);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void func_8009A350(s32, s32, s32, u16 *);
extern void func_800A2B04(void *, s32, s32);
extern s16 func_800A45D8(u16, u16, s16);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(u16, u16, s16);
extern s32 func_80174A00(void *, u16, u16, s16);
extern void func_80175494(void *, void *, void *);

extern s32 D_80045340;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_800DE870;
extern void *D_80170890[];
extern u8 D_80170B48[];
extern u8 D_801714B8;
extern u8 D_8017609C[];
extern u8 D_801760A4[];
extern Pair16 D_8017610C[];


typedef struct S_801757E0_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801757E0_0_pre;   /* the 0x14 bytes before arg0 in func_801757E0, addressed as arg0[-1] */

typedef struct S_801757E0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    union { u8 u; s8 s; } unk_AC;   /* accessed as both */
    union { u8 u; s8 s; } unk_AD;   /* accessed as both */
} S_801757E0_0;   /* arg0 in func_801757E0 */

typedef struct S_801757E0_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { void * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_801757E0_1;   /* arg2 in func_801757E0 */

typedef struct S_801757E0_2 {
    u8 pad_00[0x2];
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801757E0_2;   /* arg1 in func_801757E0 */

typedef struct S_801757E0_3 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    u8 pad_20[0x30];
    union { s32 n; volatile s32 v; } unk_50;   /* accessed as both */
    union { s32 n; volatile s32 v; } unk_54;   /* accessed as both */
    s32 unk_58;
    u8 pad_5C[0x8];
    s32 unk_64;
} S_801757E0_3;   /* work in func_801757E0 */

typedef struct S_801757E0_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801757E0_4;   /* object in func_801757E0 */

typedef struct S_801757E0_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801757E0_5;   /* display in func_801757E0 */

typedef struct S_801757E0_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801757E0_6;   /* owner in func_801757E0 */

typedef struct S_801757E0_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801757E0_7;   /* transform in func_801757E0 */

typedef struct S_801757E0_8 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
} S_801757E0_8;   /* arg3 in func_801757E0 */

/* Update the action sequence, spawning particles and checking the tile ahead. */
void func_801757E0(void *actor, void *motion, void *animation, void *entity)
{
    u16 offsets[3];
    u16 collision_flags;
    s16 timer;
    s16 floor_height;
    s32 particle_index;
    s32 x;
    s32 y;
    s32 target_x;
    s32 target_y;
    void *particle;
    void *particle_work;
    void *sprite;
    void *particle_transform;
    void *owner;
    Pair16 *directions;

#define motion motion

#ifdef __mips__
    {
        static void *volatile dispatch_labels[] = {
            &&state_0, &&state_1, &&state_2, &&state_3,
            &&state_4, &&state_5, &&state_6, &&state_7,
            &&state_8, &&state_9, &&end, &&end, &&end,
            &&end, &&end, &&end, &&state_16,
        };
        u32 state = ((S_801757E0_0 *)actor)->unk_9B;

        if (state >= 17) {
            goto end;
        }
        goto *D_80170890[state];
    }
state_0:
#else
    switch (((S_801757E0_0 *)actor)->unk_9B) {
    case 0:
#endif
    if (((S_801757E0_1 *)animation)->unk_14 & 0x8000) {
        ((S_801757E0_0 *)actor)->unk_9B = 2;
        ((S_801757E0_1 *)animation)->unk_14 |= 0x6000;
        goto end;
    }
    ((S_801757E0_2 *)motion)->unk_14 = 0;
    ((S_801757E0_2 *)motion)->unk_10 = 0;
    ((S_801757E0_2 *)motion)->unk_0C = 0;
    ((S_801757E0_0 *)actor)->unk_96.u = 0xE;
    ((S_801757E0_0 *)actor)->unk_AC.u = 0;
    ((S_801757E0_0 *)actor)->unk_AD.u = 0;
    ((S_801757E0_0 *)actor)->unk_9B++;
    func_800A56E0(0x80A);
    goto end;

#ifdef __mips__
state_1:
#else
    case 1:
#endif
    for (particle_index = 0; particle_index < 2; particle_index++) {
        particle = func_8003FC64(0x212);
        if (particle != 0) {
            register Pair16 *particle_directions ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

            particle_work = (u8 *)particle + 0x20;
            ((S_801757E0_3 *)particle_work)->unk_1E = 0x28;
            ((S_801757E0_4 *)particle)->unk_10 = D_80170B48;
            func_8004491C(particle, &D_80045340);

            sprite = ((S_801757E0_4 *)particle)->unk_0C;
            ((S_801757E0_5 *)sprite)->unk_14 |= 0x0C;
            ((S_801757E0_5 *)sprite)->unk_10 = 0x60;
            ((S_801757E0_5 *)sprite)->unk_14 |= 2;

            owner = ((S_801757E0_0_pre *)actor)[-1].unk_00;
            particle_transform = ((S_801757E0_4 *)particle)->unk_08;
            if (func_8003DE58(((S_801757E0_6 *)owner)->unk_08, owner, offsets, 1)) {
                ((S_801757E0_7 *)particle_transform)->unk_02 = ((S_801757E0_2 *)motion)->unk_02.u;
                ((S_801757E0_7 *)particle_transform)->unk_06 = ((S_801757E0_2 *)motion)->unk_06.u;
                ((S_801757E0_7 *)particle_transform)->unk_0A = ((S_801757E0_2 *)motion)->unk_0A.u;
                ((S_801757E0_7 *)particle_transform)->unk_02 += offsets[0];
                ((S_801757E0_7 *)particle_transform)->unk_06 += offsets[1];
                ((S_801757E0_7 *)particle_transform)->unk_0A += offsets[2];
            }

            x = (func_80069EF8() & 0x1F) - 0x10;
            y = (func_80069EF8() & 0x1F) - 0x10;
            particle_directions = D_8017610C;
            ((S_801757E0_7 *)particle_transform)->unk_02 += x;
            ((S_801757E0_7 *)particle_transform)->unk_06 += y;
            ((S_801757E0_3 *)particle_work)->unk_50.n = x << 12;
            ((S_801757E0_3 *)particle_work)->unk_54.n = y << 12;
            {
                s32 velocity_x = ((S_801757E0_3 *)particle_work)->unk_50.v;
                s32 direction_x =
                    particle_directions[(((S_801757E0_8 *)entity)->unk_2A.u >> 9) & 7].x;

                particle_directions = (Pair16 *)0x80170000;
                ((S_801757E0_3 *)particle_work)->unk_50.n =
                    velocity_x + (direction_x << 16);
            }
            {
                u16 facing_angle = ((S_801757E0_8 *)entity)->unk_2A.u;

                ASM_KEEP_DEP_NV(particle_directions, facing_angle);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                particle_directions =
                    (Pair16 *)((u8 *)particle_directions + 0x610C);
                ASM_USE(particle_directions);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                ((S_801757E0_3 *)particle_work)->unk_54.n = ((S_801757E0_3 *)particle_work)->unk_54.v +
                    (particle_directions[(facing_angle >> 9) & 7].y << 16);
            }
            ((S_801757E0_3 *)particle_work)->unk_58 = -(func_80069EF8() + 0x50000);
            ((S_801757E0_3 *)particle_work)->unk_64 = 0x6000;

            sprite = ((S_801757E0_4 *)particle)->unk_0C;
            ((S_801757E0_5 *)sprite)->unk_1C = 0x800;
            ((S_801757E0_5 *)sprite)->unk_1E = 0x800;
            ((S_801757E0_5 *)sprite)->unk_0E = 0x80;
            ((S_801757E0_5 *)sprite)->unk_0D = 0x80;
            ((S_801757E0_5 *)sprite)->unk_0C = 0x80;
            ((S_801757E0_5 *)sprite)->unk_12 = 0x7DCF;
            ((S_801757E0_5 *)sprite)->unk_14 |= 0x100;
            func_8003DB94(sprite, &D_800DE870, 0);
        }
    }

    timer = ((S_801757E0_0 *)actor)->unk_96.u - 1;
    ((S_801757E0_0 *)actor)->unk_96.u = timer;
    if (timer > 0 && !(((S_801757E0_1 *)animation)->unk_14 & 0x8000)) {
        goto end;
    }
    ((S_801757E0_0 *)actor)->unk_96.u = 0x78;
    ((S_801757E0_0 *)actor)->unk_9B++;
    goto end;

#ifdef __mips__
state_2:
#else
    case 2:
#endif
    if ((((S_801757E0_1 *)animation)->unk_04 == 2 &&
         (((S_801757E0_1 *)animation)->unk_14 & 0x1000)) ||
        (((S_801757E0_1 *)animation)->unk_14 & 0x8000)) {
        ((S_801757E0_1 *)animation)->unk_14 |= 0x800;
        ((S_801757E0_0 *)actor)->unk_96.u = 0x23;
    }

    timer = ((S_801757E0_0 *)actor)->unk_96.u - 1;
    ((S_801757E0_0 *)actor)->unk_96.u = timer;
    if (timer <= 0 || (((S_801757E0_1 *)animation)->unk_14 & 0x8000)) {
        ((S_801757E0_0 *)actor)->unk_96.u = 0;
        ((S_801757E0_1 *)animation)->unk_14 &= 0xF7FF;
    }

check_effect_trigger:
    if (((S_801757E0_0 *)actor)->unk_96.s != 0x0A &&
        !(((S_801757E0_1 *)animation)->unk_14 & 0x8000)) {
        goto final_flags;
    }

    directions = D_8017610C;
    ((S_801757E0_0 *)actor)->unk_AD.s = 0;
    x = ((S_801757E0_2 *)motion)->unk_02.s +
        (directions[(((S_801757E0_8 *)entity)->unk_2A.u >> 9) & 7].x << 6);
    y = ((S_801757E0_2 *)motion)->unk_06.s +
        (directions[(((S_801757E0_8 *)entity)->unk_2A.u >> 9) & 7].y << 6);
    target_x = (u16)x;
    target_y = (u16)y;

    if ((s16)func_800A45D8(target_x, target_y,
                           ((S_801757E0_2 *)motion)->unk_0A.s) != 0) {
        ((S_801757E0_0 *)actor)->unk_AD.s = 1;
    }
    if (((S_801757E0_0 *)actor)->unk_AD.s == 0) {
        func_8009A350(((S_801757E0_1 *)animation)->unk_24,
                      ((S_801757E0_1 *)animation)->unk_25,
                      (((S_801757E0_8 *)entity)->unk_2A.u >> 9) & 7,
                      &collision_flags);
        if (collision_flags & 0x8400) {
            ((S_801757E0_0 *)actor)->unk_AD.s = 1;
        }
    }
    if (((S_801757E0_0 *)actor)->unk_AD.s == 0) {
        if (func_80174A00(entity,
                ((S_801757E0_1 *)animation)->unk_24 +
                    directions[(((S_801757E0_8 *)entity)->unk_2A.u >> 9) & 7].x,
                ((S_801757E0_1 *)animation)->unk_25 +
                    directions[(((S_801757E0_8 *)entity)->unk_2A.u >> 9) & 7].y,
                ((S_801757E0_2 *)motion)->unk_0A.s) != 0) {
            ((S_801757E0_0 *)actor)->unk_AD.s = 1;
        }
    }
    if (((S_801757E0_0 *)actor)->unk_AD.s == 0) {
        floor_height = func_800BCB04(target_x, target_y,
                             ((S_801757E0_2 *)motion)->unk_0A.s - 0x20);
        if (floor_height >= 0x200 ||
            floor_height > ((S_801757E0_2 *)motion)->unk_0A.s + 0x20 ||
            floor_height < ((S_801757E0_2 *)motion)->unk_0A.s - 0x20) {
            ((S_801757E0_0 *)actor)->unk_AD.s = 1;
        }
    }
    if (((S_801757E0_0 *)actor)->unk_AD.s == 0) {
        func_80175494(actor, motion, animation);
    }

final_flags:
    if (!(((S_801757E0_1 *)animation)->unk_14 & 0xE000)) {
        goto end;
    }
    ((S_801757E0_2 *)motion)->unk_14 = 0;
    ((S_801757E0_2 *)motion)->unk_10 = 0;
    ((S_801757E0_2 *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((S_801757E0_1 *)animation)->unk_24, ((S_801757E0_1 *)animation)->unk_25);

    if (((S_801757E0_1 *)animation)->unk_2C.p != D_8017609C) {
        ((S_801757E0_1 *)animation)->unk_2C.p = D_8017609C;
        ((S_801757E0_1 *)animation)->unk_14 &= 0xF7FF;
        func_80047784(animation,
            ((S_801757E0_1 *)animation)->unk_2C.p2
                [((D_80083228 + ((S_801757E0_8 *)entity)->unk_2A.s + 0x100) >> 9) & 7],
            0);
    }
    ((S_801757E0_0 *)actor)->unk_96.u = 0;
    if (((S_801757E0_0 *)actor)->unk_AD.s == 0) {
        ((S_801757E0_0 *)actor)->unk_9B++;
        goto end;
    }
    ((S_801757E0_0 *)actor)->unk_9B = 0x10;
    goto end;

#ifdef __mips__
state_3:
#else
    case 3:
#endif
    {
        s16 spin_timer = ((S_801757E0_0 *)actor)->unk_96.u + 1;

        ((S_801757E0_0 *)actor)->unk_96.u = spin_timer;
        if ((spin_timer & 3) == 0) {
            register s32 spin_angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            spin_angle = ((S_801757E0_8 *)entity)->unk_2A.s + 0x200;
            ASM_KEEP(spin_angle);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            if (spin_angle >= 0x1000) {
                spin_angle -= 0x1000;
            }
            ((S_801757E0_8 *)entity)->unk_2A.s = spin_angle;
        }
    }
    if (((S_801757E0_0 *)actor)->unk_96.s != 0x13) {
        goto end;
    }
    goto bump_state;

#ifdef __mips__
state_4:
#else
    case 4:
#endif
    timer = ((S_801757E0_0 *)actor)->unk_96.u + 1;
    ((S_801757E0_0 *)actor)->unk_96.u = timer;
    if (timer < 0x0A && !(((S_801757E0_1 *)animation)->unk_14 & 0x8000)) {
        goto end;
    }
    ((S_801757E0_0 *)actor)->unk_96.u = 0;
    ((S_801757E0_0 *)actor)->unk_9B++;
    (*(void * *)((u8 *)animation + 0x2C)) = D_801760A4;
    func_80047784(animation,
        D_801760A4[((D_80083228 + ((S_801757E0_8 *)entity)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    goto end;

#ifdef __mips__
state_5:
#else
    case 5:
#endif
    if (((S_801757E0_1 *)animation)->unk_14 & 0xE000) {
        (*(void * *)((u8 *)animation + 0x2C)) = D_8017609C;
        func_80047784(animation,
            D_8017609C[((D_80083228 + ((S_801757E0_8 *)entity)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        goto bump_state;
    }
    goto end;

#ifdef __mips__
state_6:
#else
    case 6:
#endif
    timer = ((S_801757E0_0 *)actor)->unk_96.u + 1;
    ((S_801757E0_0 *)actor)->unk_96.u = timer;
    if (timer < 0x14 && !(((S_801757E0_1 *)animation)->unk_14 & 0x8000)) {
        goto end;
    }
    goto bump_state;

#ifdef __mips__
state_7:
#else
    case 7:
#endif
    {
        s16 spin_timer = ((S_801757E0_0 *)actor)->unk_96.u + 1;

        ((S_801757E0_0 *)actor)->unk_96.u = spin_timer;
        if ((spin_timer & 3) == 0) {
            register s32 spin_angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            spin_angle = ((S_801757E0_8 *)entity)->unk_2A.s + 0x200;
            ASM_KEEP(spin_angle);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            if (spin_angle >= 0x1000) {
                spin_angle -= 0x1000;
            }
            ((S_801757E0_8 *)entity)->unk_2A.s = spin_angle;
        }
    }
    if (((S_801757E0_0 *)actor)->unk_96.s != 0x13) {
        goto end;
    }
    goto bump_state;

#ifdef __mips__
state_8:
#else
    case 8:
#endif
    if (((S_801757E0_0 *)actor)->unk_AC.s != 0x4D) {
        goto end;
    }
    goto bump_state;

bump_state:
    ((S_801757E0_0 *)actor)->unk_96.u = 0;
bump_state_loaded:
    ((S_801757E0_0 *)actor)->unk_9B++;
    goto end;

#ifdef __mips__
state_9:
#else
    case 9:
#endif
    func_800AD594(entity, 0x800);
    ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_801757E0_0 *)actor)->unk_8C = &D_801714B8;
    D_8008346C = 0;
    (*(u16 *)((u8 *)entity + 0x46)) &= 0x7FFF;

#ifdef __mips__
state_16:
#else
    case 16:
#endif
    timer = ((S_801757E0_0 *)actor)->unk_96.u + 1;
    ((S_801757E0_0 *)actor)->unk_96.u = timer;
    if (timer >= 0x1E) {
        ((S_801757E0_0 *)actor)->unk_9B = 9;
        ((S_801757E0_0 *)actor)->unk_96.u = 0;
    }
    goto end;

#ifndef __mips__
    default:
        break;
    }
#endif

end:
    return;
}
