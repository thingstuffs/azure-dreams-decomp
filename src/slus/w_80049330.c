#include "common.h"

/* extern decls */
extern int D_800814A8[4]; /* >8B forces hi/lo addressing (matches target's lui/lw) */
extern int func_800492B0(int arg0);

typedef struct {
    unsigned char unk0;
    unsigned char unk1;
    unsigned char unk2;
    unsigned char unk3;
} S_80049330;

/* If arg0->unk0 is nonzero, extract a 5-bit field from byte offset 3 and
 * forward it to func_800492B0. Otherwise return the global D_800814A8. */
int func_80049330(S_80049330 *arg0)
{
    if (arg0->unk0 != 0) {
        return func_800492B0(arg0->unk3 & 0x1F);
    }
    return D_800814A8[0];
}
