#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009D808(); /* extern */
M2C_UNK func_8009D940(); /* extern */
M2C_UNK func_8009DA50();    /* extern */
extern u16 D_80082D08[];
extern s32 D_801007F8[];
extern s32 D_80100900[];

typedef struct S_8009CEE8_0 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x8];
    s32 * unk_0C;
} S_8009CEE8_0;   /* temp_v1 in func_8009CEE8 */

/* Builds the entry list and processes each entry's items at its coordinates. */
void func_8009CEE8(void) {
    M2C_UNK setup_a[2];
    M2C_UNK setup_b[2];
    s32 *item_cursor;
    s32 coord_x;
    s32 coord_y;
    void **entry_cursor;
    S_8009CEE8_0 *entry;
    u16 *base;

    base = D_80082D08;
    func_8009D808(base, setup_a, setup_b);
    func_8009D940(setup_a, setup_b, D_80100900, D_801007F8);
    entry_cursor = (void **)D_801007F8;
    if (D_801007F8[0] != 0) {
        do {
            entry = *entry_cursor;
            item_cursor = entry->unk_0C;
            if (item_cursor != NULL) {
                coord_x = entry->unk_00;
                coord_y = entry->unk_02;
                while (*item_cursor != 0) {
                    func_8009DA50(*item_cursor, base, (s16)coord_x, (s16)coord_y);
                    item_cursor++;
                }
            }
            entry_cursor = (void **)((s8 *)((void **)((s8 *)entry_cursor + 4)));
        } while (*entry_cursor != NULL);
    }
}
