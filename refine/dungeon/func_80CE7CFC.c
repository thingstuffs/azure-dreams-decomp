#include "common.h"


typedef struct { s32 w0, w1, w2, w3; } Blk16;

extern void *func_8003FD64();
extern s32 func_8003DE58();
extern void func_8004491C();
extern void func_80047784();

extern s16 D_80083228;
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_800DDC40[];
extern u8 D_80170DC4[];
extern u8 D_80175EB4[];
extern u8 D_80175EBC[];


typedef struct S_801714FC_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x12];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    union { s32 i; void * p; } unk_60;   /* accessed as both */
    u8 pad_64[0xE];
    union { s8 s; u8 u; } unk_72;   /* accessed as both */
    union { s8 s; u8 u; } unk_73;   /* accessed as both */
} S_801714FC_0;   /* arg3 in func_801714FC */

typedef struct S_801714FC_1 {
    u8 pad_00[0x94];
    s16 unk_94;
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
} S_801714FC_1;   /* v1 in func_801714FC */

typedef struct S_801714FC_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801714FC_2;   /* s2 in func_801714FC */

typedef struct S_801714FC_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801714FC_3;   /* s0v in func_801714FC */

typedef struct S_801714FC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801714FC_4;   /* q in func_801714FC */

typedef struct S_801714FC_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801714FC_5;   /* arg1 in func_801714FC */

typedef struct S_801714FC_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801714FC_6_pre;   /* the 0x14 bytes before arg0 in func_801714FC, addressed as arg0[-1] */

typedef struct S_801714FC_7 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_801714FC_7;   /* r in func_801714FC */

typedef struct S_801714FC_8_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_801714FC_8_pre;   /* the 0x18 bytes before ((S_801714FC_0 *)arg3)->unk_60.p in func_801714FC, addressed as ((S_801714FC_0 *)arg3)->unk_60.p[-1] */

typedef struct S_801714FC_8 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_801714FC_8;   /* ((S_801714FC_0 *)arg3)->unk_60.p in func_801714FC */

/* Create and position an effect using a linked object or stored tile coordinates. */
void func_801714FC(void *source_object, void *source_pos, void *sprite_template, void *actor)
{
    void *effect;
    void *effect_state;
    void *effect_data;
    void *template_data;
    void *linked_pos;
    u16 pos_offset[4];

    if (((S_801714FC_0 *)actor)->unk_60.i == 0 && ((S_801714FC_0 *)actor)->unk_72.s >= 0) {
        return;
    }
    effect = func_8003FD64(0x112, &D_80083498);
    if (effect == 0) {
        return;
    }
    effect_state = (u8 *)effect + 0x20;
    ((S_801714FC_1 *)effect_state)->unk_96 = 0xa;
    ((S_801714FC_1 *)effect_state)->unk_9E = 0xa;
    ((S_801714FC_2 *)effect)->unk_10 = (void *)&D_80170DC4;
    ((S_801714FC_1 *)effect_state)->unk_94 = ((S_801714FC_0 *)actor)->unk_2A.u;
    effect_data = ((S_801714FC_2 *)effect)->unk_0C;
    template_data = sprite_template;
    {
        Blk16 *src_block = (Blk16 *)template_data;
        Blk16 *dst_block = (Blk16 *)effect_data;
        Blk16 *src_end = src_block + 3;
        do {
            *dst_block = *src_block;
            dst_block++;
            src_block++;
        } while (src_block != src_end);
    }
    ((S_801714FC_3 *)effect_data)->unk_1E = 0x1000;
    ((S_801714FC_3 *)effect_data)->unk_1C = 0x1000;
    ((S_801714FC_3 *)effect_data)->unk_0E = 0x80;
    ((S_801714FC_3 *)effect_data)->unk_0D = 0x80;
    ((S_801714FC_3 *)effect_data)->unk_0C = 0x80;
    ((S_801714FC_3 *)effect_data)->unk_14 = ((S_801714FC_3 *)effect_data)->unk_14 & 0xfff3;
    func_8004491C(effect, &D_80045340);
    (*(void * *)((u8 *)effect_data + 0x2c)) = (void *)&D_80175EB4;
    func_80047784(effect_data,
        ((u8 *)&D_80175EB4)[(((s32)D_80083228 + (s32)((S_801714FC_0 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    effect_data = ((S_801714FC_2 *)effect)->unk_08;
    if (((S_801714FC_0 *)actor)->unk_60.i != 0 && (((S_801714FC_0 *)actor)->unk_14 & 0x04000000) == 0) {
        u8 *direction_offsets = (u8 *)&D_80175EBC;
        linked_pos = ((S_801714FC_8_pre *)(((S_801714FC_0 *)actor)->unk_60.p))[-1].unk_00;
        ((S_801714FC_3 *)effect_data)->unk_02 = ((S_801714FC_4 *)linked_pos)->unk_02
            - ((*(s16 *)((u8 *)direction_offsets + ((((S_801714FC_0 *)actor)->unk_2A.u >> 7) & 0x1c))) * 0x10);
        ((S_801714FC_3 *)effect_data)->unk_06 = ((S_801714FC_4 *)linked_pos)->unk_06
            - ((*(s16 *)((u8 *)direction_offsets + (((((S_801714FC_0 *)actor)->unk_2A.u >> 7) & 0x1c) + 2))) * 0x10);
        ((S_801714FC_3 *)effect_data)->unk_0A = ((S_801714FC_4 *)linked_pos)->unk_0A
            - (D_800DDC40[((S_801714FC_8 *)(((S_801714FC_0 *)actor)->unk_60.p))->unk_13] >> 1);
        return;
    }
    if (((S_801714FC_0 *)actor)->unk_72.s < 0) {
        s32 tile_x, tile_y;
        ((S_801714FC_0 *)actor)->unk_72.u = -(u8)((S_801714FC_0 *)actor)->unk_72.u;
        if (((S_801714FC_0 *)actor)->unk_73.s < 0) {
            ((S_801714FC_0 *)actor)->unk_73.u = -(u8)((S_801714FC_0 *)actor)->unk_73.u;
        }
        tile_x = ((S_801714FC_0 *)actor)->unk_72.s;
        ((S_801714FC_3 *)effect_data)->unk_02 = (tile_x << 6) + 0x20;
        tile_y = ((S_801714FC_0 *)actor)->unk_73.s;
        ((S_801714FC_3 *)effect_data)->unk_06 = (tile_y << 6) + 0x20;
        ((S_801714FC_3 *)effect_data)->unk_0A = ((S_801714FC_5 *)source_pos)->unk_0A;
        {
            void *source_data = ((S_801714FC_6_pre *)source_object)[-1].unk_00;
            if (func_8003DE58(((S_801714FC_7 *)source_data)->unk_08, source_data, pos_offset, 0) != 0) {
                ((S_801714FC_3 *)effect_data)->unk_0A = ((S_801714FC_3 *)effect_data)->unk_0A + pos_offset[2];
                return;
            }
        }
        ((S_801714FC_3 *)effect_data)->unk_0A = ((S_801714FC_3 *)effect_data)->unk_0A - 0x28;
    }
}
