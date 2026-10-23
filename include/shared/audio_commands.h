#ifndef SHARED_AUDIO_COMMANDS_H
#define SHARED_AUDIO_COMMANDS_H

/* Packed SD_Call commands, not effect-bank sample IDs. The queue dispatcher
 * routes 0x300 to CD cue control and 0xB4 to the fast CD volume decrease. */
enum AudioCommand {
    AUDIO_FADE_CD_FAST = 0xB4,
    AUDIO_PLAY_CD_CUE = 0x300,
    AUDIO_RESUME_CD = 0x4300,
};

#endif
