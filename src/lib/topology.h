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

#pragma once

#define _GNU_SOURCE

#include <stdbool.h>
#include <stdint.h>

/**
 * YbTopology is a simple composite struct to query various aspects of the
 * system in order to provide more information to act on.
 */
typedef struct YbTopology {
        /* Memory information */
        struct {
                int64_t mem_mib; /**<Memory available in MiB */
                bool swap_avail; /**<If swap is enabled */
        } memory;

        /* Root partition information (currently unused) */
        struct {
                int __reserved1;
        } rootfs;
} YbTopology;

/**
 * Initialise a YbTopology struct to analyse the system.
 */
bool yb_topology_init(YbTopology *top);

/**
 * Return the recommended swappiness value for this topology
 */
int8_t yb_topology_get_swappiness(YbTopology *top);

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
