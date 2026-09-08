#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

extern void func_80047738(void *, u8, s8);
extern void func_80047784(void *, u8, s32);
extern u8 D_8006CCF8[];
extern s16 D_80083228[];

typedef struct S_800211C4_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800211C4_0;   /* arg0 in func_800211C4 */


typedef struct S_800211C4_2 {
    u8 pad_00[0x20];
    s16 unk_20;
} S_800211C4_2;   /* arg1_hold in func_800211C4 */

/* Update the record for its current direction and set its direction flag. */
void func_800211C4(S_800211C4_0 *orientation, void *state_ptr, Rec_D_80082E80 *record) {
    u8 *flags_page;
    s32 flags_base;
    s32 direction;
    u8 *direction_data;
    s32 angle_sector;
    u16 angle;
    u16 flags;
    S_800211C4_2 *state = state_ptr;

    angle = (orientation->unk_2A + 0x2000) & 0xFFF;
    orientation->unk_2A = angle;
    angle_sector = (s32)(D_80083228[0] + angle + 0x100) >> 9;
    direction = angle_sector & 7;
    if (record->unk_14.at00_u16.v & 0x6000) {
        func_80047784(record, *((u8 *)record->unk_2C.as_s32 + direction), 0);
    }
    if (state->unk_20 == direction) {
        flags_page = (u8 *)0x80070000;
        goto update_flags;
    }
    direction_data = (u8 *)record->unk_2C.as_s32;
    if (direction_data != 0) {
        func_80047738(record, direction_data[direction], record->unk_04.as_s8);
    }
    state->unk_20 = direction;
    flags_page = (u8 *)0x80070000;
update_flags:
    flags_base = (s32)flags_page - 0x3308;
    ASM_KEEP(flags_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    direction_data = (u8 *)(direction + flags_base);
    if (direction_data[0] != 0) {
        flags = record->unk_14.at00_u16.v | 1;
    } else {
        flags = record->unk_14.at00_u16.v & 0xFFFE;
    }
    record->unk_14.at00_u16.v = flags;
}
