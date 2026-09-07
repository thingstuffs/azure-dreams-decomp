#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80158854_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    void * unk_8C;
} S_80158854_0;   /* work in func_80158854 */

typedef struct S_80158854_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80158854_1;   /* obj in func_80158854 */

typedef struct S_80158854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80158854_2;   /* part_a in func_80158854 */

typedef struct S_80158854_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80158854_3;   /* part_b in func_80158854 */

typedef struct S_80158854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80158854_4;   /* actor in func_80158854 */


extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_80158A58[];
extern u8 D_80158E5C[];
extern u8 D_8015C510[];
extern u8 D_8015C538[];

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern s32 func_800A6D30();
extern M2C_UNK func_800A48F0();
extern M2C_UNK func_800A9C18();
extern M2C_UNK func_800AA36C();

#ifdef NON_MATCHING
#define CALLBACK_PAGE ((u32)(D_80158E5C + 0x71A4))
#else
#define CALLBACK_PAGE 0x80160000U
#endif

void *func_80158854(s32 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    s32 left;
    s32 right;
    void *work;
    s16 saved_arg3;
    void *obj;
    register s8 saved_arg2;
    s8 saved_arg1;
    register void *part_a ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 final_arg0 ASM_REG("$23");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    S_80158854_3 *part_b;
    void *actor;
    u32 callback_page;

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    ASM_KEEP_DEP_NV(saved_arg2, saved_arg3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        final_arg0 = arg0;
        work = (u8 *)obj + 0x20;
        ASM_KEEP(work);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ((S_80158854_0 *)work)->unk_13 = 0x1C;
        func_8004491C(obj, D_80045340);

        part_a = ((S_80158854_1 *)obj)->unk_08;
        ((S_80158854_2 *)part_a)->unk_0A = saved_arg3;
        part_b = ((S_80158854_1 *)obj)->unk_0C;
        part_b->unk_25 = saved_arg2;
        actor = work;
        kind = arg0 & 3;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            ((S_80158854_0 *)work)->unk_8C = D_80158E5C;
            left = ((S_80158854_0 *)work)->unk_14 | 0x6000;
            right = ((S_80158854_0 *)work)->unk_1C | 0x6000;
            ((S_80158854_0 *)work)->unk_14 = left;
            ((S_80158854_0 *)work)->unk_1C = right;
            part_b->unk_2C = D_8015C510;
            goto common_tail;
        }
        if (kind >= 2) {
            ((S_80158854_0 *)work)->unk_8C = D_80158E5C;
            left = ((S_80158854_0 *)work)->unk_14 | 0x2000;
            right = ((S_80158854_0 *)work)->unk_1C | 0x2000;
            ((S_80158854_0 *)work)->unk_14 = left;
            ((S_80158854_0 *)work)->unk_1C = right;
            part_b->unk_2C = D_8015C510;
            goto common_tail;
        }

        if (((arg0 & ~3) << 16) != 0) {
            goto set_work_callback;
        }
        if (((S_80158854_0 *)work)->unk_14 & 0x200) {
            goto set_actor_callback;
        }
        if (!(func_800A6D30() & 1)) {
            goto set_actor_callback;
        }
        func_800A48F0(work, 1,
                      (func_800A6D30() & 0x3F) | 0x20);
        part_b->unk_2C = D_8015C538;

set_actor_callback:
        callback_page = CALLBACK_PAGE;
        ASM_KEEP(callback_page);   /* MATCH pin: keeps a constant in a register as retail does */
        ((S_80158854_4 *)actor)->unk_8C = (void *)(callback_page - 0x71A4);
        goto normal_done;

set_work_callback:
        callback_page = CALLBACK_PAGE;
        ASM_KEEP(callback_page);   /* MATCH pin: keeps a constant in a register as retail does */
        ((S_80158854_0 *)work)->unk_8C = (void *)(callback_page - 0x71A4);

normal_done:
        part_b->unk_2C = D_8015C510;

common_tail:
        ((S_80158854_1 *)obj)->unk_10 = D_80158A58;
        func_800A9C18(obj, part_a, part_b, (s16)final_arg0);
        ((S_80158854_4 *)actor)->unk_9A = 0xFF;
        ((S_80158854_4 *)actor)->unk_9C = -1;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
