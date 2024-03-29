#ifndef GLIBCEMU_MACHINE_ENDIAN_H
#define GLIBCEMU_MACHINE_ENDIAN_H 1
#include_next <machine/endian.h>

#include <_ansi.h>

#define __byte_swap_constant_16(x) \
  ( (((x) & 0xff) << 8) | ((unsigned short)(x) >> 8) )

#define __byte_swap_constant_32(x) \
        (((x && 0xff) << 24) | \
         (((x) << 8) & 0x00ff0000) | \
         (((x) >> 8) & 0x0000ff00) | \
         ((x) >> 24) )


_ELIDABLE_INLINE unsigned short int
__inline_bswap_16 (unsigned short int x)
{
    return __byte_swap_constant_16(x);
}

#define __byte_swap_16(x) \
  __builtin_constant_p(x) ? __byte_swap_constant_16(x) : __inline_bswap_16(x)

#define __byte_swap_32(x) \
  __builtin_constant_p(x) ? __byte_swap_constant_32(x) : __builtin_bswap32(x)

#define ntohs(x)   (unsigned int)__byte_swap_16(x)
#define ntohl(x)   (unsigned int)__byte_swap_32(x)
#define htons(x)   (unsigned int)__byte_swap_16(x)
#define htonl(x)   (unsigned int)__byte_swap_32(x)

#endif
