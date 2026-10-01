#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80158894_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x6C];
    void * unk_8C;
} S_80158894_0;   /* result in func_80158894 */

typedef struct S_80158894_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80158894_1;   /* created in func_80158894 */

typedef struct S_80158894_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80158894_2;   /* position in func_80158894 */

typedef struct S_80158894_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80158894_3;   /* (void *)part_ptr in func_80158894 */

typedef struct S_80158894_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80158894_4;   /* (void *)actor_ptr in func_80158894 */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80158E9C[];
extern u8 D_8015CED8[];
extern u8 D_8015CF00[];
extern void func_80158A98(void);

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *func_80158894(s16 flags, s32 kind_id, s32 variant, s32 spawn_value)
{
    void *result;
    void *created;
    void *position;
    s32 part_ptr;
    s32 actor_ptr;
    s16 saved_flags;
    register s16 held_kind ASM_REG("$21");   /* UNRESOLVED C shape (pin): global.c must rank kind above child_a/position (retail $s5 vs $s6); at cdk kind is 2 refs/live 20 vs position 4/77 - position live >= 81 flips it (duplicated actor callback stores in the default arms do that) but cse then folds actor into result and jump2 merges the stores */
    s32 held_value;
    s32 held_variant;
    s16 original_flags;

    saved_flags = flags;
    held_kind = kind_id;
    held_value = spawn_value;
    held_variant = variant;
    result = 0;
    created = func_8003FD64(0x112, &D_80083498);
    original_flags = saved_flags;
    if (created != 0) {
        result = (u8 *)created + 0x20;
        ((S_80158894_0 *)result)->unk_13 = 0xE;
        func_8004491C(created, func_80045340);

        position = ((S_80158894_1 *)created)->unk_08;
        variant = saved_flags & 3;
        ((S_80158894_2 *)position)->unk_0A = held_value;
        part_ptr = (s32)((S_80158894_1 *)created)->unk_0C;
        ((S_80158894_3 *)((void *)part_ptr))->unk_24 = held_kind;
        ((S_80158894_3 *)((void *)part_ptr))->unk_25 = held_variant;
        actor_ptr = (s32)result;

        if (variant == 1) {
            ((S_80158894_0 *)result)->unk_8C = D_80158E9C;
            ((S_80158894_0 *)result)->unk_14 |= 0x6000;
            ((S_80158894_0 *)result)->unk_1C |= 0x6000;
            ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CED8;
        } else if (variant >= 2) {
            ((S_80158894_0 *)result)->unk_8C = D_80158E9C;
            ((S_80158894_0 *)result)->unk_14 |= 0x2000;
            ((S_80158894_0 *)result)->unk_1C |= 0x2000;
            ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CED8;
        } else {
            if (((saved_flags & ~3) << 16) == 0) {
                if (!(((S_80158894_0 *)result)->unk_14 & 0x200) && (func_800A6D30() & 1)) {
                    func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
                    ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CF00;
                }
                ((S_80158894_4 *)((void *)actor_ptr))->unk_8C = D_80158E9C;
            } else {
                ((S_80158894_0 *)result)->unk_8C = D_80158E9C;
            }
            ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CED8;
        }
        ((S_80158894_1 *)created)->unk_10 = func_80158A98;
        func_800A9C18(created, position, (void *)part_ptr, (s16)original_flags);
        ((S_80158894_4 *)((void *)actor_ptr))->unk_9A = 0xFF;
        ((S_80158894_4 *)((void *)actor_ptr))->unk_9C = -1;
        func_800AA36C((void *)actor_ptr, position, (void *)part_ptr, result);
    }
    return result;
}
