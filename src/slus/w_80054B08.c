#include "shared/sound_state.h"
#include "common.h"
typedef struct CueRecord {
    u16 value;
    u8 pad_02[0x2];
    u32 base;
    u32 first;
    u32 second;
} CueRecord;

extern CueRecord *func_8003F534(void);
extern int func_80054AF0(int arg0);
extern void func_80054C58(void);
extern void func_80054CD4(void);
extern void func_80054E00(s32 arg0);
/* Loads pending CD cue fields from the current record or dispatches a countdown message. */
void func_80054B08(s32 message)
{
    s32 message_type = message & 0xF000;
    switch (message_type) {
    case 0:
    {
        SoundPlaybackState *status;
        u32 offset_mask;
        u16 record_value;
        u32 first_offset;
        register u32 second_offset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
        CueRecord *record;
        u32 offset_base;
        u8 first_tag;
        u8 second_tag;
        u32 flags;
        record = func_8003F534();
        offset_mask = 0xFF0000;
        ASM_KEEP(offset_mask);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
        record_value = record->value;
        status = &D_800847D0;
        status->unk_1C = record_value;
        offset_base = record->base;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
        first_offset = record->first;
        offset_mask |= 0xFFFF;
        status->unk_10 = first_offset;
        second_offset = record->second;
        first_tag = (u8) (first_offset >> 24);
        first_offset = first_offset & offset_mask;
        status->unk_10 = first_offset;
        first_offset = first_offset - 0x20;
        first_offset = first_offset + offset_base;
        status->unk_31 = first_tag;
        status->unk_10 = first_offset;
        status->unk_18 = 0;
        second_tag = (u8) (second_offset >> 24);
        status->unk_14 = second_offset;
        second_offset = second_offset & offset_mask;
        status->unk_33 = second_tag;
        status->unk_14 = second_offset;
        second_offset = second_offset + 0x20;
        flags = status->flags00;
        status->unk_14 = second_offset + offset_base;
        if (flags & 0x400) {
            status->flags00 = flags | 0x4000;
            D_80084864[0] = 2;
            break;
        }
        if (status->flags04 & 0x200) {
            break;
        }
        {
            SoundTask *update_state = &D_80084858;
            s16 signed_value;
            int initial_value;
            update_state->unk_04 = 0;
            offset_mask = (s16)record_value;
            signed_value = (s16)offset_mask;
            initial_value = func_80054AF0(signed_value);
            update_state->unk_08 = initial_value;
            update_state->unk_0A = initial_value;
        }
        func_80054C58();
        func_80054CD4();
        break;
    }

    case 0x1000:
        func_80054E00(0x74);
        break;

    case 0x2000:
        func_80054E00(0xE4);
        break;

    case 0x4000:
        func_80054E00(0xF4);
        break;

    }

}
