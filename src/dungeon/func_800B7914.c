#include "common.h"

/* Fixed 0x6000-byte memory-card image: the read/write wrappers use 0xC0
 * 128-byte units, and the checksum covers [0x208,0x6000). The resident
 * reset routine clears the two words at +0x208C/+0x2090. This is the
 * serialized object's base and extent, not an inferred address page.
 * See docs/evidence/r121_hardholds.md for the independent retail witnesses. */
typedef struct SaveImage {
    u8 prefix[0x208C];
    s32 pending;
    s32 active;
    u8 suffix[0x3F6C];
} SaveImage;

extern u8 D_80082E6B, D_800DCF4E;
extern s16 D_8008146C;
extern char D_800DF3D4[];
extern s32 func_80033BC0(s32);
extern void func_80040AA0(s32);
extern void func_8003E4FC(s32, char *, s32);
extern void func_8003F320(void);

void trigger_action_21_or_update_control(void) {
    if (D_80082E6B == 0x11) {
        SaveImage *save = (SaveImage *)0x80010000;
        if (save->active == 0 && D_8008146C == 0x28 &&
            func_80033BC0(0xA2) == 0 && save->pending == 0) {
            save->pending = 1;
            func_80040AA0(0x21);
            D_800DCF4E = 0;
            return;
        }
    }
    func_8003E4FC(6, D_800DF3D4, 0);
    func_8003F320();
}
