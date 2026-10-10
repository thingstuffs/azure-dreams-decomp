#include "modules/dungeon_ovl_18a6800.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
extern int abs(int);

typedef struct S_func_81886800_1 {
    void *unk_00;
    void *unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union {
        s16 s16;
        u16 u16;
    } unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    union {
        s16 s16;
        u16 u16;
    } unk_10;
    u8 unk_12;
    u8 pad_13[0x1];
    u16 unk_14;
    union {
        s16 s16;
        u16 u16;
    } unk_16;
    union {
        s16 s16;
        u16 u16;
    } unk_18;
    u8 pad_1A[0x2];
    union {
        u32 u32;
        struct {
            u8 pad_1C[0x2];
            union {
                s16 s16;
                struct {
                    union {
                        s8 s8;
                        u8 u8;
                    } unk_1E;
                    union {
                        s8 s8;
                        u8 u8;
                    } unk_1F;
                } parts;
            } unk_1E;
        } parts;
    } unk_1C;
    union {
        s16 s16;
        struct {
            u8 unk_20;
            u8 unk_21;
        } parts;
    } unk_20;
    u8 pad_22[0x6];
    void *unk_28;
    union {
        s32 s32;
        struct {
            u8 pad_2C[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_2E;
        } parts;
    } unk_2C;
    u8 pad_30[0x28];
    s16 unk_58;
} S_func_81886800_1;

typedef struct S_func_81886800_2 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
} S_func_81886800_2;

typedef struct S_func_81886800_3 {
    u8 pad_00[0x8];
    void *unk_08;
    union {
        u32 u32;
        struct {
            u8 unk_0C;
            u8 unk_0D;
            u8 unk_0E;
        } parts;
    } unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_func_81886800_3;

typedef struct S_func_81886800_4 {
    u16 unk_00;
} S_func_81886800_4;

typedef struct S_func_81886800_5 {
    u16 unk_00;
} S_func_81886800_5;

typedef struct S_func_81886800_6 {
    u16 unk_00;
} S_func_81886800_6;

typedef struct S_func_81886800_7 {
    s32 unk_00;
} S_func_81886800_7;

typedef struct S_func_81886800_8 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[0xC];
    union {
        u32 u32;
        struct {
            u8 pad_70[0x2];
            union {
                s8 s8;
                u8 u8;
            } unk_72;
            union {
                s8 s8;
                u8 u8;
            } unk_73;
        } parts;
    } unk_70;
    u8 pad_74[0x14];
    union {
        s16 s16;
        u16 u16;
    } unk_88;
} S_func_81886800_8;

typedef struct S_func_81886800_9 {
    s32 unk_00;
} S_func_81886800_9;

typedef struct S_func_81886800_10 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union {
        void * ptr;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A;
        } parts;
    } unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_func_81886800_10;

typedef struct S_func_81886800_11 {
    union {
        s32 s32;
        struct {
            u8 pad_00[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_02;
        } parts;
    } unk_00;
    union {
        s32 s32;
        struct {
            u8 pad_04[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_06;
        } parts;
    } unk_04;
    union {
        s32 s32;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A;
        } parts;
    } unk_08;
    union {
        s32 s32;
        struct {
            u8 pad_0C[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_0E;
        } parts;
    } unk_0C;
    union {
        s32 s32;
        struct {
            u8 pad_10[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_12;
        } parts;
    } unk_10;
} S_func_81886800_11;

typedef struct S_func_81886800_12 {
    u16 unk_00;
} S_func_81886800_12;

typedef struct S_func_81886800_13 {
    void *unk_00;
} S_func_81886800_13;

typedef struct S_func_81886800_14 {
    s16 unk_00;
} S_func_81886800_14;

typedef struct S_func_81886800_15 {
    u16 unk_00;
} S_func_81886800_15;

typedef struct S_func_81886800_16 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_func_81886800_16;

typedef struct S_func_81886800_17 {
    union {
        s16 s16;
        u16 u16;
    } unk_00;
} S_func_81886800_17;

typedef struct S_func_81886800_18 {
    s32 unk_00;
} S_func_81886800_18;

typedef struct S_func_81886800_19 {
    s32 unk_00;
} S_func_81886800_19;


extern void func_800B835C(void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern s32 func_800644B8(s32);
extern s32 set_item_w0(s32, s32, s32, s32);
extern s32 func_800A45D8(s32, s32, s32);
extern void func_80065F90(s32, s32);
extern void func_800262B8(s32, s32, void *);

extern u8 D_8002632C[];
extern u8 D_80026344[];
extern u8 D_80026878[];

void func_80024064(S_func_81886800_1 *effect, S_func_81886800_11 *motion, S_func_81886800_3 *sprite);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_18a6800_entry)(S_func_81886800_1 *, S_func_81886800_11 *, S_func_81886800_3 *) = func_80024064;

/* Initialize and update a moving effect through targeting, collision, and fading states. */
void func_80024064(S_func_81886800_1 *effect, S_func_81886800_11 *motion, S_func_81886800_3 *sprite)
{
    S_func_81886800_8 *owner;
    S_func_81886800_2 *owner_base;
    S_func_81886800_11 *owner_motion;
    S_func_81886800_8 *target_object;
    s32 state;
    u16 owner_flags;
    s16 surface_pos[3];
    s32 texture_rect[2];

    owner = effect->unk_00;
    state = effect->unk_0A.s16;
    owner_base = (S_func_81886800_2 *)((u8 *)owner - 0x20);
    owner_motion = owner_base->unk_08;
    switch (state) {
    case 0:
    texture_rect[0] = 0x01000340;
    texture_rect[1] = 0x00200020;
    func_800B835C(D_8002632C, texture_rect, 1, 0);

    sprite->unk_0C.u32 = 0x00808080;
    sprite->unk_1E = 0x555;
    sprite->unk_1C = 0x555;
    sprite->unk_08 = D_80026344;
    ((S_func_81886800_4 *)(D_80026324))->unk_00 = 0;
    ((S_func_81886800_5 *)(D_80026328))->unk_00 = 0;
    ((S_func_81886800_6 *)(&D_8002632A))->unk_00 = 0;
    ((S_func_81886800_7 *)(D_80026470))->unk_00 = 0;
    owner_flags = owner->unk_2A;
    ((S_func_81886800_9 *)(D_80026474))->unk_00 = 0;
    effect->unk_16.u16 = (owner_flags >> 9) & 7;
    effect->unk_0A.u16++;

    case 1:
    if (func_8003DF74(
            ((S_func_81886800_10 *)(owner_base->unk_0C))->unk_08.ptr,
            owner_base->unk_0C, surface_pos, 0) == 0) {
        if ((((S_func_81886800_10 *)(owner_base->unk_0C))->unk_14 & 0x8000) == 0) {
            break;
        }
    }

    motion->unk_00.parts.unk_02.u16 = owner_motion->unk_00.parts.unk_02.u16;
    motion->unk_04.parts.unk_06.u16 = owner_motion->unk_04.parts.unk_06.u16;
    if (((S_func_81886800_10 *)(owner_base->unk_0C))->unk_14 & 0x8000) {
        motion->unk_08.parts.unk_0A = owner_motion->unk_08.parts.unk_0A - 64;
        effect->unk_2C.parts.unk_2E.u16 = motion->unk_08.parts.unk_0A;
    } else {
        motion->unk_08.parts.unk_0A = owner_motion->unk_08.parts.unk_0A + surface_pos[2];
        effect->unk_2C.parts.unk_2E.u16 = motion->unk_08.parts.unk_0A;
    }

    {
        S_func_81886800_12 *effect_flags = effect->unk_04;
        if ((effect_flags->unk_00 & 0x80) == 0) {
            break;
        }
        if ((effect->unk_12 & 4) == 0) {
            func_8004491C((u8 *)effect - 0x20, func_80045340);
            sprite->unk_10 = 0x20;
            sprite->unk_0C.parts.unk_0E = 0x80;
            sprite->unk_0C.parts.unk_0D = 0x80;
            sprite->unk_0C.parts.unk_0C = 0x80;
            sprite->unk_14 |= 0xC;
            effect->unk_12 |= 4;
        }
    }

    if (owner->unk_60 != 0) {
        {
            S_func_81886800_10 *target_data;

            target_data =
                ((S_func_81886800_13 *)((u8 *)(owner->unk_60) - 0x18))->unk_00;
            effect->unk_0C = target_data->unk_02;
            effect->unk_0E = target_data->unk_06;
            {
                u8 target_kind;
                u8 *height_offsets;

                height_offsets = D_800DDC40;
                target_kind = ((S_func_81886800_8 *)(owner->unk_60))->unk_13;
                effect->unk_10.u16 =
                    target_data->unk_08.parts.unk_0A - height_offsets[target_kind];
            }
            {
                s16 direction;
                u8 tile_coord;
                direction = effect->unk_16.s16;
                target_data = ((S_func_81886800_13 *)((u8 *)(owner) - 0x14))->unk_00;
                tile_coord = target_data->unk_24 +
                        ((u8 *)dirStepX)[(s32)direction * 2];
                effect->unk_1C.parts.unk_1E.parts.unk_1E.u8 = tile_coord;
                effect->unk_20.parts.unk_20 = tile_coord;
            }
            {
                s16 direction;
                u8 tile_coord;
                direction = effect->unk_16.s16;
                tile_coord = target_data->unk_25 +
                        ((u8 *)dirStepY)[(s32)direction * 2];
                effect->unk_1C.parts.unk_1E.parts.unk_1F.u8 = tile_coord;
                effect->unk_20.parts.unk_21 = tile_coord;
            }
            {
#ifdef __mips__
                s32 owner_tile;
#else
                s32 owner_tile;
                s32 state;
#endif
                s32 tile_distance;
                owner_tile = owner->unk_70.parts.unk_72.s8;
                state = target_data->unk_24;
                if (owner_tile == state) {
                    owner_tile = owner->unk_70.parts.unk_73.s8;
                    state = target_data->unk_25;
                    tile_distance = owner_tile - state;
                } else {
                    tile_distance = owner_tile - state;
                }
                tile_distance = abs(tile_distance);
                effect->unk_14 = tile_distance + 1;
            }
        }
    } else {
        effect->unk_14 = 8;
        effect->unk_0C = motion->unk_00.parts.unk_02.u16;
        effect->unk_0E = motion->unk_04.parts.unk_06.u16;
        effect->unk_10.u16 = owner->unk_88.u16 - 80;
    }
    {
        u8 *x_offsets = ((u8 *)dirStepX);
        s16 direction = effect->unk_16.s16;
        motion->unk_0C.parts.unk_0E.u16 =
            ((S_func_81886800_14 *)(x_offsets + (s32)direction * 2))->unk_00 * 8;
        {
            u8 *y_offsets = ((u8 *)dirStepY);
            s16 y_direction = effect->unk_16.s16;
            motion->unk_10.parts.unk_12.u16 =
                ((S_func_81886800_14 *)(y_offsets + (s32)y_direction * 2))->unk_00 * 8;
        }
    }
    effect->unk_0A.u16++;
    break;

    case 2:
    {
        s32 x_velocity;
        motion->unk_00.s32 += motion->unk_0C.s32;
        x_velocity = motion->unk_0C.s32 + (motion->unk_0C.s32 >> 4);
        motion->unk_0C.s32 = x_velocity;
        if ((x_velocity < 0 ? -x_velocity : x_velocity) > 0x200000) {
            x_velocity = x_velocity > 0 ? 0x200000 : -0x200000;
            motion->unk_0C.s32 = x_velocity;
        }
    }
    {
        s32 y_velocity;
        motion->unk_04.s32 += motion->unk_10.s32;
        y_velocity = motion->unk_10.s32 + (motion->unk_10.s32 >> 4);
        motion->unk_10.s32 = y_velocity;
        if ((y_velocity < 0 ? -y_velocity : y_velocity) > 0x200000) {
            y_velocity = y_velocity > 0 ? 0x200000 : -0x200000;
            motion->unk_10.s32 = y_velocity;
        }
    }
    {
        s32 height = effect->unk_2C.s32;
        height += (((s32)effect->unk_10.s16 << 16) - height) >> 4;
        effect->unk_2C.s32 = height;
        height = motion->unk_08.s32;
        height += (((s32)effect->unk_10.s16 << 16) - height) >> 4;
        motion->unk_08.s32 = height;
    }
    {
        s32 bob_offset = func_800644B8((s32)effect->unk_18.s16 << 7);
        motion->unk_08.s32 += bob_offset << 6;
    }
    func_80024DE8(motion, sprite);
    {
        s32 tile_coord = motion->unk_00.parts.unk_02.s16;
        if (tile_coord < 0) {
            tile_coord += 63;
        }
        effect->unk_1C.parts.unk_1E.parts.unk_1E.u8 = tile_coord >> 6;
        tile_coord = motion->unk_04.parts.unk_06.s16;
        effect->unk_1C.parts.unk_1E.parts.unk_1F.u8 = (tile_coord / 64);
    }
    if (effect->unk_20.s16 == effect->unk_1C.parts.unk_1E.s16) {
        break;
    }
    if (owner->unk_60 != 0) {
        if (effect->unk_58 == 0) {
            s32 target_distance = set_item_w0(
                ((S_func_81886800_1 *)(effect))->unk_1C.parts.unk_1E.parts.unk_1E.u8,
                ((S_func_81886800_1 *)(effect))->unk_1C.parts.unk_1E.parts.unk_1F.u8,
                ((S_func_81886800_8 *)(owner))->unk_70.parts.unk_72.u8,
                ((S_func_81886800_8 *)(owner))->unk_70.parts.unk_73.u8);
            target_distance = (s16)target_distance;
            if (target_distance < 5) {
                effect->unk_58 = 1;
                func_800A56E0(0x300);
            }
        }
    }
    if (owner->unk_60 != 0) {
        if ((((S_func_81886800_8 *)(owner))->unk_70.u32 & 0xFFFF0000) ==
            (((S_func_81886800_1 *)(effect))->unk_1C.u32 & 0xFFFF0000)) {
            S_func_81886800_11 *snapped_motion;

            snapped_motion = motion;
            {
                s32 coordinate = owner->unk_70.parts.unk_72.s8;
                motion->unk_00.parts.unk_02.s16 = (coordinate << 6) + 0x20;
            }
            {
                s32 coordinate = owner->unk_70.parts.unk_73.s8;
                motion->unk_04.parts.unk_06.s16 = (coordinate << 6) + 0x20;
            }
            motion->unk_08.parts.unk_0A = effect->unk_10.u16;
            func_80024DE8(snapped_motion, sprite);
            {
                u16 next_state = effect->unk_0A.u16;
                u16 target_id =
                    ((S_func_81886800_8 *)(owner->unk_60))->unk_88.u16;
                next_state++;
                effect->unk_0A.u16 = next_state;
                ((S_func_81886800_15 *)(D_80026878))->unk_00 = target_id;
            }
            break;
        }
    }

    {
        u8 x = effect->unk_1C.parts.unk_1E.parts.unk_1E.u8;
        u8 y = effect->unk_1C.parts.unk_1E.parts.unk_1F.u8;
        s32 timer = effect->unk_14 - 1;
        s32 collision;
        effect->unk_14 = timer;
        effect->unk_20.parts.unk_20 = x;
        effect->unk_20.parts.unk_21 = y;
        if ((timer << 16) != 0) {
            s32 world_x = (((s32)effect->unk_1C.parts.unk_1E.parts.unk_1E.s8 << 6) + 0x20) & 0xFFE0;
            s32 world_y = (((s32)effect->unk_1C.parts.unk_1E.parts.unk_1F.s8 << 6) + 0x20) & 0xFFE0;
            collision = func_800A45D8(world_x, world_y, effect->unk_2C.parts.unk_2E.s16);
            if ((collision << 16) == 0) {
                break;
            }
        }
        effect->unk_0A.u16 = 16;
        break;
    }

    case 3:
    func_80065F90(motion->unk_0C.parts.unk_0E.s16, motion->unk_10.parts.unk_12.s16);
    target_object = owner->unk_60;
    effect->unk_28 = func_80024C80(
        effect, motion, target_object->unk_88.s16, target_object);
    if (effect->unk_28 == 0) {
        break;
    }
    effect->unk_0A.u16++;
    case 4:
    {
        sprite->unk_0C.parts.unk_0C -= sprite->unk_0C.parts.unk_0C >> 2;
        sprite->unk_0C.parts.unk_0D -= sprite->unk_0C.parts.unk_0D >> 2;
        sprite->unk_0C.parts.unk_0E -= sprite->unk_0C.parts.unk_0E >> 2;
        if ((((S_func_81886800_16 *)(effect->unk_28))->unk_1E & 0x8000) == 0) {
            break;
        }
        if (owner->unk_60 != 0) {
            func_800262B8(owner->unk_60,
                          effect->unk_09, owner);
        }
        effect->unk_0A.u16 = 17;
        break;
    }

    case 16:
    {
#ifdef __mips__
#else
        S_func_81886800_11 *motion;
#endif
        motion->unk_00.s32 += motion->unk_0C.s32;
        motion->unk_04.s32 += motion->unk_10.s32;
        {
            s32 target_height = (s32)effect->unk_10.s16 << 16;
            s32 height = motion->unk_08.s32;
            height += (target_height - height) >> 4;
            motion->unk_08.s32 = height;
        }
        sprite->unk_0C.parts.unk_0C -= sprite->unk_0C.parts.unk_0C >> 1;
        sprite->unk_0C.parts.unk_0D -= sprite->unk_0C.parts.unk_0D >> 1;
        sprite->unk_0C.parts.unk_0E -= sprite->unk_0C.parts.unk_0E >> 1;
        func_80024DE8(motion, sprite);
        if (sprite->unk_0C.parts.unk_0C < 2) {
            effect->unk_0A.u16++;
        }
        break;
    }

    case 17:
    if (((S_func_81886800_17 *)(&D_80026326))->unk_00.s16 != 0) {
        break;
    }
    ((S_func_81886800_18 *)(((u8 *)(&dungeonStatus.unk_0C))))->unk_00 = 0;
    ((S_func_81886800_12 *)((u8 *)effect - 2))->unk_00 |= 0x8000;
    ((S_func_81886800_19 *)(((u8 *)(&objectFlagBlock))))->unk_00 |= 0x8000;

    }
    {
        u16 frame_count = effect->unk_18.u16;
        ((S_func_81886800_17 *)(&D_80026326))->unk_00.u16 = 0;
        effect->unk_18.u16 = frame_count + 1;
    }
}

