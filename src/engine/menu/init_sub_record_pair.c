#include "common.h"
#include "engine/graphics.h"
#include "engine/menu.h"

/* CVECTOR-style color entry: r,g,b + a 4th (pad/code) byte. */
typedef struct S_80080B54 {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} S_80080B54;

extern S_80080B54 shared_primitive_color;

/* Initializes a subrecord pair with shared data and the default color entry. */
void init_sub_record_pair(void *record_pair, void *init_data)
{
    init_paired_packet_records(record_pair, init_data);
    build_tinted_gradient_rect((u8 *)record_pair + 0x18, init_data, &shared_primitive_color);
}
