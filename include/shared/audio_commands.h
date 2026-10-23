#ifndef SHARED_AUDIO_COMMANDS_H
#define SHARED_AUDIO_COMMANDS_H

/* Packed low-16-bit SD_Call queue commands; drain_audio_commands_and_service_channels dispatches by bits 8..11.
 * The 0x300 group controls CD cues and bits 12..15 select its control mode; these are not sample-bank indices. */
enum AudioCommand {
    AUDIO_FADE_CD_FAST = 0xB4, /* 0xB0 ramp family; mask 0x4 selects the CD stream task and set_sound_task_priority installs parameter 0xF */
    AUDIO_PLAY_CD_CUE = 0x300, /* reads the current sound-stream cue and installs its pending sector range before playback setup */
    AUDIO_RESUME_CD = 0x4300, /* 0x300 cue-control group with mode 0x4000; dispatches stream control event 0xF4 */
};

#endif
