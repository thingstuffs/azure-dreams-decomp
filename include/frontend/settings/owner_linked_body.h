#ifndef FRONTEND_SETTINGS_OWNER_LINKED_BODY_H
#define FRONTEND_SETTINGS_OWNER_LINKED_BODY_H

#include "common.h"

/* create_settings_sprite_object stores the settings owner in the node body; the installed
 * remove_record_with_marked_owner callback follows that same link. */
typedef struct SettingsOwnerLinkedBody {
    void *owner;
} SettingsOwnerLinkedBody;

#endif
