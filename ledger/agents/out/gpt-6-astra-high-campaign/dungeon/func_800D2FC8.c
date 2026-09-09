#include "common.h"

typedef void (*Callback)();

extern void func_8003DB94();
extern void func_800478B8();
extern s32 func_80069EF8(void);
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800D8C64;
extern u8 D_800E260C[];
extern Callback D_800E264C[];

typedef struct S_func_800D8728_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[3];
    u8 unk_71;
    u8 pad_72[0x16];
    union {
        s16 s16;
        u16 u16;
    } unk_88;
    u8 pad_8A[2];
    Callback unk_8C;
    union {
        s32 s32;
        struct {
            u8 pad_90[2];
            union {
                s16 s16;
                u16 u16;
            } unk_92;
        } half;
    } unk_90;
    s16 unk_94;
    u8 pad_96[2];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[2];
    u8 unk_9D;
    u8 pad_9E[2];
    union {
        s16 s16;
        u16 u16;
    } unk_A0;
} S_func_800D8728_0;

typedef struct S_func_800D8728_1 {
    union {
        s32 s32;
        struct {
            u8 pad_00[2];
            u16 unk_02;
        } half;
    } unk_00;
    union {
        s32 s32;
        struct {
            u8 pad_04[2];
            u16 unk_06;
        } half;
    } unk_04;
    u8 pad_08[2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_800D8728_1;

typedef struct S_func_800D8728_2 {
    u8 pad_00[4];
    s8 unk_04;
    u8 pad_05[0xD];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[6];
    u8 *unk_2C;
} S_func_800D8728_2;

/* Update entity callbacks, facing, movement, and floor contact. */
void func_800D8728(void *entity_data, void *motion_data, void *monster_data)
{
    register S_func_800D8728_0 *self ASM_REG("$4") = entity_data;
    register S_func_800D8728_0 *entity ASM_REG("$17") = self;
    register S_func_800D8728_1 *motion = motion_data;
    S_func_800D8728_2 *monster = monster_data;
    register S_func_800D8728_0 *actor ASM_REG("$18");
    s16 previous_direction;
    register s32 direction_sector ASM_REG("$2");
    register s32 state_direction ASM_REG("$16");
    register s32 lookup_direction ASM_REG("$21");
    register s32 compare_direction ASM_REG("$4");
    s16 floor_height;
    u16 model_flags;

    ASM_KEEP_NV(self);
    actor = entity;
    *(u16 *)((u8 *)monster + 0x12) = 0;

    if (D_80083462 & 0x2000) {
        Callback special_callback = entity->unk_8C;
        if (special_callback == (Callback)&D_800D8C64) {
            special_callback(entity, motion, monster, self);
            return;
        }
        entity->unk_71 &= 0x7F;
        return;
    }

    ASM_CLOBBER("$5");
    previous_direction = (s8)entity->unk_6D;
    if (func_800A9E70(entity, motion, monster, entity) != 0) {
        return;
    }

    {
        Callback callback = entity->unk_8C;
        if (callback != 0) {
            callback(entity, motion, monster, entity);
        }
    }
    D_800E264C[entity->unk_9A](entity, motion, monster, entity);

    if ((s16)previous_direction != (s8)entity->unk_6D) {
        func_800AA36C(entity, motion, monster, entity);
    }

    model_flags = monster->unk_14;
    if (!(model_flags & 0x8000)) {
        direction_sector = (D_80083228 + entity->unk_2A + 0x100) >> 9;
        state_direction = direction_sector & 7;
        lookup_direction = state_direction;
        compare_direction = state_direction;
        if (entity->unk_94 != compare_direction) {
            void *direction_table = monster->unk_2C;
            if (direction_table != 0) {
                register s32 direction_offset ASM_REG("$2") = (s16)compare_direction * 4;
                func_8003DB94(monster,
                              *(void **)(direction_offset + (s32)direction_table),
                              monster->unk_04);
            }
            entity->unk_94 = state_direction;
        }

        {
            u16 facing_flags;
            if (D_8006CCF8[lookup_direction] != 0) {
                facing_flags = monster->unk_14 | 1;
            } else {
                ASM_KEEP(lookup_direction);
                facing_flags = ((volatile S_func_800D8728_2 *)monster)->unk_14 & 0xFFFE;
            }
            ((volatile S_func_800D8728_2 *)monster)->unk_14 = facing_flags;
        }

        if (!(actor->unk_1C & 0x20)) {
            if (!(((volatile S_func_800D8728_2 *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            ((volatile S_func_800D8728_2 *)monster)->unk_14 |= 0x7000;
        }

        func_800A020C(actor->unk_1C, (u8 *)monster + 0xC);
    } else if (model_flags & 0x800) {
        monster->unk_14 = model_flags & 0x8FFF;
    } else {
        monster->unk_14 = model_flags | 0x7000;
    }

    motion->unk_00.s32 += motion->unk_0C;
    motion->unk_04.s32 += motion->unk_10;

    if (entity->unk_9A == 14) {
        s16 hop_timer;
        hop_timer = (s16)(--entity->unk_A0.u16);
        if (hop_timer == 2) {
            s32 hop_direction_offset;
            entity->unk_98 |= 1;
            *(u8 **)((u8 *)monster + 0x2C) = D_800E260C;
            hop_direction_offset = ((D_80083228 + actor->unk_2A + 0x100) >> 7) & 0x1C;
            func_8003DB94(monster, *(void **)(D_800E260C + hop_direction_offset), 0);
        }

        if (entity->unk_A0.s16 == 0) {
            motion->unk_14 = (s32)0xFFE00000;
        }

        if ((u16)(entity->unk_A0.u16 + 7) < 8) {
            motion->unk_14 += 0x40000;
        } else {
            motion->unk_14 = 0;
        }

        if (entity->unk_A0.s16 < -7) {
            entity->unk_98 &= 0xFFFE;
            entity->unk_A0.u16 = (func_80069EF8() & 0x3F) | 0x40;
        }
    } else {
        entity->unk_98 &= 0xFFFE;
    }

    if (entity->unk_98 & 8) {
        entity->unk_9D = 0;
    } else {
        motion->unk_14 +=
            ((s8)entity->unk_9D * 5) << 14;
        entity->unk_9D++;
    }
    entity->unk_90.s32 += motion->unk_14;

    if (!(entity->unk_98 & 4)) {
        floor_height = func_800BCB04(motion->unk_00.half.unk_02,
                                   motion->unk_04.half.unk_06,
                                   (s16)(actor->unk_88.u16 - 0x20));
        if (floor_height < 0x200) {
            if (entity->unk_90.half.unk_92.s16 + actor->unk_88.s16 < floor_height) {
                actor->unk_1C &= 0xF7FFFFFF;
            } else if (floor_height >= actor->unk_88.s16) {
                entity->unk_90.s32 = 0;
                motion->unk_14 = 0;
                actor->unk_1C |= 0x08000000;
                entity->unk_9D = 0;
            } else {
                motion->unk_14 = 0;
                actor->unk_1C |= 0x08000000;
                entity->unk_9D = 0;
                entity->unk_90.half.unk_92.u16 = floor_height - actor->unk_88.u16;
            }

            if (actor->unk_1C & 0x40000000) {
                actor->unk_1C &= 0xBFFFFFFF;
                floor_height = func_800BCB04((monster->unk_24 << 6) | 0x20,
                                           (monster->unk_25 << 6) | 0x20,
                                           (s16)(actor->unk_88.u16 - 0x20));
                entity->unk_90.half.unk_92.u16 += actor->unk_88.u16 - floor_height;
                actor->unk_88.u16 = floor_height;
            }
            goto finish;
        }
    }

    actor->unk_1C &= 0xF7FFFFFF;
finish:
    motion->unk_0A =
        actor->unk_88.u16 + entity->unk_90.half.unk_92.u16;
    monster->unk_14 |= 0x40;
    ASM_KEEP(entity);
    ASM_KEEP(motion);
}
