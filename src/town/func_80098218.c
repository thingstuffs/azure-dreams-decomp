#include "common.h"

typedef s32 M2C_UNK;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[3];
} LocalRecord;

extern s16 func_8008C758(LocalRecord *, M2C_UNK *, s32, s32 *, s32, s32);
extern s16 func_8008CF48(LocalRecord *, s32 *);
extern M2C_UNK *D_800D0408;
extern s32 D_800FE5C0[];

s32 func_80095978(s32 *arg0, s32 *arg1) {
    LocalRecord rec;
    s32 local_out;
    s32 *height_base;
    s32 *local_out_ptr;
    s32 result;
    s16 first;
    s16 second;

    height_base = D_800FE5C0;
    local_out_ptr = &local_out;
    rec.x = arg0[0];
    rec.y = arg0[1];
    rec.z = arg0[2] - height_base[5];
    first = func_8008CF48(&rec, local_out_ptr);
    *arg1 = local_out;
    rec.x = arg0[0];
    rec.y = arg0[1];
    rec.z = arg0[2] - height_base[5];
    second = func_8008C758(&rec, D_800D0408, 4, local_out_ptr, first, *arg1);
    if (second < first) {
        first = second;
        *arg1 = local_out;
    }
    if (first >= 64) {
        first = 64;
    }
    result = first;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    return result;
}

/* MECHANISM: A 24-byte escaping record at sp+0x18 followed by the sibling
   output local at sp+0x30 creates retail's 0x50 frame.  The global height
   base and output-local address remain live across both external calls.
   A kept named return value prevents the final sign extension sinking. */
