#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BA810_0 {
    void * unk_00;
} S_800BA810_0;   /* arg0 in func_800BA810; pointer addresses record offset 0x18 */

typedef struct S_800BA810_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800BA810_1;   /* temp_v1 in func_800BA810 */

typedef struct S_800BA810_2 {
    void * unk_00;
} S_800BA810_2;   /* temp_a0_2 in func_800BA810; pointer addresses record offset 0x18 */

typedef struct S_800BA810_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800BA810_3;   /* temp_v0_4 in func_800BA810 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800BA6B8;
void func_800403BC(s32 *);                  /* extern */
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
typedef struct S_8006DE24_Entry {
    u8 pad[0x12];
    u8 type;
    u8 pad13;
} S_8006DE24_Entry;
extern S_8006DE24_Entry D_8006DE24[];
void func_800BA764(u16, u16, s16, u32);      /* extern */
s16 func_800BCB04();                   /* extern */
typedef struct S_800B50B0_Entity {
    u8 pad00[0x13];
    u8 kind13;
    u8 pad14[0x16];
    u16 angle2a;
    u8 pad2c[0x1c];
    u8 kind48;
    u8 pad49[0x17];
    void *child60;
    u8 pad64[0x24];
    s16 height88;
} S_800B50B0_Entity;
extern S_800B50B0_Entity *D_800DF374;
extern u16 D_800DF378;
extern u16 D_800DF37A;
extern u8 D_800DF380[];

/* Updates marked dungeon tiles for the selected entity, mode, and facing. */
void func_800BA810(S_800B50B0_Entity *entity, s16 selection) {
    s32 height;
    s16 forward_height;
    s16 adjacent_height;
    s16 range_height;
    register s32 *tile_list ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 direction;
    register s32 mode ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 entry_value ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 mode_index ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 forward_steps;
    s32 adjacent_steps;
    register s32 range_steps ASM_REG("$17");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 tile_z;
    u32 tile_x;
    u8 entry_id;
    u8 entry_type;
    u16 angle;
    void *child;
    S_800BA810_3 *child_position;
    S_800BA810_1 *position;

    if (entity == NULL) {
        D_800DF374 = NULL;
        func_800403BC(&D_800BA6B8);
        return;
    }
    if (D_800DF374 == entity) {
        ASM_KEEP_NV(selection);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        if (D_800DF37A == (s16) entity->angle2a) {
            tile_list = &D_800BA6B8;
            if (D_800DF378 != (selection & 0xFFFF)) {
                goto prepare_update;
            }
        } else {
            tile_list = &D_800BA6B8;
            goto update_tiles;
        }
    } else {
prepare_update:
        tile_list = &D_800BA6B8;
update_tiles:
        angle = entity->angle2a;
        do { D_800DF374 = entity; } while (0);
        ASM_KEEP_NV(selection);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        D_800DF378 = selection;
        ASM_KEEP_NV(selection);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        D_800DF37A = angle;
        func_800403BC(tile_list);
        do { mode = selection & 0x3FFF; } while (0);
        position = ((S_800BA810_0 *)((u8 *)entity - 0x18))->unk_00;
        height = entity->height88;
        entry_value = (u16) position->unk_02;
        tile_x = (u32) entry_value >> 6;
        tile_z = (u16) position->unk_06 >> 6;
        mode_index = mode;
        direction = (entity->angle2a >> 9) & 7;
        if (mode_index == 8) {
            forward_steps = 1;
            if ((entity->kind13 == 0x16) && (entity->kind48 == 0xF)) {
                forward_steps = 0xA;
            }
            if (forward_steps > 0) {
                do {
                    forward_height = height - 0x20;
                    tile_x += (s16) D_8006CCD8[direction];
                    tile_z += (s16) D_8006CCE8[direction];
                    height = func_800BCB04(((tile_x << 6) + 0x20) & 0xFFE0, ((tile_z << 6) + 0x20) & 0xFFE0, forward_height);
                    if (height >= 0x201) {
                        break;
                    }
                    func_800BA764(tile_x & 0xFFFF, tile_z & 0xFFFF, height, 0xFF);
                    forward_steps -= 1;
                } while (forward_steps > 0);
            } else {
                return;
            }
            return;
        }
        if (mode_index == 11) {
            adjacent_steps = 1;
            do {
                adjacent_height = height - 0x20;
                tile_x += (s16) D_8006CCD8[direction];
                tile_z += (s16) D_8006CCE8[direction];
                height = func_800BCB04(((tile_x << 6) + 0x20) & 0xFFE0, ((tile_z << 6) + 0x20) & 0xFFE0, adjacent_height);
                if (height >= 0x201) {
                    break;
                }
                func_800BA764(tile_x & 0xFFFF, tile_z & 0xFFFF, height, 0xFF00);
                adjacent_steps -= 1;
            } while (adjacent_steps > 0);
            return;
        }
        if (mode_index == 12) {
            func_800BA764(tile_x & 0xFFFF, tile_z & 0xFFFF, height, 0xFFFF);
            return;
        }
        entry_value = mode;
        entry_value -= 1;
        if ((u32) entry_value >= 3U) {
            return;
        }
        mode_index -= 1;
        entry_value = mode_index * 3;
        entry_id = *((u8 *) entity + entry_value + 8);
        entry_type = D_8006DE24[entry_id].type;
        if (entry_type == 1) {
            entry_value = D_800DF380[entry_id];
            range_steps = entry_value & 0x1F;
            if (range_steps > 0) {
                do {
                    range_height = height - 0x20;
                    tile_x += (s16) D_8006CCD8[direction];
                    tile_z += (s16) D_8006CCE8[direction];
                    height = func_800BCB04(((tile_x << 6) + 0x20) & 0xFFE0, ((tile_z << 6) + 0x20) & 0xFFE0, range_height);
                    if (height >= 0x201) {
                        break;
                    }
                    func_800BA764(tile_x & 0xFFFF, tile_z & 0xFFFF, height, 0xFF);
                    range_steps -= 1;
                } while (range_steps > 0);
            }
        } else if (entry_type == 2) {
            child = entity->child60;
            if (child != NULL) {
                child_position = ((S_800BA810_2 *)((u8 *)child - 0x18))->unk_00;
                func_800BA764((u16) child_position->unk_02 >> 6, (u16) child_position->unk_06 >> 6, ((S_800B50B0_Entity *)child)->height88, 0xFF);
            }
        }
    }
}
/* Warning: struct S_8006DE24_Entry is not defined (only forward-declared) */
