#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
} S_80013564;

extern S_80013564 D_80013564[];
extern int func_8004A6C0(void);
extern void bzero(void *ptr, int len);

/* Clear the selected record and its paired values when the index is below 20. */
void func_8004A7D8(void)
{
    s32 record_index = func_8004A6C0();

    if (record_index < 0x14) {
        bzero((void *)(0x800133E8 + record_index * 19), 0x13);
        D_80013564[record_index].unk0 = 0;
        D_80013564[record_index].unk2 = 0;
    }
}
