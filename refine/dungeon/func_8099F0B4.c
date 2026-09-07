#include "common.h"


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800A48F0(void *, s32, s32);
extern s32 func_800A6D30();
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_80170A94(void);
extern void func_801710EC(void);

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_801708B4[];
extern u8 D_801714C8[];
extern u8 D_80171500[];
extern u8 D_80171544[];
extern u8 D_80171554[];
extern u8 D_80171580[];
extern u8 D_801724D0[];
extern u8 D_80172508[];
extern u8 D_80172534[];
extern u8 D_80172550[];
extern u8 D_801725C8[];
extern u8 D_80172908[];
extern u8 D_80172A4C[];
extern u8 D_80172B48[];
extern u8 D_80172CFC[];
extern u8 D_80172D40[];
extern u8 D_80172E3C[];
extern u8 D_80172E68[];
extern u8 D_80172F5C[];
extern u8 D_80172FFC[];
extern u8 D_8017316C[];
extern u8 D_801731CC[];
extern u8 D_801735C4[];
extern u8 D_801735FC[];
extern u8 D_80173600[];
extern u8 D_80173608[];
extern u8 D_8017360C[];
extern u8 D_80173614[];
extern u8 D_80173618[];
extern u8 D_80173620[];
extern u8 D_801737E4[];
extern u8 D_80173864[];
extern u8 D_80173920[];
extern u8 D_80173964[];
extern u8 D_80175E40[];
extern u8 D_80175EA0[];


typedef struct S_801708B4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801708B4_0;   /* entity in func_801708B4 */

typedef struct S_801708B4_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_801708B4_1;   /* inner in func_801708B4 */

typedef struct S_801708B4_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_801708B4_2;   /* part_a in func_801708B4 */

typedef struct S_801708B4_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801708B4_3;   /* part_b in func_801708B4 */

typedef struct S_801708B4_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_801708B4_4;   /* result in func_801708B4 */

/* Create an entity at the given grid position and initialize its behavior and spawn flags. */
void *func_801708B4(s16 spawn_flags, s8 grid_x, s8 grid_y, s16 height)
{
    void *entity;
    S_801708B4_2 *position;
    S_801708B4_3 *placement;
    S_801708B4_4 *actor;
    s32 spawn_mode;
    s16 saved_flags;
    u8 *entity_data;
    register s8 saved_x ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s16 saved_height;
    register s8 saved_y ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */

    saved_flags = spawn_flags;
    entity_data = 0;
    saved_x = grid_x;
    saved_height = height;
    saved_y = grid_y;
    entity = func_8003FD64(0x112, D_80083498);
    if (entity != 0) {
        entity_data = (u8 *)entity + 0x20;
        ((S_801708B4_0 *)entity)->unk_10 = func_80170A94;
        ((S_801708B4_1 *)entity_data)->unk_13 = 2;
        func_8004491C(entity, &D_80045340);

        position = ((S_801708B4_0 *)entity)->unk_08;
        position->unk_0A = saved_height;
        placement = ((S_801708B4_0 *)entity)->unk_0C;
        spawn_mode = spawn_flags & 3;
        placement->unk_25 = saved_y;
        actor = entity_data;
        placement->unk_2C = D_80175E40;
        placement->unk_24 = saved_x;

        if (spawn_mode == 1) {
            ((S_801708B4_1 *)entity_data)->unk_14 |= 0x6000;
            ((S_801708B4_1 *)entity_data)->unk_1C |= 0x6000;
        } else if (spawn_mode >= 2) {
            ((S_801708B4_1 *)entity_data)->unk_14 |= 0x2000;
            ((S_801708B4_1 *)entity_data)->unk_1C |= 0x2000;
        } else if (((spawn_flags & -4) << 16) == 0) {
            if (!(((S_801708B4_1 *)entity_data)->unk_14 & 0x200)) {
                void *call_entity = entity;
                void *call_position = position;

                ASM_SET(call_entity);   /* MATCH pin: retail delay-slot contents depend on it */
                ASM_SET(call_position);   /* MATCH pin: retail delay-slot contents depend on it */
                if (func_800A6D30(call_entity, call_position) & 1) {
                    s32 random_value;
                    void *second_entity = entity;

                    ASM_SET(second_entity);   /* MATCH pin: retail delay-slot contents depend on it */
                    random_value = func_800A6D30(second_entity);

                    func_800A48F0(entity_data, 1, (random_value & 0x3F) | 0x20);
                    placement->unk_2C = D_80175EA0;
                }
            }
        }

        func_800A9C18(entity, position, placement, saved_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = func_801710EC;
        ((S_801708B4_1 *)entity_data)->unk_1C |= 0x40000;
        actor->unk_92 = -0x20;
        func_800AA36C(actor, position, placement, entity_data);
    }
    return entity_data;
}
