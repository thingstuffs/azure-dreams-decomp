#include "common.h"


extern s32 func_8003FA44();
extern void *func_8003FC64();
extern void func_8004491C();
extern void func_800A56E0();
extern void func_800A6508();
extern s32 func_800A6D30(void *, s32, s32, s32);
extern void func_800CD6AC();

extern u8 D_80045C34[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u16 D_80083460[6];
extern u8 D_800CD474[];
extern u8 D_800E03E0[];
extern u8 D_800E3D40;


typedef struct S_800CD6E0_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD6E0_0_pre;   /* the 0x14 bytes before arg0 in func_800CD6E0, addressed as arg0[-1] */

typedef struct S_800CD6E0_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xF];
    u8 unk_13;
    u8 pad_14[0x74];
    u16 unk_88;
} S_800CD6E0_0;   /* arg0 in func_800CD6E0 */

typedef struct S_800CD6E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD6E0_1;   /* owner in func_800CD6E0 */

typedef struct S_800CD6E0_2 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800CD6E0_2;   /* (obj = func_8003FC64(2)) in func_800CD6E0 */

typedef struct S_800CD6E0_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x10];
    void * unk_20;
} S_800CD6E0_3;   /* obj in func_800CD6E0 */

typedef struct S_800CD6E0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD6E0_4;   /* prim in func_800CD6E0 */

typedef struct S_800CD6E0_5 {
    s16 unk_00;
} S_800CD6E0_5;   /* (void *)table_offset in func_800CD6E0 */

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
} S_800CD6E0_6;   /* spr in func_800CD6E0 */

typedef struct S_800CD6E0_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
    u16 unk_0A;
} S_800CD6E0_7;   /* link in func_800CD6E0 */

/* Conditionally creates four sprites around the source owner. */
s32 func_800CD6E0(void *source, s32 passthrough_1, s32 passthrough_2, s32 passthrough_3) {
    void *effect;
    S_800CD6E0_1 *owner;
    S_800CD6E0_4 *position;
    S_800CD6E0_6 *sprite;
    S_800CD6E0_7 *effect_link;
    s16 *x_offsets;
    u16 *effect_counts;
    s32 effect_index;
    register s32 random_or_effect_id ASM_REG("$4");
    s32 divisor;
    register s32 spawn_roll ASM_REG("$2");
    register s32 color ASM_REG("$7");
    register s32 roll_value ASM_REG("$3");
    s32 owner_coord;
    s32 coord;
    register s32 y_entry ASM_REG("$5");
    void *update_callback;

    if (D_800E3D40 == 0) {
        random_or_effect_id = func_800A6D30(source, passthrough_1, passthrough_2, passthrough_3) & 0xFFFF;
        roll_value = ((S_800CD6E0_0 *)source)->unk_03;
        if (roll_value != 0) {
            divisor = roll_value;
            ASM_KEEP(divisor);
            roll_value = random_or_effect_id % divisor;
            spawn_roll = roll_value;
            goto check_gate;
        }
    }

    spawn_roll = 0;
check_gate:
    if (spawn_roll < 0x30) {
        owner = ((S_800CD6E0_0_pre *)source)[-1].unk_00;
        if (owner->unk_14 & 0x8000) {
            func_800CD6AC(source, 0x10);
            return 1;
        }
        if (func_8003FA44(4) == 0) {
            return 0;
        }

        effect_index = 0;
        update_callback = (void *)D_800CD474;
        effect_counts = D_80083460;
        x_offsets = D_8006CCD8;
        do {
            ((S_800CD6E0_2 *)((effect = func_8003FC64(2))))->unk_10 = update_callback;
            func_8004491C(effect, D_80045C34);
            color = 0x808080;
            random_or_effect_id = 0x50D;
            ASM_KEEP_NV(random_or_effect_id);
            y_entry = effect_index << 2;

            owner_coord = owner->unk_24;
            coord = *x_offsets;
            position = ((S_800CD6E0_3 *)effect)->unk_08;
            owner_coord <<= 6;
            coord = (coord << 5) + 0x20;
            owner_coord += coord;
            coord = (u32)D_8006CCE8;
            y_entry += coord;
            position->unk_02 = owner_coord;
            owner_coord = owner->unk_25;
            coord = ((S_800CD6E0_5 *)((void *)y_entry))->unk_00;
            owner_coord <<= 6;
            coord = (coord << 5) + 0x20;
            owner_coord += coord;
            position->unk_06 = owner_coord;
            x_offsets += 2;
            position->unk_0A = ((S_800CD6E0_0 *)source)->unk_88 - 0x200;

            sprite = ((S_800CD6E0_3 *)effect)->unk_0C;
            coord = 0x1000;
            sprite->unk_1C = coord;
            coord = 0x2000;
            sprite->unk_1E = coord;
            coord = (s32)D_800E03E0;
            sprite->unk_08 = (void *)coord;
            sprite->unk_10 = 0x20;
            sprite->unk_16 = 0x400;
            sprite->unk_0C = color;
            sprite->unk_18 = (effect_index << 10) + 0x400;
            sprite->unk_14 |= 0xC;

            effect_link = (u8 *)effect + 0x20;
            effect_link->unk_0A = ((S_800CD6E0_0 *)source)->unk_88;
            ((S_800CD6E0_3 *)effect)->unk_20 = source;
            effect_link->unk_06 = 0xC;
            effect_link->unk_08 = effect_index;
            ((S_800CD6E0_3 *)effect)->unk_20 = source;
            effect_index++;
            effect_counts[5]++;
            func_800A56E0(random_or_effect_id, sprite, position, color);
        } while (effect_index < 4);

        return 1;
    }

    if (((S_800CD6E0_0 *)source)->unk_13 == 0) {
        func_800A6508(random_or_effect_id);
    }
    return 1;
}
