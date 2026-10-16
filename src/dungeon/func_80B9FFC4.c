/* Relink of matched dungeon/func_809A2D74; every changed retail word is a paired relocation. */
#define D_801710EC D_8016AE9C
#define D_80175E40 D_8016EEE8
#define D_80175EA0 D_8016EF00
#include "common.h"
#include "shared/game_work.h"

typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} Actor;

typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} Entity;

typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} MapObject;

extern s32 func_800AC82C(Actor *, s32, Entity *, MapObject *);
extern s32 dungeonCheckActorFloorTrap(Entity *, MapObject *);
extern void func_80047784(Entity *, s16, s16);

extern u8 D_8016AE9C[9];
extern u8 D_8016EEE8[9];
extern u8 D_8016EF00[9];

/* Update actor and entity state after checking the map object. */
void func_8016D7C4(Actor *actor, s32 action, Entity *entity, MapObject *map_object)
{
    if (func_800AC82C(actor, action, entity, map_object) != 0) {
        if ((dungeonCheckActorFloorTrap(entity, map_object) << 16) > 0) {
            actor->unk_8C = D_8016AE9C;
            return;
        }
    } else if (entity->unk_2C == D_8016EF00 &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = D_8016EEE8;
        func_80047784(entity,
                      D_8016EEE8[((gameWork.view.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7],
                      0);
    }
}
