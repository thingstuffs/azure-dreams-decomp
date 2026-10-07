#include "common.h"
#include "records/Rec_D_80082E80.h"


extern void func_800478B8(void *record);


typedef struct S_80024264_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    s16 unk_04;
    u8 pad_06[0x2];
    void * unk_08;
} S_80024264_0;   /* arg0 in func_80024264 */

typedef struct S_80024264_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024264_1;   /* owner in func_80024264 */


/* Advances the timed state sequence and updates the record channels and packed values. */
void func_80024264(S_80024264_0 *sequence, s32 unused, Rec_D_80082E80 *record)
{
    s16 word_or_frame;
    s16 state;
    s32 next_high_word;
    S_80024264_1 *owner;

    owner = sequence->unk_08;
    owner->unk_14++;
    sequence->unk_02.u++;
    func_800478B8(record);

    state = sequence->unk_00.s;
    switch (state) {
    case 0:
    {
        u8 channel_value;
        u16 low_word;

        channel_value = record->unk_0C.at02_u8.v;
        word_or_frame = record->unk_1C.at02_u16.v;
        channel_value++;
        record->unk_0C.at02_u8.v = channel_value;
        record->unk_0C.at01_u8.v = channel_value;
        record->unk_0C.at00_u8.v = channel_value;
        low_word = record->unk_1C.at00_u16.v;
        word_or_frame += 0x10;
        record->unk_1C.at02_u16.v = word_or_frame;
        low_word += 0x100;
        record->unk_1C.at00_u16.v = low_word;
        break;
    }
    case 1:
    {
        u8 channel_value;
        u16 low_word;

        channel_value = record->unk_0C.at02_u8.v;
        low_word = record->unk_1C.at00_u16.v;
        channel_value++;
        low_word += 0x80;
        record->unk_0C.at02_u8.v = channel_value;
        record->unk_0C.at01_u8.v = channel_value;
        record->unk_0C.at00_u8.v = channel_value;
        record->unk_1C.at00_u16.v = low_word;
        next_high_word = sequence->unk_02.s << 8;
        record->unk_1C.at02_u16.v = next_high_word;
        break;
    }
    case 2:
    {
        u8 channel_value;

        channel_value = record->unk_0C.at02_u8.v + 6;
        record->unk_0C.at02_u8.v = channel_value;
        record->unk_0C.at01_u8.v = channel_value;
        record->unk_0C.at00_u8.v = channel_value;
        word_or_frame = sequence->unk_02.s;

        next_high_word = (word_or_frame + 0x10) << 8;
        record->unk_1C.at02_u16.v = next_high_word;
        break;
    }
    case 3:
        goto state_3;
    default:
        return;
    }

    if (sequence->unk_02.s < sequence->unk_04) {
        return;
    }
    sequence->unk_02.u = 0;
    sequence->unk_00.u++;
    return;

state_3:
    func_800478B8(record);
}
