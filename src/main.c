/*
 * main.c
 *
 *  Created on: May 4, 2020
 *      Author: David Jonsson
 */
#include <omp.h>
#include <signal.h>

#include "cpu.h"
#include "tui.h";
#include "mapper.h"
#include "display.h"
#include "instruction_tbl.h"
#include "clock.h"
#include "ppu.h"
#include "config.h"


void sigint(int signal)
{
    shutdown = 1;
    tui_destroy();
    puts("Interrupted!");
}

void sigsegv(int signal)
{
    shutdown = 1;
    tui_destroy();
    puts("Segfault!");
}

int main(int argc, char **argv)
{
    signal(SIGINT, sigint);
    signal(SIGSEGV, sigsegv);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            gettimeofday(&start, NULL);
            log_clear();
            clock_init();
            mapper_init(argv[1]);
            cpu_run();
            mapper_destroy();
        }
        #ifdef USE_TUI
        #pragma omp section
        {
            tui_init();
            while(!shutdown)
            {
                tui_draw();
            }
        }
        #endif
        #pragma omp section
        {
            display_init();
            while(!shutdown)
            {
                display_draw();
                capture_events();
            }
            display_destroy();
        }
    }
    return 0;
}
