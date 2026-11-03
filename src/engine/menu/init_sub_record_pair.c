#include "common.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics.h"
#include "engine/menu.h"

/* Default packed GPU color shared by the primitive builders. */
extern SpriteColor shared_primitive_color;

/* Initializes a subrecord pair with shared data and the default color entry. */
void init_sub_record_pair(void *record_pair, void *init_data)
{
    init_paired_packet_records(record_pair, init_data);
    build_tinted_gradient_rect((u8 *)record_pair + 0x18, init_data, &shared_primitive_color);
}
