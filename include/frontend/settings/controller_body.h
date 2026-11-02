#ifndef FRONTEND_SETTINGS_CONTROLLER_BODY_H
#define FRONTEND_SETTINGS_CONTROLLER_BODY_H
#include "shared/object_node.h"
#include "shared/transition_slots.h"
/* Prefix of the two child node families, whose body state is at node+0x28.
 * The slots hold node headers rather than callback body addresses. */
typedef struct SettingsControllerChildNode {
    ObjectNodeHeader header;
    void *owner;
    unsigned char pad_24[4];
    short state;
} SettingsControllerChildNode;
/* Created and dispatched by create_settings_controller. */
typedef struct Obj {
    unsigned char pad_00[4];
    SettingsControllerChildNode *slotsA[3];
    SettingsControllerChildNode *slotsB[2];
    TransitionSlot fade;
    short state;
    unsigned short counter;
    short selected_item;
    unsigned short flags;
} SettingsMenuBody;
#endif
