#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef s32 M2C_UNK;

typedef struct S_80FAB000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FAB000_0;   /* obj in func_8014C880 */

typedef struct S_80FAB000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FAB000_1;   /* work in func_8014C880 */

typedef struct S_80FAB000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FAB000_2;   /* part_a in func_8014C880 */

typedef struct S_80FAB000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80FAB000_3;   /* part_b in func_8014C880 */

typedef struct S_80FAB000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x3];
    s16 unk_A0;
} S_80FAB000_4;   /* actor in func_8014C880 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30(void);
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern u8 D_8014CA70[];
extern M2C_UNK D_8014D138;
extern u8 D_80150AD4[];
extern u8 D_80150AFC[];





void *func_8014C880(s16 flags, s16 field24_input, s16 field25_input, s16 field0A_input)
;
void *func_8014C880(s16 flags, s16 field24_input, s16 field25_input, s16 field0A_input)
{
    s32 kind;
    void *obj;
    S_80FAB000_2 *part_a;
    S_80FAB000_3 *part_b;
    S_80FAB000_1 *work;
    S_80FAB000_4 *actor;
    s32 left;
    s32 right;
    s8 field24_value;
    s16 field0A_value;
    s8 field25_value;

    work = 0;
    field24_value = field24_input;
    field0A_value = field0A_input;
    field25_value = field25_input;
    obj = func_8003FD64(0x112, ((s32 *)&D_80083498.next));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80FAB000_0 *)obj)->unk_10 = D_8014CA70;
        work->unk_13 = 0x26;
        func_8004491C(obj, func_80045340);

        part_a = ((S_80FAB000_0 *)obj)->unk_08;
        part_a->unk_0A = field0A_value;
        part_b = ((S_80FAB000_0 *)obj)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = field25_value;
        actor = work;
        actor = work;
        part_b->unk_2C = D_80150AD4;
        part_b->unk_24 = field24_value;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (kind >= 2) {
            left = work->unk_14 | 0x2000;
            right = work->unk_1C | 0x2000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else {
            if (((flags & ~3) << 16) == 0) {
                if (!(work->unk_14 & 0x200)) {
                    left = func_800A6D30();
                    if (left & 1) {
                        work->unk_1C |= 0x200;
                        func_800A48F0(work, 1,
                                      (func_800A6D30() & 0x3F) | 0x20);
                        part_b->unk_2C = D_80150AFC;
                    }
                }
            }
        }
        func_800A9C18(((void *)(obj)), part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014D138;
        work->unk_1C |= 0x40000;
        actor->unk_A0 = 0;
        actor->unk_92 = -0x30;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
