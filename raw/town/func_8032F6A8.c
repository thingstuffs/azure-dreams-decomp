#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} TownRecord;

extern void func_8001ACE8(s32);
extern void func_8001AD60(s32);
extern s32 func_8001ADE0(s32);
extern s16 D_8001B8A8[3];

void func_80019EA8(s32 arg0, s32 arg1)
{
    register s32 i ASM_REG("$17");
    TownRecord *record;
    s16 *global;

    if ((arg0 != 0) && (i = 0, (arg1 > 0))) {
        global = D_8001B8A8;
loop:
        record = (TownRecord *)((i * 8) + arg0);
        func_8001AD60(record->unk2);
        ASM_KEEP(i);
        if (func_8001ADE0(global[1]) == 0) {
            func_8001AD60(record->unk4);
        } else {
            record = (TownRecord *)((i * 8) + arg0);
            if (func_8001ADE0(record->unk0) != 0) {
                func_8001ACE8(record->unk4);
            }
        }
        func_8001AD60(((TownRecord *)((i * 8) + arg0))->unk0);
        i++;
        if (i < arg1) {
            goto loop;
        }
    }
}

/* MECHANISM: A held pointer to D_8001B8A8 supplies retail's long-lived s4 base,
   while index-derived eight-byte record pointers force retail's repeated sll/addu.
   A guarded index seam preserves branch-local recomputation; pinning only the
   runtime index to s1 leaves the record pointer to fall naturally into s0. */
