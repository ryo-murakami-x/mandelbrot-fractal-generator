/* Simple PNG Writer - Public Domain
   
   A minimal PNG writer for RGB images.
   
   USAGE:
      Before you #include this file, do this in *one* C or C++ file:
         #define STB_IMAGE_WRITE_IMPLEMENTATION
      Then #include "stb_image_write.h" from that file.
*/

#ifndef INCLUDE_STB_IMAGE_WRITE_H
#define INCLUDE_STB_IMAGE_WRITE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <zlib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int stbi_write_png(const char *filename, int w, int h, int comp, const void *data, int stride_in_bytes);



#ifdef STB_IMAGE_WRITE_IMPLEMENTATION

static uint32_t png_crc32_table[256];

static void png_init_crc32(void)
{
    for (int n = 0; n < 256; n++) {
        uint32_t crc = n;
        for (int k = 0; k < 8; k++)
            crc = (crc & 1) ? (0xedb88320 ^ (crc >> 1)) : (crc >> 1);
        png_crc32_table[n] = crc;
    }
}

static uint32_t png_crc32(const unsigned char *data, int len)
{
    uint32_t crc = 0xffffffff;
    for (int n = 0; n < len; n++)
        crc = png_crc32_table[(crc ^ data[n]) & 0xff] ^ (crc >> 8);
    return crc ^ 0xffffffff;
}

static void png_write_u32(FILE *f, uint32_t v)
{
    unsigned char data[4];
    data[0] = (v >> 24) & 0xff;
    data[1] = (v >> 16) & 0xff;
    data[2] = (v >> 8) & 0xff;
    data[3] = v & 0xff;
    fwrite(data, 1, 4, f);
}

static void png_write_chunk(FILE *f, const char *type, const unsigned char *data, int len)
{
    png_write_u32(f, len);
    fwrite(type, 1, 4, f);
    if (data) fwrite(data, 1, len, f);
    
    unsigned char chunk_data[len + 4];
    memcpy(chunk_data, type, 4);
    if (data) memcpy(chunk_data + 4, data, len);
    uint32_t crc = png_crc32(chunk_data, len + 4);
    png_write_u32(f, crc);
}

int stbi_write_png(const char *filename, int w, int h, int comp, const void *data, int stride_in_bytes)
{
    static int crc_table_init = 0;
    if (!crc_table_init) {
        png_init_crc32();
        crc_table_init = 1;
    }
    
    FILE *f = fopen(filename, "wb");
    if (!f) return 0;
    
    // PNG signature
    unsigned char sig[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
    fwrite(sig, 1, 8, f);
    
    // IHDR chunk
    unsigned char ihdr[13];
    ihdr[0] = (w >> 24) & 0xff;
    ihdr[1] = (w >> 16) & 0xff;
    ihdr[2] = (w >> 8) & 0xff;
    ihdr[3] = w & 0xff;
    ihdr[4] = (h >> 24) & 0xff;
    ihdr[5] = (h >> 16) & 0xff;
    ihdr[6] = (h >> 8) & 0xff;
    ihdr[7] = h & 0xff;
    ihdr[8] = 8; // bit depth
    ihdr[9] = (comp == 1) ? 0 : (comp == 2) ? 4 : (comp == 3) ? 2 : 6; // color type
    ihdr[10] = 0; // compression method
    ihdr[11] = 0; // filter method
    ihdr[12] = 0; // interlace method
    
    png_write_chunk(f, "IHDR", ihdr, 13);
    
    // IDAT chunk - simplified: no compression for now
    int idat_len = (w * comp + 1) * h;
    unsigned char *idat = (unsigned char *)malloc(idat_len);
    if (!idat) {
        fclose(f);
        return 0;
    }
    
    int pos = 0;
    const unsigned char *src = (const unsigned char *)data;
    for (int y = 0; y < h; y++) {
        idat[pos++] = 0; // filter type 0 (None)
        for (int x = 0; x < w * comp; x++)
            idat[pos++] = src[x];
        src += stride_in_bytes ? stride_in_bytes : (w * comp);
    }
    
    // Compress with zlib
    uLongf compressed_size = compressBound(pos);
    unsigned char *compressed = (unsigned char *)malloc(compressed_size);
    if (!compressed) {
        free(idat);
        fclose(f);
        return 0;
    }
    
    if (compress2(compressed, &compressed_size, idat, pos, 9) != Z_OK) {
        free(compressed);
        free(idat);
        fclose(f);
        return 0;
    }
    
    png_write_chunk(f, "IDAT", compressed, compressed_size);
    
    // IEND chunk
    png_write_chunk(f, "IEND", NULL, 0);
    
    free(compressed);
    free(idat);
    fclose(f);
    
    return 1;
}

#endif

#ifdef __cplusplus
}
#endif

#endif

