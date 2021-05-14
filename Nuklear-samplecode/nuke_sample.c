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
        first_window_proc
};

Window calculator_window = {
        nk_true,
        nk_false,
        "Calculator",
        10, 10,
        180, 250,
        calculator
};

Window node_editor_window = {
        nk_true,
        nk_false,
        "Node Editor",
        265,  10,
        800, 600,
        node_editor
};


Window overview_window = {
        nk_true,
        nk_false,
        "Full Overview",
        10, 10,
        400, 600,
        overview
};

