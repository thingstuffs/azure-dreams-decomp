#include "common.h"


typedef struct {
    s16 x;
    u16 y;
} Copy4;

typedef struct {
    Copy4 entries[8];
} __attribute__((packed)) Copy24;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Copy12;

typedef struct {
    s32 a;
    s32 b;
} Pair;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    Pair pair;
} OutPair;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Triple;

extern Copy24 D_80024014;
extern Copy12 D_80026668;
extern Copy12 D_80026674;
extern Copy12 D_80026680;
extern Copy12 D_80026698;
extern Copy12 D_800266A4;
extern s16 D_800266BC[5];
extern u8 D_80045340[9];
extern u8 D_80025348[12];
extern u8 D_80025398[12];
extern u8 D_8002558C[12];
extern u8 D_80025648[12];
extern u8 D_8006CCD8[64];
extern u8 D_8006CCE8[64];
extern s32 D_800814A0[3];
extern s32 D_8008346C[2];
extern u8 D_800DDC40[256];
extern u8 D_800E3D68[256];

extern void func_800B835C(void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern s32 func_8002512C(void);
extern void func_80025228(void *, s32, s32, s32, s32, s32, s32);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800A56E0(s32);
extern void *func_8003FC64(s32);
extern s32 func_8009D218(void *, s32, void *);
extern s32 func_800A6D30(void);
extern void func_800C8A3C(void *, s32, s32);

/* In-row shared tails, spelled as absolute noreturn calls (the row's own true
   range is [0x8002592C, 0x80026668); these are words 834, 157, 247, 359 and
   544 of this same function -- NORETURN-DECL AUDIT case (a)). */
extern void func_80026634(void) __attribute__((noreturn));
extern void func_800261AC(void) __attribute__((noreturn));
extern void func_80025D08(void) __attribute__((noreturn));
extern void func_80025BA0(void) __attribute__((noreturn));
extern void func_80025EC8(void) __attribute__((noreturn));


typedef struct S_818FA12C_0 {
    u8 pad_00[0x8];
    s16 * unk_08;
    u8 * unk_0C;
} S_818FA12C_0;   /* base in func_818FA12C */

typedef struct S_818FA12C_1 {
    u8 pad_00[0x8];
    u32 unk_08;
    union { struct { u32 v; } at00; struct { volatile u8 v; } at00u; struct { u8 v; } at00p; struct { u8 pad[0x1]; volatile u8 v; } at01; struct { u8 pad[0x1]; u8 v; } at01u; struct { u8 pad[0x2]; volatile u8 v; } at02; struct { u8 pad[0x2]; u8 v; } at02u; } unk_0C;   /* overlapping accesses */
    volatile u16 unk_10;
    u8 pad_12[0x2];
    volatile u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    union { volatile u16 v; u16 n; } unk_1C;   /* accessed as both */
    union { volatile u16 v; u16 n; } unk_1E;   /* accessed as both */
} S_818FA12C_1;   /* packet in func_818FA12C */

typedef struct S_818FA12C_2_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_818FA12C_2_pre;   /* the 0x14 bytes before parent in func_818FA12C, addressed as parent[-1] */

typedef struct S_818FA12C_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { u8 * p; void * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_818FA12C_2;   /* parent in func_818FA12C */

typedef struct S_818FA12C_3 {
    u8 pad_00[0x10];
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x1];
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
} S_818FA12C_3;   /* colors in func_818FA12C */

typedef struct S_818FA12C_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818FA12C_4;   /* out in func_818FA12C */

typedef struct S_818FA12C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818FA12C_5;   /* table_entry in func_818FA12C */

typedef struct S_818FA12C_6 {
    u8 * unk_00;
} S_818FA12C_6;   /* obj - 0x18 in func_818FA12C */

typedef struct S_818FA12C_7 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_818FA12C_7;   /* src in func_818FA12C */

typedef struct S_818FA12C_8 {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_818FA12C_8;   /* obj_data in func_818FA12C */

typedef struct S_818FA12C_9 {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_818FA12C_9;   /* obj2_data in func_818FA12C */

typedef struct S_818FA12C_10 {
    u8 pad_00[0x38];
    u8 unk_38;
} S_818FA12C_10;   /* cursor in func_818FA12C */

typedef struct S_818FA12C_11 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_818FA12C_11;   /* tmpsrc in func_818FA12C */

typedef struct S_818FA12C_12 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_818FA12C_12;   /* ((S_818FA12C_0 *)base)->unk_0C in func_818FA12C */

typedef struct S_818FA12C_13 {
    u16 unk_00;
} S_818FA12C_13;   /* (*(void * *)((u8 *)self + 4)) in func_818FA12C */

typedef struct S_818FA12C_14 {
    u8 * unk_00;
} S_818FA12C_14;   /* ((S_818FA12C_2 *)parent)->unk_60.p - 0x18 in func_818FA12C */

typedef struct S_818FA12C_15 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FA12C_15;   /* ((S_818FA12C_2 *)parent)->unk_60.p in func_818FA12C */

typedef struct S_818FA12C_16 {
    u8 * unk_00;
} S_818FA12C_16;   /* ((S_818FA12C_2 *)parent)->unk_60.p - 0x14 in func_818FA12C */

/* Update a projectile effect, spawn impact particles, and advance its cleanup state. */
void func_818FA12C(void *effect, void *motion, void *volatile render_data)
{
    u8 *self = effect;
    u8 *position = motion;
    register u8 *parent ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *parent_base;
    u8 *target_pos;
    s16 *origin;
    OutPair out_pair;
    Copy24 velocities;
    s32 state;

    Copy24 *velocity_table;
    u8 *impact;
    velocity_table = &D_80024014;
    ASM_KEEP(self);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    parent = (*(u8 * *)((u8 *)self + 0));
    velocities = *velocity_table;
    (*(s16 *)((u8 *)self + 0x0A));
    parent_base = parent - 0x20;
    state = (*(s16 *)((u8 *)self + 0x0A));
    origin = ((S_818FA12C_0 *)parent_base)->unk_08;
    switch (state) {

    case 0:
        {
            register u8 *packet ASM_REG("$9") = render_data;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 packed_pos;
            s32 packed_size;
            s32 copy_flags;
            u8 *colors;
            s32 state;
            ((S_818FA12C_1 *)packet)->unk_0C.at00.v = 0x00808080;
            packed_pos = 0x1400340;
            copy_flags = 0;
            ASM_KEEP(copy_flags);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            (*(Copy12 *)((u8 *)self + 0xA2)) = D_80026698;
            packed_size = 0x400040;
            colors = (u8 *)&D_800266A4;
            ((S_818FA12C_1 *)packet)->unk_08 = (u32)(self + 0xA2);
            (*(u16 *)((u8 *)self + 0x7E)) = (((S_818FA12C_2 *)parent)->unk_2A >> 9) & 7;
            ((S_818FA12C_3 *)colors)->unk_10 = 0x80;
            ((S_818FA12C_3 *)colors)->unk_11 = 0x80;
            ((S_818FA12C_3 *)colors)->unk_12 = 0x80;
            ((S_818FA12C_3 *)colors)->unk_14 = 4;
            ((S_818FA12C_3 *)colors)->unk_15 = 4;
            ((S_818FA12C_3 *)colors)->unk_16 = 4;
            out_pair.pair.a = packed_pos;
            out_pair.pair.b = packed_size;
            func_800B835C(colors, &out_pair.pair, 1, copy_flags);
            state = (*(u16 *)((u8 *)self + 0x0A));
            D_800266BC[0] = 1;
            (*(u16 *)((u8 *)self + 0x0A)) = state + 1;
        }

    case 1:
        {
            u8 *target;
            u8 *parent_data;
            s32 step_result;
            s32 height;
            s32 origin_z;
            register s32 flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 frames ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            register s32 frames_copy ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u32 target_height;
            s32 tile_distance;
            register s32 frames_squared ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register u8 *packet ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            step_result = func_8003DF74(((S_818FA12C_12 *)(((S_818FA12C_0 *)parent_base)->unk_0C))->unk_08,
                ((S_818FA12C_0 *)parent_base)->unk_0C, &out_pair, 0);
            if (step_result == 0 && !(((S_818FA12C_12 *)(((S_818FA12C_0 *)parent_base)->unk_0C))->unk_14 & 0x8000)) {
                goto done;
            }
            ((S_818FA12C_4 *)position)->unk_00.at02.v = ((S_818FA12C_5 *)origin)->unk_02;
            ((S_818FA12C_4 *)position)->unk_04.at02.v = ((S_818FA12C_5 *)origin)->unk_06;
            origin_z = ((S_818FA12C_5 *)origin)->unk_0A;
            ((S_818FA12C_4 *)position)->unk_08.at02.v = origin_z;
            if (!(((S_818FA12C_12 *)(((S_818FA12C_0 *)parent_base)->unk_0C))->unk_14 & 0x8000)) {
                ((S_818FA12C_4 *)position)->unk_00.at02.v += out_pair.x;
                ((S_818FA12C_4 *)position)->unk_04.at02.v += out_pair.y;
                height = ((S_818FA12C_4 *)position)->unk_08.at02.v + out_pair.z;
                ASM_TAILSLOT_PIN(height);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_80025BA0();
            } else {
                ASM_SCHED_BARRIER();   /* reorg CALL+BARRIER flip: keep the bnez slot a nop */
                ((S_818FA12C_4 *)position)->unk_08.at02.v = origin_z - 0x40;
            }
            if (!(((S_818FA12C_13 *)((*(void * *)((u8 *)self + 4))))->unk_00 & 0x80)) {
                goto done;
            }
            if (!((*(u8 *)((u8 *)self + 0x7A)) & 4)) {
                func_8004491C(self - 0x20, D_80045340);
                packet = render_data;
                ((S_818FA12C_1 *)packet)->unk_10 = 0x20;
                ((S_818FA12C_1 *)packet)->unk_0C.at02.v = 0x20;
                ((S_818FA12C_1 *)packet)->unk_0C.at00u.v = 0x20;
                flags = ((S_818FA12C_1 *)packet)->unk_14;
                ((S_818FA12C_1 *)packet)->unk_0C.at01.v = 0xE0;
                ((S_818FA12C_1 *)packet)->unk_1E.v = 2000;
                ((S_818FA12C_1 *)packet)->unk_1C.v = 2000;
                flags |= 0x0C;
                ((S_818FA12C_1 *)packet)->unk_14 = flags;
                flags &= 0xFFFC;
                ((S_818FA12C_1 *)packet)->unk_14 = flags;
                (*(u8 *)((u8 *)self + 0x7A)) |= 4;
            }
            if ((target = ((S_818FA12C_2 *)parent)->unk_60.p) != 0) {
                target_pos = ((S_818FA12C_6 *)(target - 0x18))->unk_00;
                target_height = D_800DDC40[(*(u8 *)((u8 *)target + 0x13))];
                (*(u16 *)((u8 *)self + 0x78)) = ((S_818FA12C_7 *)target_pos)->unk_08.at02.v - (target_height >> 1);
                parent_data = ((S_818FA12C_2_pre *)parent)[-1].unk_00;
                (*(u8 *)((u8 *)self + 0xBA)) = ((S_818FA12C_8 *)parent_data)->unk_24
                    + D_8006CCD8[(*(s16 *)((u8 *)self + 0x7E)) * 2];
                (*(u8 *)((u8 *)self + 0xBB)) = ((S_818FA12C_8 *)parent_data)->unk_25
                    + D_8006CCE8[(*(s16 *)((u8 *)self + 0x7E)) * 2];
                flags = (s8)((S_818FA12C_2 *)parent)->unk_72;
                if (flags != ((S_818FA12C_8 *)parent_data)->unk_24) {
                    tile_distance = flags - ((S_818FA12C_8 *)parent_data)->unk_24;
                } else {
                    flags = (s8)((S_818FA12C_2 *)parent)->unk_73;
                    tile_distance = flags - ((S_818FA12C_8 *)parent_data)->unk_25;
                }
                if (tile_distance < 0) {
                    tile_distance = -tile_distance;
                }
                (*(u8 *)((u8 *)self + 0x7B)) = tile_distance * 2 - 1;
                func_80025D08();
            } else {
                (*(u16 *)((u8 *)self + 0x78)) = ((S_818FA12C_2 *)parent)->unk_88 - 0x50;
                (*(u8 *)((u8 *)self + 0x7B)) = 0x20;
            }
            ASM_SCHED_BARRIER();   /* block boundary the deleted join label used to give */
            ((S_818FA12C_4 *)position)->unk_0C = (s32)velocities.entries[(*(s16 *)((u8 *)self + 0x7E))].x << 16;
            ((S_818FA12C_4 *)position)->unk_10 = (u32)velocities.entries[(*(s16 *)((u8 *)self + 0x7E))].y << 16;
            ((S_818FA12C_4 *)position)->unk_14 = (((s32)(*(s16 *)((u8 *)self + 0x78)) << 16) - ((S_818FA12C_4 *)position)->unk_08.at00.v)
                / (s8)(*(u8 *)((u8 *)self + 0x7B));
            (*(u16 *)((u8 *)self + 0x82)) = 0;
            (*(u16 *)((u8 *)self + 0x90)) = 0;
            (*(u16 *)((u8 *)self + 0x92)) = 0;
            (*(u16 *)((u8 *)self + 0x94)) = 5;
            (*(u16 *)((u8 *)self + 0x96)) = 200;
            (*(u16 *)((u8 *)self + 0x0A))++;
            (*(s16 *)((u8 *)self + 0x88)) = (s8)(*(u8 *)((u8 *)self + 0x7B));
            step_result = (*(u8 *)((u8 *)self + 0x7B)) << 24;
            ASM_KEEP_NV(step_result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            frames = step_result >> 24;
            frames_copy = frames;
            ASM_KEEP_NV(frames_copy);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            frames_squared = frames * frames_copy;
            (*(s16 *)((u8 *)self + 0x8A)) = frames_squared;
            func_80026634();
        }

    case 2:
        {
            s32 index;
            s32 random_bits;
            s32 hit_result;
            register s32 angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            s16 pulse_ticks;
            s32 shrinking;
            register u8 *flash ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u8 *flash_data;
            register u8 *impact_state ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            void *flash_state;
            void *animation;
            register s32 render_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u8 *impact_data;
            register s32 *impact_pos ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            u8 *clear_cursor;

            index = 0;
            do {
                u8 *emitter;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                s32 direction;
                s32 color;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                s32 intensity;
                random_bits = func_80069EF8();
                emitter = self - 0x20;
                color = 0x40E020;
                intensity = (random_bits & 0xFF) | 0x80;
                direction = (*(s16 *)((u8 *)self + 0x7E));
                func_80025228(emitter, direction, color, intensity, 0, 0, 0);
                index++;
            } while (index < 8);
            hit_result = func_800A4778(((S_818FA12C_4 *)position)->unk_00.at02.v, ((S_818FA12C_4 *)position)->unk_04.at02.v,
                ((S_818FA12C_4 *)position)->unk_08.at02u.v, ((S_818FA12C_2 *)parent)->unk_60.p2);
            if (hit_result << 16) {
                register u8 *packet ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                (*(u16 *)((u8 *)self + 0x0A)) = 8;
                (*(u16 *)((u8 *)self + 0x82)) = 0;
                packet = render_data;
                ((S_818FA12C_1 *)packet)->unk_0C.at02u.v = 0;
                ((S_818FA12C_1 *)packet)->unk_0C.at01u.v = 0;
                ((S_818FA12C_1 *)packet)->unk_0C.at00p.v = 0;
                func_80026634();
            }
            {
                register u8 *packet ASM_REG("$9") = render_data;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 scale_y;
                angle = ((S_818FA12C_1 *)packet)->unk_1A + 0x400;
                ASM_KEEP(angle);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                if (angle >= 0x1001) {
                    angle -= 0x1000;
                }
                ((S_818FA12C_1 *)packet)->unk_1A = angle;
                shrinking = (*(s16 *)((u8 *)self + 0x90));
                if (shrinking == 0) {
                    ((S_818FA12C_1 *)packet)->unk_1C.n += (*(u16 *)((u8 *)self + 0x96));
                    scale_y = ((S_818FA12C_1 *)packet)->unk_1E.n + (*(u16 *)((u8 *)self + 0x96));
                    ASM_TAILSLOT_PIN(scale_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction pulse_ticks (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    func_80025EC8();
                } else {
                    packet = render_data;
                    ((S_818FA12C_1 *)packet)->unk_1C.n -= (*(u16 *)((u8 *)self + 0x96));
                    ((S_818FA12C_1 *)packet)->unk_1E.n -= (*(u16 *)((u8 *)self + 0x96));
                }
            }
            pulse_ticks = (*(s16 *)((u8 *)self + 0x92)) + 1;
            (*(s16 *)((u8 *)self + 0x92)) = pulse_ticks;
            if (pulse_ticks >= (*(s16 *)((u8 *)self + 0x94))) {
                (*(s16 *)((u8 *)self + 0x92)) = 0;
                (*(s16 *)((u8 *)self + 0x90)) ^= 1;
            }
            (*(u8 *)((u8 *)self + 0x7B))--;
            if ((s8)(*(u8 *)((u8 *)self + 0x7B)) > 0) {
                goto update_position;
            }
            if (((S_818FA12C_2 *)parent)->unk_60.p == 0) {
                goto missing_target;
            }
            (*(u16 *)((u8 *)self + 0x0A)) = 3;
            (*(u16 *)((u8 *)self + 0x82)) = 0;
            target_pos = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
            ((S_818FA12C_4 *)position)->unk_00.at02.v = ((S_818FA12C_7 *)target_pos)->unk_00.at02.v;
            ((S_818FA12C_4 *)position)->unk_04.at02.v = ((S_818FA12C_7 *)target_pos)->unk_04.at02.v;
            ((S_818FA12C_4 *)position)->unk_08.at02.v = ((S_818FA12C_7 *)target_pos)->unk_08.at02.v - D_800DDC40[((S_818FA12C_15 *)(((S_818FA12C_2 *)parent)->unk_60.p))->unk_13];
            func_800A56E0(0x300);
            flash = func_8003FC64(0x212);
            if (flash != 0) {
                (*(u16 *)((u8 *)flash + 0x22)) = 120;
                (*(u32 *)((u8 *)flash + 0x10)) = (u32)D_80025348;
                func_8004491C(flash, D_80045340);
                flash_data = (*(u8 * *)((u8 *)flash + 0x0C));
                ((S_818FA12C_9 *)flash_data)->unk_14 |= 0x0C;
                ((S_818FA12C_9 *)flash_data)->unk_10 = 0;
                ((S_818FA12C_9 *)flash_data)->unk_06 = 0;
                ((S_818FA12C_9 *)flash_data)->unk_14 |= 0x80;
                target_pos = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
                impact_pos = (*(s32 * *)((u8 *)flash + 8));
                impact_pos[0] = ((S_818FA12C_7 *)target_pos)->unk_00.at00.v;
                impact_pos[1] = ((S_818FA12C_7 *)target_pos)->unk_04.at00.v;
                impact_pos[2] = ((S_818FA12C_7 *)target_pos)->unk_08.at00.v;
                flash_data = (*(u8 * *)((u8 *)flash + 0x0C));
                ((S_818FA12C_9 *)flash_data)->unk_1E = 0x1000;
                ((S_818FA12C_9 *)flash_data)->unk_1C = 0x1000;
                ((S_818FA12C_9 *)flash_data)->unk_0E = 0x80;
                ((S_818FA12C_9 *)flash_data)->unk_0D = 0x80;
                ((S_818FA12C_9 *)flash_data)->unk_0C = 0x80;
                (*(Copy12 *)((u8 *)flash + 0x3A)) = D_80026680;
                ((S_818FA12C_9 *)flash_data)->unk_08 = flash + 0x3A;
            }
            impact = func_8003FC64(0x212);
            if (impact == 0) {
                goto cleanup_packet;
            }
            impact_state = impact + 0x20;
            index = 95;
            clear_cursor = impact_state + 95;
            (*(u16 *)((u8 *)impact_state + 2)) = 0x50;
            (*(u16 *)((u8 *)impact_state + 0x0A)) = 0x14;
            (*(u16 *)((u8 *)impact_state + 4)) = 0;
            (*(void * *)((u8 *)impact_state + 0x28)) = parent;
            (*(void * *)((u8 *)impact_state + 0x2C)) = ((S_818FA12C_2 *)parent)->unk_60.p2;
            (*(void * *)((u8 *)impact_state + 0x30)) = self;
            flash_state = flash + 0x20;
            (*(void * *)((u8 *)impact_state + 0x34)) = flash_state;
            ASM_USE(flash);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            for (; index >= 0; index--) {
                ((S_818FA12C_10 *)clear_cursor)->unk_38 = 0;
                clear_cursor--;
            }
            index = 96;
            (*(u16 *)((u8 *)impact_state + 0x9A)) = 0;
            (*(u32 *)((u8 *)impact + 0x10)) = (u32)D_80025398;
            func_8004491C(impact, D_80045340);
            impact_data = (*(u8 * *)((u8 *)impact + 0x0C));
            render_flags = 0x0C;
            ((S_818FA12C_8 *)impact_data)->unk_14 = render_flags;
            ((S_818FA12C_8 *)impact_data)->unk_10.s = index;
            ((S_818FA12C_8 *)impact_data)->unk_06 = 6;
            ((S_818FA12C_8 *)impact_data)->unk_14 = render_flags | 0x80;
            impact_pos = (*(s32 * *)((u8 *)impact + 8));
            impact_pos[0] = ((S_818FA12C_4 *)position)->unk_00.at00.v;
            impact_pos[1] = ((S_818FA12C_4 *)position)->unk_04.at00.v;
            impact_pos[2] = ((S_818FA12C_4 *)position)->unk_08.at00.v + 0x400000;
            impact_data = (*(u8 * *)((u8 *)impact + 0x0C));
            ((S_818FA12C_8 *)impact_data)->unk_1C = 0x2000;
            ((S_818FA12C_8 *)impact_data)->unk_1E = 0x1800;
            ((S_818FA12C_8 *)impact_data)->unk_0E = 0;
            ((S_818FA12C_8 *)impact_data)->unk_0D = 0;
            ((S_818FA12C_8 *)impact_data)->unk_0C = 0;
            (*(Copy12 *)((u8 *)impact_state + 0x1A)) = D_80026674;
            animation = impact_state + 0x1A;
            ASM_USE(impact_state);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            ((S_818FA12C_8 *)impact_data)->unk_08 = animation;
            func_800261AC();
        }

missing_target:
        (*(u16 *)((u8 *)self + 0x0A)) = 8;
        (*(u16 *)((u8 *)self + 0x82)) = 0;

cleanup_packet:
        {
            register u8 *packet ASM_REG("$9") = render_data;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ((S_818FA12C_1 *)packet)->unk_0C.at02u.v = 0;
            ((S_818FA12C_1 *)packet)->unk_0C.at01u.v = 0;
            ((S_818FA12C_1 *)packet)->unk_0C.at00p.v = 0;
            ((S_818FA12C_1 *)packet)->unk_1E.n = 0;
            ((S_818FA12C_1 *)packet)->unk_1C.n = 0;
            func_80026634();
        }

update_position:
        ((S_818FA12C_4 *)position)->unk_00.at00.v += ((S_818FA12C_4 *)position)->unk_0C;
        ((S_818FA12C_4 *)position)->unk_04.at00.v += ((S_818FA12C_4 *)position)->unk_10;
        ((S_818FA12C_4 *)position)->unk_08.at00.v += ((S_818FA12C_4 *)position)->unk_14;
        func_80026634();

    case 3:
        {
            s16 ticks;
            register u8 *flash_state ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            u8 *flash_data;
            register s32 *flash_pos ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            u8 *clear_cursor;
            s32 render_flags;
            register s32 clear_index ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

            ticks = (*(u16 *)((u8 *)self + 0x82)) + 1;
            (*(u16 *)((u8 *)self + 0x82)) = ticks;
            if ((s16)ticks != 4) {
                goto done;
            }
            impact = func_8003FC64(0x212);
            if (impact != 0) {
                flash_state = impact + 0x20;
                clear_index = 95;
                (*(void * *)((u8 *)flash_state + 0x28)) = parent;
                (*(void * *)((u8 *)flash_state + 0x2C)) = ((S_818FA12C_2 *)parent)->unk_60.p2;
                (*(void * *)((u8 *)flash_state + 0x30)) = self;
                clear_cursor = flash_state + 95;
                for (; clear_index >= 0; clear_index--) {
                    ((S_818FA12C_10 *)clear_cursor)->unk_38 = 0;
                    clear_cursor--;
                }
                (*(u16 *)((u8 *)flash_state + 0x9A)) = 0;
                (*(u32 *)((u8 *)impact + 0x10)) = (u32)D_80025648;
                func_8004491C(impact, D_80045340);
                flash_data = (*(u8 * *)((u8 *)impact + 0x0C));
                render_flags = ((S_818FA12C_8 *)flash_data)->unk_14 & 0xFFF3;
                ((S_818FA12C_8 *)flash_data)->unk_14 = render_flags;
                ((S_818FA12C_8 *)flash_data)->unk_10.u = 0x20;
                ((S_818FA12C_8 *)flash_data)->unk_14 = render_flags | 0x80;
                target_pos = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
                flash_pos = (*(s32 * *)((u8 *)impact + 8));
                flash_pos[0] = ((S_818FA12C_7 *)target_pos)->unk_00.at00.v;
                flash_pos[1] = ((S_818FA12C_7 *)target_pos)->unk_04.at00.v;
                flash_pos[2] = ((S_818FA12C_7 *)target_pos)->unk_08.at00.v;
                flash_data = (*(u8 * *)((u8 *)impact + 0x0C));
                ((S_818FA12C_8 *)flash_data)->unk_1E = 0x1000;
                ((S_818FA12C_8 *)flash_data)->unk_1C = 0x1000;
                ((S_818FA12C_8 *)flash_data)->unk_0E = 0x80;
                ((S_818FA12C_8 *)flash_data)->unk_0D = 0x80;
                ((S_818FA12C_8 *)flash_data)->unk_0C = 0x80;
                (*(Copy12 *)((u8 *)flash_state + 0x1A)) = D_80026668;
                ((S_818FA12C_8 *)flash_data)->unk_08 = flash_state + 0x1A;
                ASM_USE(flash_state);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            }
            if ((s16)(*(u16 *)((u8 *)self + 0x82)) != 4) {
                goto done;
            }
            (*(u16 *)((u8 *)self + 0x0A)) = 4;
            (*(u16 *)((u8 *)self + 0x82)) = 0;
            (*(u16 *)((u8 *)self + 0x9C)) = 0;
            func_80026634();
        }

    case 4:
        {
            s16 ticks;
            register u8 *particle ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u8 *particle_data;
            register u8 *particle_state ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            register s32 *particle_pos ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            u8 *target_data;
            s32 random_bonus;
            s32 amount;
            s32 offset_radius;
            s32 height_random;
            register s32 offset ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 fixed_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            s32 offset_sign;
            s16 effect_kind;
            s32 power_bonus;

            ticks = (*(u16 *)((u8 *)self + 0x82)) + 1;
            (*(u16 *)((u8 *)self + 0x82)) = ticks;
            if ((ticks & 3) != 0 || (s16)ticks >= 80) {
                goto case_4_tail;
            }
            particle = func_8003FC64(0x212);
            if (particle == 0) {
                goto case_4_tail;
            }
            particle_state = particle + 0x20;
            (*(u16 *)((u8 *)particle_state + 2)) = 20;
            (*(u16 *)((u8 *)particle_state + 0x0A)) = 10;
            (*(u16 *)((u8 *)particle_state + 4)) = 0;
            (*(u32 *)((u8 *)particle + 0x10)) = (u32)D_8002558C;
            func_8004491C(particle, D_80045340);
            particle_data = (*(u8 * *)((u8 *)particle + 0x0C));
            ((S_818FA12C_8 *)particle_data)->unk_10.u = 0x20;
            ((S_818FA12C_8 *)particle_data)->unk_14 |= 0x0C;
            target_pos = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
            particle_pos = (*(s32 * *)((u8 *)particle + 8));
            offset_radius = func_80069EF8();
            offset_sign = func_8002512C();
            offset_radius &= 0x1F;
            offset_radius += 16;
            offset = offset_radius * offset_sign;
            fixed_offset = offset << 16;
            particle_pos[0] = ((S_818FA12C_7 *)target_pos)->unk_00.at00.v + fixed_offset;
            offset_radius = func_80069EF8();
            offset_sign = func_8002512C();
            offset_radius &= 0x1F;
            offset_radius += 16;
            offset = offset_radius * offset_sign;
            fixed_offset = offset << 16;
            particle_pos[1] = ((S_818FA12C_7 *)target_pos)->unk_04.at00.v + fixed_offset;
            height_random = func_80069EF8();
            particle_pos[2] = ((S_818FA12C_7 *)target_pos)->unk_08.at00.v
                - (D_800DDC40[((S_818FA12C_2 *)parent)->unk_60.p[0x13]] << 15)
                - ((height_random & 0x1F) << 16);
            particle_data = (*(u8 * *)((u8 *)particle + 0x0C));
            target_data = ((S_818FA12C_16 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x14))->unk_00;
            ((S_818FA12C_8 *)particle_data)->unk_1C = ((S_818FA12C_11 *)target_data)->unk_1C >> 1;
            ((S_818FA12C_8 *)particle_data)->unk_1E = ((S_818FA12C_11 *)target_data)->unk_1E >> 1;
            ((S_818FA12C_8 *)particle_data)->unk_0E = 0;
            ((S_818FA12C_8 *)particle_data)->unk_0D = 0;
            ((S_818FA12C_8 *)particle_data)->unk_0C = 0;
            (*(Copy12 *)((u8 *)particle + 0x3A)) = D_80026668;
            ((S_818FA12C_8 *)particle_data)->unk_08 = particle + 0x3A;
            ASM_USE(particle);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

case_4_tail:
            if ((s16)(*(u16 *)((u8 *)self + 0x82)) == 80) {
                if (func_8009D218(((S_818FA12C_2 *)parent)->unk_60.p2, 4, parent) == 0) {
                    random_bonus = func_800A6D30();
                    power_bonus = (*(u8 *)((u8 *)self + 9)) >> 2;
                    random_bonus = (random_bonus & 3) + 4;
                    amount = power_bonus + random_bonus;
                    if (D_800E3D68[0] == 0xFF) {
                        effect_kind = 0xFF;
                    } else {
                        effect_kind = 16;
                    }
                    func_800C8A3C(((S_818FA12C_2 *)parent)->unk_60.p2, effect_kind, amount);
                }
            }
            if ((s16)(*(u16 *)((u8 *)self + 0x82)) < 120) {
                func_80026634();
            }
            goto state_advance;
        }

    case 5:
        {
            if ((*(s16 *)((u8 *)self + 0x9C)) == 0) {
                goto done;
            }
        }

state_advance:
        (*(u16 *)((u8 *)self + 0x0A))++;
        (*(u16 *)((u8 *)self + 0x82)) = 0;
        func_80026634();

    case 6:
        {
            s16 ticks;
            ticks = (*(u16 *)((u8 *)self + 0x82)) + 1;
            (*(u16 *)((u8 *)self + 0x82)) = ticks;
            if ((s16)ticks < 11) {
                goto done;
            }
            (*(u16 *)((u8 *)self + 0x0A)) = 8;
            (*(u16 *)((u8 *)self + 0x82)) = 30;
            func_80026634();
        }

    case 8:
        {
            s16 ticks;
            s32 effect_active;
            ticks = (*(u16 *)((u8 *)self + 0x82));
            (*(u16 *)((u8 *)self + 0x82)) = ticks + 1;
            if ((s16)(ticks + 1) < 31) {
                goto done;
            }
            effect_active = D_800266BC[0];
            (*(u16 *)((u8 *)self + 0x82)) = ticks;
            if (effect_active == 0) {
                D_8008346C[0] = 0;
                (*(u16 *)((u8 *)self + -2)) |= 0x8000;
                D_800814A0[0] |= 0x8000;
                func_80026634();
            }
            D_800266BC[0] = 0;
            goto done;
        }

    case 7:
    default:
        goto done;
    }

done:
    return;
}
