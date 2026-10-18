#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x2C];
    s32 field_2C;
    u8 pad_30[0x4A - 0x30];
    u8 field_4A;
    u8 pad_4B;
    u8 field_4C;
} Entity;

typedef struct {
    s32 field_00;
    u8 pad_04[0x20 - 0x04];
    s32 field_20;
    s32 field_24;
    u8 pad_28[0x2C - 0x28];
    s32 field_2C;
    u8 pad_30[0x50 - 0x30];
} Slot;

extern Slot D_80085FA8[];
extern s32 D_800869B4[3];

extern s32 read_next_byte_and_finish(Entity *);
extern void audio_sequence_note_off(s32, s32, s32);
extern void func_80056E10(s32, s32, s32);
extern void sound_set_seven_bit_channel_value_and_notify(s32, s32, s32);
extern void func_8005845C(u8, u8);
extern void audio_dispatch_midi_event(Entity *, s32, s32, s32);

/* Processes the next entity command and returns its control flag. */
s32 audio_read_compact_sequence_event(Entity *entity)
{
    register Entity *ent = entity;
    s32 command;
    s16 operand;
    s32 value;
    s16 saved_command;
    s32 command_index;

    command = read_next_byte_and_finish(ent);
    saved_command = command;
    if (!(command & 0x80)) {
        s32 next_byte = read_next_byte_and_finish(ent);
        value = next_byte & 0x7F;
        if (value != 0) {
            operand = next_byte;
            func_80056E10(ent->field_4C, command & 0x7F, value);
        } else {
            operand = next_byte;
            audio_sequence_note_off(ent->field_4C, command & 0x7F, 0);
        }
        ent->field_4A = saved_command;
        return 0 < (operand & 0x80);
    }

    command_index = (command & 0x7F) - 0x46;
    if ((u32)command_index >= 0x3A) {
        goto default_command;
    }
    command = command_index;
    switch (command) {

    case 4:
    audio_sequence_note_off(ent->field_4C, ent->field_4A, 0);
    return 0;
    case 5:
    audio_sequence_note_off(ent->field_4C, ent->field_4A, 0);
    return 1;
    case 1:
    {
        s32 next_byte = read_next_byte_and_finish(ent);
        u32 slot_count;
        operand = next_byte;
        slot_count = D_800869B4[0];
        {
            u32 slot_index = 0;
            while (slot_index < slot_count) {
                D_80085FA8[slot_index].field_24 = ((next_byte & 0x7F) << 1) + 2;
                slot_index++;
            }
        }
        return 0 < (operand & 0x80);
    }
    case 2:
    {
        s32 next_byte = read_next_byte_and_finish(ent);
        operand = next_byte;
        sound_set_seven_bit_channel_value_and_notify(ent->field_4C, 0, next_byte & 0x7F);
        goto ret_bool;
    }
    case 3:
    {
        s32 next_byte = read_next_byte_and_finish(ent);
        operand = next_byte;
        func_8005845C(ent->field_4C, next_byte & 0x7F);
        goto ret_bool;
    }
    case 0:
    {
        s32 next_byte = read_next_byte_and_finish(ent);
        operand = next_byte;
        ent->field_4C = next_byte & 0xF;
        goto ret_bool;
    }
    case 57:
    operand = read_next_byte_and_finish(ent);
    ent->field_2C = 1;
    goto ret_bool;
    default:
    default_command:
    {
        s32 next_byte = read_next_byte_and_finish(ent);
        operand = next_byte;
        audio_dispatch_midi_event(ent, (ent->field_4C + 0xB0) & 0xFF,
                      saved_command & 0x7F, next_byte & 0x7F);
    }
    }

ret_bool:
    return 0 < (operand & 0x80);
}
