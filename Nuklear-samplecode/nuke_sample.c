//
// Created by bernard on 5/14/21.
//

#include "nuke_sample.h"

Window first_window = {
        nk_true,
        nk_false,
        "First Window",
        10, 270,
        230, 250,
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE,
        nk_false,
        first_window_proc
};

Window calculator_window = {
        nk_true,
        nk_false,
        "Calculator",
        10, 10,
        180, 250,
        NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR|NK_WINDOW_MOVABLE,
        nk_false,
        calculator
};

Window node_editor_window = {
        nk_true,
        nk_false,
        "Node Editor",
        265,  10,
        800, 600,
        NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE,
        nk_true,
        node_editor
};


Window overview_window = {
        nk_true,
        nk_false,
        "Full Overview",
        10, 10,
        400, 600,
        0,
        nk_true,
        overview
};

