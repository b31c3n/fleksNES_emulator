/*
 * bus.c
 *
 *  Created on: May 12, 2020
 *      Author: David Jonsson
 */

#include "bus.h"
#include "instruction.h"
#include "cpu.h"

struct bus
    cpu_bus =
    {
        .listeners_ =
        {
            &cpu_peripheral_ram,
            &cpu_peripheral_prgrom,
            &cpu_peripheral_prgram,
            &cpu_peripheral_ppu,
        },
        .nr_listeners_ = 4,
        .servered_ = true,
    };
struct bus
    ppu_bus=
    {
        .listeners_ =
        {
            &ppu_peripheral_chrrom,
            &ppu_peripheral_nametable,
            &ppu_peripheral_palette
        },
        .nr_listeners_ = 3,
        .servered_ = true,
    };

void bus_read(
        struct bus *bus,
        uint16_t address)
{
    bus->servered_ = false;
    bus->write_ = false;
    bus->address_ = address;
    if(bus == &cpu_bus)
        tick();
}

void bus_write(
        struct bus *bus,
        uint16_t address)
{
    bus->servered_ = false;
    bus->write_ = true;
    bus->address_ = address;
    if(bus == &cpu_bus)
        tick();
}

void bus_listen(
        struct peripheral *peripheral,
        struct bus *bus)
{
    if(peripheral->address_min_ <= bus->address_ &&
       peripheral->address_max_ >= bus->address_ &&
       !bus->servered_)
    {
        if(bus->write_) peripheral->write(peripheral);
        else            peripheral->read(peripheral);
        bus->servered_ = true;
    }
}
