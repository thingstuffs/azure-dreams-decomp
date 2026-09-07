#include "common.h"

/* Given a u16 index, walks D_8006CE80[idx].unk04->unk0C, a null-terminated list of s32 values, calling func_80041284() on each. */
typedef struct S_8006CE80_inner {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 *unk0C; /* null-terminated list of callback args */
} S_8006CE80_inner;

typedef struct S_8006CE80 {
    s32 unk00;
    S_8006CE80_inner *unk04;
    s32 unk08;
} S_8006CE80;

extern S_8006CE80 D_8006CE80[100];
extern void func_80041284(s32);

void func_800411FC(u16 arg0) {
    S_8006CE80 *ent;
    S_8006CE80_inner *rec;
    s32 *list;

    ent = &D_8006CE80[arg0];
    rec = ent->unk04;
    if (rec == 0) {
        return;
    }
    list = rec->unk0C;
    if (list == 0) {
        return;
    }
    if (*list == 0) {
        return;
    }
    do {
        func_80041284(*list);
        list++;
    } while (*list != 0);
}
