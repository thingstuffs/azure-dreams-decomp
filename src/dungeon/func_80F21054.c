#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80158854_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void * unk_10;
} S_80158854_0;   /* object in func_80158854 */

typedef struct S_80158854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80158854_1;   /* result in func_80158854 */

typedef struct S_80158854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80158854_2;   /* part0 in func_80158854 */

typedef struct S_80158854_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80158854_3;   /* part1 in func_80158854 */

typedef struct S_80158854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_80158854_4;   /* actor in func_80158854 */


extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_80158A8C[];
extern u8 D_8015BD30[];
extern u8 D_8015BD78[];
extern u8 D_80158F74[];

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern s32 func_800A6D30();
extern M2C_UNK func_800A48F0();
extern M2C_UNK func_800A9C18();
extern M2C_UNK func_800AA36C();
extern M2C_UNK func_80044A50();
extern M2C_UNK func_800BC318();

#ifdef __mips__
#define BODY_STORAGE
#define BODY_ATTR __attribute__((used, section(".text.func_80158854")))
#else
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void *func_80158854(s16 flags, s16 kind_id, s16 variant, s16 spawn_value) BODY_ATTR;

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select, then finish through the mode branch that either zeroes or arms the actor's 0xA6 state. */
BODY_STORAGE void *func_80158854(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    s32 mode;
    void *object_base;
    S_80158854_3 *part1;
    S_80158854_2 *part0;
    void *actor;
    void *object;
    S_80158854_1 *result;

    result = 0;
    mode = 1;
    object = func_8003FD64(274, D_80083498);
    if (object == 0) {
        goto done;
    }

    result = (u8 *)object + 0x20;
    ((S_80158854_0 *)object)->unk_10 = D_80158A8C;
    result->unk_13 = 0x23;
    func_8004491C(object, D_80045340);
    part0 = ((S_80158854_0 *)object)->unk_08;
    part0->unk_0A = spawn_value;
    part1 = ((S_80158854_0 *)object)->unk_0C;
    part1->unk_25 = variant;
    actor = result;
    part1->unk_2C = D_8015BD30;
    kind = flags & 3;
    part1->unk_24 = kind_id;
    if (kind == 1) {
        result->unk_14 |= 0x6000;
        result->unk_1C |= 0x6000;
    } else if (kind >= 2) {
        result->unk_14 |= 0x2000;
        result->unk_1C |= 0x2000;
    } else if (((flags & ~3) << 16) == 0) {
        if (result->unk_14 & 0x200) {
            goto status_done;
        }
        if (!(func_800A6D30() & 1)) {
            goto status_done;
        }
        result->unk_1C |= 0x200;
        func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
        part1->unk_2C = D_8015BD78;
    status_done:
        mode = func_800A6D30() & 3;
    }
    func_800A9C18(object, part0, part1, flags);
    ((S_80158854_4 *)actor)->unk_9A = 0xFF;
    ((S_80158854_4 *)actor)->unk_9C = -1;
    ((S_80158854_4 *)actor)->unk_8C = D_80158F74;
    ((S_80158854_4 *)actor)->unk_A4 = -1;
    if (mode != 0) {
        ((S_80158854_4 *)actor)->unk_A6 = 0;
    } else {
        object_base = (u8 *)actor - 0x20;
        ((S_80158854_4 *)actor)->unk_A6 = 1;
        part1->unk_10 = 0x60;
        part1->unk_14 |= 0xC;
        part1->unk_12 -= 0x80;
        func_80044A50(object_base);
        func_800BC318(object_base);
    }
    func_800AA36C(actor, part0, part1, result);
done:
    return result;
}
