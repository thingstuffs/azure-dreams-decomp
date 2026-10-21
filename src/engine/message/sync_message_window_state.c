#include "common.h"

#include "common.h"
#include "engine/message.h"

typedef struct Func80037F70Inner {
    u8 pad_00[0x85];
    u8 field_85;
    u8 field_86;
} Func80037F70Inner;

typedef struct Func80037F70Outer {
    Func80037F70Inner *field_00;
} Func80037F70Outer;

extern const char message_window_primary_sync_data[0x10];
extern const char message_window_tail_sync_data[0x10];
extern const char message_window_detail_sync_data[0x10];
extern u8 runtime_script_state[0xB0];

extern s32 func_80043FB8(const char *format, ...);

/* Processes global state, updates the inner context, and saves then clears its status byte. */
void sync_message_window_state(Func80037F70Outer *context)
{
    u8 *state = runtime_script_state;

    func_80043FB8(message_window_primary_sync_data, state);
    func_80043FB8(message_window_tail_sync_data, state + 0xA8);
    func_80043FB8(message_window_detail_sync_data, state + 0x9C);
    sync_message_window_data(context->field_00);
    context->field_00->field_86 = context->field_00->field_85;
    context->field_00->field_85 = 0;
}
