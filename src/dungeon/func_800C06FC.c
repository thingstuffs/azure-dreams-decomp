#include "common.h"
#include "m2c_compat.h"

typedef struct CounterBlock {
    u8 pad[0xA];
    u16 count;
} CounterBlock;

M2C_UNK func_8003DB94();        /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80045C34;
extern CounterBlock D_80083460;
extern M2C_UNK D_800C5D80;

typedef struct S_800C5E5C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800C5E5C_0;   /* temp_v0 in func_800C5E5C */

typedef struct S_800C5E5C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C5E5C_1;   /* temp_v0_2 in func_800C5E5C */

typedef struct S_800C5E5C_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C5E5C_2;   /* temp_s0 in func_800C5E5C */

typedef struct S_800C5E5C_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    s16 unk_10;
} S_800C5E5C_3;   /* temp_v0_3 in func_800C5E5C */

/* Spawn twelve effects at the given position, optionally playing a sound. */
void func_800C5E5C(s16 x, s16 y, s16 z, s32 sprite_id, s16 play_sound) {
    M2C_UNK object_type;
    s32 effect_index;
    s32 effect_offset;
    s32 size;
    S_800C5E5C_2 *sprite;
    CounterBlock *counter;
    void *effect;
    S_800C5E5C_1 *transform;
    S_800C5E5C_3 *effect_state;
    u16 sprite_flags;

    if (play_sound != 0) {
        func_800A56E0(0x816);
    }
    effect_index = 0xB;
    size = 0x20;
    counter = &D_80083460;
    effect_offset = 0xFFFA0000;
    do {
        object_type = 0x12;
        if (effect_index != 0) {
            object_type = 0x212;
            effect = func_8003FC64(object_type);
        } else {
            effect = func_8003FC64(object_type);
        }
        if (effect != NULL) {
            ((S_800C5E5C_0 *)effect)->unk_10 = &D_800C5D80;
            func_8004491C(effect, &D_80045C34);
            transform = ((S_800C5E5C_0 *)effect)->unk_08;
            transform->unk_02 = x;
            transform->unk_06 = y;
            transform->unk_0A = z;
            transform->unk_14 = effect_offset;
            sprite = ((S_800C5E5C_0 *)effect)->unk_0C;
            func_8003DB94(sprite, sprite_id, 0);
            sprite_flags = sprite->unk_14;
            {
                s32 color;
                color = 0x808080;
                sprite->unk_0C = color;
            }
            {
                s32 scale;
                scale = 0x1000;
                sprite->unk_1E = scale;
                sprite->unk_1C = scale;
            }
            effect_state = effect + 0x20;
            sprite->unk_10 = size;
            sprite_flags |= 0xC;
            sprite->unk_14 = sprite_flags;
            effect_state->unk_10 = size;
            effect_state->unk_0C = effect_index;
            if (effect_index == 0) {
                counter->count = (u16) (counter->count + 1);
            }
        }
        effect_offset += 0x8000;
        effect_index -= 1;
    } while (effect_index >= 0);
}
