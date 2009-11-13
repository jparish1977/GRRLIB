/*------------------------------------------------------------------------------
Copyright (c) 2009 The GRRLIB Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
------------------------------------------------------------------------------*/

/**
 * @file GRRLIB.h
 * GRRLIB user include file
 */

#ifndef __GRRLIB_H__
#define __GRRLIB_H__

//==============================================================================
// Includes
//==============================================================================
#include <gccore.h>
//==============================================================================

//==============================================================================
// C++ header
//==============================================================================
#ifdef __cplusplus
   extern "C" {
#endif /* __cplusplus */

//==============================================================================
// Extra standard declarations
//==============================================================================
typedef  unsigned int  uint;

//==============================================================================
// Primitive colour macros
//==============================================================================
#define R(c)  (((c) >>24) &0xFF)  /**< Exract Red   component of colour. */
#define G(c)  (((c) >>16) &0xFF)  /**< Exract Green component of colour. */
#define B(c)  (((c) >> 8) &0xFF)  /**< Exract Blue  component of colour. */
#define A(c)  ( (c)       &0xFF)  /**< Exract Alpha component of colour. */

/**
 * Build an RGB pixel from components.
 */
#define RGBA(r,g,b,a) ( (u32)( ( ((u32)(r))        <<24) |  \
                               ((((u32)(g)) &0xFF) <<16) |  \
                               ((((u32)(b)) &0xFF) << 8) |  \
                               ( ((u32)(a)) &0xFF      ) ) )

//==============================================================================
// typedefs, enumerators & structs
//==============================================================================
/**
 * Compositions Modes.
 */
typedef  enum Composition_Modes {
    GRRLIB_COMPOSE_NORMAL,      /**< NORMAL : a-over-b alpha composition (normal) */
} GRRLIB_ComposeMode;

//------------------------------------------------------------------------------
/**
 * GRRLIB Blending Modes.
 */
typedef  enum GRRLIB_blendMode {
    GRRLIB_BLEND_ALPHA  = 0,    /**< Alpha Blending.        */
    GRRLIB_BLEND_ADD    = 1,    /**< Additive Blending.     */
    GRRLIB_BLEND_SCREEN = 2,    /**< Alpha Light Blending.  */
    GRRLIB_BLEND_MULTI  = 3,    /**< Multiply Blending.     */
    GRRLIB_BLEND_INV    = 4,    /**< Invert Color Blending. */
} GRRLIB_blendMode;

#define GRRLIB_BLEND_NONE   (GRRLIB_BLEND_ALPHA)    /**< Alias for GRRLIB_BLEND_ALPHA. */
#define GRRLIB_BLEND_LIGHT  (GRRLIB_BLEND_ADD)      /**< Alias for GRRLIB_BLEND_ADD. */
#define GRRLIB_BLEND_SHADE  (GRRLIB_BLEND_MULTI)    /**< Alias for GRRLIB_BLEND_MULTI. */

//------------------------------------------------------------------------------
/**
 * Structure to hold the current drawing settings.
 */
typedef  struct GRRLIB_drawSettings {
    bool              antialias;    /**< AntiAlias is enabled when set to true. */
    GRRLIB_blendMode  blend;        /**< Blending Mode.                         */
} GRRLIB_drawSettings;

//------------------------------------------------------------------------------
/**
 * Structure to hold the texture information.
 */
typedef  struct GRRLIB_texImg {
    uint   w;           /**< Texture width.    */
    uint   h;           /**< Texture height.   */
    int    handlex;     /**< Texture handle x. */
    int    handley;     /**< Texture handle y. */
    int    offsetx;     /**< Texture offset x. */
    int    offsety;     /**< Texture offset y. */

    bool   tiledtex;    /**< Texture is tiled if set to true.   */
    uint   tilew;       /**< Width of one tile.                 */
    uint   tileh;       /**< Height of one tile.                */
    uint   nbtilew;     /**< Number of tiles for the x axis.    */
    uint   nbtileh;     /**< Number of tiles for the y axis.    */
    uint   tilestart;   /**< Offset to tile starting position.  */
    f32    ofnormaltexx;/**< Offset of normalized texture on x. */
    f32    ofnormaltexy;/**< Offset of normalized texture on y. */

    void  *data;        /**< Pointer to the texture data. */
} GRRLIB_texImg;

//------------------------------------------------------------------------------
/**
 * Structure to hold the bytemap character information.
 */
typedef  struct GRRLIB_bytemapChar {
    u8  character;      /**< Character identity. */
    u8  width;          /**< Character width.    */
    u8  height;         /**< Character height.   */
    s8  relx;           /**< Horizontal offset relative to cursor (-128 to 127).            */
    s8  rely;           /**< Vertical offset relative to cursor (-128 to 127).              */
    u8  kerning;        /**< Kerning (Horizontal cursor shift after drawing the character). */
    u8  *data;          /**< Character data (uncompressed, 8 bits per pixel).               */
} GRRLIB_bytemapChar;

//------------------------------------------------------------------------------
/**
 * Structure to hold the bytemap font information.
 */
typedef  struct GRRLIB_bytemapFont {
        char  *name;                /**< Font name.                      */
        u32   *palette;             /**< Font palette.                   */
        u16   nbChar;               /**< Number of characters in font.   */
        u8    version;              /**< Version.                        */
        s8    tracking;             /**< Tracking (Add-space after each char) (-128 to 127). */

        GRRLIB_bytemapChar  *charDef;   /**< Array of bitmap characters. */
    }
GRRLIB_bytemapFont;

//------------------------------------------------------------------------------
/**
 * This structure contains information about the type, size, and layout of a file that containing a device-independent bitmap (DIB).
 */
typedef  struct tagBITMAPFILEHEADER {
    u16 bfType;             /**< Specifies the file type. It must be set to the signature word BM (0x4D42) to indicate bitmap. */
    u32 bfSize;             /**< Specifies the size, in bytes, of the bitmap file. */
    u16 bfReserved1;        /**< Reserved; set to zero. */
    u16 bfReserved2;        /**< Reserved; set to zero. */
    u32 bfOffBits;          /**< Specifies the offset, in bytes, from the BITMAPFILEHEADER structure to the bitmap bits. */
} BITMAPFILEHEADER;
/**
 * This structure contains information about the dimensions and color format of a device-independent bitmap (DIB).
 */
typedef  struct tagBITMAPINFOHEADER {
    u32 biSize;             /**< Specifies the size of the structure, in bytes. */
    u32 biWidth;            /**< Specifies the width of the bitmap, in pixels. */
    u32 biHeight;           /**< Specifies the height of the bitmap, in pixels. */
    u16 biPlanes;           /**< Specifies the number of planes for the target device. */
    u16 biBitCount;         /**< Specifies the number of bits per pixel. */
    u32 biCompression;      /**< Specifies the type of compression for a compressed bottom-up bitmap.*/
    u32 biSizeImage;        /**< Specifies the size, in bytes, of the image. */
    u32 biXPelsPerMeter;    /**< Specifies the horizontal resolution, in pixels per meter, of the target device for the bitmap. */
    u32 biYPelsPerMeter;    /**< Specifies the vertical resolution, in pixels per meter, of the target device for the bitmap. */
    u32 biClrUsed;          /**< Specifies the number of color indexes in the color table that are actually used by the bitmap. */
    u32 biClrImportant;     /**< Specifies the number of color indexes required for displaying the bitmap. */
} BITMAPINFOHEADER;
/**
 * The RGBQUAD structure describes a color consisting of relative intensities of
 * red, green, and blue. The bmiColors member of the BITMAPINFO structure
 * consists of an array of RGBQUAD structures.
 */
typedef struct tagRGBQUAD {
    u8 rgbBlue;             /**< Specifies the intensity of blue in the color. */
    u8 rgbGreen;            /**< Specifies the intensity of green in the color. */
    u8 rgbRed;              /**< Specifies the intensity of red in the color. */
    u8 rgbReserved;         /**< Not used; must be set to zero. */
} RGBQUAD;

//==============================================================================
// Allow general access to screen and frame information
//==============================================================================
#if defined __GRRLIB_CORE__
# define GRR_EXTERN
# define GRR_INIT(v)     = v
# define GRR_INITS(...)  = { __VA_ARGS__ }
#else
# define GRR_EXTERN      extern
# define GRR_INIT(v)
# define GRR_INITS(...)
#endif

GRR_EXTERN  GXRModeObj  *rmode;
GRR_EXTERN  void        *xfb[2]  GRR_INITS(NULL, NULL);
GRR_EXTERN  u32         fb       GRR_INIT(0);

//==============================================================================
// procedure and function prototypes
// Inline function handling - http://www.greenend.org.uk/rjk/2003/03/inline.html
//==============================================================================
#include "grrlib/GRRLIB__lib.h"

#if defined __GRRLIB_CORE__
#  define INLINE
#else
# if __GNUC__ && !__GNUC_STDC_INLINE__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif
#include "grrlib/GRRLIB__inline.h"

//==============================================================================
// C++ footer
//==============================================================================
#ifdef __cplusplus
   }
#endif /* __cplusplus */

#endif // __GRRLIB_H__

/**
 * @mainpage GRRLIB Documentation
 * @image html grrlib_logo.png
 * Welcome to the GRRLIB documentation.
 *
 * @section Introduction
 * GRRLIB is a C/C++ 2D Graphics library for Wii application developers.
 * It is essentially a wrapper which presents a friendly interface to the Nintendo GX core.
 *
 * @section Credits
 * Project Leader : NoNameNo\n
 * Documentation  : Crayon, BlueChip\n
 * Lead Coder     : NoNameNo\n
 * Support Coders : Crayon, Xane, DragonMinded, BlueChip\n
 * Advisors       : RedShade, Jespa\n
 *
 * @section Licence
 * Copyright (c) 2009 The GRRLIB Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
