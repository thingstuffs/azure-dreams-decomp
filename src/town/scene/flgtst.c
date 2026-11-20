#include "common.h"
#include "town/menu/window.h"
#include "town/scene.h"
#include "town/map/variant_data.h"
#include "engine/message/data.h"
#include "engine/message.h"

extern u8 D_800D3C00[];


typedef struct Packet {
    s32 handler;
    s32 descriptor;
    s32 pad8;
    s32 padC;
    s32 mode;
    s32 pad14;
    s32 data0;
    s32 data1;
    MessageServiceHandler *service_handlers;
    void **variable_addresses;
    s32 *variables;
    s32 handler_arg0;
    s32 handler_arg1;
    s32 handler_arg2;
    s32 handler_arg3;
} Packet;

typedef void (*PacketHandler)(Packet *);

/* flgtst: dispatches a packet containing the handler arguments and current global state. */
void flgtst(s32 handler_arg0, s32 handler_arg1, s32 handler_arg2, s32 handler_arg3) {
    Packet packet;
    ScriptController *controller = &runtime_script_state;

    packet.handler = 0x80016000;
    packet.descriptor = 0x80012D70;
    packet.variables = controller->variables;
    packet.data0 = (s32)D_800D3C00;
    packet.handler_arg0 = handler_arg0;
    packet.handler_arg1 = handler_arg1;
    packet.handler_arg2 = handler_arg2;
    packet.handler_arg3 = handler_arg3;
    packet.mode = town_map_variant;
    packet.data1 = (s32)town_object_callbacks;
    packet.service_handlers = controller->service_handlers;
    packet.variable_addresses = controller->variable_addresses;
    (*(PacketHandler *)0x80016000)(&packet);
}
