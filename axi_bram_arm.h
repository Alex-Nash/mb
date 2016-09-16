#ifndef AXI_BRAM_ARM_H
#define AXI_BRAM_ARM_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <linux/ioctl.h>

#define MEM_DEV         "/dev/axi_bram"

struct bram_rw_data {
    uint32_t *data;
    uint32_t offset;
    uint32_t size;
};

#define TIMER_IOC_MAGIC  'b'

#define AXI_BRAM_READ            _IOR(TIMER_IOC_MAGIC, 1, struct bram_rw_data)
#define AXI_BRAM_WRITE           _IOW(TIMER_IOC_MAGIC, 2, struct bram_rw_data)


int BramMemoryWrite(uint32_t offset, uint32_t *data, uint32_t length);

#endif
