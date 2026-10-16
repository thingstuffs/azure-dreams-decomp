#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"


extern s32 hasEnoughAvailableRuntimeNodes();
extern s32 func_8004491C();
extern s32 func_800A56E0();
extern void func_800A6508();
extern s32 func_800A6D30(void);
extern void dungeonApplyModeSelectedTrapMask();


extern u8 D_800CD474[];
extern u8 D_800E03E0[];



typedef struct S_800CD6E0_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD6E0_0_pre;   /* the 0x14 bytes before arg0 in dungeonCreateFourOwnerSpriteEffects, addressed as arg0[-1] */

typedef struct S_800CD6E0_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xF];
    u8 unk_13;
    u8 pad_14[0x74];
    u16 unk_88;
} S_800CD6E0_0;   /* arg0 in dungeonCreateFourOwnerSpriteEffects */

typedef struct S_800CD6E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD6E0_1;   /* owner in dungeonCreateFourOwnerSpriteEffects */

typedef struct S_800CD6E0_2 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800CD6E0_2;   /* (obj = func_8003FC64(2)) in dungeonCreateFourOwnerSpriteEffects */

typedef struct S_800CD6E0_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x10];
    void * unk_20;
} S_800CD6E0_3;   /* obj in dungeonCreateFourOwnerSpriteEffects */

typedef struct S_800CD6E0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD6E0_4;   /* prim in dungeonCreateFourOwnerSpriteEffects */

typedef struct S_800CD6E0_6 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
} S_800CD6E0_6;   /* spr in dungeonCreateFourOwnerSpriteEffects */

typedef struct S_800CD6E0_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
    u16 unk_0A;
} S_800CD6E0_7;   /* link in dungeonCreateFourOwnerSpriteEffects */

/* Conditionally creates four sprites around the source owner. */
s32 dungeonCreateFourOwnerSpriteEffects(void *source, s16 slot_index, s32 slot_bits) {
    void *effect;
    S_800CD6E0_1 *owner;
    S_800CD6E0_4 *position;
    S_800CD6E0_6 *sprite;
    S_800CD6E0_7 *effect_link;
    s32 color;
    s16 *x_offsets;
    DungeonGlobalStatus *effect_counts;
    s32 effect_index;
    s32 random;
    s16 roll;
    s32 spawn_roll;
    s32 owner_coord;
    s32 owner_coord_2;
    s32 y_offset;
    s32 y_table;
    s32 y_entry;
    void *update_callback;

    if (D_800E3D40 != 0) {
        roll = 0;
    } else {
        random = func_800A6D30() & 0xFFFF;
        if (((S_800CD6E0_0 *)source)->unk_03 != 0) {
            roll = random % ((S_800CD6E0_0 *)source)->unk_03;
        } else {
            roll = 0;
        }
    }

    if (roll < 0x30) {
        owner = ((S_800CD6E0_0_pre *)source)[-1].unk_00;
        if (owner->unk_14 & 0x8000) {
            dungeonApplyModeSelectedTrapMask(source, 0x10);
            return 1;
        }
        if (hasEnoughAvailableRuntimeNodes(4) == 0) {
            return 0;
        }

        effect_index = 0;
        update_callback = (void *)D_800CD474;
        effect_counts = &dungeonStatus;
        x_offsets = dirStepX;
        for (; effect_index < 4; x_offsets += 2) {
            ((S_800CD6E0_2 *)((effect = func_8003FC64(2))))->unk_10 = update_callback;
            func_8004491C(effect, func_80045C34);
            color = 0x808080;
            y_offset = effect_index << 2;

            owner_coord_2 = owner->unk_24 << 6;
            spawn_roll = *x_offsets;
            position = ((S_800CD6E0_3 *)effect)->unk_08;
            spawn_roll = (spawn_roll << 5) + 0x20;
            owner_coord_2 += spawn_roll;
            y_table = (u32)dirStepY;
            y_entry = y_offset + y_table;
            y_table = owner_coord_2;
            position->unk_02 = y_table;
            owner_coord = owner->unk_25 << 6;
            spawn_roll = *(s16 *)y_entry;
            spawn_roll = (spawn_roll << 5) + 0x20;
            owner_coord += spawn_roll;
            position->unk_06 = owner_coord;
            position->unk_0A = ((S_800CD6E0_0 *)source)->unk_88 - 0x200;

            sprite = ((S_800CD6E0_3 *)effect)->unk_0C;
            spawn_roll = 0x1000;
            sprite->unk_1C = spawn_roll;
            spawn_roll = 0x2000;
            sprite->unk_1E = spawn_roll;
            spawn_roll = (s32)D_800E03E0;
            sprite->unk_08 = (void *)spawn_roll;
            sprite->unk_10 = 0x20;
            sprite->unk_16 = 0x400;
            sprite->unk_0C = color;
            sprite->unk_18 = (effect_index << 10) + 0x400;
            sprite->unk_14 |= 0xC;

            effect_link = (S_800CD6E0_7 *)((u8 *)effect + 0x20);
            effect_link->unk_0A = ((S_800CD6E0_0 *)source)->unk_88;
            ((S_800CD6E0_3 *)effect)->unk_20 = source;
            effect_link->unk_06 = 0xC;
            color = effect_index;
            effect_link->unk_08 = color;
            ((S_800CD6E0_3 *)effect)->unk_20 = source;
            effect_index++;
            effect_counts->unk_0A++;
            func_800A56E0(0x50D);
        }

        return 1;
    }

    if (((S_800CD6E0_0 *)source)->unk_13 == 0) {
        func_800A6508();
    }
    return 1;
}
