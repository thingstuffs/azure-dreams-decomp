#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_source.h"

typedef struct S_81844800_0_pre {
    u16 unk_00;
} S_81844800_0_pre;   /* the 0x2 bytes before arg0 in func_80024020, addressed as arg0[-1] */

typedef struct S_81844800_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x44];
    union { u16 s; s16 u; } unk_50;   /* accessed as both */
    union { u16 s; s16 u; } unk_52;   /* accessed as both */
} S_81844800_0;   /* arg0 in func_80024020 */

typedef struct S_81844800_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_81844800_1_pre;   /* the 0x14 bytes before root in func_80024020, addressed as root[-1] */

typedef struct S_81844800_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_81844800_1;   /* root in func_80024020 */

typedef struct S_81844800_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81844800_2;   /* object in func_80024020 */

typedef struct S_81844800_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_81844800_3;   /* arg1_reg in func_80024020 */

typedef struct S_81844800_4 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_81844800_4;   /* render in func_80024020 */

typedef struct S_81844800_5 {
    u8 pad_00[0x4];
    u32 unk_04;
} S_81844800_5;   /* s8_page in func_80024020 */

typedef struct S_81844800_6 {
    u8 pad_00[0x48];
    u16 unk_48;
    u16 unk_4A;
    u16 unk_4C;
} S_81844800_6;   /* part in func_80024020 */

typedef struct S_81844800_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_81844800_7;   /* info in func_80024020 */

typedef struct S_81844800_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_81844800_8_pre;   /* the 0x14 bytes before created in func_80024020, addressed as created[-1] */

typedef struct S_81844800_9 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81844800_9;   /* arg2_reg in func_80024020 */

typedef struct S_81844800_10 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_81844800_10;   /* base_before in func_80024020 */

typedef struct S_81844800_11 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81844800_11;   /* base_after in func_80024020 */

typedef struct S_81844800_12 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x20];
    u16 unk_2A;
    u16 unk_2C;
} S_81844800_12;   /* initial_part in func_80024020 */


typedef struct S_81844800_14 {
    union { s32 * s; s32 u; } unk_00;   /* accessed as both */
    union { s32 * s; s32 u; } unk_04;   /* accessed as both */
    union { struct { s32 * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_81844800_14;   /* ((S_81844800_2 *)object)->unk_08 in func_80024020 */

typedef struct S_81844800_15 {
    u16 unk_00;
} S_81844800_15;   /* ((S_81844800_0 *)arg0)->unk_04 in func_80024020 */

typedef struct S_81844800_16 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81844800_16;   /* ((S_81844800_10 *)base_before)->unk_0C in func_80024020 */

typedef struct S_81844800_17 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81844800_17;   /* ((S_81844800_11 *)base_after)->unk_08 in func_80024020 */


typedef struct Vec3 {
    s16 x;
    s16 y;
    s16 z;
} Vec3;


extern u8 D_800DEA68[];
extern u8 D_800DECF8[];


extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern s32 func_800A3820(s16 entry_index);
extern void *func_800A05A4(void *, u8, u8, s16, s16);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
extern void *func_8003DE58(void *, void *, Vec3 *, s32);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_800A56E0(s32);
extern void func_8004491C(void *, void *);

extern void func_80024C84(void);
extern void func_80024868(void);
extern void func_8002472C(void);


static __inline__ s16 delta_axis(s8 target, u16 start) {
    s32 t = target;
    t <<= 6;
    start -= 32;
    return t - start;
}
void func_80024020(void *effect, void *motion, void *source_render);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const module_entry)(void *, void *, void *) __asm__("func_80024000") = func_80024020;

/* Updates a staged effect, moves it toward its target, and emits particles. */
void func_80024020(void *effect, void *motion, void *source_render) {
    void *owner;
    Vec3 delta;
    s32 target_timer;
    void *owner_start;
    void *owner_sprite;
    void *spawned;
    void *particle_data;
    void *sprite;
    s32 particles_left;
    S_81844800_5 *sprite_page;
    s16 state;
    s16 state_2;

    owner = ((S_81844800_0 *)effect)->unk_00;
    {
        owner_start = (u8 *)owner - 0x20;
    }
    state = ((S_81844800_0 *)effect)->unk_0A.s;
    owner_sprite = ((S_81844800_1_pre *)owner)[-1].unk_00;
    if (state != 0) {
        if (state < 5) {
            particles_left = 12;
            sprite_page = D_800DEA68;
            do {
                spawned = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
                if (spawned != 0) {
                    particle_data = (u8 *)spawned + 0x20;
                    sprite = ((S_81844800_2 *)spawned)->unk_0C;
                    ((S_81844800_2 *)spawned)->unk_10 = func_80024C84;
                    ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_00.s =
                        ((S_81844800_3 *)motion)->unk_00.at00.v + (((func_80069EF8() & 0x1FF) - 255) << 13);
                    ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_04.s =
                        ((S_81844800_3 *)motion)->unk_04.at00.v + (((func_80069EF8() & 0x1FF) - 255) << 13);
                    ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_08.at00.v =
                        ((S_81844800_3 *)motion)->unk_08.at00.v + (((func_80069EF8() & 0x1FF) - 255) << 10);

                    {
                        u16 flags = ((S_81844800_4 *)sprite)->unk_14;
                        ((S_81844800_4 *)sprite)->unk_1E = 0x1000;
                        ((S_81844800_4 *)sprite)->unk_1C = 0x1000;
                        ((S_81844800_4 *)sprite)->unk_10 = 0x40;
                        ((S_81844800_4 *)sprite)->unk_00 = sprite_page;
                        ((S_81844800_4 *)sprite)->unk_14 = flags | 0xC;
                        {
                            u32 texture_page = sprite_page->unk_04;
                            ((S_81844800_4 *)sprite)->unk_04 = 0;
                            ((S_81844800_4 *)sprite)->unk_05 = 0;
                            ((S_81844800_4 *)sprite)->unk_0C = 0x00404040;
                            ((S_81844800_4 *)sprite)->unk_08 = texture_page;
                        }
                    }
                    ((S_81844800_2 *)spawned)->unk_20 = effect;
                    ((S_81844800_6 *)particle_data)->unk_48 = func_80069EF8() & 3;
                    ((S_81844800_6 *)particle_data)->unk_4A = 8;
                    ((S_81844800_6 *)particle_data)->unk_4C = 0;
                }
                particles_left--;
            } while (particles_left >= 0);
        }
    }
    switch (((S_81844800_0 *)effect)->unk_0A.s) {
    case 0:
    {
        void *target;
        if ((((S_81844800_15 *)(((S_81844800_0 *)effect)->unk_04))->unk_00 & 0x80) == 0) {
            return;
        }
        target = func_800A05A4(
            owner,
            ((S_81844800_7 *)owner_sprite)->unk_24,
            ((S_81844800_7 *)owner_sprite)->unk_25,
            ((S_81844800_1 *)owner)->unk_2A,
            (s16)func_800A3820(9));
        ((S_81844800_1 *)owner)->unk_60 = target;
        if (target == 0) {
            ((S_81844800_1 *)owner)->unk_72.s = ((S_81844800_7 *)owner_sprite)->unk_24;
            ((S_81844800_1 *)owner)->unk_73.s = ((S_81844800_7 *)owner_sprite)->unk_25;
        } else {
            sprite = ((S_81844800_8_pre *)target)[-1].unk_00;
            if ((((S_81844800_4 *)sprite)->unk_14 & 0x8000) != 0) {
                if ((((S_81844800_9 *)source_render)->unk_14 & 0x8000) != 0) {
                    func_8009CE1C(
                        ((S_81844800_1 *)owner)->unk_60,
                        10,
                        ((S_81844800_0 *)effect)->unk_09,
                        4,
                        ((S_81844800_1 *)owner)->unk_2A,
                        owner,
                        2);
                    ((S_81844800_0 *)effect)->unk_0A.u = 5;
                    return;
                }
            }
            ((S_81844800_1 *)owner)->unk_72.s = ((S_81844800_4 *)sprite)->unk_24;
            ((S_81844800_1 *)owner)->unk_73.s = ((S_81844800_4 *)sprite)->unk_25;
        }
        {
            if (func_8003DE58(
                ((S_81844800_16 *)(((S_81844800_10 *)owner_start)->unk_0C))->unk_08,
                ((S_81844800_10 *)owner_start)->unk_0C, &delta, 0) == 0) {
                delta.z = 0;
                delta.y = 0;
                delta.x = 0;
            }
            {
                s32 target_x;
                ((S_81844800_3 *)motion)->unk_00.at02.v =
                    ((S_81844800_17 *)(((S_81844800_11 *)owner_start)->unk_08))->unk_02 + delta.x;
                ((S_81844800_3 *)motion)->unk_04.at02.v =
                    ((S_81844800_17 *)(((S_81844800_11 *)owner_start)->unk_08))->unk_06 + delta.y;
                ((S_81844800_3 *)motion)->unk_08.at02.v =
                    ((S_81844800_17 *)(((S_81844800_11 *)owner_start)->unk_08))->unk_0A + delta.z;
                ((S_81844800_0 *)effect)->unk_50.s = 8;
                {
                    target_x = ((S_81844800_1 *)owner)->unk_72.u;
                    {
                        ((S_81844800_3 *)motion)->unk_0C.at02.v =
                            delta_axis(target_x, ((S_81844800_3 *)motion)->unk_00.at02.v);
                    }
                }
                ((S_81844800_3 *)motion)->unk_0C.at00.v /= ((S_81844800_0 *)effect)->unk_50.u;
                {
                    target_x = ((S_81844800_1 *)owner)->unk_73.u;
                    {
                        ((S_81844800_3 *)motion)->unk_10.at02.v =
                            delta_axis(target_x, ((S_81844800_3 *)motion)->unk_04.at02.v);
                    }
                }
                ((S_81844800_3 *)motion)->unk_10.at00.v /= ((S_81844800_0 *)effect)->unk_50.u;
                ((S_81844800_3 *)motion)->unk_14.at02.v = func_800BCB04(
                    ((S_81844800_3 *)motion)->unk_00.at02.v,
                    ((S_81844800_3 *)motion)->unk_04.at02.v,
                    (s16)(((S_81844800_17 *)(((S_81844800_11 *)owner_start)->unk_08))->unk_0A - 48)) -
                    (((S_81844800_3 *)motion)->unk_08.at02.v + 176);
            }
            ((S_81844800_3 *)motion)->unk_14.at00.v /= ((S_81844800_0 *)effect)->unk_50.u;
            func_800A56E0(0x300);
            ((S_81844800_0 *)effect)->unk_0A.u++;
            return;
        }
    }

    case 1:
        ((S_81844800_3 *)motion)->unk_00.at00.v += ((S_81844800_3 *)motion)->unk_0C.at00.v;
        ((S_81844800_3 *)motion)->unk_04.at00.v += ((S_81844800_3 *)motion)->unk_10.at00.v;
        ((S_81844800_3 *)motion)->unk_08.at00.v += ((S_81844800_3 *)motion)->unk_14.at00.v;
        state = ((S_81844800_0 *)effect)->unk_50.s - 1;
        ((S_81844800_0 *)effect)->unk_50.s = state;
        if ((state << 16) > 0) {
            return;
        }
        {
            target_timer = 12;
            state = ((S_81844800_0 *)effect)->unk_0A.u;
            ((S_81844800_0 *)effect)->unk_50.s = target_timer;
            ((S_81844800_0 *)effect)->unk_0A.u = state + 1;
            return;
        }

    case 2:
    {
        state = ((S_81844800_0 *)effect)->unk_50.s - 1;
        ((S_81844800_0 *)effect)->unk_50.s = state;
        if ((state << 16) > 0) {
            return;
        }
        if (((S_81844800_1 *)owner)->unk_60 == 0) {
            ((S_81844800_0 *)effect)->unk_50.s = 8;
            ((S_81844800_0 *)effect)->unk_0A.u = 5;
            return;
        }
        target_timer = 10;
        state = ((S_81844800_0 *)effect)->unk_0A.u;
        ((S_81844800_0 *)effect)->unk_50.s = target_timer;
        ((S_81844800_0 *)effect)->unk_0A.u = state + 1;
        return;
    }

    case 3:
        if ((((S_81844800_0 *)effect)->unk_52.s & 0x7FFF) == 0) {
            spawned = func_8003FD64(0x201, ((u8 *)(&D_80083498)));
            if (spawned != 0) {
                S_81844800_12 *burst_data = (u8 *)spawned + 0x20;
                ((S_81844800_2 *)spawned)->unk_10 = func_8002472C;
                func_8004491C(spawned, func_80024868);
                burst_data->unk_2A = 8;
                ((S_81844800_2 *)spawned)->unk_20 = effect;
                burst_data->unk_04 = ((S_81844800_3 *)motion)->unk_00.at02.v;
                burst_data->unk_06 = ((S_81844800_3 *)motion)->unk_04.at02.v;
                burst_data->unk_08 = ((S_81844800_3 *)motion)->unk_08.at02.v;
                ((S_81844800_0 *)effect)->unk_52.s++;
                burst_data->unk_2C = 0;
            }
        }
        if (((S_81844800_0 *)effect)->unk_50.u == 7 &&
            ((S_81844800_1 *)owner)->unk_60 != 0) {
            func_8009CE1C(
                ((S_81844800_1 *)owner)->unk_60,
                10,
                ((S_81844800_0 *)effect)->unk_09,
                4,
                ((S_81844800_1 *)owner)->unk_2A,
                owner,
                2);
        }
        particles_left = 20;
        do {
            spawned = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
            if (spawned != 0) {
                particle_data = (u8 *)spawned + 0x20;
                sprite = ((S_81844800_2 *)spawned)->unk_0C;
                ((S_81844800_2 *)spawned)->unk_10 = func_80024C84;
                ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_00.u =
                    ((S_81844800_3 *)motion)->unk_00.at00.v;
                ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_04.u =
                    ((S_81844800_3 *)motion)->unk_04.at00.v;
                state = (func_80069EF8() & 0x3F) - 176;
                ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_08.at02.v =
                    ((S_81844800_3 *)motion)->unk_08.at02.v - state;
                ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_0E = (func_80069EF8() & 0xF) - 8;
                ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_12 = (func_80069EF8() & 0xF) - 8;
                ((S_81844800_14 *)(((S_81844800_2 *)spawned)->unk_08))->unk_16 = -(func_80069EF8() & 7);
                {
                    u16 flags = ((S_81844800_4 *)sprite)->unk_14;
                    ((S_81844800_4 *)sprite)->unk_1E = 0x1000;
                    ((S_81844800_4 *)sprite)->unk_1C = 0x1000;
                    ((S_81844800_4 *)sprite)->unk_10 = 0x60;
                    ((S_81844800_4 *)sprite)->unk_00 = D_800DECF8;
                    ((S_81844800_4 *)sprite)->unk_14 = flags | 0xC;
                    {
                        u32 texture_page = ((u32)((SpriteSourceEntry *)D_800DECF8)->unk_04);
                        ((S_81844800_4 *)sprite)->unk_04 = 0;
                        ((S_81844800_4 *)sprite)->unk_05 = 0;
                        ((S_81844800_4 *)sprite)->unk_0C = 0x00404040;
                        ((S_81844800_4 *)sprite)->unk_08 = texture_page;
                    }
                }
                ((S_81844800_2 *)spawned)->unk_20 = effect;
                ((S_81844800_6 *)particle_data)->unk_48 = func_80069EF8() & 3;
                ((S_81844800_6 *)particle_data)->unk_4A = 16;
                ((S_81844800_6 *)particle_data)->unk_4C = 0;
            }
            particles_left--;
        } while (particles_left >= 0);
        state = ((S_81844800_0 *)effect)->unk_50.s - 1;
        ((S_81844800_0 *)effect)->unk_50.s = state;
        if ((state << 16) > 0) {
            return;
        }
        {
            u16 timer_reset = 8;
            state_2 = ((S_81844800_0 *)effect)->unk_0A.u;
            ((S_81844800_0 *)effect)->unk_50.s = timer_reset;
            ((S_81844800_0 *)effect)->unk_0A.u = state_2 + 1;
            return;
        }

    case 4:
        state = ((S_81844800_0 *)effect)->unk_50.s - 1;
        ((S_81844800_0 *)effect)->unk_50.s = state;
        if ((state << 16) > 0) {
            return;
        }
        ((S_81844800_0 *)effect)->unk_0A.u++;
        return;

    case 5:
    {
        u16 effect_count;
        if ((((S_81844800_0 *)effect)->unk_52.u & 0x8000) != 0) {
            effect_count = ((S_81844800_0 *)effect)->unk_52.s & 0x7FFF;
            ((S_81844800_0 *)effect)->unk_52.s = effect_count;
            return;
        }
        dungeonStatus.unk_0C = 0;
        ((S_81844800_0_pre *)effect)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }

        return;
    }
}
