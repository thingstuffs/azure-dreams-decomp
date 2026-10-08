#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80FE1000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FE1000_0;   /* obj in func_8016A8A8 */

typedef struct S_80FE1000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FE1000_1;   /* work in func_8016A8A8 */

typedef struct S_80FE1000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FE1000_2;   /* part_a in func_8016A8A8 */

typedef struct S_80FE1000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80FE1000_3;   /* part_b in func_8016A8A8 */

typedef struct S_80FE1000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FE1000_4;   /* actor in func_8016A8A8 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();

extern u8 D_8016AA7C[];
extern u8 D_8016E038[];
extern u8 D_8016E088[];
extern u8 D_8016AEA8[];



/* Creates a dungeon object and initializes its kind flags and part parameters. */
void *func_8016A8A8(s16 kind_flags, s32 part_value_24, s32 part_value_25, s16 part_value_0a)
{
    s32 kind;
    void *obj;
    void *part_a;
    S_80FE1000_3 *part_b;
    void *work;
    S_80FE1000_4 *actor;
    s32 flags;
    s32 paired_flags;
    s16 saved_value_24;
    s16 saved_value_0a;
    s16 saved_value_25;

    work = 0;
    saved_value_24 = part_value_24;
    saved_value_0a = part_value_0a;
    saved_value_25 = part_value_25;
    obj = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80FE1000_0 *)obj)->unk_10 = D_8016AA7C;
        ((S_80FE1000_1 *)work)->unk_13 = 0x28;
        func_8004491C(obj, func_80045340);

        part_a = ((S_80FE1000_0 *)obj)->unk_08;
        ((S_80FE1000_2 *)part_a)->unk_0A = saved_value_0a;
        part_b = ((S_80FE1000_0 *)obj)->unk_0C;
        kind = kind_flags & 3;
        part_b->unk_25 = saved_value_25;
        actor = work;
        part_b->unk_2C = D_8016E038;
        part_b->unk_24 = saved_value_24;

        if (kind == 1) {
            flags = ((S_80FE1000_1 *)work)->unk_14 | 0x6000;
            paired_flags = ((S_80FE1000_1 *)work)->unk_1C | 0x6000;
            ((S_80FE1000_1 *)work)->unk_14 = flags;
            ((S_80FE1000_1 *)work)->unk_1C = paired_flags;
        } else if (kind >= 2) {
            flags = ((S_80FE1000_1 *)work)->unk_14 | 0x2000;
            paired_flags = ((S_80FE1000_1 *)work)->unk_1C | 0x2000;
            ((S_80FE1000_1 *)work)->unk_14 = flags;
            ((S_80FE1000_1 *)work)->unk_1C = paired_flags;
        } else {
            if ((((kind_flags & ~3) << 16) == 0) &&
                !(((S_80FE1000_1 *)work)->unk_14 & 0x200)) {
                flags = func_800A6D30();
                if (flags & 1) {
                    ((S_80FE1000_1 *)work)->unk_1C |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    part_b->unk_2C = D_8016E088;
                }
            }
        }


        func_800A9C18(obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8016AEA8;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
