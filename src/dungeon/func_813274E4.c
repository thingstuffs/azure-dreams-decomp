#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_8016ECE4_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8016ECE4_0;   /* base in dungeonSpawnConditionalSourceEffect */

typedef struct S_8016ECE4_1 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
    u8 pad_1A[0xA];
    void * unk_24;
    u8 pad_28[0x1C];
    s8 unk_44;
    s8 unk_45;
    s8 unk_46;
    s8 unk_47;
    s8 unk_48;
    s8 unk_49;
    u8 pad_4A[0x2];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_8016ECE4_1;

typedef struct S_8016ECE4_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8016ECE4_2;

typedef struct S_8016ECE4_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016ECE4_3;

typedef struct S_8016ECE4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8016ECE4_4;

typedef struct S_8016ECE4_5 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8016ECE4_5;

typedef struct S_8016ECE4_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x7E];
    s16 unk_AA;
} S_8016ECE4_6;


typedef struct {
    s16 field0;
    s16 field2;
} TableEntry;

s32 func_8004491C();
s32 func_80069EF8();
extern M2C_UNK D_800777F4;
extern u8 D_8016E528;
extern void *D_80174704[];
extern TableEntry D_80174708[];


/* Spawn and initialize an effect at the source position when its mode and status allow it. */
void dungeonSpawnConditionalSourceEffect(void) {
    s32 rounded_x;
    s32 rounded_y;
    u8 high_byte;
    u8 low_byte;
    u16 count;
    register S_8016ECE4_3 *sprite;
    S_8016ECE4_1 *effect_state;
    S_8016ECE4_5 *source_pos;
    S_8016ECE4_6 *source_state;
    void *effect;
    S_8016ECE4_4 *effect_pos;
    void *source;

    source = D_80174704[0];
    {
        u8 *addr = (u8 *)0x80010000;   /* integer page, two genuine reads of the 16-bit counter at 0x80013610 (decision 44; func_8132C638 uses the same counter) */
        low_byte = addr[0x3611];
        high_byte = addr[0x3610];
    }
    count = low_byte | (high_byte << 8);
    source_pos = ((S_8016ECE4_0 *)source)->unk_08;
    source_state = source + 0x20;
    if (((count & 3) == 1) && !(func_80069EF8(source) & 1)) {
        effect = func_8003FC64(0x12);
        if (effect != NULL) {
            effect_state = effect + 0x20;
            effect_state->unk_12 = 3;
            ((S_8016ECE4_2 *)effect)->unk_10 = &D_8016E528;
            func_8004491C(effect, func_80045340);
            sprite = ((S_8016ECE4_2 *)effect)->unk_0C;
            sprite->unk_14 = (u16) (sprite->unk_14 & 0xFFF3);
            effect_state->unk_24 = source_state;
            effect_pos = ((S_8016ECE4_2 *)effect)->unk_08;
            effect_pos->unk_02 = (u16) source_pos->unk_02.s;
            effect_pos->unk_06 = (u16) source_pos->unk_06.s;
            effect_pos->unk_0A = (s16) (source_pos->unk_0A - 0x80);
            effect_state->unk_50 = 0;
            effect_state->unk_4C = 0;
            effect_state->unk_54 = 0;
            effect_state->unk_60 = 0;
            effect_state->unk_18 = (s16) (((u16) source_state->unk_2A >> 9) & 7);
            sprite = ((S_8016ECE4_2 *)effect)->unk_0C;
            sprite->unk_1E = 0x1000;
            sprite->unk_1C = 0x1000;
            sprite->unk_06 = (s16) (D_80174708[((u16) source_state->unk_2A >> 9) & 7].field2 * 6);
            source_state->unk_AA = 0x4D;
            rounded_x = source_pos->unk_02.u;
            effect_state->unk_48 = (s8) (rounded_x / 64);
            rounded_y = source_pos->unk_06.u;
            effect_state->unk_49 = (s8) (rounded_y / 64);
            sprite->unk_0E = 0x80;
            sprite->unk_0D = 0x80;
            sprite->unk_0C = 0x80;
            sprite->unk_08 = &D_800777F4;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0x80);
            effect_state->unk_44 = 3;
            effect_state->unk_45 = 6;
            effect_state->unk_46 = 0;
            effect_state->unk_47 = 0;
        }
    }
}
