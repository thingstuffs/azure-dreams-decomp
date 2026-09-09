#include "common.h"

typedef struct S_80024370_0_pre {
    u16 unk_00;
} S_80024370_0_pre;   /* the 0x2 bytes before arg0 in func_80024370, addressed as arg0[-1] */

typedef struct S_80024370_0 {
    void * unk_00;
    u16 unk_04;
} S_80024370_0;   /* arg0 in func_80024370 */

typedef struct S_80024370_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024370_1;   /* object in func_80024370 */

typedef struct S_80024370_2 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80024370_2;   /* global_page in func_80024370 */



extern void func_80024264(void *arg0);
#ifndef NON_MATCHING
__asm__(".set func_80024264_returning, func_80024264");
extern void func_80024264_returning(void *arg0);
#else
#define func_80024264_returning func_80024264
#endif
extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

/* Advance the entry counters, trigger count milestones, and update the target. */
void func_80024370(void *entry, s32 unused, void *target)
{
    S_80024370_1 *object;
    u16 count;

    object = ((S_80024370_0 *)entry)->unk_00;
    object->unk_14++;

    count = ((S_80024370_0 *)entry)->unk_04 + 1;
    ((S_80024370_0 *)entry)->unk_04 = count;

    if ((s16)count == 8) {
        goto count_8;
    }
    if ((s16)count == 0x10) {
        goto count_16;
    }
    goto done;

count_8:
    func_80024264_returning(((S_80024370_0 *)entry)->unk_00);
    goto done;

count_16:
    {
        s32 *global_page;

        global_page = (s32 *)0x80080000;
        ((S_80024370_0_pre *)entry)[-1].unk_00 |= 0x8000;
        ((S_80024370_2 *)global_page)->unk_14A0 |= 0x8000;
    }
done:
    func_800478B8(target);
}
