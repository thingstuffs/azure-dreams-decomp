#include "town/map/object_callback.h"

typedef struct S_8008B9D8_0 {
    u8 pad_00[0x68];
    void (*unk_68)(struct S_8008B9D8_0 *object, void *position, void *sprite);
} S_8008B9D8_0;   /* arg0 in func_8008B9D8 */

/* Invoke the object's callback with the node's position and sprite records. */
void run_map_object_callback(S_8008B9D8_0 *object, void *position, void *sprite) {
    object->unk_68(object, position, sprite);
}
