#include "axi_bram_arm.h"


int BramMemoryWrite(uint32_t offset, uint32_t *data, uint32_t length)
{
    int mem_file;
    mem_file = open(MEM_DEV, O_RDWR);

    if(mem_file < 0) {
        printf("AxiBram: can't open mem dev\n");
        return -1;
    }

    struct bram_rw_data rw_data;

    rw_data.size = length;
    rw_data.offset = (offset>>2);
    rw_data.data = data;
    if(ioctl(mem_file, AXI_BRAM_WRITE, &rw_data)) {
        printf("AxiBram: error writting data\n");
        close(mem_file);
        return -1;
    }

    close(mem_file);

    return 0;
}
