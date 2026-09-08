#include "common.h"

typedef struct S_80170878_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80170878_0;   /* created in func_80170878 */

typedef struct S_80170878_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_80170878_1;   /* result in func_80170878 */

typedef struct S_80170878_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170878_2;   /* position in func_80170878 */

typedef struct S_80170878_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170878_3;   /* part_b in func_80170878 */

typedef struct S_80170878_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170878_4;   /* actor in func_80170878 */



extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();

extern s32 D_80045340;
extern u8 D_80083498[];
extern void *func_80170A58();
extern u8 D_80171014[];
extern u8 D_8017420C[];
extern u8 D_8017425C[];

void *func_80170878(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *result = 0;
    void *created;
    register void *position ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_80170878_3 *part_b;
    S_80170878_4 *actor;
    register s32 saved_arg1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 saved_arg3;
    register s32 saved_arg2 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 saved_arg0 = (s32)arg0;
    register s32 original_arg0 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *call_a0;
    void *call_a1;
    s32 kind;

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    created = func_8003FD64(0x112, D_80083498);
    original_arg0 = saved_arg0;
    if (created == 0) {
        goto done;
    }

    result = (u8 *)created + 0x20;
    ((S_80170878_0 *)created)->unk_10 = func_80170A58;
    ((S_80170878_1 *)result)->unk_13 = 0x10;
    func_8004491C(created, &D_80045340);

    position = ((S_80170878_0 *)created)->unk_08;
    ((S_80170878_2 *)position)->unk_0A = saved_arg3;
    part_b = ((S_80170878_0 *)created)->unk_0C;
    kind = saved_arg0 & 3;
    part_b->unk_25 = saved_arg2;
    actor = result;
    part_b->unk_2C = D_8017420C;
    part_b->unk_24 = saved_arg1;

    if (kind == 1) {
        ((S_80170878_1 *)result)->unk_14 |= 0x6000;
        ((S_80170878_1 *)result)->unk_1C |= 0x6000;
        goto setup;
    }
    if (kind >= 2) {
        ((S_80170878_1 *)result)->unk_14 |= 0x2000;
        ((S_80170878_1 *)result)->unk_1C |= 0x2000;
        goto setup;
    }

    call_a0 = created;
    if (((saved_arg0 & ~3) << 16) == 0) {
        if (!(((S_80170878_1 *)result)->unk_14 & 0x200)) {
            call_a1 = position;
            if (func_800A6D30() & 1) {
                func_800A48F0(result, 1,
                    (func_800A6D30() & 0x3F) | 0x20);
                part_b->unk_2C = D_8017425C;
            }
        }
    }

setup:
    func_800A9C18(created, position, part_b, (s16)original_arg0);
    actor->unk_9A = 0xFF;
    actor->unk_9C = -1;
    actor->unk_8C = D_80171014;
    ((S_80170878_1 *)result)->unk_1C |= 0x40000;
    actor->unk_92 = -0x20;
    func_800AA36C(actor, position, part_b, result);

done:
    return result;
}
