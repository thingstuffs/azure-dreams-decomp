#include "common.h"


typedef s32 M2C_UNK;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_8016F2E0[];
extern M2C_UNK D_8016F78C;
extern u8 D_80174A2C[];
extern void *D_80174CD8;


typedef struct S_8016F160_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8016F160_0;   /* obj in func_8016F160 */

typedef struct S_8016F160_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016F160_1;   /* work in func_8016F160 */

typedef struct S_8016F160_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016F160_2;   /* part_a in func_8016F160 */

typedef struct S_8016F160_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8016F160_3;   /* part_b in func_8016F160 */

typedef struct S_8016F160_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
    s8 unk_9C;
    u8 pad_9D[0x13];
    s16 unk_B0;
} S_8016F160_4;   /* tail_ptr in func_8016F160 */

/* Allocate an actor, initialize its parts and mode flags, and return its work area. */
void *func_8016F160(s16 mode, s8 config_24, s8 config_25, s16 config_0a)
{
    s32 mode_kind;
    void *obj;
    S_8016F160_2 *part_a;
    S_8016F160_3 *part_b;
    void *work;
    s16 saved_mode;
    register s8 saved_config_24 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_config_0a;
    register s8 saved_config_25 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *actor;
    void *actor_state;

    work = 0;
    saved_config_24 = config_24;
    saved_config_0a = config_0a;
    saved_config_25 = config_25;
    obj = func_8003FD64(0x112, &D_80083498);
    saved_mode = mode;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        D_80174CD8 = obj;
        ((S_8016F160_0 *)obj)->unk_10 = D_8016F2E0;
        ((S_8016F160_1 *)work)->unk_13 = 0x32;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_8016F160_0 *)obj)->unk_08;
        part_a->unk_0A = saved_config_0a;
        part_b = ((S_8016F160_0 *)obj)->unk_0C;
        mode_kind = mode & 3;
        part_b->unk_25 = saved_config_25;
        actor = work;
        part_b->unk_2C = D_80174A2C;
        part_b->unk_24 = saved_config_24;

        if (mode_kind == 1) {
            ((S_8016F160_1 *)work)->unk_14 |= 0x6000;
            ((S_8016F160_1 *)work)->unk_1C |= 0x6000;
        } else if (mode_kind >= 2) {
            ((S_8016F160_1 *)work)->unk_14 |= 0x2000;
            ((S_8016F160_1 *)work)->unk_1C |= 0x2000;
        }

        func_800A9C18(obj, part_a, part_b, saved_mode);
        ASM_USE_NV(actor);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        actor_state = actor;
        ((S_8016F160_4 *)actor_state)->unk_9A = 0xFF;
        ((S_8016F160_4 *)actor_state)->unk_9C = -1;
        ((S_8016F160_4 *)actor_state)->unk_8C = &D_8016F78C;
        ((S_8016F160_4 *)actor_state)->unk_9B = 0;
        ((S_8016F160_4 *)actor_state)->unk_B0 = 0;
        part_b->unk_14 |= 0x80;
        func_800AA36C(actor_state, part_a, part_b, work);
    }
    return work;
}
