#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct {
    s32 words[6];
} Copy24;

extern s32 D_800814A0;
extern s32 D_80175F38;

s32 func_8003DE58(s32, void *, s16 *, s32);
void func_80047784(void *, s32, s32);
void func_800478B8(void *);



typedef struct S_80174D24_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    Copy24 * unk_04;
    void * unk_08;
} S_80174D24_0;   /* arg0 in func_80174D24 */

typedef struct S_80174D24_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174D24_1;   /* arg1 in func_80174D24 */

typedef struct S_80174D24_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174D24_2;   /* object in func_80174D24 */


typedef struct S_80174D24_4 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_80174D24_4;   /* ((S_80174D24_0 *)arg0)->unk_08 in func_80174D24 */

/* Copies object data with offsets and advances a timed target flag cycle. */
void func_80174D24(void *state, void *output, void *target)
{
    u16 offsets[3];
    void *object;
    Copy24 *source;
    s32 copy_word_a;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 copy_word_b;
    register s32 copy_word_c ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 copy_word_d ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 offset_mode;
    s32 object_id;
    s32 phase;
    u16 old_ticks;
    s32 signed_ticks;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 target_flags;

    if (((S_80174D24_4 *)(((S_80174D24_0 *)state)->unk_08))->unk_2C != &D_80175F38) {
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto out;
    }

    source = ((S_80174D24_0 *)state)->unk_04;
    copy_word_a = source->words[0];
    copy_word_b = source->words[1];
    copy_word_c = source->words[2];
    copy_word_d = source->words[3];
   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80174D24_1 *)output)->unk_00.at00.v = copy_word_a;
    ((S_80174D24_1 *)output)->unk_04.at00.v = copy_word_b;
    ((S_80174D24_1 *)output)->unk_08.at00.v = copy_word_c;
    ((S_80174D24_1 *)output)->unk_0C = copy_word_d;
    copy_word_a = source->words[4];
    copy_word_b = source->words[5];
    ((S_80174D24_1 *)output)->unk_10 = copy_word_a;
    ((S_80174D24_1 *)output)->unk_14 = copy_word_b;

    object = ((S_80174D24_0 *)state)->unk_08;
    offset_mode = 0;
    object_id = ((S_80174D24_2 *)object)->unk_08;
    if (func_8003DE58(object_id, object,
                      (s16 *)offsets, offset_mode) != 0) {
        ((S_80174D24_1 *)output)->unk_00.at02.v += offsets[0];
        ((S_80174D24_1 *)output)->unk_04.at02.v += offsets[1];
        ((S_80174D24_1 *)output)->unk_08.at02.v += offsets[2];
    }

    old_ticks = ((S_80174D24_0 *)state)->unk_02;
    phase = ((S_80174D24_0 *)state)->unk_00.s;
    copy_word_a = old_ticks + 1;
    ((S_80174D24_0 *)state)->unk_02 = copy_word_a;

    if (phase == 0) {
        goto mode_zero;
    }
    if (phase == 1) {
        goto mode_one;
    }
    goto out;

mode_zero:
    func_800478B8(target);
    target_flags = ((Rec_D_80082E80 *)target)->unk_14.at00_u16.v;
    if ((target_flags & 0x6000) == 0) {
        goto out;
        ((Rec_D_80082E80 *)target)->unk_14.at00_u16.v = target_flags | 0x80;
    } else {
        ((Rec_D_80082E80 *)target)->unk_14.at00_u16.v = target_flags | 0x80;
    }
    ((S_80174D24_0 *)state)->unk_02 = 0;
    ((S_80174D24_0 *)state)->unk_00.u++;
    goto out;

mode_one:
    signed_ticks = (s16)copy_word_a;
    if (signed_ticks < 0x40) {
        goto out;
    }
    ((Rec_D_80082E80 *)target)->unk_14.at00_u16.v &= 0xFF7F;
    func_80047784(target, 0x38, 0);
    ((S_80174D24_0 *)state)->unk_02 = 0;
    ((S_80174D24_0 *)state)->unk_00.s = 0;

out:
    return;
}

/* MECHANISM: True-space epilogue joins and a u16[3] output object produce the 0x28 frame.
   Four guarded short-lived copy pins reproduce retail's v1/a0/a1/a2 copy roles.
   Ordering mode_zero before mode_one removes the word-61 displacement cascade. */
