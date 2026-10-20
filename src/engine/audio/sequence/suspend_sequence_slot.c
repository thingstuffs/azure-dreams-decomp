#include "common.h"



typedef struct {
    s16 field_0;
    s16 field_2;
    s32 field_4;
    u16 field_8;
    u16 field_A;
} S_80086C00;

typedef struct {
    s32 field_0;
    s32 field_4;
    u16 field_8;
    u16 field_A;
    u8 pad0C[0x40 - 0x0C];
} S_8005B070_req;

extern s32 audio_voice_count[4];
extern s32 audio_voice_masks[64];
extern s32 audio_sequence_active[4];
extern u8 audio_voice_records[0x78 * 64];
extern s32 audio_update_guard[4];
extern S_80086C00 audio_sequence_slots[8];

extern void func_8005F134(S_8005B070_req *request);

/* Process eligible entries and set the selected slot state to 4. */
void suspend_sequence_slot(s16 slot_index)
{
    S_8005B070_req request;
    u8 *entry;
    s32 entry_index;
    s32 *entry_id;
    S_80086C00 *slots;

    entry_index = 0;
    audio_update_guard[0] = 1;
    if (audio_voice_count[0] > 0) {
        entry_id = audio_voice_masks;
        entry = audio_voice_records;
loop:
        if (*(u16 *)(entry + 6) < 0x10U) {
            if (*(u16 *)(entry + 0x1A) != 0) {
                s32 request_type;
                request_type = 3;
                request.field_4 = request_type;
                request.field_0 = *entry_id;
                request.field_8 = 0;
                request.field_A = 0;
                func_8005F134(&request);
            }
        }
        entry_id++;
        entry += 0x78;
        {
            s32 entry_count = audio_voice_count[0];
            do {
                entry_index++;
            } while (0);
            if (entry_index < entry_count)
                goto loop;
        }
    }
    slots = audio_sequence_slots;
    slots[slot_index].field_2 = 4;
    audio_update_guard[0] = 0;
    audio_sequence_active[0] = 0;
}
