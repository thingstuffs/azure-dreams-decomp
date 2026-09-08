#include "common.h"
#include "records/Rec_func_80173CFC_arg1.h"


typedef struct {
    u32 word[3];
} __attribute__((packed)) Copy12;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);

extern u8 D_80045340;
extern u8 D_80173C0C;
extern u8 D_80175324[12];


typedef struct S_80173CFC_0 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x21];
    s16 unk_24;
} S_80173CFC_0;   /* part in func_80173CFC */

typedef struct S_80173CFC_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80173CFC_1;   /* data in func_80173CFC */

typedef struct S_80173CFC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80173CFC_2;   /* pos in func_80173CFC */


/* Creates an effect at an offset from the source position with randomized rotation. */
void func_80173CFC(void *unused_context, Rec_func_80173CFC_arg1 *source_pos, s32 unused_value, s16 scale)
{
    void *effect;
    S_80173CFC_0 *effect_part;
    S_80173CFC_1 *effect_data;
    S_80173CFC_2 *effect_pos;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        effect_part = (u8 *)effect + 0x20;
        effect_part->unk_24 = 5;
        (*(void * *)((u8 *)effect + 0x10)) = &D_80173C0C;
        func_8004491C(effect, &D_80045340);
        effect_data = (*(void * *)((u8 *)effect + 0xC));
        effect_data->unk_10 = 0x60;
        effect_data->unk_14 |= 0xC;
        effect_pos = (*(void * *)((u8 *)effect + 8));
        effect_pos->unk_02 = source_pos->unk_00.at02_u16.v;
        effect_pos->unk_06 = source_pos->unk_04.at02_u16.v;
        effect_pos->unk_0A = source_pos->unk_0A - 0x28;
        effect_data = (*(void * *)((u8 *)effect + 0xC));
        effect_data->unk_06 = 6;
        effect_data->unk_1E = scale;
        effect_data->unk_1C = scale;
        effect_part->unk_01 = 0x30;
        effect_part->unk_02 = 0x30;
        (*(s8 *)((u8 *)effect + 0x20)) = 0x30;
        effect_data->unk_0E = 0x30;
        effect_data->unk_0D = 0x30;
        effect_data->unk_0C = 0x30;
        effect_data->unk_1A = rand() & 0xFFF;
        (*(Copy12 *)((u8 *)effect + 0x9A)) = (*(Copy12 *)((u8 *)D_80175324 + 0));
        effect_data->unk_08 = (u8 *)effect + 0x9A;
    }
}

/* MECHANISM: The four-argument ABI keeps source_pos/scale in s3/s4 while effect, effect_data, and
   effect+0x20 occupy s2/s1/s0, producing retail's 0x28 frame and full save set.
   One packed 12-byte assignment emits the retail lwl/lwr and swl/swr copy. */
