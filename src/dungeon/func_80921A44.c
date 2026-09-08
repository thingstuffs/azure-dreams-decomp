#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80921A44_0 {
    union { s32 s; volatile s32 u; } unk_00;   /* accessed as both */
    union { volatile s32 s; s32 u; } unk_04;   /* accessed as both */
    union { volatile s32 s; s32 u; } unk_08;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_0C;   /* accessed as both */
    s32 unk_10;
} S_80921A44_0;   /* arg1 in func_80921A44 */


typedef struct S_80921A44_2_pre {
    u16 unk_00;
} S_80921A44_2_pre;   /* the 0x2 bytes before arg0 in func_80921A44, addressed as arg0[-1] */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0;
extern void func_800478B8(void *, void *, s32, s32);
/* Advance position, damp horizontal motion, and propagate object status flags. */
void func_80921A44(void *entry, void *motion, void *object) {
    s32 velocity_y;
    s32 velocity_x;
    s32 next_x;
    s32 position_z;

    velocity_x = ((S_80921A44_0 *)motion)->unk_0C.s;
    velocity_y = ((S_80921A44_0 *)motion)->unk_10;
    next_x = ((S_80921A44_0 *)motion)->unk_00.s + ((S_80921A44_0 *)motion)->unk_0C.u;
    position_z = ((S_80921A44_0 *)motion)->unk_08.s;
    ((S_80921A44_0 *)motion)->unk_00.u = next_x;
    ((S_80921A44_0 *)motion)->unk_08.u = position_z + 0xFFFE8000;
    ((S_80921A44_0 *)motion)->unk_04.s = (s32) (((S_80921A44_0 *)motion)->unk_04.u + ((S_80921A44_0 *)motion)->unk_10);
    ((S_80921A44_0 *)motion)->unk_0C.u = (s32) ((velocity_x * 4) / 5);
    ((S_80921A44_0 *)motion)->unk_10 = (s32) ((velocity_y * 4) / 5);
    func_800478B8(object, motion, (s32) (velocity_y * 4) >> 0x1F, (s32) (velocity_x * 4) >> 0x1F);
    if (((Rec_D_80082E80 *)object)->unk_14.at00_u16.v & 0x6000) {
        (*(u16 *)((u8 *)entry + -2)) = (u16) (((S_80921A44_2_pre *)entry)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
