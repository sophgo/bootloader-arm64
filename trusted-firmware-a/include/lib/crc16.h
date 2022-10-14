#ifndef _CRC16_H_
#define _CRC16_H_

/* 16 bit CRC with polynomial x^16+x^12+x^5+1 (CRC-CCITT) */
uint16_t crc16_ccitt(uint16_t crc_start, unsigned char *s, int len);
uint16_t crc16_pacing(uint16_t crc_start, uint32_t *buf, int len);

#endif /* _CRC16_H_ */
