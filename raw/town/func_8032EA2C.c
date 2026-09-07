#include "common.h"

extern void func_80018E34(s32);
extern void func_80018EA8(void);
extern void func_800190C0(void *);
extern void func_800191EC(void *);

void func_8001922C(void *arg0, s32 arg1)
{
    register void *in_entry ASM_REG("$4");
    register s32 in_condition ASM_REG("$5");
    u8 *entry;
    s32 index;
    register u8 terminal ASM_REG("$18");
    s32 condition;

    in_entry = arg0;
    in_condition = arg1;
    ASM_USE(in_entry);
    ASM_USE(in_condition);
    do {
        entry = in_entry;
    } while (0);
    condition = in_condition;
    index = 0;
    if (entry[1] != 0) {
        terminal = 0x18;
loop:
        if ((entry[3] & 0x20) && entry[1] != terminal) {
            if (condition == 0) {
                func_800190C0(entry);
                entry += 4;
                goto next;
            }
            func_800191EC(entry);
            func_80018E34(index);
        }
        entry += 4;
next:
        index++;
        if (entry[1] != 0) {
            goto loop;
        }
    }
    func_80018EA8();
}
