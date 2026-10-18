#include "modules/dungeon_ovl_1852800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/types3c_types.h"





typedef struct S_818330F0_1 {
    void * unk_00;
    u8 pad_04[0x8];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
} S_818330F0_1;   /* arg0 in func_800248F0 */


typedef struct S_818330F0_3 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_818330F0_3;


/* cfail-repair: tf7-phase1-cache-v3 */
/* Ease the position toward its target, brighten the primitive, and flag completion. */
void func_800248F0(void *effect, void *position, void *primitive) {
    s16 target_z;
    s16 current_z;
    void *owner;

    ((SignedPositionView *)position)->unk_02 = (s16) ((u16) ((SignedPositionView *)position)->unk_02
        + ((((S_818330F0_1 *)effect)->unk_0C - ((SignedPositionView *)position)->unk_02) / 12));
    ((SignedPositionView *)position)->unk_06 = (s16) ((u16) ((SignedPositionView *)position)->unk_06
        + ((((S_818330F0_1 *)effect)->unk_0E - ((SignedPositionView *)position)->unk_06) / 12));
    target_z = ((S_818330F0_1 *)effect)->unk_10;
    current_z = ((SignedPositionView *)position)->unk_0A;
    ((SignedPositionView *)position)->unk_0A = (s16) ((u16) ((SignedPositionView *)position)->unk_0A + ((target_z
        - current_z) / 10));
    ((Rec_D_80082E80 *)primitive)->unk_0C.at00_s32.v = (s32) (((Rec_D_80082E80 *)primitive)->unk_0C.at00_s32.v
        + 0xC0C0C);
    owner = ((S_818330F0_1 *)effect)->unk_00;
    ((S_818330F0_3 *)owner)->unk_52 = (u16) (((S_818330F0_3 *)owner)->unk_52 | 0x8000);
    func_800478B8(primitive);
    if ((u8) ((Rec_D_80082E80 *)primitive)->unk_0C.at00_s32.v >= 0x91U) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((u16 *)effect)[-1] | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}
