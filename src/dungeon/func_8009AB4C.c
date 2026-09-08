/* row func_8009AB4C, true base 0x800A02AC -- exemplar-seeded from landed
 * func_8009AC64 [true base 0x800A03C4] (MATCH @2.8.1-G0, gate_verified).
 * Opcode-sequence similarity 0.9655. Sole adaptation measured off the retail
 * stream: the func_800A2CB8 guard in the loop body is absent here (retail
 * drops the jal + its sll/beq test); register roles follow.
 * Ordinary code: no alias, no section attribute, no literal word arrays.
 */
#include "common.h"

extern u16 D_8008347E;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_8009A540(s32, u8, u8, s16);
s32 func_8009B25C(void *, u16, u16, s16);

/* Check eight neighboring positions in cyclic order and return the first result that passes the direction check. */
s32 func_800A02AC(void *entity, u16 x, u16 y) {
    u16 *x_offsets;
    u16 *y_offsets;
    register void *entity_data ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *current_entity;
    u16 base_x;
    u16 base_y;
    s32 result;
    register s32 attempt ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 direction;

    current_entity = entity;
    base_x = x;
    base_y = y;
    x_offsets = D_8006CCD8;
    y_offsets = D_8006CCE8;
    entity_data = *(void **)((s8 *)current_entity - 0x14);
    direction = D_8008347E & 7;
    for (attempt = 0; attempt < 8; attempt++, direction = (direction + 1) & 7) {
        result = func_8009B25C(current_entity, (base_x + x_offsets[direction]) & 0xFFFF, (base_y + y_offsets[direction]) & 0xFFFF, *(s16 *)((s8 *)current_entity + 0x88));
        if (result != 0) {
            if (((func_8009A540(direction, *(u8 *)((s8 *)entity_data + 0x24), *(u8 *)((s8 *)entity_data + 0x25), (s16)((u16)*(s16 *)((s8 *)current_entity + 0x88) - 0x20)) << 16) == 0)) {
                continue;
            }
            current_entity = entity;
            return result;
        }
    }
    return 0;
}
