#include "common.h"
#include "m2c_compat.h"

typedef struct S_80023C80_0_pre {
    u16 unk_00;
} S_80023C80_0_pre;   /* the 0x2 bytes before obj in func_80023C80, addressed as obj[-1] */

typedef struct S_80023C80_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u8 pad_02[0x2];
    void ** unk_04;
    u8 pad_08[0x4];
    union { u16 s; volatile u16 u; } unk_0C;   /* accessed as both */
    union { u16 s; volatile u16 u; } unk_0E;   /* accessed as both */
    s16 unk_10;
    s16 unk_12;
} S_80023C80_0;   /* obj in func_80023C80 */

typedef struct S_80023C80_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80023C80_1;   /* (void *)work in func_80023C80 */


extern s32 D_800814A0;

/* Advances object state, updates coordinates and size, or sets status flags. */
void func_80023C80(void *object) {
    void *obj;
    s32 state;
    s32 size;
    u16 state_bits;

    obj = object;

    state = ((S_80023C80_0 *)obj)->unk_00.s;
    state_bits = (u16) ((S_80023C80_0 *)obj)->unk_00.s;

    if (state == 1) {
        goto update_geometry;
    }
    if (state >= 2) {
        goto check_flag_state;
    }
    if (state == 0) {
        goto initialize;
    }
    goto done;

check_flag_state:
    if (state == 2) {
        goto set_flags;
    }
    goto done;

initialize:
    ((S_80023C80_0 *)obj)->unk_00.u = state_bits + 1;
    goto done;

update_geometry:
{
    void **coords_ref;
    s32 coord;
    s32 offset;

    coords_ref = ((S_80023C80_0 *)obj)->unk_04;
    coord = (s32)*coords_ref;
    coord = ((S_80023C80_1 *)((void *)coord))->unk_02;
    if (coord < 0) {
        coord += 0x1F;
    }
    ((S_80023C80_0 *)obj)->unk_0C.s = (u16) ((coord >> 5) + 0x94);
    coord = (s32)*coords_ref;
    coord = ((S_80023C80_1 *)((void *)coord))->unk_06;
    if (coord < 0) {
        coord += 0x1F;
    }
    ((S_80023C80_0 *)obj)->unk_0E.s = (u16) ((coord >> 5) + 0x75);
    coord = (s32)*coords_ref;
    coord = ((S_80023C80_1 *)((void *)coord))->unk_0A;
    coord = 0 - coord;
    offset = coord >> 6;
    if (coord < 0) {
        offset = (s32) (coord + 0x3F) >> 6;
    }
    if (offset < 0) {
        offset = 0;
    }
    size = offset + 3;
    ((S_80023C80_0 *)obj)->unk_12 = size;
    ((S_80023C80_0 *)obj)->unk_10 = size;
    ((S_80023C80_0 *)obj)->unk_0C.s =
        (u16) (((S_80023C80_0 *)obj)->unk_0C.u - offset);
    ((S_80023C80_0 *)obj)->unk_0E.s =
        (u16) (((S_80023C80_0 *)obj)->unk_0E.u - offset);
    goto done;
}

set_flags:
    (*(u16 *)((u8 *)obj + -2)) =
        (u16) (((S_80023C80_0_pre *)obj)[-1].unk_00 | 0x8000);
    D_800814A0 |= 0x8000;

done:

}

/* MECHANISM: The signed 0/1/2 dispatch is laid out in retail block order and
   joins the true-space epilogue at 0x80023D98, so the leaf stays frameless.
   ABI $a0 holds the object; $v1/$v0 carry the two-level pointer loads. */
