#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} UnkStruct800223E8;

extern s32 D_80024628[];
extern s32 strlen(s32 arg0);
extern void func_800537D0(s32 value, s32 width, s32 buf);

// Clamp the value to 999999 and format it into the text buffer.
void func_800223E8(UnkStruct800223E8 *textEntry)
{
    if (D_80024628[0] > 0xF423F) {
        D_80024628[0] = 0xF423F;
    }

    func_800537D0(D_80024628[0], strlen(textEntry->unk4) - 1,
                  textEntry->unk4);
}
