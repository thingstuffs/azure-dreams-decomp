#include "common.h"
#include "engine/cd.h"
#include "engine/scene.h"
#include "slus.h"

extern void *create_monster_status_object(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* Forwards five arguments to create_monster_status_object after calling load_bin_nametwin and drain_cd_command_queue; returns the opened display object. */
void *load_and_open_monster_status_display(s32 first_arg, s32 second_arg, s32 third_arg, s32 fourth_arg, s32 fifth_arg)
{
    load_bin_nametwin();
    drain_cd_command_queue();
    return create_monster_status_object(first_arg, second_arg, third_arg, fourth_arg, fifth_arg);
}
