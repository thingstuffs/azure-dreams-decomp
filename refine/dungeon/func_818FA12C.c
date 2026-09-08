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

/* Updates a traveling effect, spawns impact visuals, and applies its target effect. */
void func_818FA12C(void *effect, void *motion, void *volatile render_packet)
{
    u8 *self = effect;
    u8 *position = motion;
    register u8 *parent ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *parent_header;
    u8 *source_pos;
    s16 *origin;
    OutPair offset;
    Copy24 directions;
    s32 state;

    Copy24 *direction_table;
    direction_table = &D_80024014;
    ASM_KEEP(self);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    parent = (*(u8 * *)((u8 *)self + 0));
    directions = *direction_table;
    (*(s16 *)((u8 *)self + 0x0A));
    parent_header = parent - 0x20;
    state = (*(s16 *)((u8 *)self + 0x0A));
    origin = ((S_818FA12C_0 *)parent_header)->unk_08;
    switch (state) {

    case 0:
        {
            register u8 *packet ASM_REG("$9") = render_packet;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 texture_xy;
            s32 texture_size;
            s32 copy_mode;
            u8 *palette;
            s32 state;
            ((S_818FA12C_1 *)packet)->unk_0C.at00.v = 0x00808080;
            texture_xy = 0x1400340;
            copy_mode = 0;
            ASM_KEEP(copy_mode);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            (*(Copy12 *)((u8 *)self + 0xA2)) = D_80026698;
            texture_size = 0x400040;
            palette = (u8 *)&D_800266A4;
            ((S_818FA12C_1 *)packet)->unk_08 = (u32)(self + 0xA2);
            (*(u16 *)((u8 *)self + 0x7E)) = (((S_818FA12C_2 *)parent)->unk_2A >> 9) & 7;
            ((S_818FA12C_3 *)palette)->unk_10 = 0x80;
            ((S_818FA12C_3 *)palette)->unk_11 = 0x80;
            ((S_818FA12C_3 *)palette)->unk_12 = 0x80;
            ((S_818FA12C_3 *)palette)->unk_14 = 4;
            ((S_818FA12C_3 *)palette)->unk_15 = 4;
            ((S_818FA12C_3 *)palette)->unk_16 = 4;
            offset.pair.a = texture_xy;
            offset.pair.b = texture_size;
            func_800B835C(palette, &offset.pair, 1, copy_mode);
            state = (*(u16 *)((u8 *)self + 0x0A));
            D_800266BC[0] = 1;
            (*(u16 *)((u8 *)self + 0x0A)) = state + 1;
        }

    case 1:
        {
            u8 *target;
            u8 *parent_packet;
            s32 result;
            s32 offset_z;
            s32 origin_z;
            register s32 flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 duration ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            register s32 duration_copy ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u32 target_height;
            s32 distance;
            register s32 duration_sq ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register u8 *packet ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            result = func_8003DF74(((S_818FA12C_12 *)(((S_818FA12C_0 *)parent_header)->unk_0C))->unk_08,
                ((S_818FA12C_0 *)parent_header)->unk_0C, &offset, 0);
            if (result == 0 && !(((S_818FA12C_12 *)(((S_818FA12C_0 *)parent_header)->unk_0C))->unk_14 & 0x8000)) {
                goto done;
            }
            ((S_818FA12C_4 *)position)->unk_00.at02.v = ((S_818FA12C_5 *)origin)->unk_02;
            ((S_818FA12C_4 *)position)->unk_04.at02.v = ((S_818FA12C_5 *)origin)->unk_06;
            origin_z = ((S_818FA12C_5 *)origin)->unk_0A;
            ((S_818FA12C_4 *)position)->unk_08.at02.v = origin_z;
            if (!(((S_818FA12C_12 *)(((S_818FA12C_0 *)parent_header)->unk_0C))->unk_14 & 0x8000)) {
                ((S_818FA12C_4 *)position)->unk_00.at02.v += offset.x;
                ((S_818FA12C_4 *)position)->unk_04.at02.v += offset.y;
                offset_z = ((S_818FA12C_4 *)position)->unk_08.at02.v + offset.z;
                ((S_818FA12C_4 *)position)->unk_08.at02.v = offset_z;
            } else {
                ((S_818FA12C_4 *)position)->unk_08.at02.v = origin_z - 0x40;
            }
            if (!(((S_818FA12C_13 *)((*(void * *)((u8 *)self + 4))))->unk_00 & 0x80)) {
                goto done;
            }
            if (!((*(u8 *)((u8 *)self + 0x7A)) & 4)) {
                func_8004491C(self - 0x20, D_80045340);
                packet = render_packet;
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
                source_pos = ((S_818FA12C_6 *)(target - 0x18))->unk_00;
                target_height = D_800DDC40[(*(u8 *)((u8 *)target + 0x13))];
                (*(u16 *)((u8 *)self + 0x78)) = ((S_818FA12C_7 *)source_pos)->unk_08.at02.v - (target_height >> 1);
                parent_packet = ((S_818FA12C_2_pre *)parent)[-1].unk_00;
                (*(u8 *)((u8 *)self + 0xBA)) = ((S_818FA12C_8 *)parent_packet)->unk_24
                    + D_8006CCD8[(*(s16 *)((u8 *)self + 0x7E)) * 2];
                (*(u8 *)((u8 *)self + 0xBB)) = ((S_818FA12C_8 *)parent_packet)->unk_25
                    + D_8006CCE8[(*(s16 *)((u8 *)self + 0x7E)) * 2];
                flags = (s8)((S_818FA12C_2 *)parent)->unk_72;
                if (flags != ((S_818FA12C_8 *)parent_packet)->unk_24) {
                    distance = flags - ((S_818FA12C_8 *)parent_packet)->unk_24;
                } else {
                    flags = (s8)((S_818FA12C_2 *)parent)->unk_73;
                    distance = flags - ((S_818FA12C_8 *)parent_packet)->unk_25;
                }
                if (distance < 0) {
                    distance = -distance;
                }
                (*(u8 *)((u8 *)self + 0x7B)) = distance * 2 - 1;
            } else {
                (*(u16 *)((u8 *)self + 0x78)) = ((S_818FA12C_2 *)parent)->unk_88 - 0x50;
                (*(u8 *)((u8 *)self + 0x7B)) = 0x20;
            }
            ((S_818FA12C_4 *)position)->unk_0C = (s32)directions.entries[(*(s16 *)((u8 *)self + 0x7E))].x << 16;
            ((S_818FA12C_4 *)position)->unk_10 = (u32)directions.entries[(*(s16 *)((u8 *)self + 0x7E))].y << 16;
            ((S_818FA12C_4 *)position)->unk_14 = (((s32)(*(s16 *)((u8 *)self + 0x78)) << 16) - ((S_818FA12C_4 *)position)->unk_08.at00.v)
                / (s8)(*(u8 *)((u8 *)self + 0x7B));
            (*(u16 *)((u8 *)self + 0x82)) = 0;
            (*(u16 *)((u8 *)self + 0x90)) = 0;
            (*(u16 *)((u8 *)self + 0x92)) = 0;
            (*(u16 *)((u8 *)self + 0x94)) = 5;
            (*(u16 *)((u8 *)self + 0x96)) = 200;
            (*(u16 *)((u8 *)self + 0x0A))++;
            (*(s16 *)((u8 *)self + 0x88)) = (s8)(*(u8 *)((u8 *)self + 0x7B));
            result = (*(u8 *)((u8 *)self + 0x7B)) << 24;
            ASM_KEEP_NV(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            duration = result >> 24;
            duration_copy = duration;
            ASM_KEEP_NV(duration_copy);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            duration_sq = duration * duration_copy;
            (*(s16 *)((u8 *)self + 0x8A)) = duration_sq;
            goto done;
        }

    case 2:
        {
            s32 index;
            s32 random;
            s32 collision;
            register s32 angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            s16 frame;
            s32 shrinking;
            register u8 *burst ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register u8 *glow ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u8 *glow_data;
            register u8 *effect_data ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            void *glow_data_ptr;
            void *texture;
            register s32 render_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u8 *burst_packet;
            register s32 *effect_pos ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            u8 *clear_ptr;

            index = 0;
            do {
                u8 *emitter;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                s32 direction;
                s32 color;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                s32 brightness;
                random = func_80069EF8();
                emitter = self - 0x20;
                color = 0x40E020;
                brightness = (random & 0xFF) | 0x80;
                direction = (*(s16 *)((u8 *)self + 0x7E));
                func_80025228(emitter, direction, color, brightness, 0, 0, 0);
                index++;
            } while (index < 8);
            collision = func_800A4778(((S_818FA12C_4 *)position)->unk_00.at02.v, ((S_818FA12C_4 *)position)->unk_04.at02.v,
                ((S_818FA12C_4 *)position)->unk_08.at02u.v, ((S_818FA12C_2 *)parent)->unk_60.p2);
            if (collision << 16) {
                register u8 *packet ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                (*(u16 *)((u8 *)self + 0x0A)) = 8;
                (*(u16 *)((u8 *)self + 0x82)) = 0;
                packet = render_packet;
                ((S_818FA12C_1 *)packet)->unk_0C.at02u.v = 0;
                ((S_818FA12C_1 *)packet)->unk_0C.at01u.v = 0;
                ((S_818FA12C_1 *)packet)->unk_0C.at00p.v = 0;
                goto done;
            }
            {
                register u8 *packet ASM_REG("$9") = render_packet;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
                    ((S_818FA12C_1 *)packet)->unk_1E.n = scale_y;
                } else {
                    packet = render_packet;
                    ((S_818FA12C_1 *)packet)->unk_1C.n -= (*(u16 *)((u8 *)self + 0x96));
                    ((S_818FA12C_1 *)packet)->unk_1E.n -= (*(u16 *)((u8 *)self + 0x96));
                }
            }
            frame = (*(s16 *)((u8 *)self + 0x92)) + 1;
            (*(s16 *)((u8 *)self + 0x92)) = frame;
            if (frame >= (*(s16 *)((u8 *)self + 0x94))) {
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
            source_pos = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
            ((S_818FA12C_4 *)position)->unk_00.at02.v = ((S_818FA12C_7 *)source_pos)->unk_00.at02.v;
            ((S_818FA12C_4 *)position)->unk_04.at02.v = ((S_818FA12C_7 *)source_pos)->unk_04.at02.v;
            ((S_818FA12C_4 *)position)->unk_08.at02.v = ((S_818FA12C_7 *)source_pos)->unk_08.at02.v - D_800DDC40[((S_818FA12C_15 *)(((S_818FA12C_2 *)parent)->unk_60.p))->unk_13];
            func_800A56E0(0x300);
            glow = func_8003FC64(0x212);
            if (glow != 0) {
                (*(u16 *)((u8 *)glow + 0x22)) = 120;
                (*(u32 *)((u8 *)glow + 0x10)) = (u32)D_80025348;
                func_8004491C(glow, D_80045340);
                glow_data = (*(u8 * *)((u8 *)glow + 0x0C));
                ((S_818FA12C_9 *)glow_data)->unk_14 |= 0x0C;
                ((S_818FA12C_9 *)glow_data)->unk_10 = 0;
                ((S_818FA12C_9 *)glow_data)->unk_06 = 0;
                ((S_818FA12C_9 *)glow_data)->unk_14 |= 0x80;
                source_pos = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
                effect_pos = (*(s32 * *)((u8 *)glow + 8));
                effect_pos[0] = ((S_818FA12C_7 *)source_pos)->unk_00.at00.v;
                effect_pos[1] = ((S_818FA12C_7 *)source_pos)->unk_04.at00.v;
                effect_pos[2] = ((S_818FA12C_7 *)source_pos)->unk_08.at00.v;
                glow_data = (*(u8 * *)((u8 *)glow + 0x0C));
                ((S_818FA12C_9 *)glow_data)->unk_1E = 0x1000;
                ((S_818FA12C_9 *)glow_data)->unk_1C = 0x1000;
                ((S_818FA12C_9 *)glow_data)->unk_0E = 0x80;
                ((S_818FA12C_9 *)glow_data)->unk_0D = 0x80;
                ((S_818FA12C_9 *)glow_data)->unk_0C = 0x80;
                (*(Copy12 *)((u8 *)glow + 0x3A)) = D_80026680;
                ((S_818FA12C_9 *)glow_data)->unk_08 = glow + 0x3A;
            }
            burst = func_8003FC64(0x212);
            if (burst == 0) {
                goto cleanup_packet;
            }
            effect_data = burst + 0x20;
            index = 95;
            clear_ptr = effect_data + 95;
            (*(u16 *)((u8 *)effect_data + 2)) = 0x50;
            (*(u16 *)((u8 *)effect_data + 0x0A)) = 0x14;
            (*(u16 *)((u8 *)effect_data + 4)) = 0;
            (*(void * *)((u8 *)effect_data + 0x28)) = parent;
            (*(void * *)((u8 *)effect_data + 0x2C)) = ((S_818FA12C_2 *)parent)->unk_60.p2;
            (*(void * *)((u8 *)effect_data + 0x30)) = self;
            glow_data_ptr = glow + 0x20;
            (*(void * *)((u8 *)effect_data + 0x34)) = glow_data_ptr;
            ASM_USE(glow);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            for (; index >= 0; index--) {
                ((S_818FA12C_10 *)clear_ptr)->unk_38 = 0;
                clear_ptr--;
            }
            index = 96;
            (*(u16 *)((u8 *)effect_data + 0x9A)) = 0;
            (*(u32 *)((u8 *)burst + 0x10)) = (u32)D_80025398;
            func_8004491C(burst, D_80045340);
            burst_packet = (*(u8 * *)((u8 *)burst + 0x0C));
            render_flags = 0x0C;
            ((S_818FA12C_8 *)burst_packet)->unk_14 = render_flags;
            ((S_818FA12C_8 *)burst_packet)->unk_10.s = index;
            ((S_818FA12C_8 *)burst_packet)->unk_06 = 6;
            ((S_818FA12C_8 *)burst_packet)->unk_14 = render_flags | 0x80;
            effect_pos = (*(s32 * *)((u8 *)burst + 8));
            effect_pos[0] = ((S_818FA12C_4 *)position)->unk_00.at00.v;
            effect_pos[1] = ((S_818FA12C_4 *)position)->unk_04.at00.v;
            effect_pos[2] = ((S_818FA12C_4 *)position)->unk_08.at00.v + 0x400000;
            burst_packet = (*(u8 * *)((u8 *)burst + 0x0C));
            ((S_818FA12C_8 *)burst_packet)->unk_1C = 0x2000;
            ((S_818FA12C_8 *)burst_packet)->unk_1E = 0x1800;
            ((S_818FA12C_8 *)burst_packet)->unk_0E = 0;
            ((S_818FA12C_8 *)burst_packet)->unk_0D = 0;
            ((S_818FA12C_8 *)burst_packet)->unk_0C = 0;
            (*(Copy12 *)((u8 *)effect_data + 0x1A)) = D_80026674;
            texture = effect_data + 0x1A;
            ASM_USE(effect_data);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            ((S_818FA12C_8 *)burst_packet)->unk_08 = texture;
            goto cleanup_packet;
        }

    missing_target:
        (*(u16 *)((u8 *)self + 0x0A)) = 8;
        (*(u16 *)((u8 *)self + 0x82)) = 0;

    cleanup_packet:
        {
            register u8 *packet ASM_REG("$9") = render_packet;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ((S_818FA12C_1 *)packet)->unk_0C.at02u.v = 0;
            ((S_818FA12C_1 *)packet)->unk_0C.at01u.v = 0;
            ((S_818FA12C_1 *)packet)->unk_0C.at00p.v = 0;
            ((S_818FA12C_1 *)packet)->unk_1E.n = 0;
            ((S_818FA12C_1 *)packet)->unk_1C.n = 0;
            goto done;
        }

    update_position:
        ((S_818FA12C_4 *)position)->unk_00.at00.v += ((S_818FA12C_4 *)position)->unk_0C;
        ((S_818FA12C_4 *)position)->unk_04.at00.v += ((S_818FA12C_4 *)position)->unk_10;
        ((S_818FA12C_4 *)position)->unk_08.at00.v += ((S_818FA12C_4 *)position)->unk_14;
        goto done;

    case 3:
        {
            s16 frame;
            u8 *flash;
            register u8 *effect_data ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            u8 *flash_packet;
            register s32 *effect_pos ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            u8 *clear_ptr;
            s32 render_flags;
            register s32 index ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

            frame = (*(u16 *)((u8 *)self + 0x82)) + 1;
            (*(u16 *)((u8 *)self + 0x82)) = frame;
            if ((s16)frame != 4) {
                goto done;
            }
            flash = func_8003FC64(0x212);
            if (flash != 0) {
                effect_data = flash + 0x20;
                index = 95;
                (*(void * *)((u8 *)effect_data + 0x28)) = parent;
                (*(void * *)((u8 *)effect_data + 0x2C)) = ((S_818FA12C_2 *)parent)->unk_60.p2;
                (*(void * *)((u8 *)effect_data + 0x30)) = self;
                clear_ptr = effect_data + 95;
                for (; index >= 0; index--) {
                    ((S_818FA12C_10 *)clear_ptr)->unk_38 = 0;
                    clear_ptr--;
                }
                (*(u16 *)((u8 *)effect_data + 0x9A)) = 0;
                (*(u32 *)((u8 *)flash + 0x10)) = (u32)D_80025648;
                func_8004491C(flash, D_80045340);
                flash_packet = (*(u8 * *)((u8 *)flash + 0x0C));
                render_flags = ((S_818FA12C_8 *)flash_packet)->unk_14 & 0xFFF3;
                ((S_818FA12C_8 *)flash_packet)->unk_14 = render_flags;
                ((S_818FA12C_8 *)flash_packet)->unk_10.u = 0x20;
                ((S_818FA12C_8 *)flash_packet)->unk_14 = render_flags | 0x80;
                source_pos = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
                effect_pos = (*(s32 * *)((u8 *)flash + 8));
                effect_pos[0] = ((S_818FA12C_7 *)source_pos)->unk_00.at00.v;
                effect_pos[1] = ((S_818FA12C_7 *)source_pos)->unk_04.at00.v;
                effect_pos[2] = ((S_818FA12C_7 *)source_pos)->unk_08.at00.v;
                flash_packet = (*(u8 * *)((u8 *)flash + 0x0C));
                ((S_818FA12C_8 *)flash_packet)->unk_1E = 0x1000;
                ((S_818FA12C_8 *)flash_packet)->unk_1C = 0x1000;
                ((S_818FA12C_8 *)flash_packet)->unk_0E = 0x80;
                ((S_818FA12C_8 *)flash_packet)->unk_0D = 0x80;
                ((S_818FA12C_8 *)flash_packet)->unk_0C = 0x80;
                (*(Copy12 *)((u8 *)effect_data + 0x1A)) = D_80026668;
                ((S_818FA12C_8 *)flash_packet)->unk_08 = effect_data + 0x1A;
                ASM_USE(effect_data);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            }
            if ((s16)(*(u16 *)((u8 *)self + 0x82)) != 4) {
                goto done;
            }
            (*(u16 *)((u8 *)self + 0x0A)) = 4;
            (*(u16 *)((u8 *)self + 0x82)) = 0;
            (*(u16 *)((u8 *)self + 0x9C)) = 0;
            goto done;
        }

    case 4:
        {
            s16 frame;
            register u8 *particle ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u8 *particle_packet;
            register u8 *effect_data ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            register s32 *effect_pos ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            u8 *target_packet;
            s32 random_bonus;
            s32 amount;
            s32 random;
            s32 height_random;
            register s32 offset_pixels ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 fixed_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            s32 strength;
            s16 effect_kind;

            frame = (*(u16 *)((u8 *)self + 0x82)) + 1;
            (*(u16 *)((u8 *)self + 0x82)) = frame;
            if ((frame & 3) != 0 || (s16)frame >= 80) {
                goto case_4_tail;
            }
            particle = func_8003FC64(0x212);
            if (particle == 0) {
                goto case_4_tail;
            }
            effect_data = particle + 0x20;
            (*(u16 *)((u8 *)effect_data + 2)) = 20;
            (*(u16 *)((u8 *)effect_data + 0x0A)) = 10;
            (*(u16 *)((u8 *)effect_data + 4)) = 0;
            (*(u32 *)((u8 *)particle + 0x10)) = (u32)D_8002558C;
            func_8004491C(particle, D_80045340);
            particle_packet = (*(u8 * *)((u8 *)particle + 0x0C));
            ((S_818FA12C_8 *)particle_packet)->unk_10.u = 0x20;
            ((S_818FA12C_8 *)particle_packet)->unk_14 |= 0x0C;
            source_pos = ((S_818FA12C_14 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x18))->unk_00;
            effect_pos = (*(s32 * *)((u8 *)particle + 8));
            random = func_80069EF8();
            strength = func_8002512C();
            random &= 0x1F;
            random += 16;
            offset_pixels = random * strength;
            fixed_offset = offset_pixels << 16;
            effect_pos[0] = ((S_818FA12C_7 *)source_pos)->unk_00.at00.v + fixed_offset;
            random = func_80069EF8();
            strength = func_8002512C();
            random &= 0x1F;
            random += 16;
            offset_pixels = random * strength;
            fixed_offset = offset_pixels << 16;
            effect_pos[1] = ((S_818FA12C_7 *)source_pos)->unk_04.at00.v + fixed_offset;
            height_random = func_80069EF8();
            effect_pos[2] = ((S_818FA12C_7 *)source_pos)->unk_08.at00.v
                - (D_800DDC40[((S_818FA12C_2 *)parent)->unk_60.p[0x13]] << 15)
                - ((height_random & 0x1F) << 16);
            particle_packet = (*(u8 * *)((u8 *)particle + 0x0C));
            target_packet = ((S_818FA12C_16 *)(((S_818FA12C_2 *)parent)->unk_60.p - 0x14))->unk_00;
            ((S_818FA12C_8 *)particle_packet)->unk_1C = ((S_818FA12C_11 *)target_packet)->unk_1C >> 1;
            ((S_818FA12C_8 *)particle_packet)->unk_1E = ((S_818FA12C_11 *)target_packet)->unk_1E >> 1;
            ((S_818FA12C_8 *)particle_packet)->unk_0E = 0;
            ((S_818FA12C_8 *)particle_packet)->unk_0D = 0;
            ((S_818FA12C_8 *)particle_packet)->unk_0C = 0;
            (*(Copy12 *)((u8 *)particle + 0x3A)) = D_80026668;
            ((S_818FA12C_8 *)particle_packet)->unk_08 = particle + 0x3A;
            ASM_USE(particle);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        case_4_tail:
            if ((s16)(*(u16 *)((u8 *)self + 0x82)) == 80) {
                if (func_8009D218(((S_818FA12C_2 *)parent)->unk_60.p2, 4, parent) == 0) {
                    random_bonus = func_800A6D30();
                    strength = (*(u8 *)((u8 *)self + 9)) >> 2;
                    random_bonus = (random_bonus & 3) + 4;
                    amount = strength + random_bonus;
                    if (D_800E3D68[0] == 0xFF) {
                        effect_kind = 0xFF;
                    } else {
                        effect_kind = 16;
                    }
                    func_800C8A3C(((S_818FA12C_2 *)parent)->unk_60.p2, effect_kind, amount);
                }
            }
            if ((s16)(*(u16 *)((u8 *)self + 0x82)) < 120) {
                goto done;
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
        goto done;

    case 6:
        {
            s16 frame;
            frame = (*(u16 *)((u8 *)self + 0x82)) + 1;
            (*(u16 *)((u8 *)self + 0x82)) = frame;
            if ((s16)frame < 11) {
                goto done;
            }
            (*(u16 *)((u8 *)self + 0x0A)) = 8;
            (*(u16 *)((u8 *)self + 0x82)) = 30;
            goto done;
        }

    case 8:
        {
            s16 frame;
            s32 active;
            frame = (*(u16 *)((u8 *)self + 0x82));
            (*(u16 *)((u8 *)self + 0x82)) = frame + 1;
            if ((s16)(frame + 1) < 31) {
                goto done;
            }
            active = D_800266BC[0];
            (*(u16 *)((u8 *)self + 0x82)) = frame;
            if (active == 0) {
                D_8008346C[0] = 0;
                (*(u16 *)((u8 *)self + -2)) |= 0x8000;
                D_800814A0[0] |= 0x8000;
                goto done;
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
