#include "common.h"

extern void func_80018E34(s32);
extern void func_80018EA8(void);
extern void func_800190C0(void *);
extern void func_800191EC(void *);

/* Processes flagged four-byte entries according to the mode, skipping type 0x18. */
void func_8001922C(void *entries, s32 entry_mode)
{
    void *entry_list;
    s32 initial_mode;
    u8 *entry;
    s32 entry_index;
    register u8 excluded_type ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    s32 mode;

    entry_list = entries;
    initial_mode = entry_mode;
    do {
        entry = entry_list;
    } while (0);
    mode = initial_mode;
    entry_index = 0;
    if (entry[1] != 0) {
        excluded_type = 0x18;
loop:
        if ((entry[3] & 0x20) && entry[1] != excluded_type) {
            if (mode == 0) {
                func_800190C0(entry);
                entry += 4;
                goto next;
            }
            func_800191EC(entry);
            func_80018E34(entry_index);
        }
        entry += 4;
next:
        entry_index++;
        if (entry[1] != 0) {
            goto loop;
        }
    }
    func_80018EA8();
}
