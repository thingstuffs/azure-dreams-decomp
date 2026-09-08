#include "common.h"

#include "common.h"

extern s32 D_800869C0[];

/* Sort up to 16 entries before the first zero key in ascending key order. */
void func_80059DAC(void)
{
    s32 saved_entry[2];
    register s32 entry_count ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    s32 entry_index;
    s32 compare_index;
    void *scan_entry;
    void *entry;
    void *entries;
    register void *compare_entry ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *sort_entry;

    entry_count = 0;
    scan_entry = D_800869C0;
count_entries:
    if (*(s32 *)scan_entry != 0) {
        entry_count++;
        if (entry_count < 16) {
            scan_entry = (s8 *)scan_entry + 8;
            goto count_entries;
        }
    }

    entry_index = 0;
    if (entry_count > 0) {
        entry = D_800869C0;
        entries = entry;
        do {
            compare_index = entry_count - 1;
            if (entry_index < compare_index) {
                register s32 compare_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

                compare_offset = compare_index * 8;
                sort_entry = entry;
                compare_entry = (void *)(compare_offset + (s32)entries);
                do {
                    if (*(s32 *)sort_entry > *(s32 *)compare_entry) {
                        saved_entry[1] = *(s32 *)((s8 *)sort_entry + 4);
                        saved_entry[0] = *(s32 *)sort_entry;
                        *(s32 *)((s8 *)sort_entry + 4) = *(s32 *)((s8 *)compare_entry + 4);
                        *(s32 *)sort_entry = *(s32 *)compare_entry;
                        *(s32 *)((s8 *)compare_entry + 4) = saved_entry[1];
                        *(s32 *)compare_entry = saved_entry[0];
                    }
                    compare_index--;
                    compare_entry = (s8 *)compare_entry - 8;
                } while (entry_index < compare_index);
            }
            entry_index++;
            entry = (s8 *)entry + 8;
        } while (entry_index < entry_count);
    }
}
