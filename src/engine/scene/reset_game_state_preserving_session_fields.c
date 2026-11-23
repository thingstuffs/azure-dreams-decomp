#include "common.h"
#include "shared/game_state.h"

#include "engine/scene.h"
#include "sdk/libc.h"
#include "slus/data.h"

typedef struct {
    s32 word;
    s8 byte4;
    s8 byte5;
} __attribute__((packed)) Copy6;

typedef struct {
    s32 word0;
    s32 word4;
    s8 byte8;
    s8 byte9;
} __attribute__((packed)) Copy10;

/* Clear the memory region and copy defaults while preserving six saved fields. */
void reset_game_state_preserving_session_fields(void)
{
    u8 *page = (u8 *)0x80010000;
    void *clear_page = page;
    u8 saved_3186;
    u32 saved_3180;
    u8 saved_3184;
    u8 saved_2d6e;
    u16 saved_2094;
    u16 saved_2098;


    saved_3186 = GAME_STATE->options.unk_3186;
    saved_3180 = GAME_STATE->options.option_color;
    saved_3184 = GAME_STATE->options.unk_3184;
    saved_2d6e = GAME_STATE->message_speed;
    saved_2094 = GAME_STATE->familiar_direction[0];
    saved_2098 = GAME_STATE->familiar_ai_mode[0];

    bzero(clear_page, 0x5C84);

    *(Copy6 *)0x8001020C = *(Copy6 *)session_reset_default_pair;
    *(Copy10 *)0x80010238 = *(Copy10 *)session_reset_default_block;

    GAME_STATE->options.unk_3186 = saved_3186;
    GAME_STATE->options.option_color = saved_3180;
    GAME_STATE->options.unk_3184 = saved_3184;
    GAME_STATE->message_speed = saved_2d6e;
    GAME_STATE->familiar_direction[0] = saved_2094;
    GAME_STATE->familiar_ai_mode[0] = saved_2098;
}
