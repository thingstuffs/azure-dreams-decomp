#include "modules/town_ovl_79dd70.h"

void townInitializeSourceAndInitialData(void *source_data, void *initial_data)
{
    Object *object;
    Object *allocated;
    Payload88 *payload;
    RenderPart *part;
    u8 *table;

    table = D_80020014;
    allocated = (Object *)func_8003FC64(0x136);
    object = allocated;
    if (object != 0) {
        payload = (Payload88 *)((u8 *)object + 0x20);
        *payload = *(Payload88 *)source_data;
        object->callback = townUpdateBouncingPickup;
        *object->initial = *(Initial24 *)initial_data;
        func_8004491C((struct RegistrationNode *)object, (s32)func_80045340);
        part = object->render;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        part->image = D_8002445C[*(s16 *)((u8 *)source_data + 0x54)];
        part->x = 0;
        part->y = 0;
        part->color = 0x808080;
        part->flags |= 0x80;
        *(void **)((u8 *)payload + 0x50) = table;
        townConfigureTheSetModeN1((u8 *)payload + 8, object->initial, D_80024420);
    }
}
