#ifndef PORT_H
#define PORT_H

#include <Util/Type.h>


uint8_t  in8      (uint16_t portNum);
void     out8     (uint16_t port, uint8_t data);
void     out8Slow (uint16_t port, uint8_t data);

uint16_t in16     (uint16_t port);
void     out16    (uint16_t port, uint16_t data);

uint32_t in32     (uint16_t port);
void     out32    (uint16_t port, uint32_t data);


#endif

