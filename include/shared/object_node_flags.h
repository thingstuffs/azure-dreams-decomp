#ifndef SHARED_OBJECT_NODE_FLAGS_H
#define SHARED_OBJECT_NODE_FLAGS_H

/* ObjectNodeHeader.flags (+0x1E), or the halfword at object body -2.
 * remove_marked_active_nodes unlinks nodes carrying this bit. */
#define NODE_REMOVE 0x8000 /* retirement request; remove_marked_active_nodes unlinks the node, then recycles it unless allocation flag 0x80 is set */

#endif
