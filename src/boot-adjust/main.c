/*
 * This file is part of yokeybob.
 *
 * Copyright © 2018 Solus Project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "topology.h"

/**
 * TODO: Actually write this stuff to the kernel
 */
static bool yb_apply_memory_constraints(YbTopology *top)
{
        if (top->memory.mem_mib > 0) {
                printf("Avail memory: %ld\n", top->memory.mem_mib);
        }

        if (top->memory.swap_avail) {
                fputs("Have swap!\n", stdout);
        }

        printf("Recommended swappiness: %d\n", yb_topology_get_swappiness(top));

        return true;
}

/**
 * For now this is our testing entry into yokeybob whilst we sort out some
 * basic library functionality.
 */
int main(int argc, char **argv)
{
        YbTopology top = { 0 };
        if (!yb_topology_init(&top)) {
                return EXIT_FAILURE;
        }

        return yb_apply_memory_constraints(&top) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
