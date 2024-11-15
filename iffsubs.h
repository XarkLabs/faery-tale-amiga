/* iffsubs.c */
// Xark: NOTE Types altered to match C file (not Manx C promotion rules)
void ReadHeader(void);
void ReadLength(void);
BOOL unpackbrush(char * filename, struct BitMap * bitmap, int16_t x, int16_t y);
void unpack_line(char * dest);

