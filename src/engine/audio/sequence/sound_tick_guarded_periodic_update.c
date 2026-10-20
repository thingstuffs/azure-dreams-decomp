#include "common.h"

extern void sound_update_voice_modulation_slots(void);
extern void func_800584E4(void);
extern void func_8005ACDC(void);

typedef struct {
    s32 v;
    s32 pad[2];
} PaddedS32;

extern PaddedS32 D_800737A8;
extern PaddedS32 D_80073824;
extern PaddedS32 D_80085F98;

/* Runs an enabled update with a reentry guard and periodic maintenance. */
long long sound_tick_guarded_periodic_update(void)
{
    s32 update_enabled;

    update_enabled = D_80073824.v;
    if ((update_enabled != 0) && (D_80085F98.v == 0)) {
        D_80085F98.v = 1;
        func_800584E4();
        if (D_800737A8.v >= 11) {
            sound_update_voice_modulation_slots();
            func_8005ACDC();
            D_800737A8.v = 0;
        }
        D_80085F98.v = 0;
        D_800737A8.v += 1;
    }
}
