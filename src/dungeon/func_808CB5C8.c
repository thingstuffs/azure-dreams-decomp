#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80067014();
M2C_UNK func_800671A8();
s32 func_80123200();
void func_80123928();
void func_801239B8();
extern M2C_UNK D_8011ACD8;
extern M2C_UNK D_80126E98;

typedef struct S_80123A60_0 {
    u8 pad_00[0xF];
    u8 unk_0F;
} S_80123A60_0;   /* arg0 in func_80123A60 */

/* Draws available entries for the selected group at fixed screen positions. */
void func_80123A60(S_80123A60_0 *state) {
    s16 draw_rect[4];
    s32 *entry;
    register s32 *entry_table ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 entry_id;
    register s32 slot ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 group;

    draw_rect[0] = 0x180;
    draw_rect[1] = 0x80;
    draw_rect[2] = 0x36;
    draw_rect[3] = 0x60;
    func_800671A8(draw_rect, 0, 0, 0);
    func_801239B8(&D_8011ACD8, 0x192, 0xD0);
    func_80067014(0);
    slot = 0;
    if (state->unk_0F == 3) {
        slot = state->unk_0F;
        entry_id = slot * 0x10;
        if (func_80123200(entry_id & 0xF0) & 0xFF) {
            entry_table = &D_80126E98;
            func_80123928(*(((slot * 0x20) + entry_id) + entry_table), 0x180, 0x80);
        }
        entry_id += 1;
        if (func_80123200(entry_id & 0xFF) & 0xFF) {
            entry_table = &D_80126E98;
            func_80123928(*((entry_id * 3) + entry_table), 0x1A4, 0xA0);
        }
        func_80067014(0);
        do {
            return;
        } while (0);
    }
    group = state->unk_0F;
    entry_id = group * 0x10;
    entry_table = &D_80126E98;
    entry = ((group * 0x20) + entry_id) + entry_table;
    do {
        if (func_80123200(entry_id & 0xFF) & 0xFF) {
            func_80123928(*entry, (s16) (((slot % 3) * 0x12) + 0x180), (s16) (((slot / 3) * 0x10) + 0x80));
        }
        slot += 1;
        entry += 3;
        entry_id += 1;
    } while (slot < 0x10);
    func_80067014(0);
}
