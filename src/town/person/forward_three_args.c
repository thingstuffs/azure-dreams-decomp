#include "common.h"
#include "town/person.h"

void func_800C8644(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* Forward the three values to func_800C8644. */
void forward_three_args(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    func_800C8644(object, position, sprite);
}
