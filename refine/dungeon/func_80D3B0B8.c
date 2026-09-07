#include "common.h"

typedef struct S_80D3B0B8_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x14];
    u8 * unk_AC;
} S_80D3B0B8_0;   /* temp_s3 in func_80D3B0B8 */

typedef struct S_80D3B0B8_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80D3B0B8_1;   /* temp_v0 in func_80D3B0B8 */

typedef struct S_80D3B0B8_2 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x84];
    u8 unk_B0;
} S_80D3B0B8_2;   /* saved_arg0 in func_80D3B0B8 */

typedef struct S_80D3B0B8_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80D3B0B8_3;   /* temp_s1 in func_80D3B0B8 */

typedef struct S_80D3B0B8_4 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_80D3B0B8_4;   /* base_80083160 in func_80D3B0B8 */

typedef struct S_80D3B0B8_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D3B0B8_5;   /* temp_v1 in func_80D3B0B8 */

typedef struct S_80D3B0B8_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D3B0B8_6;   /* saved_arg1 in func_80D3B0B8 */

typedef struct S_80D3B0B8_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80D3B0B8_7;   /* saved_arg2 in func_80D3B0B8 */


typedef struct Copy16 {
    s32 word[4];
} Copy16;


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void func_800BC26C(void *, s32, void *, void *);

extern s32 D_80045340;
extern u8 D_80083160[];
extern u8 D_80083498[];
extern u8 D_800D5594[];
extern s8 D_800DCECC[];
extern u8 D_800E23F0[];

/* Creates an owner-linked object with copied position and direction-adjusted sprite data. */
void func_80D3B0B8(u8 *owner_data, u8 *source_position, u8 *source_sprite) {
    u8 *owner = owner_data;
    u8 *position_src = source_position;
    u8 *sprite_src = source_sprite;
    u8 *object;
    register u8 *object_data ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *sprite;
    u8 *view_state;
    u8 *position;
    Copy16 *copy_dst;
    Copy16 *copy_src;
    Copy16 *copy_end;
    u8 *direction_table;

    object = func_8003FD64(0x112, D_80083498);
    object_data = object + 0x20;
    if (object != 0) {
        ((S_80D3B0B8_0 *)object_data)->unk_96 = 0x78;
        ((S_80D3B0B8_1 *)object)->unk_10 = D_800D5594;
        ((S_80D3B0B8_0 *)object_data)->unk_AC = owner - 0x20;
        ((S_80D3B0B8_0 *)object_data)->unk_94 = ((S_80D3B0B8_2 *)owner)->unk_2A.s;
        copy_src = (Copy16 *)sprite_src;
        ((S_80D3B0B8_0 *)object_data)->unk_2A = ((S_80D3B0B8_2 *)owner)->unk_2A.s;
        sprite = ((S_80D3B0B8_1 *)object)->unk_0C;

        copy_end = (Copy16 *)(sprite_src + 0x30);
        copy_dst = (Copy16 *)sprite;
        do {
            *copy_dst = *copy_src;
            copy_src++;
            copy_dst++;
        } while (copy_src != copy_end);
        ASM_KEEP(copy_dst);   /* MATCH pin: load-bearing for the whole function shape */

        func_8004491C(object, &D_80045340);
        direction_table = D_800E23F0;
        ((S_80D3B0B8_3 *)sprite)->unk_2C = direction_table;
        view_state = D_80083160;
        func_80047784(sprite,
            direction_table[((((S_80D3B0B8_4 *)view_state)->unk_C8 +
                ((S_80D3B0B8_2 *)owner)->unk_2A.u + 0x100) >> 9) & 7], 0);

        position = ((S_80D3B0B8_1 *)object)->unk_08;
        ((S_80D3B0B8_5 *)position)->unk_02 = ((S_80D3B0B8_6 *)position_src)->unk_02;
        ((S_80D3B0B8_5 *)position)->unk_06 = ((S_80D3B0B8_6 *)position_src)->unk_06;
        ((S_80D3B0B8_5 *)position)->unk_0A = ((S_80D3B0B8_6 *)position_src)->unk_0A;
        {
            u16 sprite_field_1c;
            u16 sprite_field_1e;

            sprite_field_1c = ((S_80D3B0B8_7 *)sprite_src)->unk_1C;
            ((S_80D3B0B8_3 *)sprite)->unk_1C = sprite_field_1c;
            sprite_field_1e = ((S_80D3B0B8_7 *)sprite_src)->unk_1E;
            ((S_80D3B0B8_3 *)sprite)->unk_0E = 0x80;
            ((S_80D3B0B8_3 *)sprite)->unk_0D = 0x80;
            ((S_80D3B0B8_3 *)sprite)->unk_0C = 0x80;
            ((S_80D3B0B8_3 *)sprite)->unk_1E = sprite_field_1e;
        }
        ((S_80D3B0B8_3 *)sprite)->unk_06 =
            D_800DCECC[((((S_80D3B0B8_4 *)view_state)->unk_C8 +
                ((S_80D3B0B8_2 *)owner)->unk_2A.u + 0x100) >> 9) & 7] * 4;
        ((S_80D3B0B8_2 *)owner)->unk_B0++;
        func_800BC26C(object, 0, sprite + 0x2C, object_data + 0x2A);
        ASM_KEEP(owner);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(position_src);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(sprite_src);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
}
