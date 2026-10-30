#include "common.h"
#include "town/minigame/object.h"

extern s32 pickup_reward_total[];
#include "sdk/libc.h"
#include "engine/text.h"

// Clamp the value to 999999 and format it into the text buffer.
void update_minigame_text_value(MinigameTextValueObject *text_value)
{
    if (pickup_reward_total[0] > 0xF423F) {
        pickup_reward_total[0] = 0xF423F;
    }

        format_decimal_field_space_padded(pickup_reward_total[0], strlen(text_value->text) - 1,
                  text_value->text);
}
