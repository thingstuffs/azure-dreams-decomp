#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80080000.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80080000[];


typedef struct S_80024B48_0_pre {
    u16 unk_00;
} S_80024B48_0_pre;   /* the 0x2 bytes before arg0 in func_80024B48, addressed as arg0[-1] */

typedef struct S_80024B48_0 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
    u8 pad_10[0x38];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_80024B48_0;   /* arg0 in func_80024B48 */


typedef struct S_80024B48_2 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_80024B48_2;   /* ((S_80024B48_0 *)arg0)->unk_00 in func_80024B48 */

/* Initialize object coordinates and set completion flags after 32 ticks. */
void func_80024B48(void *object) {
    s32 tile_x;
    s32 tile_y;
    s32 offset_tile_x;
    s32 offset_tile_y;

    ((S_80024B48_2 *)(((S_80024B48_0 *)object)->unk_00))->unk_52 =
        (s16) (((S_80024B48_2 *)(((S_80024B48_0 *)object)->unk_00))->unk_52 | 0x8000);
    ((S_80024B48_0 *)object)->unk_48 = (u16) (((S_80024B48_0 *)object)->unk_48 + 1);
    if (((S_80024B48_0 *)object)->unk_4C != 0) {
        if (((S_80024B48_0 *)object)->unk_4C != 1) {
            return;
        }
        goto check_completion;
    }
    tile_x = (s16) ((S_80024B48_0 *)object)->unk_0C;
    tile_y = (s16) ((S_80024B48_0 *)object)->unk_0E;
    ((S_80024B48_0 *)object)->unk_48 = 0U;
    ((S_80024B48_0 *)object)->unk_04 = (s16) ((tile_x << 6) + 0x20);
    ((S_80024B48_0 *)object)->unk_06 = (s16) ((tile_y << 6) + 0x20);
    offset_tile_x = (s16) ((S_80024B48_0 *)object)->unk_0C;
    offset_tile_y = (s16) ((S_80024B48_0 *)object)->unk_0E;
    ((S_80024B48_0 *)object)->unk_0C = (s16) ((offset_tile_x - 7) << 6);
    ((S_80024B48_0 *)object)->unk_0E = (s16) ((offset_tile_y - 7) << 6);
    ((S_80024B48_0 *)object)->unk_4C = (s16) ((u16) ((S_80024B48_0 *)object)->unk_4C + 1);
check_completion:
    if ((s16) ((S_80024B48_0 *)object)->unk_48 >= 0x20) {
        (*(u16 *)((u8 *)object + (-2))) = (u16) (((S_80024B48_0_pre *)object)[-1].unk_00 | 0x8000);
        (*(s32 *)((u8 *)D_80080000 + (0x14A0))) = (s32) (((Rec_D_80080000 *)D_80080000)->unk_14A0 | 0x8000);
    }
}
