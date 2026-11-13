#include "shared/movie_list.h"
#include "common.h"
#include "engine/movie.h"
#include "m2c_compat.h"
#include "engine/audio.h"
#include "slus.h"
#include "town/scene.h"

extern MovieListNode town_transition_callback_list;
extern s8 scene_music_hold;
extern MovieListNode D_800D42B4;

/* Pass the town data pair to append_town_movie_list_node, set the shared flag, and invoke the follow-up routines. */
void queue_transition_music_hold(void) {
    append_list_tail(&town_transition_callback_list, &D_800D42B4);
    scene_music_hold = 1;
    SD_Call(0xBF);
    drain_audio_commands_and_service_channels();
}
