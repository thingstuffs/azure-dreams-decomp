#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct S_func_818DA800_1 {
    void *unk_00;
    void *unk_04;
    u8 pad_08[2];
    union { s16 as_s16; u16 as_u16; } unk_0A;
    u8 pad_0C[0x44];
    union { s16 as_s16; u16 as_u16; } unk_50;
    union { s16 as_s16; u16 as_u16; } unk_52;
} S_func_818DA800_1;

typedef struct S_func_818DA800_2 {
    union {
        s32 as_s32;
        struct {
            u8 pad_00[2];
            union { s16 as_s16; u16 as_u16; } unk_02;
        } half;
    } unk_00;
    union {
        s32 as_s32;
        struct {
            u8 pad_04[2];
            union { s16 as_s16; u16 as_u16; } unk_06;
        } half;
    } unk_04;
    union {
        s32 as_s32;
        struct {
            u8 pad_08[2];
            union { s16 as_s16; u16 as_u16; } unk_0A;
        } half;
    } unk_08;
    union {
        s32 as_s32;
        struct {
            u8 pad_0C[2];
            s16 unk_0E;
        } half;
    } unk_0C;
    union {
        s32 as_s32;
        struct {
            u8 pad_10[2];
            s16 unk_12;
        } half;
    } unk_10;
    union {
        s32 as_s32;
        struct {
            u8 pad_14[2];
            s16 unk_16;
        } half;
    } unk_14;
} S_func_818DA800_2;

typedef struct S_func_818DA800_3 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[0xE];
    union { s8 as_s8; u8 as_u8; } unk_72;
    union { s8 as_s8; u8 as_u8; } unk_73;
} S_func_818DA800_3;

typedef struct S_func_818DA800_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_func_818DA800_4;

typedef struct S_func_818DA800_5 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0xC];
    void *unk_20;
} S_func_818DA800_5;

typedef struct S_func_818DA800_6 {
    u16 unk_00;
} S_func_818DA800_6;

typedef struct S_func_818DA800_7 {
    void *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[2];
    void *unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    s16 unk_1C;
    s16 unk_1E;
} S_func_818DA800_7;

typedef struct S_func_818DA800_8 {
    void *unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[2];
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u8 pad_14[0x34];
    u16 unk_48;
    u8 pad_4A[2];
    u16 unk_4C;
} S_func_818DA800_8;

typedef struct S_func_818DA800_9 {
    u8 pad_00[4];
    void *unk_04;
} S_func_818DA800_9;

typedef struct S_func_818DA800_10 {
    u8 unk_00;
} S_func_818DA800_10;

typedef struct S_func_818DA800_11 {
    u8 pad_00[2];
    u16 unk_02;
} S_func_818DA800_11;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A3820(s32);
extern void *func_800A05A4(void *, u8, u8, s16, s16);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_800A56E0(s32);
extern s32 func_8009D218(void *, s32, void *);
extern void func_800C8900(void *, s32, s32);

extern u8 D_80024538[];
extern u8 D_800DEAE0[];
extern u8 D_80024684[];
extern u8 D_80024714[];
extern u8 D_800E3D68[];
void func_80024020(S_func_818DA800_1 *effect_state, S_func_818DA800_2 *motion);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The phase table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const module_entry)(S_func_818DA800_1 *, S_func_818DA800_2 *) __asm__("func_80024000") = func_80024020;

/* Advances a targeted effect through movement, particle spawning, target interaction, and cleanup. */
void func_80024020(S_func_818DA800_1 *effect_state, S_func_818DA800_2 *motion)
{
    S_func_818DA800_3 *actor;
    S_func_818DA800_4 *actor_data;
    void *image_base;
    void *resource_base;
    s32 actor_or_corner;
#ifdef __mips__
    S_func_818DA800_7 *prim;
#else
    S_func_818DA800_7 *prim;
#endif
    s32 actor_header;
    S_func_818DA800_8 *child_state;
    s16 timer;
    s32 phase;
    s32 tile_coord;

    actor = effect_state->unk_00;
    timer = (u16)effect_state->unk_50.as_u16;
    timer -= 1;
    phase = effect_state->unk_0A.as_s16;
    actor_data = ((S_func_818DA800_5 *)((u8 *)actor - 0x20))->unk_0C;
    effect_state->unk_50.as_u16 = timer;

    actor_header = (s32)((u8 *)actor - 0x20);
    switch (phase) {
    case 0:
    if ((((S_func_818DA800_6 *)effect_state->unk_04)->unk_00 & 0x80) == 0) {
        break;
    }
    {
        S_func_818DA800_3 *target_actor;
        s16 height;

        height = (s16)func_800A3820(0x22);
        target_actor = func_800A05A4(actor,
            actor_data->unk_24,
            actor_data->unk_25,
            actor->unk_2A, height);
        actor->unk_60 = target_actor;
        if (target_actor == 0) {
            actor->unk_72.as_u8 = actor_data->unk_24;
            actor->unk_73.as_u8 = actor_data->unk_25;
        } else {
            prim = ((S_func_818DA800_5 *)((u8 *)target_actor - 0x20))->unk_0C;
            actor->unk_72.as_u8 = ((S_func_818DA800_4 *)prim)->unk_24;
            actor->unk_73.as_u8 = ((S_func_818DA800_4 *)prim)->unk_25;
        }
    }

    motion->unk_00.half.unk_02.as_u16 =
        ((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_header)->unk_08)->unk_00.half.unk_02.as_u16;
    motion->unk_04.half.unk_06.as_u16 =
        ((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_header)->unk_08)->unk_04.half.unk_06.as_u16;
    motion->unk_08.half.unk_0A.as_u16 =
        ((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_header)->unk_08)->unk_08.half.unk_0A.as_u16;
    effect_state->unk_50.as_u16 = 8;
    tile_coord = actor->unk_72.as_s8;
    motion->unk_0C.half.unk_0E =
        (tile_coord << 6) - (motion->unk_00.half.unk_02.as_u16 - 0x20);
    motion->unk_0C.as_s32 = motion->unk_0C.as_s32 /
        effect_state->unk_50.as_s16;
    tile_coord = actor->unk_73.as_s8;
    motion->unk_10.half.unk_12 =
        (tile_coord << 6) - (motion->unk_04.half.unk_06.as_u16 - 0x20);
    motion->unk_10.as_s32 = motion->unk_10.as_s32 /
        effect_state->unk_50.as_s16;
    motion->unk_14.half.unk_16 = func_800BCB04(
        motion->unk_00.half.unk_02.as_u16, motion->unk_04.half.unk_06.as_u16,
        (s16)(((S_func_818DA800_2 *)((S_func_818DA800_5 *)(void *)actor_header)->unk_08)->unk_08.half.unk_0A.as_u16 -
              0x30)) - motion->unk_08.half.unk_0A.as_s16;
    motion->unk_14.as_s32 = motion->unk_14.as_s32 /
        effect_state->unk_50.as_s16;
    func_800A56E0(0x300);
    effect_state->unk_0A.as_u16++;
    break;

    case 1:
    motion->unk_00.as_s32 += motion->unk_0C.as_s32;
    motion->unk_04.as_s32 += motion->unk_10.as_s32;
    motion->unk_08.as_s32 += motion->unk_14.as_s32;
    if (effect_state->unk_50.as_s16 > 0) {
        break;
    }
    {
        actor_or_corner = 3;
        image_base = D_80024538;
        resource_base = D_800DEAE0;
        do {
            S_func_818DA800_5 *burst_obj;
            s32 center_coord;
            s32 corner_coord;
            s32 position_or_z_offset;
            s32 prim_color;

            burst_obj = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
            if (burst_obj != 0) {
                func_8004491C(burst_obj, func_80045340);
                prim = burst_obj->unk_0C;
                position_or_z_offset = (s32)burst_obj->unk_08;
                burst_obj->unk_10 = image_base;
                center_coord = motion->unk_00.half.unk_02.as_s16;
                child_state = (S_func_818DA800_8 *)((u8 *)burst_obj + 0x20);
                if (actor_or_corner >> 1) {
                    corner_coord = center_coord - 16;
                } else {
                    corner_coord = center_coord + 16;
                }
                ((S_func_818DA800_2 *)(void *)position_or_z_offset)->unk_00.half.unk_02.as_s16 = corner_coord;
                position_or_z_offset = (s32)burst_obj->unk_08;
                center_coord = motion->unk_04.half.unk_06.as_s16;
                if ((actor_or_corner & 1) == 0) {
                    ((S_func_818DA800_2 *)(void *)position_or_z_offset)->unk_04.half.unk_06.as_s16 = center_coord + 16;
                    prim_color = 0xC00000;
                } else {
                    ((S_func_818DA800_2 *)(void *)position_or_z_offset)->unk_04.half.unk_06.as_s16 = center_coord - 16;
                    prim_color = 0xC00000;
                }
                position_or_z_offset = -0x100000;
                ((S_func_818DA800_2 *)burst_obj->unk_08)->unk_08.as_s32 =
                    motion->unk_08.as_s32 + position_or_z_offset;
                prim->unk_1E = 0xC00;
                prim->unk_10 = 0x60;
                {
                    u16 prim_flags;

                    prim_flags = prim->unk_14;
                    prim_color |= 0xC000;
                    prim_color |= 0xC0;
                    position_or_z_offset = resource_base;
                    prim->unk_00 = position_or_z_offset;
                    prim->unk_1C = 0;
                    prim->unk_0C = prim_color;
                    prim_flags |= 0xC;
                    prim->unk_14 = prim_flags;
                }
                prim->unk_08 = ((S_func_818DA800_9 *)prim->unk_00)->unk_04;
                prim->unk_04 = 0;
                prim->unk_05 = 0;
                child_state->unk_00 = effect_state;
                child_state->unk_48 =
                    actor->unk_60 ? 0x20 : 0xA;
                child_state->unk_4C = 0;
            }
            actor_or_corner--;
        } while (actor_or_corner >= 0);
    }
    if (actor->unk_60 != 0) {
        S_func_818DA800_5 *impact_obj;
        impact_obj = func_8003FD64(0x201, ((u8 *)(&D_80083498)));
        if (impact_obj != 0) {
            u16 effect_y;
            u16 effect_z;
            s32 duration;
            func_8004491C(impact_obj, D_80024714);
            impact_obj->unk_10 = D_80024684;
            child_state = (S_func_818DA800_8 *)((u8 *)impact_obj + 0x20);
            child_state->unk_04 = motion->unk_00.half.unk_02.as_u16;
            effect_y = motion->unk_04.half.unk_06.as_u16;
            child_state->unk_06 = effect_y;
            effect_z = motion->unk_08.half.unk_0A.as_u16;
            child_state->unk_12 = 1;
            child_state->unk_0C = -64;
            duration = 40;
            child_state->unk_08 = effect_z;
            impact_obj->unk_20 = effect_state;
            child_state->unk_10 = duration;
        }
    }
    effect_state->unk_50.as_u16 = 10;
    effect_state->unk_0A.as_u16++;
    break;

    case 2:
    if (effect_state->unk_50.as_s16 > 0) {
        break;
    }
    if (actor->unk_60 == 0) {
        effect_state->unk_50.as_u16 = 8;
        effect_state->unk_0A.as_u16 = 5;
        break;
    }
    effect_state->unk_50.as_u16 = 20;
    effect_state->unk_0A.as_u16++;
    break;

    case 3:
    if (effect_state->unk_50.as_s16 > 0) {
        break;
    }
    if (actor->unk_60 != 0 &&
        func_8009D218(actor->unk_60, 1, actor) == 0 &&
        (((S_func_818DA800_3 *)actor->unk_60)->unk_14 & 4) != 0) {
        func_800C8900(
            actor->unk_60,
            ((S_func_818DA800_10 *)D_800E3D68)->unk_00 == 0xFF ? 0xFF : 0x10,
            2);
    }
    effect_state->unk_50.as_u16 = 10;
    effect_state->unk_0A.as_u16++;
    break;

    case 4:
    if (effect_state->unk_50.as_s16 > 0) {
        break;
    }
    effect_state->unk_50.as_u16 = 4;
    effect_state->unk_0A.as_u16++;
    break;

    case 5:
    if (effect_state->unk_52.as_s16 & (u16)0x8000) {
        effect_state->unk_52.as_u16 &= 0x7FFF;
    } else {
        if (effect_state->unk_50.as_s16 <= 0) {
            dungeonStatus.unk_0C = 0;
            ((S_func_818DA800_11 *)((u8 *)effect_state - 4))->unk_02 |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            break;
        }
    }
    }
}
