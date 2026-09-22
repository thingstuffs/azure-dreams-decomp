#include "common.h"
#include "m2c_compat.h"

typedef struct S_818B7BD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818B7BD0_0;   /* obj in func_818B7BD0 */

typedef struct S_818B7BD0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    union { s16 s16; u8 u8; } unk_0E;   /* accessed as both */
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_18;   /* overlapping accesses */
    s16 unk_1C;
    s16 unk_1E;
} S_818B7BD0_1;   /* render in func_818B7BD0 */

typedef struct S_818B7BD0_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x4];
    s32 unk_18;
} S_818B7BD0_2;   /* owner in func_818B7BD0 */

typedef struct S_818B7BD0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818B7BD0_3;   /* transform in func_818B7BD0 */

typedef struct S_818B7BD0_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818B7BD0_4;   /* dst in func_818B7BD0 */


typedef union {
    s64 value;
    s32 word[2];
} M2C_WIDE;

#if defined(__mips__) || defined(mips)
#define M2C_HIGH_WORD(product) ((product).word[0])
#else
#define M2C_HIGH_WORD(product) ((s32) ((u64) (product).value >> 32))
#endif

void func_8003DB94(void *, void *, s32);
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern M2C_UNK D_800250E8;
extern M2C_UNK D_80025EE4;
extern M2C_UNK D_80045C34;

/* Spawn a 0x212 effect object for the owner with a random variant and spin, and copy the transform into it. */
s32 func_818B7BD0(S_818B7BD0_2 *owner, S_818B7BD0_3 *transform) {
    s32 roll;
    s32 random;
    s32 adjusted;
    s32 result;
    void *model;
    void *update_handler;
    S_818B7BD0_1 *render;
    S_818B7BD0_1 *part;
    void *obj;
    S_818B7BD0_4 *dst;

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        update_handler = &D_800250E8;
        part = obj + 0x20;
        ((S_818B7BD0_0 *)obj)->unk_10 = update_handler;
        ((S_818B7BD0_0 *)obj)->unk_20 = owner;
        part->unk_0E.s16 = 0;
        part->unk_10 = 0;
        roll = func_80069EF8();
        model = &D_80025EE4;
        part->unk_12 = (s16)(roll % 7);
        part->unk_14 = (u16) owner->unk_12;
        part->unk_18.at00.v = (s32) owner->unk_18;
        render = ((S_818B7BD0_0 *)obj)->unk_0C;
        render->unk_0E.u8 = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;
        render->unk_12 = 0x7E00;
        render->unk_14 = (u16) (render->unk_14 | 0x100);
        func_8003DB94(render, model, 0);
        adjusted = func_80069EF8();
        random = adjusted;
        if (random < 0) {
            adjusted = random + 0xFFF;
        }
        render->unk_18.at02.v = (s16) (random - ((adjusted >> 0xC) << 0xC));
        render->unk_1E = 0x400;
        render->unk_1C = 0x400;
        func_8004491C(obj, &D_80045C34);
        dst = ((S_818B7BD0_0 *)obj)->unk_08;
        result = (s32) obj;
        *dst = *(S_818B7BD0_4 *)transform;
        return result;
    }
    return 0;
}
