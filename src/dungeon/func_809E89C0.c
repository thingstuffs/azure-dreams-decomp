/* Relink of matched dungeon/func_809CA9C0; every changed retail word is a paired relocation. */
#define D_80170E54 D_80152E54
#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_801721C0_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_801721C0_0;   /* arg0 in func_801541C0 */


s32 dungeonAdvanceStatusTimers();                     /* extern */
s32 dungeonUpdateActorMovementToTile();                                /* extern */
void dungeonReduceActorFoodMeter();            /* extern */
s32 dungeonCheckActorFloorTrap();                /* extern */
extern M2C_UNK D_80152E54;

/* Updates object state after checking the target and conditionally clears its value. */
void func_801541C0(S_801721C0_0 *object, void *unused, void *check_data, void *target) {
    if (dungeonUpdateActorMovementToTile() != 0) {
        dungeonReduceActorFoodMeter(target, 4);
        dungeonAdvanceStatusTimers(target);
        if ((dungeonCheckActorFloorTrap(check_data, target) << 0x10) > 0) {
            object->unk_8C = &D_80152E54;
            if (dungeonStatus.flags & 0x80) {
                object->unk_90.at02.v = 0;
                object->unk_90.at00.v = 0;
            }
        }
    } else {
        if (dungeonStatus.flags & 0x80) {
            object->unk_90.at02.v = 0;
            object->unk_90.at00.v = 0;
        }
    }
}
