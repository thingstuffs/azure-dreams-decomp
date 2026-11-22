#include "common.h"
#include "shared/object_node.h"
#include "town/scene/collection.h"
#include "town/scene/object.h"
#include "town/devkit/old_minigame_imports.h"

/* Creates an object for the supplied panel, installs its update, and registers its draw callback. */
void create_payload_object(TownCollectionPanelUpdate callback, const TownCollectionPanel *payload)
{
    ObjectNodeHeader *object = func_800374FC(1, &scene_object_factory_data);

    if (object != 0) {
        TownCollectionPanel *body = NODE_BODY(object);
        *body = *payload;
        object->update_callback = callback;
        func_8003BC18(object, func_8005888C);
    }
}
