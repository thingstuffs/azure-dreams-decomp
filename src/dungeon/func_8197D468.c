#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

typedef struct S_8197D468_0_pre {
    u16 unk_00;
} S_8197D468_0_pre;   /* the 0x2 bytes before arg0 in func_8197D468, addressed as arg0[-1] */

typedef struct S_8197D468_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_8197D468_0;   /* arg0 in func_8197D468 */

typedef struct S_8197D468_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8197D468_1;   /* temp_v0 in func_8197D468 */

typedef struct S_8197D468_2 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8197D468_2;   /* arg2 in func_8197D468 */

typedef struct S_8197D468_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8197D468_3;   /* arg1 in func_8197D468 */

typedef struct S_8197D468_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8197D468_4;   /* &D_800DE990 in func_8197D468 */

typedef struct S_8197D468_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8197D468_5;   /* temp_v0_2 in func_8197D468 */

typedef struct S_8197D468_6 {
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
} S_8197D468_6;   /* temp_s0 in func_8197D468 */


typedef struct S_8197D468_8 {
    u8 pad_00[0x4C];
    s16 unk_4C;
} S_8197D468_8;   /* temp_v0_4 in func_8197D468 */

typedef struct S_8197D468_9 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8197D468_9;   /* ((S_8197D468_5 *)temp_v0_2)->unk_08 in func_8197D468 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_8008378A;
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800DED70[];
extern s32 D_800814A0;
void func_80025050(void) __attribute__((noreturn)); /* extern */
void *func_8003FD64();                 /* extern */
s32 func_80069EF8();                          /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80024BB8;
extern M2C_UNK D_800DE990;

/* Update a rising, expanding, and falling effect, spawning particles on landing. */
void func_8197D468(void *effect, void *motion, void *sprite) {
    s16 state;
    s16 ground_height;
    s32 particle_index;
    s32 particle_frames;
    s32 rise_random;
    s32 rise_velocity;
    s32 fall_random;
    s32 fall_velocity;
    u16 frames_left;
    u16 sprite_flags;
    s32 particle_color;
    void *sprite_frames;
    void *effect_data;
    void *particle_sprite;
    void *owner;
    void *particle;

    owner = ((S_8197D468_0 *)effect)->unk_00;
    ((S_8197D468_1 *)owner)->unk_52 = (u16) (((S_8197D468_1 *)owner)->unk_52 | 0x8000);
    if (((S_8197D468_2 *)sprite)->unk_14 & 0x6000) {
        ((S_8197D468_2 *)sprite)->unk_04 = 0;
        ((S_8197D468_2 *)sprite)->unk_05 = 0;
        ((S_8197D468_2 *)sprite)->unk_14 = (u16) (((S_8197D468_2 *)sprite)->unk_14 & 0x9FFF);
    }
    func_800478B8(sprite);
    state = ((S_8197D468_0 *)effect)->unk_4C.s;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_80025050();
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state == 2) {
        goto state_2;
    }
    func_80025050();

state_0:
    ((S_8197D468_3 *)motion)->unk_08.at00.v = (s32) (((S_8197D468_3 *)motion)->unk_08.at00.v + ((S_8197D468_3 *)motion)->unk_14);
    rise_random = func_80069EF8();
    rise_velocity = ((S_8197D468_3 *)motion)->unk_14 + 0x1A000;
    rise_velocity += rise_random >> 1;
    ((S_8197D468_3 *)motion)->unk_14 = rise_velocity;
    if ((u8) ((S_8197D468_2 *)sprite)->unk_0C.u8 < 0x40) {
        ((S_8197D468_2 *)sprite)->unk_0C.s32 = (s32) ((s32) ((S_8197D468_2 *)sprite)->unk_0C.s32 + 0x40404);
    }
    if (((S_8197D468_3 *)motion)->unk_14 > 0) {
        ((S_8197D468_2 *)sprite)->unk_00 = &D_800DE990;
        sprite_frames = (void *) ((S_8197D468_4 *)(&D_800DE990))->unk_04;
        ASM_KEEP(sprite_frames);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sprite_flags = ((S_8197D468_2 *)sprite)->unk_14;
        ASM_KEEP(sprite_flags);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((S_8197D468_2 *)sprite)->unk_04 = 0;
        ((S_8197D468_2 *)sprite)->unk_05 = 0;
        ((S_8197D468_2 *)sprite)->unk_1E = 0x400U;
        ((S_8197D468_2 *)sprite)->unk_1C = 0x400U;
        ((S_8197D468_2 *)sprite)->unk_10 = 0;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        ((S_8197D468_2 *)sprite)->unk_08 = sprite_frames;
        ((S_8197D468_2 *)sprite)->unk_14 = (u16) (sprite_flags | 2);
        ((S_8197D468_0 *)effect)->unk_48 = (u16) ((func_80069EF8(sprite_frames) & 3) + 4);
        ((S_8197D468_0 *)effect)->unk_4C.u = (u16) (((S_8197D468_0 *)effect)->unk_4C.u + 1);
        func_80025050();
    }
    goto done;

state_1:
    ((S_8197D468_2 *)sprite)->unk_0C.s32 = 0x606060;
    ((S_8197D468_2 *)sprite)->unk_1C = (u16) (((S_8197D468_2 *)sprite)->unk_1C + 0xC8);
    ((S_8197D468_2 *)sprite)->unk_1E = (u16) (((S_8197D468_2 *)sprite)->unk_1E + 0xC8);
    frames_left = ((S_8197D468_0 *)effect)->unk_48 - 1;
    ((S_8197D468_0 *)effect)->unk_48 = frames_left;
    if ((frames_left << 0x10) <= 0) {
        ((S_8197D468_0 *)effect)->unk_4C.u = (u16) (((S_8197D468_0 *)effect)->unk_4C.u + 1);
        func_80025050();
    }
    goto done;

state_2:
    if (((S_8197D468_2 *)sprite)->unk_14 & 0x6000) {
        ((S_8197D468_2 *)sprite)->unk_00 = &D_800DE990;
        effect_data = (void *) ((S_8197D468_4 *)(&D_800DE990))->unk_04;
        ((S_8197D468_2 *)sprite)->unk_04 = 0;
        ((S_8197D468_2 *)sprite)->unk_05 = 0;
        ((S_8197D468_2 *)sprite)->unk_08 = effect_data;
    }
    ((S_8197D468_3 *)motion)->unk_08.at00.v = (s32) (((S_8197D468_3 *)motion)->unk_08.at00.v + ((S_8197D468_3 *)motion)->unk_14);
    fall_random = func_80069EF8();
    fall_velocity = ((S_8197D468_3 *)motion)->unk_14 + 0x1C000;
    fall_velocity += fall_random >> 1;
    ((S_8197D468_3 *)motion)->unk_14 = fall_velocity;
    if ((u8) ((S_8197D468_2 *)sprite)->unk_0C.u8 < 0x80) {
        ((S_8197D468_2 *)sprite)->unk_0C.s32 = (s32) ((s32) ((S_8197D468_2 *)sprite)->unk_0C.s32 + 0x40404);
    }
    ground_height = func_800BCB04(((S_8197D468_3 *)motion)->unk_00.at02.v, ((S_8197D468_3 *)motion)->unk_04.at02.v, (s16) (D_8008378A - 0x80));
    if (((S_8197D468_3 *)motion)->unk_08.at02.v >= (ground_height - 0x20)) {
        particle_index = 4;
        do {
            particle = func_8003FD64(0x312, D_80083498);
            if (particle != NULL) {
                ((S_8197D468_5 *)particle)->unk_10 = &D_80024BB8;
                func_8004491C(particle, D_80045340);
                particle_sprite = ((S_8197D468_5 *)particle)->unk_0C;
                ((S_8197D468_9 *)(((S_8197D468_5 *)particle)->unk_08))->unk_00 = (s32) (((S_8197D468_3 *)motion)->unk_00.at00.v + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA));
                ((S_8197D468_9 *)(((S_8197D468_5 *)particle)->unk_08))->unk_04 = (s32) (((S_8197D468_3 *)motion)->unk_04.at00.v + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA));
                ((S_8197D468_9 *)(((S_8197D468_5 *)particle)->unk_08))->unk_08 = (s32) (((S_8197D468_3 *)motion)->unk_08.at00.v + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA));
                ((S_8197D468_9 *)(((S_8197D468_5 *)particle)->unk_08))->unk_0C = (s32) (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA);
                ((S_8197D468_9 *)(((S_8197D468_5 *)particle)->unk_08))->unk_10 = (s32) (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA);
                ((S_8197D468_9 *)(((S_8197D468_5 *)particle)->unk_08))->unk_14 = (s32) (0 - ((func_80069EF8() & 0x3FF) << 8));
                particle_color = 0xC00000;
   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                ((S_8197D468_6 *)particle_sprite)->unk_1E = 0xC00;
                ((S_8197D468_6 *)particle_sprite)->unk_1C = 0xC00;
                ((S_8197D468_6 *)particle_sprite)->unk_10 = 0x20;
                ((S_8197D468_6 *)particle_sprite)->unk_00 = D_800DED70;
                ((S_8197D468_6 *)particle_sprite)->unk_14 = (u16) (((S_8197D468_6 *)particle_sprite)->unk_14 | 0xC);
                particle_frames = ((Rec_D_80016000 *)D_800DED70)->unk_04.at00_s32.v;
                particle_color |= 0x6060;
                ((S_8197D468_6 *)particle_sprite)->unk_04 = 0;
                ((S_8197D468_6 *)particle_sprite)->unk_05 = 0;
                ((S_8197D468_6 *)particle_sprite)->unk_0C = particle_color;
                ((S_8197D468_6 *)particle_sprite)->unk_08 = particle_frames;
                effect_data = ((S_8197D468_0 *)effect)->unk_00;
                ((S_8197D468_5 *)particle)->unk_20 = effect_data;
                effect_data = particle + 0x20;
                ASM_KEEP(effect_data);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                ((S_8197D468_8 *)effect_data)->unk_4C = 0;
            }
            particle_index -= 1;
        } while (particle_index >= 0);
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_8197D468_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
done:
    return;
}
