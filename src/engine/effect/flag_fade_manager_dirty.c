#include "common.h"

#include "engine/effect.h"
#include "engine/node.h"
#include "slus/data.h"

/* Unlinks the fade manager node and requests its removal. */
void flag_fade_manager_dirty(void)
{
    FadeManagerBody *manager = &fade_manager_state;

    unlink_node_if_registered(manager);
    NODE_HEADER(manager)->flags |= 0x8000;
    D_800814A0_scalar |= 0x8000;
}
