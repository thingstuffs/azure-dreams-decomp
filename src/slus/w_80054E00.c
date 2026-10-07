#include "shared/sound_state.h"
#include "common.h"

/* Canonical status-block struct (established in w_800540A8.c / w_80054C58.c /
   w_800559B4.c / w_8005440C.c). field1C added here (previously an unnamed
   2-byte pad window) since this function reads it as a signed 16-bit value. */

/* Canonical task/timer object struct (established in w_800559B4.c / w_800540A8.c
   / w_80054C58.c). */

/* Opaque scalar flag; only its address is taken (never dereferenced beyond a
   single s32 write). Padded >8 bytes to force %hi/%lo addressing (matches the
   target's lui+addiu/sw sequence rather than a $gp_rel store). */
typedef struct S_80084904 {
    /* 0x00 */ s32 v;
    /* 0x04 */ u8 pad4[8];
} S_80084904;

/* Same shape/reasoning as S_80084904. */

extern S_80084904 D_80084904;

extern void func_8005A4E8(u8 a0, u8 a1, u8 a2);
extern s32 Control_CD(s32 a0, void *a1, void *a2);
extern s32 func_80053D64(void);
extern int func_80054AF0(int mode);
extern void func_80054C58(void);
extern void func_80054CD4(void);

/* Handles byte opcodes to arm, commit, or cancel a countdown. */
void func_80054E00(s32 event) {
    s32 opcode = event & 0xFF;

    switch (opcode) {
    case 0x74:
        func_8005A4E8(0, 0, 0);
        Control_CD(9, 0, 0);
        D_800847D0.flags00 &= ~0x400;
        if (D_800847D0.unk_18 == 0) {
            D_80084904.v = 1;
            D_80084858.unk_04 = 0;
            if (D_800847D0.unk_10 != 0) {
                s16 countdown = (s16)func_80054AF0(D_800847D0.unk_1C);
                D_80084858.unk_08 = countdown;
                D_80084858.unk_0A = countdown;
                break;
            }
        }
        return;

    case 0xE4:
        if (D_800847D0.flags04 & 0x200) {
            Control_CD(9, 0, 0);
            return;
        }
        if (D_800847D0.flags00 & 0x400) {
            u32 cd_position = (u32)func_80053D64();
            D_800847D0.unk_18 = cd_position;
            if (D_800847D0.unk_08 >= cd_position) {
                D_800847D0.unk_18 = D_800847D0.unk_08;
            }
            D_80084864[0] = 2;
            D_800847D0.unk_10 = D_800847D0.unk_18;
            D_800847D0.unk_14 = D_800847D0.unk_0C;
            D_800847D0.unk_31 = D_800847D0.unk_30;
            D_800847D0.unk_33 = D_800847D0.unk_32;
            D_800847D0.flags00 |= 0x4000;
        }
        return;

    case 0xF4:
        if (D_800847D0.flags00 & 0x4000) {
            D_800847D0.unk_18 = 0;
            break;
        }
        return;

    default:
        return;
    }
    func_80054C58();
    func_80054CD4();
}
