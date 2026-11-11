#ifndef ENGINE_WINDOW_PARAMS_H
#define ENGINE_WINDOW_PARAMS_H

struct Container;
struct Source;

/* Copy the template into a window parameter container. */
void copy_window_params(struct Container *container, struct Source *source);

#endif
