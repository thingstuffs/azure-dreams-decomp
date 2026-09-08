#include "common.h"
#include "m2c_compat.h"

typedef struct S_80172B00_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x14];
    s32 unk_AC;
} S_80172B00_0;   /* temp_s3 in func_80172B00 */

typedef struct S_80172B00_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80172B00_1;   /* temp_v0 in func_80172B00 */

typedef struct S_80172B00_2 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x84];
    u8 unk_B0;
} S_80172B00_2;   /* arg0 in func_80172B00 */

typedef struct S_80172B00_3 {
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
} S_80172B00_3;   /* temp_s1 in func_80172B00 */

typedef struct S_80172B00_4 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_80172B00_4;   /* base_83160 in func_80172B00 */

typedef struct S_80172B00_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80172B00_5;   /* temp_v1 in func_80172B00 */

typedef struct S_80172B00_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80172B00_6;   /* arg1 in func_80172B00 */

typedef struct S_80172B00_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80172B00_7;   /* arg2 in func_80172B00 */


void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C(); /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_800BC26C(); /* extern */
extern M2C_UNK D_80045340;
extern s8 D_80083160[];
extern s8 D_800DCECC[];
extern M2C_UNK D_80172610;
extern u8 D_80174C74[];

typedef struct {
    s32 words[4];
} CopyBlock;

/* Creates a child effect with copied position and sprite data and direction-dependent appearance. */
void func_80172B00(void *parent_data, S_80172B00_6 *source_pos, void *sprite_template) {
    s32 parent_object;
    void *sprite;
    void *effect_data;
    void *effect_object;
    S_80172B00_5 *effect_pos;
    s8 *view_state;
    register CopyBlock *copy_dst ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    CopyBlock *copy_src;
    register CopyBlock *copy_end ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    s32 word0;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 word1;
    s32 word2;
    s32 word3;
    u16 template_1c;
    void *setup_object;
    s32 direction_index;
    s32 parent_angle;
    s32 setup_mode;

    parent_object = parent_data - 0x20;
    effect_object = func_8003FD64(0x112, parent_object);
    effect_data = effect_object + 0x20;
    if (effect_object != NULL) {
        ((S_80172B00_0 *)effect_data)->unk_96 = 0x78;
        ((S_80172B00_1 *)effect_object)->unk_10 = &D_80172610;
        ((S_80172B00_0 *)effect_data)->unk_AC = parent_object;
        ((S_80172B00_0 *)effect_data)->unk_94 = (u16) ((S_80172B00_2 *)parent_data)->unk_2A.s;
        copy_src = (CopyBlock *) sprite_template;
        ((S_80172B00_0 *)effect_data)->unk_2A = (u16) ((S_80172B00_2 *)parent_data)->unk_2A.s;
        sprite = ((S_80172B00_1 *)effect_object)->unk_0C;
        copy_end = (CopyBlock *) (sprite_template + 0x30);
        copy_dst = (CopyBlock *) sprite;
        do {
            word0 = copy_src->words[0];
            word1 = copy_src->words[1];
            word2 = copy_src->words[2];
            word3 = copy_src->words[3];
   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            copy_dst->words[0] = word0;
            copy_dst->words[1] = word1;
            copy_dst->words[2] = word2;
            copy_dst->words[3] = word3;
            ASM_KEEP(copy_src);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            copy_src++;
            copy_dst++;
        } while (copy_src != copy_end);
        ASM_KEEP(copy_end);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_8004491C(effect_object, &D_80045340, copy_dst, copy_src);
        ((S_80172B00_3 *)sprite)->unk_2C = D_80174C74;
        view_state = D_80083160;
        func_80047784(sprite, D_80174C74[((s32) (((S_80172B00_4 *)view_state)->unk_C8 + (s16) ((S_80172B00_2 *)parent_data)->unk_2A.s + 0x100) >> 9) & 7], 0);
        effect_pos = ((S_80172B00_1 *)effect_object)->unk_08;
        effect_pos->unk_02 = (u16) source_pos->unk_02;
        effect_pos->unk_06 = (u16) source_pos->unk_06;
        effect_pos->unk_0A = (u16) source_pos->unk_0A;
        template_1c = ((S_80172B00_7 *)sprite_template)->unk_1C;
        ASM_KEEP(template_1c);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        setup_object = effect_object;
        ASM_KEEP(setup_object);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_80172B00_3 *)sprite)->unk_1C = template_1c;
        ((S_80172B00_3 *)sprite)->unk_1E = (u16) ((S_80172B00_7 *)sprite_template)->unk_1E;
        ((S_80172B00_3 *)sprite)->unk_0E = 0x80;
        ((S_80172B00_3 *)sprite)->unk_0D = 0x80;
        ((S_80172B00_3 *)sprite)->unk_0C = 0x80;
        direction_index = ((S_80172B00_4 *)view_state)->unk_C8;
        parent_angle = ((S_80172B00_2 *)parent_data)->unk_2A.u;
   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        setup_mode = 0;
        direction_index += parent_angle;
        direction_index += 0x100;
        direction_index >>= 9;
        direction_index &= 7;
        ((S_80172B00_3 *)sprite)->unk_06 = (s16) (D_800DCECC[direction_index] * 4);
        ((S_80172B00_2 *)parent_data)->unk_B0 = (u8) (((S_80172B00_2 *)parent_data)->unk_B0 + 1);
        func_800BC26C(setup_object, setup_mode, sprite + 0x2C, effect_data + 0x2A);
    }
}
/* MECHANISM: The 0x30 frame follows seven held callee-saved roles, including a reused &D_80083160 base.
   The 16-byte loop pins a3/a2/t0 and v0/v1/a0/a1 roles; guarded seams preserve load-all/store-all order.
   Byte-table types plus pinned call arguments and split v1 accumulator updates close the tail exactly. */
