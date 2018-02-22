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
#include <unistd.h>

#define MIB (1024 * 1024)

/**
 * Return the available memory in mib
 */
int64_t yb_available_memory(void)
{
        long page_size = -1;
        long page_count = -1;

        /* Grab the page size */
        page_size = sysconf(_SC_PAGESIZE);
        if (page_size == -1) {
#ifdef PAGESIZE
                page_size = sysconf(PAGESIZE);
#else
                return -1;
#endif
        }

        /* If for some reason we can't grab this, return -1 */
        page_count = sysconf(_SC_PHYS_PAGES);
        if (page_count == -1) {
                return -1;
        }

        return (page_count * page_size) / MIB;
}

/**
 * For now this is our testing entry into yokeybob whilst we sort out some
 * basic library functionality.
 */
int main(int argc, char **argv)
{
        int64_t avail_memory = yb_available_memory();
        if (avail_memory > 0) {
                printf("Avail memory: %ld\n", avail_memory);
        }

        fputs("Not yet implemented\n", stderr);
        return EXIT_FAILURE;
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
