#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

typedef struct {
    s32 words[8];
} __attribute__((packed)) LocalTable;

extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80045340;
extern u8 D_800DEAE0[];
extern LocalTable D_8016482C;
extern M2C_UNK D_80167540[3];
extern s32 D_80175D50;


typedef struct S_801677FC_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801677FC_0;   /* (void *)D_80175D50 in func_801677FC */

typedef struct S_801677FC_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_801677FC_1;   /* temp_v1 in func_801677FC */

typedef struct S_801677FC_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801677FC_2;   /* temp_v0 in func_801677FC */

typedef struct S_801677FC_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801677FC_3;   /* temp_a0 in func_801677FC */

typedef struct S_801677FC_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_801677FC_4;   /* temp_a0_2 in func_801677FC */

typedef struct S_801677FC_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801677FC_5;   /* temp_s2 in func_801677FC */

typedef struct S_801677FC_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801677FC_6;   /* temp_s3 in func_801677FC */

typedef struct S_801677FC_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801677FC_7;   /* temp_a0_3 in func_801677FC */

/* Spawn sixteen effects offset in the current object's facing direction with increasing sizes. */
void func_801677FC(void)
{
    LocalTable direction_offsets;
    s32 size_step;
    s32 effect_index;
    u8 *direction_entry;
    S_801677FC_3 *render_flags;
    S_801677FC_4 *effect_pos;
    S_801677FC_7 *sprite;
    S_801677FC_5 *source_pos;
    S_801677FC_6 *source_state;
    void *effect;
    S_801677FC_1 *effect_state;

    direction_offsets = D_8016482C;
    effect_index = 0;
    source_state = (void *)D_80175D50 + 0x20;
    source_pos = ((S_801677FC_0 *)((void *)D_80175D50))->unk_08;
    do {
        effect = func_8003FC64(0x212);
        if (effect != NULL) {
            effect_state = effect + 0x20;
            effect_state->unk_18 = 0xE;
            effect_state->unk_1A = 0xE;
            ((S_801677FC_2 *)effect)->unk_10 = D_80167540;
            func_8004491C(effect, &D_80045340);
            render_flags = ((S_801677FC_2 *)effect)->unk_0C;
            render_flags->unk_10 = 0x60;
            render_flags->unk_14 =
                (u16)(render_flags->unk_14 | 0xC);
            effect_pos = ((S_801677FC_2 *)effect)->unk_08;
            effect_pos->unk_00.at00.v = source_pos->unk_00;
            effect_pos->unk_04.at00.v = source_pos->unk_04;
            effect_pos->unk_08 =
                source_pos->unk_08 + (s32)0xFFCE0000;
            effect_pos->unk_00.at02.v =
                (u16)(effect_pos->unk_00.at02.v +
                ((*(s16 *)((u8 *)(&direction_offsets) + ((source_state->unk_2A >> 7) & 0x1C))) * 0x14));
            size_step = effect_index << 9;
            direction_entry = (u8 *)&direction_offsets + ((source_state->unk_2A >> 7) & 0x1C);
            effect_pos->unk_04.at02.v =
                (u16)(effect_pos->unk_04.at02.v +
                ((s16)*(u16 *)(direction_entry + 2) * 0x14));
            sprite = ((S_801677FC_2 *)effect)->unk_0C;
            sprite->unk_1C = (s16)(size_step + 0x1C00);
            sprite->unk_1E = (s16)(size_step + 0x1400);
            sprite->unk_0E = 0;
            sprite->unk_0D = 0;
            sprite->unk_0C = 0;
            sprite->unk_06 = 0;
            sprite->unk_12 = 0x7DCF;
            sprite->unk_14 =
                (u16)(sprite->unk_14 | 0x100);
            func_8003DB94(sprite, D_800DEAE0, 0);
        }
        effect_index += 1;
    } while (effect_index < 0x10);
}
