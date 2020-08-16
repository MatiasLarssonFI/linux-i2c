/**
  * I2C test.
  *
  * usage: ./i2c-test [adapter number] [chip address]
  *
  * adapter number: optional, defaults to 1
  * chip address  : optional, defaults to 0x60 for no particular reason
  *
  * This program sends the interactive user input as byte data to the I2C device.
  */

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <string>
#include <iostream>
#include <stropts.h>
#include <fcntl.h>
#include <unistd.h>

#include "i2c-dev.h"
#include "i2c.h"
#include "i2c/smbus.h"


int main(int argc, char* argv[]) {
    // setup: open character device file
    int file;
    int adapter_nr = argc > 1 ? std::stoi(argv[1]) : 1;
    char filename[20];
    unsigned uData = 1;
    std::string input;

    std::snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0) {
        perror("open");
        exit(1);
    }

    // setup: set chip address
    uint8_t addr = argc > 2 ? (uint8_t)std::stoul(argv[2], nullptr, 16) : 0x60U;

    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        perror("ioctl");
        exit(1);
    }

    // write user input as byte data
    while(uData > 0) {
        std::cout << "> ";
        std::getline(std::cin, input);
        uData = std::stoul(input);
        std::cerr << std::hex << "Writing 0x" << uData << " to 0x" << (unsigned)addr << std::endl;
        if (i2c_smbus_write_byte_data(file, 0x01, uData) != 0) {
            perror("i2c_smbus_write_byte_data");
        }
    }

    close(file);


    return 0;
}
