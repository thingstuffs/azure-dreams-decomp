#include "shared/sound_state.h"
#include "common.h"

#include "common.h"




extern void func_80054538(SoundTask *ramp);
extern void func_800546B0(void);
extern void func_80054704(void);
extern void func_80054E00(s32 event);

/* Updates the CD cue task and commits the countdown when its ramp completes. */
void func_800544A4(void) {
    if (D_800847D0.flags04 & 0x200) {
        func_80054704();
    }

    if (D_800847D0.flags00 & 0x400) {
        if (D_800847D0.flags00 & 0x4000) {
            SoundTask *task = &D_80084858;

            func_80054538(task);
            if (task->unk_0C == 3) {
                func_80054E00(0x74);
            }
        } else {
            func_800546B0();
        }
    }
}
