#include "common.h"

extern void mainCreateSettingsController(void);
extern struct { s32 v; s32 pad[2]; } D_800814A0;

/* Run the flag handler and set entry and global flags when bit 0x2000 is set. */
void mainRunFlagHandlerAndSet2000Flags(void *entry) {
    if (*(u16 *)((s8 *)entry - 2) & 0x2000) {
        mainCreateSettingsController();
        *(u16 *)((s8 *)entry - 2) = *(u16 *)((s8 *)entry - 2) | 0x8000;
        D_800814A0.v = D_800814A0.v | 0x8000;
    }
}
