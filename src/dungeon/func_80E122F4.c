#include "common.h"


typedef struct {
    s32 word[6];
} Copy24;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u16;

extern s32 func_8003DE58();
extern void *func_8003FC64();
extern void func_8004491C();
extern void func_80047784();
extern void func_80175CDC() __attribute__((noreturn));

extern s32 D_80045340;
extern u8 D_800DDC40[];
extern s32 D_80175978;


typedef struct S_80E122F4_0 {
    u8 pad_00[0x60];
    void * unk_60;
} S_80E122F4_0;   /* arg0 in func_80E122F4 */

typedef struct S_80E122F4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80E122F4_1;   /* child in func_80E122F4 */

typedef struct S_80E122F4_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x1C];
    s32 unk_28;
} S_80E122F4_2;   /* arg2_reg in func_80E122F4 */

typedef struct S_80E122F4_3 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_0C;   /* overlapping accesses */
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
} S_80E122F4_3;   /* part in func_80E122F4 */

typedef struct S_80E122F4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80E122F4_4;   /* coords in func_80E122F4 */

typedef struct S_80E122F4_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80E122F4_5;   /* reference in func_80E122F4 */

typedef struct S_80E122F4_6_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80E122F4_6_pre;   /* the 0x18 bytes before ((S_80E122F4_0 *)arg0)->unk_60 in func_80E122F4, addressed as ((S_80E122F4_0 *)arg0)->unk_60[-1] */

typedef struct S_80E122F4_6 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80E122F4_6;   /* ((S_80E122F4_0 *)arg0)->unk_60 in func_80E122F4 */

void *func_80E122F4(S_80E122F4_0 *arg0, void *arg1, void *arg2)
{
    Vec3u16 offset;
    S_80E122F4_5 *reference;
    void *obj;
    S_80E122F4_2 *arg2_reg;
    register void *ret ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    S_80E122F4_4 *coords;
    S_80E122F4_1 *child;
    S_80E122F4_3 *part;
    s32 delta;

    arg2_reg = arg2;
    reference = ((S_80E122F4_6_pre *)(arg0->unk_60))[-1].unk_00;
    obj = func_8003FC64(0x312);
    if (obj != 0) {
        (*(s32 * *)((u8 *)obj + 0x10)) = &D_80175978;
        func_8004491C(obj, &D_80045340);

        child = (*(void * *)((u8 *)obj + 0xC));
        child->unk_28 = arg2_reg->unk_28;
        child->unk_1E = 0x800;
        child->unk_1C = 0x800;
        child->unk_0C = 0x808080;
        child->unk_14 |= 0xC;
        child->unk_10 |= 0x20;
        func_80047784(child, 0x47, 0);

        coords = (*(void * *)((u8 *)obj + 8));
        (*(Copy24 *)((u8 *)obj + 0x24)) = *(Copy24 *)arg1;

        offset.z = 0;
        offset.y = 0;
        offset.x = 0;
        part = (u8 *)obj + 0x20;
        if (func_8003DE58(arg2_reg->unk_08, arg2_reg, &offset, 1) != 0) {
            part->unk_04.at02.v += offset.x;
            coords->unk_02 = part->unk_04.at02.v;
            part->unk_08.at02.v += offset.y;
            coords->unk_06 = part->unk_08.at02.v;
            part->unk_0C.at02.v += offset.z;
            coords->unk_0A = part->unk_0C.at02.v;
        }

        delta = reference->unk_00 - part->unk_04.at00.v;
        if (delta < 0) {
            delta += 31;
        }
        delta >>= 5;
        part->unk_10 = delta;
        delta = reference->unk_04 - part->unk_08.at00.v;
        if (delta < 0) {
            delta += 31;
        }
        delta >>= 5;
        part->unk_14 = delta;
        delta = (reference->unk_08 -
                 ((s32)D_800DDC40[((S_80E122F4_6 *)(arg0->unk_60))->unk_13] << 15) -
                 part->unk_0C.at00.v) / 32;
        part->unk_18 = delta;
        ret = obj;
        ASM_TAILSLOT_PIN(ret);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        func_80175CDC();
        return obj;
    }
    return 0;
}

/* MECHANISM: Reverse-order Vec3 zero stores and explicit negative-add-31/shift CFGs reproduce retail scheduling.
   Guarded $s0/$s1/$v0 roles preserve the 0x38 frame and return carrier under the noreturn tail contract.
   ASM_TAILSLOT_PIN sinks move $v0,$s1 into the LEAD-18 tail j slot after the final store. */
