#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_FUNC_8197C800_BODY_0_pre {
    u16 unk_00;
} S_FUNC_8197C800_BODY_0_pre;   /* the 0x2 bytes before arg0 in func_8002401C, addressed as arg0[-1] */

typedef struct S_FUNC_8197C800_BODY_0 {
    void * unk_00;
    void * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x44];
    union { u16 s; s16 u; } unk_50;   /* accessed as both */
    union { s16 s; u16 u; } unk_52;   /* accessed as both */
} S_FUNC_8197C800_BODY_0;   /* arg0 in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_1 {
    u8 pad_00[0x60];
    void * unk_60;
    u8 pad_64[0x90];
    s32 unk_F4;
} S_FUNC_8197C800_BODY_1;   /* D_800814A8[0] in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_2;   /* arg1 in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_FUNC_8197C800_BODY_3;   /* root in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_4 {
    u8 pad_00[0xA6];
    u16 unk_A6;
    u8 unk_A8;
} S_FUNC_8197C800_BODY_4;   /* segment in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_FUNC_8197C800_BODY_5;   /* obj in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_6;   /* src_position in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_7;   /* dst_position in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_8 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    void * unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_FUNC_8197C800_BODY_8;   /* node in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_FUNC_8197C800_BODY_9;   /* D_800DEDB0 in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_10 {
    u8 pad_00[0x4C];
    u16 unk_4C;
} S_FUNC_8197C800_BODY_10;   /* tail in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_13 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_FUNC_8197C800_BODY_13;   /* image0 in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_14 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_FUNC_8197C800_BODY_14;   /* position in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_15 {
    u8 pad_00[0x4];
    void * unk_04;
} S_FUNC_8197C800_BODY_15;   /* template in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_17 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_FUNC_8197C800_BODY_17;   /* image in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_18 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_FUNC_8197C800_BODY_18;   /* base in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_19 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u32 unk_0C;
} S_FUNC_8197C800_BODY_19;   /* status in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_20 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_FUNC_8197C800_BODY_20;   /* ((S_FUNC_8197C800_BODY_3 *)root)->unk_08 in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_21 {
    u16 unk_00;
} S_FUNC_8197C800_BODY_21;   /* ((S_FUNC_8197C800_BODY_0 *)arg0)->unk_04 in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_22 {
    u8 pad_00[0x8];
    void * unk_08;
} S_FUNC_8197C800_BODY_22;   /* ((S_FUNC_8197C800_BODY_3 *)root)->unk_0C in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_23 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_FUNC_8197C800_BODY_23;   /* D_800814A8[0] in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_24 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_FUNC_8197C800_BODY_24;   /* D_800814A8[0] in func_8002401C */

typedef struct S_FUNC_8197C800_BODY_25 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_FUNC_8197C800_BODY_25;   /* ((S_FUNC_8197C800_BODY_5 *)obj)->unk_08 in func_8002401C */



extern void *D_800814A8[];
extern u32 D_800246C0[];
extern u8 D_80024BB8[];
extern u8 D_80024C68[];
extern u8 D_800DEDB0[];
extern u8 D_800DE9D0[];
extern u8 D_800DEC00[];

extern void *func_8003FD64(s32, void *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern s16 func_800BCB04(u16, u16, s16);
extern s32 func_80069EF8(void);
extern void func_8009CE1C(void *, s32, s32, s32, s16, void *, s32);

static __inline__ s32 jitter_coordinate_64(s32 grid, s32 random)
{
    return (grid << 6) + random % 64;
}

static __inline__ s32 jitter_coordinate_32(s32 grid, s32 random)
{
    s32 scaled = grid << 6;
    s32 jitter = random % 32 + 16;

    return scaled + jitter;
}

void func_8002401C(void *input, void *output);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const module_entry)(void *, void *) __asm__("func_80024000") = func_8002401C;

/* Updates a timed effect, spawns particles, and completes its owner's action. */
void func_8002401C(void *input, void *output)
{
    s16 offsets[3];
    s32 state;
    void *owner_data;
    void *owner;
    void *particle_script;
    S_FUNC_8197C800_BODY_4 *scene;
    void *particle;
    S_FUNC_8197C800_BODY_8 *sprite;
    S_FUNC_8197C800_BODY_6 *src_position;
    S_FUNC_8197C800_BODY_7 *dst_position;
    S_FUNC_8197C800_BODY_7 *dst_position_3;
    S_FUNC_8197C800_BODY_7 *dst_position_2;
    void *particle_data;
    s32 remaining;
    register s32 result ASM_REG("$2");
    void *particle_script_debris;
    TileObject *debris_origin;
    s32 height;
    s32 offset_index;
    s32 random_value;
    u16 angle;
    u16 tail_state;
    u16 tail_timer;
    TileObject *burst_origin;
    u16 timer;

    timer = ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.s;
    owner_data = ((S_FUNC_8197C800_BODY_0 *)input)->unk_00;
    state = ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.s;
    timer -= 1;
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.s = timer;
    owner = (u8 *)owner_data - 0x20;

    switch (state) {
    case 0:
    ((S_FUNC_8197C800_BODY_1 *)(D_800814A8[0]))->unk_F4 = 0;
    ((S_FUNC_8197C800_BODY_2 *)output)->unk_00 =
        ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_08))->unk_00;
    ((S_FUNC_8197C800_BODY_2 *)output)->unk_04 =
        ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_08))->unk_04;
    ((S_FUNC_8197C800_BODY_2 *)output)->unk_08 =
        ((S_FUNC_8197C800_BODY_20 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_08))->unk_08;
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u += 1;

    case 1:
    if (!(((S_FUNC_8197C800_BODY_21 *)(((S_FUNC_8197C800_BODY_0 *)input)->unk_04))->unk_00 & 0x80)) {
        return;
    }

    scene = D_800814A8[0];
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.s = 10;
    scene->unk_A6 -= 1;
    scene->unk_A8 = ((S_FUNC_8197C800_BODY_0 *)input)->unk_08;
    particle = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
    if (particle != 0) {
        if (func_8003DE58(((S_FUNC_8197C800_BODY_22 *)(((S_FUNC_8197C800_BODY_3 *)owner)->unk_0C))->unk_08,
                          ((S_FUNC_8197C800_BODY_3 *)owner)->unk_0C, offsets, 0) == 0) {
            offsets[2] = 0;
            offsets[1] = 0;
            offsets[0] = 0;
        }
        particle_data = (u8 *)particle + 0x20;
        ((S_FUNC_8197C800_BODY_5 *)particle)->unk_10 = D_800246C0;
        func_8004491C(particle, func_80045340);
        random_value = 0x00800000u;
        sprite = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_0C;
        offset_index = offsets[0];
        src_position = ((S_FUNC_8197C800_BODY_3 *)owner)->unk_08;
        dst_position_2 = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
        result = src_position->unk_00 + (offset_index << 16);
        ((S_FUNC_8197C800_BODY_2 *)output)->unk_00 = result;
        dst_position_2->unk_00 = result;
        offset_index = offsets[1];
        src_position = ((S_FUNC_8197C800_BODY_3 *)owner)->unk_08;
        dst_position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
        result = src_position->unk_04 + (offset_index << 16);
        ((S_FUNC_8197C800_BODY_2 *)output)->unk_04 = result;
        dst_position->unk_04 = result;
        offset_index = offsets[2];
        src_position = ((S_FUNC_8197C800_BODY_3 *)owner)->unk_08;
        dst_position_3 = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
        result = src_position->unk_08 + (offset_index << 16);
        ((S_FUNC_8197C800_BODY_2 *)output)->unk_08 = result;
        dst_position_3->unk_08 = result;
        sprite->unk_1E = 0x800;
        sprite->unk_1C = 0x800;
        sprite->unk_10 = 0x20;
        sprite->unk_00 = D_800DEDB0;
        sprite->unk_14 |= 0xC;
        sprite->unk_08 = ((S_FUNC_8197C800_BODY_9 *)D_800DEDB0)->unk_04;
        random_value |= 0x8080u;
        sprite->unk_04 = 0;
        sprite->unk_05 = 0;
        sprite->unk_0C = (void *)random_value;
        ((S_FUNC_8197C800_BODY_5 *)particle)->unk_20 = input;
        ((S_FUNC_8197C800_BODY_10 *)particle_data)->unk_4C = 0;
        goto case_one_tail;
    }
case_one_tail:
    tail_state = ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u + 1;

    goto store_state;

    case 2:
    if (((S_FUNC_8197C800_BODY_0 *)input)->unk_50.u > 0) {
        return;
    }
    result = func_80053EF0(4);
    if (result != 2) {
        func_800A56E0(0x300);
    } else {
        func_800A56E0(0x4300);
    }
    tail_state = ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u;

    tail_timer = 16;

    goto store_timer;

    case 3:
    if (((S_FUNC_8197C800_BODY_0 *)input)->unk_50.u < 3) {
        remaining = 1;
        height = func_800BCB04(D_80083780.x.w.i, D_80083780.y.w.i, (s16)(D_80083780.z.w.i - 0x80));
        particle_script = D_80024BB8;
        burst_origin = &D_80082E80;
        do {
            particle = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
            if (particle != 0) {
                ((S_FUNC_8197C800_BODY_5 *)particle)->unk_10 = particle_script;
                func_8004491C(particle, func_80045340);
                sprite = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_0C;
                particle_data = (u8 *)particle + 0x20;
                random_value = func_80069EF8();
                angle = ((S_FUNC_8197C800_BODY_23 *)(D_800814A8[0]))->unk_2A;
                offset_index = (s16)angle >> 9;
                result = (s32)(dirStepX);
                {
                    s32 grid_coord;
                    void *position;
                    grid_coord = burst_origin->tileX + ((s16 *)result)[offset_index];
                    position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
                    result = jitter_coordinate_32(grid_coord, random_value);
                    ((S_FUNC_8197C800_BODY_14 *)position)->unk_02 = result;
                }
                random_value = func_80069EF8();
                angle = ((S_FUNC_8197C800_BODY_23 *)(D_800814A8[0]))->unk_2A;
                offset_index = (s16)angle >> 9;
                result = (s32)(dirStepY);
                {
                    s32 grid_coord;
                    void *position;
                    grid_coord = burst_origin->tileY + ((s16 *)result)[offset_index];
                    position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
                    result = jitter_coordinate_32(grid_coord, random_value);
                    ((S_FUNC_8197C800_BODY_14 *)position)->unk_06 = result;
                }
                {
                    u32 color;
                    void *sprite_template = 0;
                    void *position;
                    color = 0x00600000u;
                    position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
                    sprite_template = D_800DE9D0;
                    ((S_FUNC_8197C800_BODY_14 *)position)->unk_0A = height;
                    sprite->unk_1C = 0x1800;
                    sprite->unk_1E = 0x2000;
                    sprite->unk_10 = 0x60;
                    {
                        u16 flags;
                        flags = sprite->unk_14;
                        sprite->unk_00 = sprite_template;
                        flags |= 0xC;
                        sprite->unk_14 = flags;
                        sprite->unk_08 = ((S_FUNC_8197C800_BODY_15 *)sprite_template)->unk_04;
                    }
                    sprite->unk_04 = 0;
                    sprite->unk_05 = 0;
                    sprite->unk_0C = (void *)(color | 0x6060u);
                    ((S_FUNC_8197C800_BODY_5 *)particle)->unk_20 = input;
                    ((S_FUNC_8197C800_BODY_10 *)particle_data)->unk_4C = 0;
                }
            }
            remaining -= 1;
        } while (remaining >= 0);

        remaining = 9;
        particle_script_debris = D_80024C68;
        debris_origin = &D_80082E80;
        do {
            particle = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
            if (particle != 0) {
                ((S_FUNC_8197C800_BODY_5 *)particle)->unk_10 = particle_script_debris;
                func_8004491C(particle, func_80045340);
                sprite = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_0C;
                particle_data = (u8 *)particle + 0x20;
                random_value = func_80069EF8();
                angle = ((S_FUNC_8197C800_BODY_24 *)(D_800814A8[0]))->unk_2A;
                offset_index = (s16)angle >> 9;
                result = (s32)(dirStepX);
                {
                    s32 grid_coord;
                    void *position;
                    grid_coord = debris_origin->tileX + ((s16 *)result)[offset_index];
                    position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
                    result = jitter_coordinate_64(grid_coord, random_value);
                    ((S_FUNC_8197C800_BODY_14 *)position)->unk_02 = result;
                }
                random_value = func_80069EF8();
                angle = ((S_FUNC_8197C800_BODY_24 *)(D_800814A8[0]))->unk_2A;
                offset_index = (s16)angle >> 9;
                result = (s32)(dirStepY);
                {
                    s32 grid_coord;
                    void *position;
                    grid_coord = debris_origin->tileY + ((s16 *)result)[offset_index];
                    position = ((S_FUNC_8197C800_BODY_5 *)particle)->unk_08;
                    result = jitter_coordinate_64(grid_coord, random_value);
                    ((S_FUNC_8197C800_BODY_14 *)position)->unk_06 = result;
                }
                result = func_80069EF8();
                ((S_FUNC_8197C800_BODY_25 *)(((S_FUNC_8197C800_BODY_5 *)particle)->unk_08))->unk_0A =
                    height - (result & 0x1F);
                result = func_80069EF8();
                {
                    u32 color;
                    void *sprite_template = 0;
                    color = 0x00100000u;
                    ((S_FUNC_8197C800_BODY_25 *)(((S_FUNC_8197C800_BODY_5 *)particle)->unk_08))->unk_14 =
                        (s32)0xFFE60000 - (result << 2);
                    sprite->unk_1E = 0x800;
                    sprite->unk_1C = 0x800;
                    sprite->unk_10 = 0x20;
                    {
                        u16 flags;
                        flags = sprite->unk_14;
                        sprite_template = D_800DEC00;
                        sprite->unk_00 = sprite_template;
                        flags |= 0xC;
                        sprite->unk_14 = flags;
                        sprite->unk_08 = ((S_FUNC_8197C800_BODY_15 *)sprite_template)->unk_04;
                    }
                    sprite->unk_04 = 0;
                    sprite->unk_05 = 0;
                    sprite->unk_0C = (void *)(color | 0x1010u);
                    ((S_FUNC_8197C800_BODY_5 *)particle)->unk_20 = input;
                    ((S_FUNC_8197C800_BODY_10 *)particle_data)->unk_4C = 0;
                }
            }
            remaining -= 1;
        } while (remaining >= 0);
    }
    if (((S_FUNC_8197C800_BODY_0 *)input)->unk_50.u > 0) {
        return;
    }
    tail_timer = 32;
    tail_state = ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u;
store_timer:
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.s = tail_timer;
    tail_state += 1;
store_state:
    ((S_FUNC_8197C800_BODY_0 *)input)->unk_0A.u = tail_state;
    return;

    case 4:
    if (!(D_80082E80.unk_014 & 0x8000) && ((S_FUNC_8197C800_BODY_0 *)input)->unk_50.u >= 0) {
        return;
    }
    if (((S_FUNC_8197C800_BODY_0 *)input)->unk_52.s & 0x8000) {
        ((S_FUNC_8197C800_BODY_0 *)input)->unk_52.u &= 0x7FFF;
        return;
    }
    func_8009CE1C(((S_FUNC_8197C800_BODY_1 *)(D_800814A8[0]))->unk_60, 8,
                  ((S_FUNC_8197C800_BODY_0 *)input)->unk_09, 10,
                  ((S_FUNC_8197C800_BODY_18 *)owner_data)->unk_2A, owner_data, 2);
    dungeonStatus.unk_0C = 0;
    dungeonStatus.unk_0A -= 1;
    ((S_FUNC_8197C800_BODY_0_pre *)input)[-1].unk_00 |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
    }
}
