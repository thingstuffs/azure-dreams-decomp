#include "common.h"

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Inner;

typedef struct {
    s32 *unk0;
    Inner *unk4;
} Entry;

typedef struct {
    s32 unk0;
    u8 pad4[0x1C];
} Work;

extern void strncat(void *, void *, s32);
extern s32 func_8004DC14(void *, s32);
extern void func_8004E99C(void *, void *);
extern s32 D_8002503C;

void func_80027BBC(void *arg0, void *arg1)
{
    Work sp10;
    s32 var_s1;
    s32 var_s2;
    Entry **var_s0;

    var_s2 = 6;
    var_s0 = (Entry **)((u8 *)arg0 + 0x18);
    var_s1 = 0;
    for (;;) {
        Entry *entry = *var_s0;
        Inner *inner = entry->unk4;
        s32 unkA = inner->unkA;
        sp10.unk0 = D_8002503C;

        if (unkA >= 0x79) {
            if (entry->unk0 == 0) {
                strncat(&sp10, (u8 *)arg1 + var_s1, 0x12);
                (*var_s0)->unk0 = (s32 *)func_8004DC14(&sp10, 1);
            }
        } else if (entry->unk0 != 0) {
            func_8004E99C(entry->unk0, entry);
            (*var_s0)->unk0 = 0;
        }
        var_s0 += 1;
        var_s2 += 1;
        var_s1 += 0x12;
        if (var_s2 >= 0xE) {
            break;
        }
    }
}
