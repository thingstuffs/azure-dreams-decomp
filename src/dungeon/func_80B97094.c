#include "common.h"

typedef struct S_80170894_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    void * unk_8C;
} S_80170894_0;   /* work in func_80170894 */

typedef struct S_80170894_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80170894_1;   /* obj in func_80170894 */

typedef struct S_80170894_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170894_2;   /* part_a in func_80170894 */

typedef struct S_80170894_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170894_3;   /* part_b in func_80170894 */

typedef struct S_80170894_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170894_4;   /* actor in func_80170894 */



extern void *func_8003FD64(s32, const void *);
extern void func_8004491C(void *, const void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern void func_80170A98(void);
extern void func_80170E9C(void);
extern void func_80174ED8(void);
extern void func_80174F00(void);

extern s32 D_80045340;
extern u8 D_80083498[];

void *func_80170894(s32 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    void *work;
    s16 saved_arg3;
    s32 saved_arg0;
    void *obj;
    register s8 saved_arg2 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s8 saved_arg1 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *part_a;
    s16 original_arg0;
    s32 call_id;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    const void *call_target;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    saved_arg0 = arg0;
    work = 0;
    call_id = 0x112;
    saved_arg1 = arg1;
    call_target = D_80083498;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(call_id, call_target);
    original_arg0 = saved_arg0;
    if (obj != 0) {
        register void *part_b;
        void *actor;

        work = (u8 *)obj + 0x20;
        ASM_KEEP_NV(work);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ((S_80170894_0 *)work)->unk_13 = 0xE;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80170894_1 *)obj)->unk_08;
        ((S_80170894_2 *)part_a)->unk_0A = saved_arg3;
        part_b = ((S_80170894_1 *)obj)->unk_0C;
        kind = saved_arg0 & 3;
        ((S_80170894_3 *)part_b)->unk_25 = saved_arg2;
        actor = work;
        ((S_80170894_3 *)part_b)->unk_24 = saved_arg1;

        if (kind == 1) {
            s32 left_one;
            s32 right_one;

            ((S_80170894_0 *)work)->unk_8C = func_80170E9C;
            left_one = ((S_80170894_0 *)work)->unk_14 | 0x6000;
            right_one = ((S_80170894_0 *)work)->unk_1C | 0x6000;
            ((S_80170894_0 *)work)->unk_14 = left_one;
            ((S_80170894_0 *)work)->unk_1C = right_one;
            ((S_80170894_3 *)part_b)->unk_2C = func_80174ED8;
            goto callback_done;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        {
            s32 left_many;
            s32 right_many;

            ((S_80170894_0 *)work)->unk_8C = func_80170E9C;
            left_many = ((S_80170894_0 *)work)->unk_14 | 0x2000;
            right_many = ((S_80170894_0 *)work)->unk_1C | 0x2000;
            ((S_80170894_0 *)work)->unk_14 = left_many;
            ((S_80170894_0 *)work)->unk_1C = right_many;
        }
        ((S_80170894_3 *)part_b)->unk_2C = func_80174ED8;
        goto callback_done;

normal_kind:
        {
            s32 test;
            u8 *callback_page;

            test = saved_arg0 & ~3;
            test <<= 16;
            if (test != 0) {
                callback_page = (u8 *)0x80170000;
                goto work_callback;
            }
            if (((S_80170894_0 *)work)->unk_14 & 0x200) {
                callback_page = (u8 *)0x80170000;
                goto actor_callback;
            }
            if (!(func_800A6D30() & 1)) {
                callback_page = (u8 *)0x80170000;
                goto actor_callback;
            }
            func_800A48F0(work, 1,
                          (func_800A6D30() & 0x3F) | 0x20);
            ((S_80170894_3 *)part_b)->unk_2C = func_80174F00;
            callback_page = (u8 *)0x80170000;

actor_callback:
            ((S_80170894_4 *)actor)->unk_8C = callback_page + 0xE9C;
            ((S_80170894_3 *)part_b)->unk_2C = func_80174ED8;
            goto callback_done;
work_callback:
            ((S_80170894_0 *)work)->unk_8C = callback_page + 0xE9C;
            ((S_80170894_3 *)part_b)->unk_2C = func_80174ED8;
        }
callback_done:
        ((S_80170894_1 *)obj)->unk_10 = func_80170A98;
        func_800A9C18(obj, part_a, part_b, original_arg0);
        ((S_80170894_4 *)actor)->unk_9A = 0xFF;
        ((S_80170894_4 *)actor)->unk_9C = -1;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
