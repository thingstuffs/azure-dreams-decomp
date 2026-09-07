#include "common.h"

typedef struct S_800C5A64_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800C5A64_0;   /* arg2 in func_800C5A64 */

typedef struct S_800C5A64_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0xA];
    s16 unk_1C;
} S_800C5A64_1;   /* arg0 in func_800C5A64 */

typedef struct S_800C5A64_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C5A64_2;   /* counter_base in func_800C5A64 */



extern void func_800478B8(void *);
extern s32 D_800814A0;
extern s32 D_80083460;

/* Advance and damp effect motion, fade its primitive, and mark it expired when its lifetime ends. */
void func_800C5A64(void *effect, s32 *motion, void *primitive)
{
    s16 remaining;
    u8 *counter_base;

    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];
    motion[3] -= motion[3] >> 3;
    motion[4] -= motion[4] >> 3;

    func_800478B8(primitive);

    ((S_800C5A64_0 *)primitive)->unk_0C -= ((S_800C5A64_0 *)primitive)->unk_0C / ((S_800C5A64_1 *)effect)->unk_10.s;
    ((S_800C5A64_0 *)primitive)->unk_0D -= ((S_800C5A64_0 *)primitive)->unk_0D / ((S_800C5A64_1 *)effect)->unk_10.s;
    ((S_800C5A64_0 *)primitive)->unk_0E -= ((S_800C5A64_0 *)primitive)->unk_0E / ((S_800C5A64_1 *)effect)->unk_10.s;

    remaining = ((S_800C5A64_1 *)effect)->unk_10.u - 1;
    ((S_800C5A64_1 *)effect)->unk_10.s = remaining;
    if ((remaining << 16) <= 0) {
        if ((((S_800C5A64_1 *)effect)->unk_0C == 0) &&
            (((S_800C5A64_1 *)effect)->unk_1C == 0)) {
            counter_base = (u8 *)&D_80083460;
            ((S_800C5A64_2 *)counter_base)->unk_0A--;
        }
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
