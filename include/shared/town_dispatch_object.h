#ifndef SHARED_TOWN_DISPATCH_OBJECT_H
#define SHARED_TOWN_DISPATCH_OBJECT_H

/* This address is passed as the optional object to apply_entry_position.
 * The callee checks the address but does not dereference it; extent is unknown. */
extern unsigned char active_scene_dispatch_context[];

#endif
