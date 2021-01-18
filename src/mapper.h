/*
 * mapper.h
 *
 *  Created on: Jun 4, 2020
 *      Author: David Jonsson
 */

#ifndef SRC_MAPPER_H_
#define SRC_MAPPER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

extern uint8_t
    *prg_rom,
    *prg_ram,
    *chr_rom;

void mapper_init(char *file_name);
void mapper_destroy();

#define MAPPER_MIRROR_1SCREEN_LO 0
#define MAPPER_MIRROR_1SRCEEN_HI 1
#define MAPPER_MIRROR_VERTICAL   2
#define MAPPER_MIRROR_HORIZONTAL 3

struct ines_header
{
    char
        constant_[4];
    uint8_t
        prgrom_size_,
        chrrom_size_,
        flags_[5],
        padding_[5],
        mapper_ctr_mirror_;
    uint16_t
        mapper_nr_;
    uint8_t
    	ver_mirror_;
    FILE
        *file_;

} extern header;


#endif /* SRC_MAPPER_H_ */
