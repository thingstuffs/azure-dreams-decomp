#include "common.h"

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

extern u8 D_80083498[];
extern u8 D_80045340[];
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
    register s32 saved_kind_id ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 original_flags;
    register s32 create_kind ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *create_data;
    s32 kind;

    saved_flags = flags;
    result = 0;
    create_kind = 0x112;
    saved_kind_id = kind_id;
    ASM_KEEP_DEP_NV(saved_kind_id, create_kind);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    create_data = D_80083498;
    part_ptr = spawn_value;
    ASM_KEEP_DEP_NV(part_ptr, create_data);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    actor_ptr = variant;
    created = func_8003FD64(create_kind, create_data);
    original_flags = saved_flags;
    if (created == 0) {
        goto done;
    }
    result = (u8 *)created + 0x20;
    ((S_80158894_0 *)result)->unk_13 = 0xE;
    func_8004491C(created, D_80045340);

    position = ((S_80158894_1 *)created)->unk_08;
    ((S_80158894_2 *)position)->unk_0A = part_ptr;
    part_ptr = (s32)((S_80158894_1 *)created)->unk_0C;
    kind = saved_flags & 3;
    ((S_80158894_3 *)((void *)part_ptr))->unk_25 = actor_ptr;
    actor_ptr = (s32)result;
    ((S_80158894_3 *)((void *)part_ptr))->unk_24 = saved_kind_id;

    if (kind == 1) {
        ((S_80158894_0 *)result)->unk_8C = D_80158E9C;
        ((S_80158894_0 *)result)->unk_14 |= 0x6000;
        ((S_80158894_0 *)result)->unk_1C |= 0x6000;
        ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CED8;
        goto setup;
    }
    if (kind >= 2) {
        ((S_80158894_0 *)result)->unk_8C = D_80158E9C;
        ((S_80158894_0 *)result)->unk_14 |= 0x2000;
        ((S_80158894_0 *)result)->unk_1C |= 0x2000;
        ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CED8;
        goto setup;
    }

    if (((saved_flags & ~3) << 16) != 0) {
        goto set_actor;
    }
    if (!(((S_80158894_0 *)result)->unk_14 & 0x200)) {
        if (func_800A6D30() & 1) {
            func_800A48F0(result, 1,
                (func_800A6D30() & 0x3F) | 0x20);
            ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CF00;
        }
    }

#ifdef NON_MATCHING
    ((S_80158894_4 *)((void *)actor_ptr))->unk_8C = D_80158E9C;
#else
    ((S_80158894_4 *)((void *)actor_ptr))->unk_8C =
        (void *)D_80158E9C;
#endif
    goto set_part;

set_actor:
#ifdef NON_MATCHING
    ((S_80158894_0 *)result)->unk_8C = D_80158E9C;
#else
    ((S_80158894_0 *)result)->unk_8C = (void *)D_80158E9C;
#endif

set_part:
    ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CED8;

setup:
    ((S_80158894_1 *)created)->unk_10 = func_80158A98;
    func_800A9C18(created, position, (void *)part_ptr,
        (s16)original_flags);
    ((S_80158894_4 *)((void *)actor_ptr))->unk_9A = 0xFF;
    ((S_80158894_4 *)((void *)actor_ptr))->unk_9C = -1;
    func_800AA36C((void *)actor_ptr, position,
        (void *)part_ptr, result);

done:
    return result;
}
