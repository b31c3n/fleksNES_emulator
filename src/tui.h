/*
 * tui.h
 *
 *  Created on: May 13, 2020
 *      Author: David Jonsson
 */

#ifndef SRC_TUI_H_
#define SRC_TUI_H_

#include <ncurses.h>
#include <stdbool.h>

struct tui_comp
{
    WINDOW
        *window_;
    void
        (*update)(),
        (*init)(void *_this);
    int
        x_,
        y_,
        h_,
        w_;
    bool
        show_;
};

#define TUI_NR_COMPS 3
extern struct tui_comp
    tui_components[TUI_NR_COMPS];

void tui_init();
void tui_destroy();
void tui_draw();
//void tui_get_command();

#endif /* SRC_TUI_H_ */
