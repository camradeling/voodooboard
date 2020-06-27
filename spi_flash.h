#ifndef SPI_FLASH_H
#define SPI_FLASH_H
//------------------------------------------------------------------------------
//instruction codes
#define W25_WRITE_ENABLE                        0x06
#define W25_WRITE_DISABLE                       0x04
#define W25_READ_STATUS1                        0x05
#define W25_READ_STATUS2                        0x35
#define W25_WRITE_STATUS                        0x01
#define W25_PAGE_PROGRAM                        0x02
#define W25_SECTOR_ERASE                        0x20
#define W25_BLOCK_ERASE                         0x52
#define W25_BLOCK_ERASE_64                      0xD8
#define W25_CHIP_ERASE                          0xC7
#define W25_READ_DATA                           0x03
#define W25_DEVICE_ID                           0x90
#define W25_JEDEC_ID                            0x9F
#define W25_ENABLE_RESET                        0x66
#define W25_RESET                               0x99
//------------------------------------------------------------------------------
//status register 1
#define W25_SR1_BUSY                            (1 << 0)
//------------------------------------------------------------------------------
#define FLASH_PAGE_LEN                          256
//------------------------------------------------------------------------------
//addresses
#define W25_FIRMWARE_START                    0
#define W25_FIRMWARE_FINISH                   131071  //128kB
#define W25_FIRMWARE_CRC                      131072
#define W25_PARAMS_START                      163840
//------------------------------------------------------------------------------
//inner flash addresses
#define FLASH_FIRMWARE_START                    0
#define FLASH_FIRMWARE_LEN                      131072
#define RAM_BOOT                                0x4C00
//------------------------------------------------------------------------------
void vSpiFlashTask (void *pvParameters);
//------------------------------------------------------------------------------
void w25_write_enable(void);
//------------------------------------------------------------------------------
void w25_sector_erase(uint32_t addr);
//------------------------------------------------------------------------------
void w25_block64_erase(uint32_t addr);
//------------------------------------------------------------------------------
void w25_page_read(uint32_t addr, uint8_t* buf);
//------------------------------------------------------------------------------
void w25_page_write(uint32_t addr, uint8_t* buf);
//------------------------------------------------------------------------------
void w25_init(void);
//------------------------------------------------------------------------------
void w25_params_write(void);
//------------------------------------------------------------------------------
void write_flash(uint32_t addr, uint16_t data);
//------------------------------------------------------------------------------
void erase_flash(uint32_t addr);
//------------------------------------------------------------------------------
void reflash(void);
//------------------------------------------------------------------------------
#endif/*SPI_FLASH_H*/