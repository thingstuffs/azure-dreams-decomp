#include "common.h"

#include "common.h"

typedef struct Func800398BCOwner {
    u8 pad_00[0x10];
    s32 field_10;
    u8 pad_14[0x08];
    u8 *read_ptr;
    u8 pad_20[0x60];
    u8 *object_80;
    u8 pad_84[0x04];
    s8 field_88;
} Func800398BCOwner;

extern s32 func_80053EF0(s32 arg0);
extern s32 func_80039884(Func800398BCOwner *arg0);
extern void func_8003F540(s32 arg0, s32 arg1, u32 arg2, u32 arg3);
extern s16 func_80053DA8(s32 arg0);
extern s32 D_800721C0[32];
extern s32 D_8006CD50[];

/* Decodes and dispatches an eight-byte command, or rewinds it when gated by state. */
void func_800398BC(Func800398BCOwner *owner)
{
    s32 runtime_state;
    s32 owner_gate;
    u8 *command_ptr;
    u8 *second_word_ptr;
    u32 command_word;
    u32 payload_word;
    u32 table_index;

    runtime_state = func_80053EF0(4);
    owner_gate = func_80039884(owner);
    if (owner_gate != 0) {
        if (runtime_state == 0) {
            goto decode;
        }
        goto rewind;
    }
    if (runtime_state == 0x100) {
        goto rewind;
    }
    if (runtime_state != 3) {
        goto decode;
    }

rewind:
    owner->field_10 = 0;
    owner->read_ptr--;
    goto done;

decode:
    command_ptr = owner->read_ptr;
    command_word = command_ptr[0] + (command_ptr[1] << 8) +
            (command_ptr[2] << 16) + (command_ptr[3] << 24);
    second_word_ptr = command_ptr + 4;
    owner->read_ptr = second_word_ptr;
    payload_word = command_ptr[4] + (second_word_ptr[1] << 8) +
            (second_word_ptr[2] << 16) + (second_word_ptr[3] << 24);
    owner->read_ptr = command_ptr + 8;
    table_index = (command_word >> 19) & 0x1F;
    command_word &= 0xFF07FFFF;

    func_8003F540(owner->object_80[0x3C],
                  D_8006CD50[D_800721C0[table_index]],
                  command_word,
                  payload_word);
    func_80053DA8(0x300);
    owner->field_10 = 0;
done:
    return;
}
