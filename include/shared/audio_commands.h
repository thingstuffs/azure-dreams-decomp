#ifndef SHARED_AUDIO_COMMANDS_H
#define SHARED_AUDIO_COMMANDS_H

/* Packed low-16-bit SD_Call queue commands; drain_audio_commands_and_service_channels dispatches by bits 8..11.
 * The 0x300 group controls CD cues and bits 12..15 select its control mode; these are not sample-bank indices. */
enum AudioCommand {
    AUDIO_CURSOR_MOVE = 0x502, /* menu cursor moves one step */
    AUDIO_MENU_CONFIRM = 0x503, /* menu choice confirmed */
    AUDIO_CURSOR_SLIDE = 0x507, /* menu cursor slides toward its target index */
    AUDIO_ACCEPT = 0x514, /* choice accepted */
    AUDIO_CANCEL = 0x515, /* menu cancelled or closed */
    AUDIO_SLOT_REEL_STOP = 0x522, /* slot machine: a reel is stopped */
    AUDIO_SLOT_SPIN = 0x524, /* slot machine: reels spinning, requested every frame */
    AUDIO_SLOT_START = 0x526, /* slot machine: spin started */
    AUDIO_MESSAGE_END = 0xC4, /* end of a message */
    AUDIO_MESSAGE_ADVANCE = 0xB4, /* message advances; same word as AUDIO_FADE_CD_FAST */
    AUDIO_FADE_CD_FAST = 0xB4, /* 0xB0 ramp family; mask 0x4 selects the CD stream task and set_sound_task_priority installs parameter 0xF */
    AUDIO_PLAY_CD_CUE = 0x300, /* reads the current sound-stream cue and installs its pending sector range before playback setup */
    AUDIO_RESUME_CD = 0x4300, /* 0x300 cue-control group with mode 0x4000; dispatches stream control event 0xF4 */
};

#endif
