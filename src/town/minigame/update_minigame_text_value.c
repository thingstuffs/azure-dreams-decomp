#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} UnkStruct800223E8;

extern s32 pickup_reward_total[];
extern s32 strlen(s32 text);
extern void format_decimal_field_space_padded(s32 value, s32 width, char *buf);

// Clamp the value to 999999 and format it into the text buffer.
void update_minigame_text_value(UnkStruct800223E8 *textEntry)
{
    if (pickup_reward_total[0] > 0xF423F) {
        pickup_reward_total[0] = 0xF423F;
    }

    format_decimal_field_space_padded(pickup_reward_total[0], strlen(textEntry->unk4) - 1,
                  textEntry->unk4);
}
