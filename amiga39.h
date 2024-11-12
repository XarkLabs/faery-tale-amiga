#if !defined(AMIGA39_H)

#define TRUE 1
#define FALSE 0
#define NULL 0

#include <stdint.h>

typedef int8_t BYTE;
typedef uint8_t UBYTE;
typedef uint8_t BOOL;

typedef int16_t SHORT;
typedef uint16_t USHORT;

typedef int16_t WORD;
typedef uint16_t UWORD;

typedef uint16_t *PLANEPTR;

typedef int32_t LONG;
typedef uint32_t ULONG;

typedef void *BPTR;

enum
{
    JAM1,       // FrontPen is used to draw the text; background color is unchanged.
    JAM2,       // FrontPen is used to draw the text; background color is changed to the color in BackPen.
    COMPLEMENT, // The characters are drawn in the complement of the colors that were in the background.
    INVERSID    // Inverses the draw modes describe above. For instance INVERVID used with JAM1 means the character is untouched while the background is filled with the color of the FrontPen.
};ß

#endif