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

void func_80174D24(void *arg0, void *arg1, void *arg2)
{
    u16 local[3];
    void *object;
    Copy24 *source;
    register s32 copy0 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 copy1;
    register s32 copy2 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 copy3 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 call_zero;
    s32 call_arg0;
    s32 mode;
    u16 old_count;
    register u16 count ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 signed_count ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 flags;

    if (((S_80174D24_4 *)(((S_80174D24_0 *)arg0)->unk_08))->unk_2C != &D_80175F38) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto out;
    }

    source = ((S_80174D24_0 *)arg0)->unk_04;
    copy0 = source->words[0];
    copy1 = source->words[1];
    copy2 = source->words[2];
    copy3 = source->words[3];
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80174D24_1 *)arg1)->unk_00.at00.v = copy0;
    ((S_80174D24_1 *)arg1)->unk_04.at00.v = copy1;
    ((S_80174D24_1 *)arg1)->unk_08.at00.v = copy2;
    ((S_80174D24_1 *)arg1)->unk_0C = copy3;
    copy0 = source->words[4];
    copy1 = source->words[5];
    ((S_80174D24_1 *)arg1)->unk_10 = copy0;
    ((S_80174D24_1 *)arg1)->unk_14 = copy1;

    object = ((S_80174D24_0 *)arg0)->unk_08;
    ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    call_zero = 0;
    ASM_KEEP(call_zero);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    call_arg0 = ((S_80174D24_2 *)object)->unk_08;
    if (func_8003DE58(call_arg0, object,
                      (s16 *)local, call_zero) != 0) {
        ((S_80174D24_1 *)arg1)->unk_00.at02.v += local[0];
        ((S_80174D24_1 *)arg1)->unk_04.at02.v += local[1];
        ((S_80174D24_1 *)arg1)->unk_08.at02.v += local[2];
    }

    old_count = ((S_80174D24_0 *)arg0)->unk_02;
    mode = ((S_80174D24_0 *)arg0)->unk_00.s;
    count = old_count + 1;
    ASM_KEEP(old_count);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ((S_80174D24_0 *)arg0)->unk_02 = count;

    if (mode == 0) {
        goto mode_zero;
    }
    if (mode == 1) {
        goto mode_one;
    }
    goto out;

mode_zero:
    func_800478B8(arg2);
    flags = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
    if ((flags & 0x6000) == 0) {
        goto out;
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = flags | 0x80;
    ((S_80174D24_0 *)arg0)->unk_02 = 0;
    ((S_80174D24_0 *)arg0)->unk_00.u++;
    goto out;

mode_one:
    signed_count = (s16)count;
    if (signed_count < 0x40) {
        goto out;
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xFF7F;
    func_80047784(arg2, 0x38, 0);
    ((S_80174D24_0 *)arg0)->unk_02 = 0;
    ((S_80174D24_0 *)arg0)->unk_00.s = 0;

out:
    return;
}

/* MECHANISM: True-space epilogue joins and a u16[3] output object produce the 0x28 frame.
   Four guarded short-lived copy pins reproduce retail's v1/a0/a1/a2 copy roles.
   Ordering mode_zero before mode_one removes the word-61 displacement cascade. */
