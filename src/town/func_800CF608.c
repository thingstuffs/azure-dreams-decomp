#include "common.h"

typedef struct S_800CCD68_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    union { s16 s; u16 u; } unk_6A;   /* accessed as both */
    u16 unk_6C;
    u8 pad_6E[0x4];
    u16 unk_72;
} S_800CCD68_0;   /* arg0 in func_800CCD68 */


/* Steps a timed four-phase value sequence and counts completed cycles. */
void func_800CCD68(S_800CCD68_0 *sequence)
{
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 state;

    state = sequence->unk_6A.s;
    value = 1;
    if (state == value) {
        goto state_1;
    }
    value = state < 2;
    if (value == 0) {
        goto state_ge_2;
    }
    value = 2;
    ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    value = 0xC00;
    if (state == 0) {
        goto set_value;
    }
    goto done;

state_ge_2:
#ifdef NON_MATCHING
    value = 2;
#endif
    ASM_UNDEF(value);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (state == value) {
        goto state_2;
    }
    value = 3;
    if (state == value) {
        goto state_3;
    }
    goto done;

state_1:
    value = --sequence->unk_6C;
    if ((value << 16) != 0) {
        goto done;
    }
    value = 0x800;
    sequence->unk_72 = value;
    goto advance_state;

state_2:
    value = --sequence->unk_6C;
    if ((value << 16) != 0) {
        goto done;
    }
    value = 0x400;
set_value:
    sequence->unk_72 = value;
advance_state:
    value = sequence->unk_6A.u;
    sequence->unk_6C = 3;
    value++;
    sequence->unk_6A.u = value;
    goto done;

state_3:
    value = --sequence->unk_6C;
    if ((value << 16) != 0) {
        goto done;
    }
    value = sequence->unk_68;
    sequence->unk_72 = 0;
    sequence->unk_6C = state;
    sequence->unk_6A.s = 0;
    value++;
    sequence->unk_68 = value;
done:
    return;
}

