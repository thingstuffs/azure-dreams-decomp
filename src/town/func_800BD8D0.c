#include "common.h"

typedef struct S_800BB030_0_pre {
    u16 unk_00;
} S_800BB030_0_pre;   /* the 0x2 bytes before arg0 in func_800BB030, addressed as arg0[-1] */

typedef struct S_800BB030_0 {
    u8 pad_00[0x66];
    s16 unk_66;
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x2];
    union { u16 s; s16 u; } unk_6C;   /* accessed as both */
    u8 pad_6E[0x29];
    s8 unk_97;
    s8 * unk_98;
} S_800BB030_0;   /* arg0 in func_800BB030 */



extern s32 func_8009CFE0(void *, void *);
extern s32 D_800814A0[];

/* Updates a four-phase animation and clears its activity flag on completion. */
void func_800BB030(void *entity, void *context) {
    s8 *activity_flag;
    s32 phase;
    s32 phase_ticks;
    s32 quarter_ticks;
    register s32 intensity ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    if (func_8009CFE0(entity, context) != 0) {
        activity_flag = ((S_800BB030_0 *)entity)->unk_98;
        if (activity_flag != 0) {
            *activity_flag = 0;
        }
        ((S_800BB030_0_pre *)entity)[-1].unk_00 |= 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        goto end;
    }

    phase_ticks = ((S_800BB030_0 *)entity)->unk_6C.s + 1;
    phase = ((S_800BB030_0 *)entity)->unk_68.s;
    ((S_800BB030_0 *)entity)->unk_6C.s = phase_ticks;
    if (phase == 1) {
        goto state_1;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state_0;
        }
        goto end;
    }
    if (phase == 2) {
        goto state_2;
    }
    if (phase == 3) {
        goto state_3;
    }
    goto end;

state_0:
    quarter_ticks = (s16)phase_ticks / 4;
    ((S_800BB030_0 *)entity)->unk_66 = quarter_ticks * 3;
    intensity = (s16)((S_800BB030_0 *)entity)->unk_6C.s / 2;
    ((S_800BB030_0 *)entity)->unk_97 = intensity;
    if (((S_800BB030_0 *)entity)->unk_6C.u < 0x40) {
        goto end;
    }
    ((S_800BB030_0 *)entity)->unk_6C.s = 0;
    ((S_800BB030_0 *)entity)->unk_68.u++;
    goto end;

state_1: {
    s32 quarter_ticks;

    quarter_ticks = (s16)phase_ticks / 4;
    ((S_800BB030_0 *)entity)->unk_66 = 0x30 - quarter_ticks * 3;
    ((S_800BB030_0 *)entity)->unk_97 = 0x20;
    if (((S_800BB030_0 *)entity)->unk_6C.u >= 0x40) {
        ((S_800BB030_0 *)entity)->unk_6C.s = 0;
        ((S_800BB030_0 *)entity)->unk_68.u++;
    }
    goto end;
}

state_2: {
    register s32 half_ticks ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    quarter_ticks = (s16)phase_ticks / 4;
    ((S_800BB030_0 *)entity)->unk_66 = quarter_ticks * 3;
    half_ticks = (s16)((S_800BB030_0 *)entity)->unk_6C.s / 2;
    intensity = 0x20 - half_ticks;
    ((S_800BB030_0 *)entity)->unk_97 = intensity;
    if (((S_800BB030_0 *)entity)->unk_6C.u < 0x40) {
        goto end;
    }
    ((S_800BB030_0 *)entity)->unk_6C.s = 0;
    ((S_800BB030_0 *)entity)->unk_68.u++;
    goto end;
}

state_3: {
    s32 quarter_ticks;

    quarter_ticks = (s16)phase_ticks / 4;
    ((S_800BB030_0 *)entity)->unk_66 = 0x30 - quarter_ticks * 3;
    ((S_800BB030_0 *)entity)->unk_97 = 0;
    if (((S_800BB030_0 *)entity)->unk_6C.u < 0x40) {
        goto end;
    }
    ((S_800BB030_0 *)entity)->unk_6C.s = 0;
    ((S_800BB030_0 *)entity)->unk_68.s = 0;
}

end:
    return;
}
