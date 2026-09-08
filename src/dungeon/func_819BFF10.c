#include "common.h"

#define FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern s32 func_80024AE8();

/* Mark and process entries at the given coordinates with thresholds in the specified range. */
void func_80025710(void *list_head, s32 x, s32 y, s16 upper_bound, s32 lower_bound) {
    s32 match_x = x;
    s32 match_y = y;
    s32 upper_limit;
    s32 lower_limit;
    s16 threshold;
    u16 flags;
    void *range_data;
    void *position_data;
    register void *next_entry ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *entry;
    void *list_link;
    register void *head ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    list_link = list_head;
    head = list_link;
    next_entry = FIELD(list_link, s32 *, 0x5C);
    list_link = next_entry + 0x20;
    if (list_link != head) {
        ASM_KEEP(list_link);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        upper_limit = (s16)upper_bound;
        lower_limit = (s16)lower_bound;
        entry = list_link - 0x20;
        do {
            position_data = FIELD(list_link, void **, -0x14);
            range_data = FIELD(entry, void **, 8);
            if ((FIELD(position_data, u8 *, 0x24) == (match_x & 0xFFFF)) &&
                (FIELD(position_data, u8 *, 0x25) == (match_y & 0xFFFF))) {
                threshold = FIELD(range_data, s16 *, 0xA);
                if ((upper_limit >= threshold) && (lower_limit < threshold)) {
                    flags = FIELD(entry, u16 *, 0x1E);
                    if (!(flags & 0x2000)) {
                        FIELD(entry, u16 *, 0x1E) = flags | 0x2000;
                        func_80024AE8(entry, range_data, position_data);
                    }
                }
            }
            next_entry = FIELD(list_link, s32 *, 0x5C);
            list_link = next_entry + 0x20;
            ASM_KEEP(list_link);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            entry = list_link - 0x20;
        } while (list_link != head);
    }
}
