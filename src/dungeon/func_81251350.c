#include "common.h"
#include "m2c_compat.h"

typedef struct S_80170B50_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void ** unk_10;
} S_80170B50_0;   /* temp_v0 in func_80170B50 */

typedef struct S_80170B50_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    u8 pad_96[0x16];
    s32 unk_AC;
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    s16 unk_B6;
} S_80170B50_1;   /* temp_s2 in func_80170B50 */

typedef struct S_80170B50_2 {
    void * unk_00;
    u8 pad_04[0x3A];
    u16 unk_3E;
} S_80170B50_2;   /* arg0 in func_80170B50; pointer addresses record offset 0x14 */

typedef struct S_80170B50_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    M2C_UNK * unk_2C;
} S_80170B50_3;   /* temp_s1 in func_80170B50 */

typedef struct S_80170B50_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170B50_4;   /* temp_s0 in func_80170B50 */

typedef struct S_80170B50_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170B50_5;   /* arg1 in func_80170B50 */

typedef struct S_80170B50_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80170B50_6;   /* temp_a1 in func_80170B50 */

typedef struct S_80170B50_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80170B50_7;   /* arg2 in func_80170B50 */


typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Copy4;

extern u8 D_80083498[];
extern void *D_80170898[];
extern u8 D_80045340[];
extern s16 D_80083228[5];
extern M2C_UNK D_80173EB4;
extern s32 func_8003DE58();
extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern M2C_UNK func_80047784();

/* Creates an attached sprite object with copied appearance and an optional position offset. */
void func_80170B50(void *owner_data, S_80170B50_5 *base_position, void *sprite_template, s16 offset_id) {
    u32 sprite_flags;
    u16 sprite_height;
    s16 saved_offset_id;
    S_80170B50_6 *owner_model;
    S_80170B50_4 *position;
    void *sprite;
    void *object_data;
    void *object;
    void *copy_dst;
    void *copy_src;

    saved_offset_id = offset_id;
    object = func_8003FD64(0x112, D_80083498);
    if (object != NULL) {
        object_data = object + 0x20;
        ((S_80170B50_0 *)object)->unk_10 = D_80170898;
        ((S_80170B50_1 *)object_data)->unk_B6 = offset_id;
        ((S_80170B50_1 *)object_data)->unk_AC = (s32) (owner_data - 0x20);
        ((S_80170B50_1 *)object_data)->unk_94 = (u16) ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_3E;
        copy_src = sprite_template;
        ((S_80170B50_1 *)object_data)->unk_2A = (u16) ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_3E;
        sprite = ((S_80170B50_0 *)object)->unk_0C;
        copy_dst = sprite;
        do {
            *(Copy4 *)copy_dst = *(Copy4 *)copy_src;
            copy_src += 0x10;
            copy_dst += 0x10;
        } while (copy_src != (sprite_template + 0x30));
        func_8004491C(object, D_80045340, copy_dst, copy_src);
        ((S_80170B50_3 *)sprite)->unk_2C = &D_80173EB4;
        func_80047784(sprite, *((u8 *)&D_80173EB4 + ((((s32) (*D_80083228 + (s16) ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_3E + 0x100) >> 9) & 7))), 0);
        ((S_80170B50_3 *)sprite)->unk_10 = 0x20;
        sprite_flags = ((S_80170B50_3 *)sprite)->unk_14 | 0xC;
        ((S_80170B50_3 *)sprite)->unk_14 = sprite_flags;
        *(volatile u16 *)((s8 *)sprite + 0x14) = sprite_flags | 0x80;
        position = ((S_80170B50_0 *)object)->unk_08;
        position->unk_02 = (u16) base_position->unk_02;
        position->unk_06 = (u16) base_position->unk_06;
        position->unk_0A = (u16) base_position->unk_0A;
        owner_model = ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_00;
        if (func_8003DE58(owner_model->unk_08, owner_model, object_data + 0xB0, saved_offset_id) != 0) {
            position->unk_02 = (u16) (position->unk_02 + ((S_80170B50_1 *)object_data)->unk_B0);
            position->unk_06 = (u16) (position->unk_06 + ((S_80170B50_1 *)object_data)->unk_B2);
            position->unk_0A = (u16) (position->unk_0A + ((S_80170B50_1 *)object_data)->unk_B4);
        }
        ((S_80170B50_3 *)sprite)->unk_1C = (u16) ((S_80170B50_7 *)sprite_template)->unk_1C;
        sprite_height = (u16) ((S_80170B50_7 *)sprite_template)->unk_1E;
        ((S_80170B50_3 *)sprite)->unk_0E = 0x80;
        ((S_80170B50_3 *)sprite)->unk_0D = 0x80;
        ((S_80170B50_3 *)sprite)->unk_0C = 0x80;
        ((S_80170B50_3 *)sprite)->unk_1E = sprite_height;
    }
}
