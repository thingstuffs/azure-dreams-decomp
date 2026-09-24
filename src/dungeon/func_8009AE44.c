#include "common.h"
#include "records/Rec_D_800E3D7C.h"
extern int abs(int);

typedef struct S_800A05A4_1 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A05A4_1;   /* found in func_800A05A4 */

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

extern void *func_8009B4B0(void *, u16, u16);
extern s32 func_800A0548(s16, s16);
extern s16 func_800A44E0(u16, u16, s16, u32);

/* Scans along a heading for an object within the height range and records the stopping coordinates. */
void *func_800A05A4(Rec_D_800E3D7C *source, s32 start_x, s32 start_y, u16 heading, s16 max_steps)
{
    s32 dir;
    u16 x;
    u16 y;
    s16 height;
    void *found;
    s32 i;

    found = 0;
    dir = heading = (heading >> 9) & 7;
    height = 0x20;
    x = D_8006CCD8[dir] + start_x;
    y = D_8006CCE8[dir] + start_y;
    if (func_800A0548(x, y) != 0) {
        source->unk_72.as_s8 = D_8006CCD8[dir] - x;
        source->unk_73.as_s8 = D_8006CCE8[dir] - y;
        return 0;
    }
    for (i = 0; i < max_steps; i++) {
        found = func_8009B4B0(source, x, y);
        if (found != 0 && abs(((S_800A05A4_1 *)found)->unk_88 - source->unk_88.as_s16) <= height) {
            break;
        }
        if (func_800A0548(x + D_8006CCD8[dir], y + D_8006CCE8[dir]) != 0) {
            source->unk_72.as_s8 = D_8006CCD8[dir] - x;
            source->unk_73.as_s8 = D_8006CCE8[dir] - y;
            return 0;
        }
        if (func_800A44E0(x << 6, y << 6, source->unk_88.as_s16 - height, heading << 9) != 0) {
            source->unk_72.as_s8 = -x;
            source->unk_73.as_s8 = -y;
            return 0;
        }
        height += 0x20;
        x += D_8006CCD8[dir];
        y += D_8006CCE8[dir];
    }
    source->unk_72.as_s8 = x;
    source->unk_73.as_s8 = y;
    return found;
}
