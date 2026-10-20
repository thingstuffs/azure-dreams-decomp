#include "common.h"

#include "common.h"

/* D_80084850 accessed via %hi/%lo (lui+lw/sw); size > 8 forces non-gp. */
extern s32 D_80084850[3];

extern s32 pop_audio_queue(void);
extern void dispatch_audio_event(s32 a0);
extern void audio_dispatch_stream_request(s32 a0);
extern void dispatch_audio_command(s32 a0);
extern void decode_audio_selector(s32 a0);
extern void service_audio_channels(void);
extern void func_800557BC(void);

/* Dispatch commands by type until a zero code, then finalize processing. */
void func_800542BC(void) {
    s32 command_code;
    s32 command;
    s32 command_type;

    D_80084850[0] += 1;
    while (1) {
        command = pop_audio_queue();
        command_code = command & 0xFFFF;
        command_type = command & 0xF00;
        if (command_code == 0) {
            break;
        }
        switch (command_type) {
        case 0x0:
            dispatch_audio_event(command_code);
            break;
        case 0x300:
            audio_dispatch_stream_request(command_code);
            break;
        case 0x200:
            dispatch_audio_command(command_code);
            break;
        case 0x500:
        case 0x700:
        case 0x800:
        case 0x600:
            decode_audio_selector(command & 0xFFFF);
            break;
        }
    }
    service_audio_channels();
    func_800557BC();
}
