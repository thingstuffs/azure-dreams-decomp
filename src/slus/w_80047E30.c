#include "slus/gp_shared_8152c.h"

void advance_effect_state(void)
{
    relocate_sprite_metadata_pointers(&D_80016000);
    patch_sprite_packet_texture_and_palette_ids(&D_80016000, 0xB, 0x7900, 0xD);
    D_8008152C = &D_80016000;
}
