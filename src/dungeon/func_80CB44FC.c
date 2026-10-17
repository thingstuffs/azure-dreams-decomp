/* Relink of matched dungeon/func_80CAE4FC; every changed retail word is a paired relocation. */
#define D_8015D324 D_80157324
#include "modules/dungeon_ovl_ccb000.h"
extern void func_80155C0C(void *, s32, void *);
extern s32 rand(void);

void func_80155CFC(void *unused_context, Rec_func_80173CFC_arg1 *source_pos, s32 unused_value, s16 scale)
{
    void *effect;
    CL_CCB000_80173CFC_S_80173CFC_0 *effect_part;
    CL_CCB000_80173CFC_S_80173CFC_1 *effect_data;
    CL_CCB000_80173CFC_S_80173CFC_2 *effect_pos;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        effect_part = (u8 *)effect + 0x20;
        effect_part->unk_24 = 5;
        (*(void * *)((u8 *)effect + 0x10)) = func_80155C0C;
        func_8004491C(effect, func_80045340);
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
        (*(CL_CCB000_80173CFC_Copy12 *)((u8 *)effect + 0x9A)) = (*(CL_CCB000_80173CFC_Copy12 *)((u8 *)D_80157324 + 0));
        effect_data->unk_08 = (u8 *)effect + 0x9A;
    }
}

/* MECHANISM: The four-argument ABI keeps source_pos/scale in s3/s4 while effect, effect_data, and
   effect+0x20 occupy s2/s1/s0, producing retail's 0x28 frame and full save set.
   One packed 12-byte assignment emits the retail lwl/lwr and swl/swr copy. */
