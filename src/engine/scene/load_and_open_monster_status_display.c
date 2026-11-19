#include "common.h"
#include "engine/cd.h"
#include "engine/scene.h"
#include "slus.h"

#include "town/shop/object.h"

/* Forwards five arguments to create_monster_status_object after calling load_bin_nametwin and drain_cd_command_queue; returns the opened display object. */
void *load_and_open_monster_status_display(struct ActorRecord *actor, s32 second_arg, s32 third_arg, s32 fourth_arg, s32 fifth_arg)
{
    load_bin_nametwin();
    drain_cd_command_queue();
    return create_monster_status_object(actor, second_arg, third_arg, fourth_arg, fifth_arg);
}
