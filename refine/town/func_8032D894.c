#include "common.h"

typedef struct S_80018094_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x24];
    s32 * unk_30;
} S_80018094_0;   /* D_80016000 in func_80018094 */

typedef struct S_80018094_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
} S_80018094_1;   /* (((S_80018094_0 *)D_80016000)->unk_08 << 5) +
            *((S_80018094_0 *)D_80016000)->unk_30 in func_80018094 */


typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern void *D_80016000;
extern void func_8001ACA0();
extern void func_8001AC6C();


/* Applies a target rectangle positioned at the given grid cell center. */
void func_80018094(s32 target_x, s32 target_y)
{
    Rect current_rect;
    Rect target_rect;
    s32 coord_offset;

    func_8001ACA0(&current_rect);
    target_x <<= 6;
    target_y <<= 6;
    current_rect.w = 0;
    coord_offset = ((S_80018094_1 *)((((S_80018094_0 *)D_80016000)->unk_08 << 5) +
            *((S_80018094_0 *)D_80016000)->unk_30))->unk_0C + 0x20;
    target_x += coord_offset;
    target_rect.x = target_x;
    coord_offset = ((S_80018094_1 *)((((S_80018094_0 *)D_80016000)->unk_08 << 5) +
            *((S_80018094_0 *)D_80016000)->unk_30))->unk_0E + 0x20;
    target_rect.w = 0;
    target_y += coord_offset;
    target_rect.y = target_y;
    func_8001AC6C(&current_rect, &target_rect, 0x20);
}
