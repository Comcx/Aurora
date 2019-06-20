#ifndef PORT_H
#define PORT_H

#include "Types.h"


inline uint8_t  in8      (uint16_t portNum);
inline void     out8     (uint16_t port, uint8_t data);
inline void     out8Slow (uint16_t port, uint8_t data);

inline uint16_t in16     (uint16_t port);
inline void     out16    (uint16_t port, uint16_t data);

inline uint32_t in32     (uint16_t port);
inline void     out32    (uint16_t port, uint32_t data);


#endif

