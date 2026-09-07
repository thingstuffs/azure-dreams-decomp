#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct LocalResult {
    s32 unk0;
    s16 value;
} LocalResult;

extern s32 func_8003DE58(void *, void *, LocalResult *, s32);
extern void func_800A2B04(void *, u8, u8);
extern s16 func_800BCB04(s32, s32, s16);
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;

void func_800AACA4(void *arg0, void *arg1, void *arg2, void *arg3) {
    LocalResult local;
    void *object;
    void *root;
    void *table;
    void *entry;
    register u32 offset ASM_REG("$2");
    u32 first_offset;
    s16 count;
    s32 result;
    s16 next_count;
    u16 initial_value;

    FIELD(arg0, s8, 0x9A) = 12;
    FIELD(arg0, s8, 0x9B) = 0;
    FIELD(arg0, s32, 0x8C) = 0;
    initial_value = FIELD(FIELD(arg3, void *, 0x60), u16, 0x2A);
    FIELD(arg3, s32, 0x1C) &= 0xFFF7FFFF;
    FIELD(arg3, u16, 0x6A) = initial_value;
    FIELD(arg0, s16, 0x96) = 2;

    root = FIELD(arg3, void *, 0x60);
    object = FIELD(root, void *, -0x14);
    table = FIELD(FIELD(object, void *, 0x28), void *, 0);
    entry = FIELD(FIELD(table, void *, 0), void *, FIELD(FIELD(object, void *, 0x2C), u8, 2) * 4);
    if (func_8003DE58(FIELD(entry, void *, 4), object, &local, 0) == 0) {
        local.value = -0x60;
    }

    root = FIELD(arg3, void *, 0x60);
    FIELD(arg1, s16, 0xA) = FIELD(FIELD(root, void *, -0x18), u16, 0xA) + local.value;
    FIELD(arg2, u8, 0x24) = FIELD(object, u8, 0x24);
    FIELD(arg2, u8, 0x25) = FIELD(object, u8, 0x25);
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    count = FIELD(arg3, s16, 0x8A);
    if (count != 0) {
        first_offset = FIELD(arg3, u16, 0x6A);
        first_offset >>= 8;
        first_offset &= 0xE;
        result = func_800BCB04(
            ((FIELD(arg2, u8, 0x24) + FIELD(&D_8006CCD8, s16, first_offset) * count) << 6) + 0x20 & 0xFFE0,
            ((FIELD(arg2, u8, 0x25) + FIELD(&D_8006CCE8, s16, first_offset) * count) << 6) + 0x20 & 0xFFE0,
            FIELD(arg1, s16, 0xA));
        next_count = FIELD(arg3, u16, 0x8A) + 2;
        FIELD(arg3, s16, 0x8A) = next_count;
        if (result < 0x200) {
            FIELD(arg1, s32, 0x14) = -((FIELD(arg1, s16, 0xA) - result) << 15) / next_count;
        } else {
            FIELD(arg1, s32, 0x14) = -((FIELD(arg1, s16, 0xA) - FIELD(FIELD(arg3, void *, 0x60), s16, 0x88)) << 15) / next_count;
        }
        FIELD(arg3, s16, 0x8A) = FIELD(arg3, u16, 0x8A) - 2;
    }

    offset = FIELD(arg3, u16, 0x6A);
    offset >>= 8;
    offset &= 0xE;
    FIELD(arg2, u8, 0x24) += FIELD(&D_8006CCD8, u8, offset);
    ASM_SCHED_BARRIER();
    offset = FIELD(arg3, u16, 0x6A);
    offset >>= 8;
    offset &= 0xE;
    FIELD(arg2, u8, 0x25) += FIELD(&D_8006CCE8, u8, offset);
}

/* MECHANISM: A signed stack halfword plus a one-read initial u16 reproduce the 0x30 frame and prefix schedule.
   The true-space CFG duplicates quotient arms so gcc tail-merges only the shared divide/store.
   Split unsigned index live ranges, a guarded $v0 tail role, and a zero-operand fence close base scheduling. */
