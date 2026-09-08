#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80024750;
extern Copy12 D_80025E64;
extern M2C_UNK D_80045340;


typedef struct S_818FF5B8_0 {
    u8 pad_00[0x2C];
    void * unk_2C;
    s32 unk_30;
    void ** unk_34;
} S_818FF5B8_0;   /* temp_v1 in func_818FF5B8 */

typedef struct S_818FF5B8_1 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_818FF5B8_1;   /* *arg0 in func_818FF5B8 */

typedef struct S_818FF5B8_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818FF5B8_2;   /* temp_a3 in func_818FF5B8 */

typedef struct S_818FF5B8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF5B8_3;   /* temp_v1_2 in func_818FF5B8 */

typedef struct S_818FF5B8_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818FF5B8_4;   /* arg1 in func_818FF5B8 */

typedef struct S_818FF5B8_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_818FF5B8_5;   /* arg2 in func_818FF5B8 */

/* Creates an owner-linked object with the supplied position and appearance. */
void func_818FF5B8(void **owner_ref, S_818FF5B8_4 *spawn_pos, S_818FF5B8_5 *appearance) {
    S_818FF5B8_2 *sprite;
    void *object;
    S_818FF5B8_0 *state;
    S_818FF5B8_3 *position;
    register u8 *copy_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register Copy12 *copy_src ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 copy0 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u32 copy4 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 copy8 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    object = func_8003FC64(0x212);
    state = object + 0x20;
    if (object != NULL) {
        state->unk_2C = (void *) *owner_ref;
        state->unk_30 = (s32) ((S_818FF5B8_1 *)(*owner_ref))->unk_60;
        state->unk_34 = owner_ref;
        (*(M2C_UNK **)((u8 *)object + 0x10)) = &D_80024750;
        func_8004491C(object, &D_80045340);
        sprite = (*(void **)((u8 *)object + 0xC));
        sprite->unk_10 = 0x20;
        sprite->unk_06 = 0;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        position = (*(void **)((u8 *)object + 8));
        position->unk_00 = (s32) spawn_pos->unk_00;
        position->unk_04 = (s32) spawn_pos->unk_04;
        position->unk_08 = (s32) spawn_pos->unk_08;
        sprite = (*(void **)((u8 *)object + 0xC));
        sprite->unk_1E = 0x800;
        sprite->unk_1C = 0x800;
        sprite->unk_0C = (u8) appearance->unk_0C;
        sprite->unk_0D = (u8) appearance->unk_0D;
        sprite->unk_0E = (u8) appearance->unk_0E;
        sprite->unk_1A = (s16) (0x1000 - appearance->unk_1A);
        ASM_KEEP(sprite);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        copy_page = (u8 *) 0x80020000;
        ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        copy_src = (Copy12 *) (copy_page + 0x5E64);
        copy0 = copy_src->word0;
        copy4 = copy_src->word4;
        copy8 = copy_src->word8;
        (*(Copy12 *)((u8 *)object + 0x40)).word0 = copy0;
        (*(Copy12 *)((u8 *)object + 0x40)).word4 = copy4;
        (*(Copy12 *)((u8 *)object + 0x40)).word8 = copy8;
        ASM_KEEP(copy8);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sprite->unk_08 = (void *) (object + 0x40);
    }
}

/* MECHANISM: Reordered header stores and reused/pinned the subobject in retail $a3.
   A pinned a2/v1/a0/a1 packed copy plus ASM_KEEP seams preserves load-delay nops.
   An opaque v0-held 0x80020000 page yields retail's split lui/addiu address pair. */
