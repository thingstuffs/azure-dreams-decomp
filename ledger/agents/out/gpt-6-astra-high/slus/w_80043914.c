#include "common.h"

typedef struct {
    u8 pad_0x00[0x48];
    u8 field_0x48;
    u8 pad_0x49[0x8C - 0x49];
} S_800E3E48;

typedef struct {
    u8 field_0x00;
    u8 pad_0x01[2];
    u8 field_0x03;
} S_80043914_Arg;

extern S_800E3E48 D_800E3E48[];
extern u8 D_800E2968[16];

/* Maps the selected entry's code from 0xD/0xF to 0xF/0xA for type 0x16. */
void func_80043914(S_80043914_Arg *input)
{
    S_80043914_Arg *entrySelector = input;

    if (entrySelector->field_0x00 == 0x16) {
        S_800E3E48 *entries = D_800E3E48;
        u8 entryCode = entries[entrySelector->field_0x03 & 0x1F].field_0x48;
        register u8 mappedCode ASM_REG("$2");   /* MATCH pin: slus-diff */

        if (entryCode == 0xD) {
            mappedCode = 0xF;
        } else if (entryCode == 0xF) {
            mappedCode = 0xA;
        } else {
            return;
        }
        D_800E2968[0] = mappedCode;
    }
}
