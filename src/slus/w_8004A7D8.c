#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
} S_80013564;

extern int func_8004A6C0(void);
extern void bzero(void *ptr, int len);

/* Clear the selected record and its paired values when the index is below 20. */
void func_8004A7D8(void)
{
    s32 record_index = func_8004A6C0();

    if (record_index < 0x14) {
        s32 offset = record_index * sizeof(S_80013564);

        bzero((void *)(0x800133E8 + record_index * 19), 0x13);
        ((S_80013564 *)(offset + 0x80013564))->unk0 = 0;
        ((S_80013564 *)(offset + 0x80013564))->unk2 = 0;
    }
}
