#include "common.h"

typedef struct S_800BBCA0_0 {
    u8 pad_00[0x48];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_800BBCA0_0;   /* self in func_800BBCA0 */

typedef struct S_800BBCA0_1 {
    u8 pad_00[0x8];
    s32 * unk_08;
    u8 * unk_0C;
    u8 * unk_10;
} S_800BBCA0_1;   /* object in func_800BBCA0 */

typedef struct S_800BBCA0_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800BBCA0_2;   /* origin in func_800BBCA0 */

typedef struct S_800BBCA0_3 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x36];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_800BBCA0_3;   /* motion in func_800BBCA0 */

typedef struct S_800BBCA0_4 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800BBCA0_4;   /* sprite in func_800BBCA0 */

typedef struct S_800BBCA0_5 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800BBCA0_5;   /* spriteType in func_800BBCA0 */



extern s32 func_80033BC0(s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);

extern s32 D_80045340;
extern s32 D_800814A0;
extern u8 D_80083498[];
extern u8 D_800BC00C[];
extern u8 D_800F1654[];

/* Spawns particles around the origin, emits a burst, then marks the effect finished. */
void func_800BBCA0(void *effect, void *effect_origin)
{
    register void *self ASM_REG("$21") = effect;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *origin ASM_REG("$20") = effect_origin;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u16 next_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 state;
    u16 timer;
    s32 spawn_count;
    s32 rand_value;
    u8 *object;
    u8 *sprite;
    u8 *motion;
    s32 *position;
    s32 *velocity;
    u8 *object_type;
    u8 *sprite_type;

    timer = ((S_800BBCA0_0 *)self)->unk_48 - 1;
    state = ((S_800BBCA0_0 *)self)->unk_4C.s;
    ((S_800BBCA0_0 *)self)->unk_48 = timer;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        spawn_count = 7;
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    object_type = D_800BC00C;
    sprite_type = D_800F1654;
    do {
        object = func_8003FD64(0x312, D_80083498);
        if (object != 0) {
            ((S_800BBCA0_1 *)object)->unk_10 = object_type;
            func_8004491C(object, &D_80045340);
            sprite = ((S_800BBCA0_1 *)object)->unk_0C;
            motion = object + 0x20;

            rand_value = rand();
            position = ((S_800BBCA0_1 *)object)->unk_08;
            position[0] = ((S_800BBCA0_2 *)origin)->unk_00.at00.v + (((rand_value & 0x1FF) - 0x100) << 13);
            rand_value = rand();
            position = ((S_800BBCA0_1 *)object)->unk_08;
            position[1] = ((S_800BBCA0_2 *)origin)->unk_04.at00.v + (((rand_value & 0x1FF) - 0x100) << 13);
            rand_value = rand();
            position = ((S_800BBCA0_1 *)object)->unk_08;
            position[2] = ((S_800BBCA0_2 *)origin)->unk_08.at00.v + (((rand_value & 0x1FF) - 0x100) << 13);

            ((S_800BBCA0_3 *)motion)->unk_0C = ((S_800BBCA0_2 *)origin)->unk_00.at02.v;
            ((S_800BBCA0_3 *)motion)->unk_0E = ((S_800BBCA0_2 *)origin)->unk_04.at02.v;
            ((S_800BBCA0_3 *)motion)->unk_10 = ((S_800BBCA0_2 *)origin)->unk_08.at02.v;
            ((S_800BBCA0_4 *)sprite)->unk_1E = 0x100;
            ((S_800BBCA0_4 *)sprite)->unk_1C = 0x100;
            ((S_800BBCA0_4 *)sprite)->unk_10 = 0x20;
            ((S_800BBCA0_4 *)sprite)->unk_14 |= 0xC;
            ((S_800BBCA0_3 *)motion)->unk_48 = 6;
            ((S_800BBCA0_4 *)sprite)->unk_00 = sprite_type;
            ((S_800BBCA0_4 *)sprite)->unk_08 = ((S_800BBCA0_5 *)sprite_type)->unk_04;
            ((S_800BBCA0_4 *)sprite)->unk_04 = 0;
            ((S_800BBCA0_4 *)sprite)->unk_05 = 0;
            ((S_800BBCA0_4 *)sprite)->unk_0C = 0x101010;
        }
        spawn_count--;
    } while (spawn_count >= 0);
    if (func_80033BC0(0x97) != 0) {
        next_state = ((S_800BBCA0_0 *)self)->unk_4C.u;
        next_state++;
        goto store_state;
    }
    goto done;

state_one:
    spawn_count = 0x64;
    object_type = D_800BC00C;
    sprite_type = D_800F1654;
    do {
        object = func_8003FD64(0x312, D_80083498);
        motion = object + 0x20;
        if (object != 0) {
            ((S_800BBCA0_1 *)object)->unk_10 = object_type;
            func_8004491C(object, &D_80045340);
            sprite = ((S_800BBCA0_1 *)object)->unk_0C;

            rand_value = rand();
            position = ((S_800BBCA0_1 *)object)->unk_08;
            position[0] = ((S_800BBCA0_2 *)origin)->unk_00.at00.v + (((rand_value & 0x1FF) - 0x100) << 10);
            rand_value = rand();
            position = ((S_800BBCA0_1 *)object)->unk_08;
            position[1] = ((S_800BBCA0_2 *)origin)->unk_04.at00.v + (((rand_value & 0x1FF) - 0x100) << 10);
            rand_value = rand();
            position = ((S_800BBCA0_1 *)object)->unk_08;
            position[2] = ((S_800BBCA0_2 *)origin)->unk_08.at00.v + (((rand_value & 0x1FF) - 0x100) << 10);
            rand_value = rand();
            velocity = ((S_800BBCA0_1 *)object)->unk_08;
            velocity[3] = ((rand_value & 0x1FF) - 0x100) << 14;
            rand_value = rand();
            velocity = ((S_800BBCA0_1 *)object)->unk_08;
            velocity[4] = ((rand_value & 0x1FF) - 0x100) << 14;
            rand_value = rand();
            velocity = ((S_800BBCA0_1 *)object)->unk_08;
            velocity[5] = ((rand_value & 0x1FF) - 0x100) << 12;

            ((S_800BBCA0_4 *)sprite)->unk_1E = 0x200;
            ((S_800BBCA0_4 *)sprite)->unk_1C = 0x200;
            ((S_800BBCA0_4 *)sprite)->unk_10 = 0x20;
            ((S_800BBCA0_4 *)sprite)->unk_14 |= 0xC;
            ((S_800BBCA0_3 *)motion)->unk_48 = 0xF;
            ((S_800BBCA0_3 *)motion)->unk_4C = 1;
            ((S_800BBCA0_4 *)sprite)->unk_00 = sprite_type;
            ((S_800BBCA0_4 *)sprite)->unk_08 = ((S_800BBCA0_5 *)sprite_type)->unk_04;
            ((S_800BBCA0_4 *)sprite)->unk_04 = 0;
            ((S_800BBCA0_4 *)sprite)->unk_05 = 0;
            ((S_800BBCA0_4 *)sprite)->unk_0C = 0x808080;
        }
        spawn_count--;
    } while (spawn_count >= 0);
    next_state = ((S_800BBCA0_0 *)self)->unk_4C.u;
    ((S_800BBCA0_0 *)self)->unk_48 = 0x10;
    next_state++;

store_state:
    ((S_800BBCA0_0 *)self)->unk_4C.u = next_state;
    goto done;

state_two:
    if ((s16)timer < 0) {
        (*(u16 *)((u8 *)self + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}
