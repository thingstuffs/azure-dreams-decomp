#include "common.h"


typedef struct LocalResult {
    s32 unk0;
    s16 value;
} LocalResult;

extern s32 func_8003DE58(void *, void *, LocalResult *, s32);
extern void func_800A2B04(void *, u8, u8);
extern s16 func_800BCB04(s32, s32, s16);
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;


typedef struct S_800AACA4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_800AACA4_0;   /* arg0 in func_800AACA4 */

typedef struct S_800AACA4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x40];
    void * unk_60;
    u8 pad_64[0x6];
    u16 unk_6A;
    u8 pad_6C[0x1E];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_800AACA4_1;   /* arg3 in func_800AACA4 */

typedef struct S_800AACA4_2_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800AACA4_2_pre;   /* the 0x18 bytes before root in func_800AACA4, addressed as root[-1] */

typedef struct S_800AACA4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    void * unk_28;
    void * unk_2C;
} S_800AACA4_3;   /* object in func_800AACA4 */

typedef struct S_800AACA4_4 {
    void * unk_00;
} S_800AACA4_4;   /* table in func_800AACA4 */

typedef struct S_800AACA4_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AACA4_5;   /* entry in func_800AACA4 */

typedef struct S_800AACA4_6 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800AACA4_6;   /* arg1 in func_800AACA4 */

typedef struct S_800AACA4_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800AACA4_7;   /* arg2 in func_800AACA4 */

typedef struct S_800AACA4_8 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_800AACA4_8;   /* ((S_800AACA4_1 *)arg3)->unk_60 in func_800AACA4 */

typedef struct S_800AACA4_9 {
    void * unk_00;
} S_800AACA4_9;   /* ((S_800AACA4_3 *)object)->unk_28 in func_800AACA4 */

typedef struct S_800AACA4_10 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800AACA4_10;   /* ((S_800AACA4_3 *)object)->unk_2C in func_800AACA4 */

typedef struct S_800AACA4_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AACA4_11;   /* ((S_800AACA4_2_pre *)root)[-1].unk_00 in func_800AACA4 */

void func_800AACA4(S_800AACA4_0 *arg0, S_800AACA4_6 *arg1, S_800AACA4_7 *arg2, S_800AACA4_1 *arg3) {
    LocalResult local;
    S_800AACA4_3 *object;
    void *root;
    S_800AACA4_4 *table;
    S_800AACA4_5 *entry;
    register u32 offset ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 first_offset;
    s16 count;
    s32 result;
    s16 next_count;
    u16 initial_value;

    arg0->unk_9A = 12;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    initial_value = ((S_800AACA4_8 *)(arg3->unk_60))->unk_2A;
    arg3->unk_1C &= 0xFFF7FFFF;
    arg3->unk_6A = initial_value;
    arg0->unk_96 = 2;

    root = arg3->unk_60;
    object = ((S_800AACA4_2_pre *)root)[-1].unk_04;
    table = ((S_800AACA4_9 *)(object->unk_28))->unk_00;
    entry = (*(void * *)((u8 *)(table->unk_00) + ((S_800AACA4_10 *)(object->unk_2C))->unk_02 * 4));
    if (func_8003DE58(entry->unk_04, object, &local, 0) == 0) {
        local.value = -0x60;
    }

    root = arg3->unk_60;
    arg1->unk_0A = ((S_800AACA4_11 *)(((S_800AACA4_2_pre *)root)[-1].unk_00))->unk_0A + local.value;
    arg2->unk_24 = object->unk_24;
    arg2->unk_25 = object->unk_25;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);

    count = arg3->unk_8A.s;
    if (count != 0) {
        first_offset = arg3->unk_6A;
        first_offset >>= 8;
        first_offset &= 0xE;
        result = func_800BCB04(
            ((arg2->unk_24 + (*(s16 *)((u8 *)(&D_8006CCD8) + first_offset)) * count) << 6) + 0x20 & 0xFFE0,
            ((arg2->unk_25 + (*(s16 *)((u8 *)(&D_8006CCE8) + first_offset)) * count) << 6) + 0x20 & 0xFFE0,
            arg1->unk_0A);
        next_count = arg3->unk_8A.u + 2;
        arg3->unk_8A.s = next_count;
        if (result < 0x200) {
            arg1->unk_14 = -((arg1->unk_0A - result) << 15) / next_count;
        } else {
            arg1->unk_14 = -((arg1->unk_0A - ((S_800AACA4_8 *)(arg3->unk_60))->unk_88) << 15) / next_count;
        }
        arg3->unk_8A.s = arg3->unk_8A.u - 2;
    }

    offset = arg3->unk_6A;
    offset >>= 8;
    offset &= 0xE;
    arg2->unk_24 += (*(u8 *)((u8 *)(&D_8006CCD8) + offset));
    offset = arg3->unk_6A;
    offset >>= 8;
    offset &= 0xE;
    arg2->unk_25 += (*(u8 *)((u8 *)(&D_8006CCE8) + offset));
}

/* MECHANISM: A signed stack halfword plus a one-read initial u16 reproduce the 0x30 frame and prefix schedule.
   The true-space CFG duplicates quotient arms so gcc tail-merges only the shared divide/store.
   Split unsigned index live ranges, a guarded $v0 tail role, and a zero-operand fence close base scheduling. */
