/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_80170A54_0 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_80170A54_0;   /* base in func_80170A54 */

typedef struct S_80170A54_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80170A54_1;   /* object in func_80170A54 */

typedef struct S_80170A54_2 {
    u16 unk_00;
} S_80170A54_2;   /* arg0 in func_80170A54; pointer addresses record offset 0x2 */


__asm__(".set D_80080000, 0x80080000");

void func_800489F4(); /* extern */
extern void *D_800814A8[3];
extern u8 D_80080000[];

/* Applies a direction-indexed table entry in state 2 and sets record and global flags. */
void func_80170A54(void *record_data) {
    S_80170A54_1 *active_object = (S_80170A54_1 *)D_800814A8[0];
    TileObject *state_data = &D_80082E80;


    {
        u8 direction_entry;
        if (state_data->unk_004 != 2)
            goto done;
        direction_entry = ((u8 *)state_data->unk_02C)[
                 (((s32) (gameWork.view.viewAngle +
                          active_object->unk_2A +
                          0x100) >> 9) & 7)];
        func_800489F4(state_data, direction_entry,
            4, 1);
        ((S_80170A54_2 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_80170A54_2 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
done:
    ;
}
