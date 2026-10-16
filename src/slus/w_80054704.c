#include "shared/sound_state.h"
#include "common.h"

#include "common.h"

/* Canonical status block shared across the D_800847D0 family (established in
   w_80054E00.c / w_800540A8.c / w_80054C58.c / w_800559B4.c). */


extern s32 getCdFlagsWithConditionalBit(void);
extern void func_80054D64(void);
extern void audioHandleStreamControlEvent(s32 event);
extern void submitTaggedDriverByte(u8 a0, u8 a1, u8 a2);

/* When subsystem bit 4 is set, clears flag 0x200 and commits or arms the countdown. */
void func_80054704(void) {
    if (getCdFlagsWithConditionalBit() & 4) {
        D_800847D0.flags04 &= ~0x200;
        if (D_800847D0.unk_10 != 0) {
            audioHandleStreamControlEvent(0x74);
            return;
        }
        if (!(D_800847D0.flags00 & 0x4000)) {
            D_800847D0.flags00 |= 0x400;
            func_80054D64();
            submitTaggedDriverByte(0, 0, 1);
        }
    }
}
