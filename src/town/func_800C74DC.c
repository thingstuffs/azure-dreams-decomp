#include "common.h"

typedef struct {
    s32 unk0;       /* 0x00 */
    s16 *unk4;      /* 0x04 */
} Entry;            /* size 8 */

extern Entry D_80082660[];
extern s32 D_80082A38[64];

void func_800C4C3C(s32 arg0) {
    s32 *dst = D_80082A38;
    s16 *ent;
    s16 *sub;

    if (arg0 != 0) {
        ent = D_80082660[arg0].unk4;
        if (ent != 0) {
            sub = (s16 *)((u8 *)ent + 0x20);
            dst[0x13] = *(s16 *)((u8 *)sub + 0x84);
            dst[0x14] = *(s16 *)((u8 *)sub + 0x86);
        }
    }
}
