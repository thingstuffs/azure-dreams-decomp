#include "modules/town_ovl_3ef1c8.h"

s32 townSelectDialogueWith799Override(s32 speaker, s32 interaction, s32 dialogue_id) {
    s32 dialogue;

    if (townCheckTableResultBelowMinus47(speaker, interaction) != 0) {

        return &D_8001B63C;
    }
    dialogue = func_80019ABC(&D_8001A97C, &D_8001B1FC, speaker, dialogue_id);
    if (func_80019A04(&D_8001A97C, speaker, dialogue_id) != 0) {
        if (func_8001A510(0x799) != 0) {

            dialogue = &D_8001CDF2;
        } else {
            dialogue = func_8001628C(speaker, interaction, dialogue_id);
        }
    }
    return dialogue;
}
