#include "common.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics.h"
#include "engine/menu.h"
#include "slus/data.h"


/* Initializes a subrecord pair with shared data and the default color entry. */
void init_packet_pair_and_gradient(u8 *packets, const RECT *rect)
{
    init_paired_packet_records(packets, rect);
    build_tinted_gradient_rect(packets + 0x18, (const u8 *)rect, &shared_primitive_color);
}
