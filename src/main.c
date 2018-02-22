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

#include <stdbool.h>
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
 * Determine if swap is available on this system by consulting /proc/swaps
 *
 * We don't really parse /proc/swaps, instead we just make sure we read more
 * than one line from the file (as the header always exists) and assume that
 * the kernel isn't messing us around with invalid entries. It is not our job
 * to validate that swap works, but that it is attached.
 */
bool yb_has_swap(void)
{
        FILE *fp = NULL;
        char *bfr = NULL;
        size_t n = 0;
        ssize_t read = 0;
        int line_count = 0;

        fp = fopen("/proc/swaps", "r");
        if (!fp) {
                return false;
        }

        while ((read = getline(&bfr, &n, fp)) > 0) {
                if (read < 1) {
                        goto next_line;
                }

                ++line_count;
        next_line:
                free(bfr);
                bfr = NULL;

                /* No sense in more allocs here */
                if (line_count > 1) {
                        break;
                }
        }

        if (bfr) {
                free(bfr);
        }

        fclose(fp);

        return line_count > 1;
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
        if (yb_has_swap()) {
                printf("Have swap!\n");
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
