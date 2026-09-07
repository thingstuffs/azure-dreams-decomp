#include "common.h"

#include "common.h"

typedef struct {
    u8 unk0;
    u8 unk1;
} S_8004AFE8;

extern unsigned char *D_80081540;
extern s32 func_8004AE3C(void **arg0);
extern void func_8004AFC8(void *base, s32 count, s32 size, void *compar);
extern s32 func_8004AFE8(S_8004AFE8 **arg0);
extern void func_8004B028(u8 *arg0, S_8004AFE8 **arg1, s32 arg2);
extern void *memcpy(void *dst, void *src, s32 n);
extern void bzero(void *p, s32 n);
extern s32 func_8004AE68(void *a0, void *a1);
extern s32 func_8004AE98(void *a0, void *a1);

/* Sorts entries, then orders each group using a table built from the original list. */
void func_8004B08C(S_8004AFE8 **entries) {
    S_8004AFE8 *saved_entries[0x40];
    u8 scratch[0x80];
    s32 count;
    s32 next_key;
    s32 group_key;
    S_8004AFE8 **group;
    register u8 *work_buf ASM_REG("$17"); /* s1: copy then loop work */
    u8 *scratch_base;

    scratch_base = scratch;
    D_80081540 = scratch_base;
    group = entries;
    count = func_8004AE3C((void **)entries);
    work_buf = (u8 *)saved_entries;
    memcpy(work_buf, group, count * 4);
    ((S_8004AFE8 **)work_buf)[count] = 0;
    func_8004AFC8(group, count, 4, func_8004AE68);
    group_key = 0;
    if (*group != 0) {
        work_buf = scratch_base;
    next_group:
        if (group != 0) {
            next_key = (*group)->unk1;
            if (next_key != group_key) {
                group_key = next_key;
                bzero(work_buf, 0x80);
                count = func_8004AFE8(group);
                func_8004B028(work_buf, saved_entries, group_key);
                func_8004AFC8(group, count, 4, func_8004AE98);
                group = group + count;
            }
            if (*group != 0) {
                goto next_group;
            }
        }
    }
}
