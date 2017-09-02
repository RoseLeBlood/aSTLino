/*
 * The MIT License
 *
 * Copyright 2016 annas.
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

/* 
 * File:   colors.hpp
 * Author: annas
 *
 * Created on 25. November 2016, 12:27
 */

#ifndef COLORS_HPP
#define COLORS_HPP

#include "color.hpp"

namespace std 
{
    namespace math
    {
        template <typename T>
	class colors_base
	{
        public:
            const color<T>      AliceBlue = color<T>(0xF0F8FFFF);
            const color<T>      AntiqueWhite = color<T>(0xFAEBD7FF);
            const color<T>      Aqua = color<T>(0x00FFFFFF);
            const color<T>      Aquamarine = color<T>(0x7FFFD4FF);
	    const color<T>      Azure = color<T>(0xF0FFFFFF);
	    const color<T>      Beige = color<T>(0xF5F5DCFF);
            const color<T>	Bisque = color<T>(0xFFE4C4FF);
            const color<T>	Black = color<T>(0x000000FF);
            const color<T>	BlanchedAlmond = color<T>(0xFFEBCDFF);
            const color<T>	Blue = color<T>(0x0000FFFF);
            const color<T>	BlueViolet = color<T>(0x8A2BE2FF);
            const color<T>	Brown = color<T>(0xA52A2AFF);
            const color<T>	BurlyWood = color<T>(0xDEB887FF);
            const color<T>	CadetBlue = color<T>(0x5F9EA0FF);
            const color<T>	Chartreuse = color<T>(0x7FFF00FF);
            const color<T>	Chocolate = color<T>(0xD2691EFF);
            const color<T>	Coral = color<T>(0xFF7F50FF);
            const color<T>	CornflowerBlue = color<T>(0x6495EDFF); 
            const color<T>	Cornsilk = color<T>(0xFFF8DCFF);
            const color<T>	Crimson = color<T>(0xDC143CFF);
            const color<T>	Cyan = color<T>(0x00FFFFFF);
            const color<T>	DarkBlue = color<T>(0x00008BFF);
            const color<T>	DarkCyan = color<T>(0x008B8BFF);
            const color<T>	DarkGoldenrod = color<T>(0xB8860BFF);
            const color<T>	DarkGray = color<T>(0xA9A9A9FF);
            const color<T>	DarkGreen = color<T>(0x006400FF);
            const color<T>	DarkKhaki = color<T>(0xBDB76BFF);
            const color<T>	DarkMagenta = color<T>(0x8B008BFF);
            const color<T>	DarkOliveGreen = color<T>(0x556B2FFF);
            const color<T>	DarkOrange = color<T>(0xFF8C00FF);
            const color<T>	DarkOrchid = color<T>(0x9932CCFF);
            const color<T>	DarkRed = color<T>(0x8B0000FF);
            const color<T>	DarkSalmon = color<T>(0xE9967AFF);
            const color<T>	DarkSeaGreen = color<T>(0x8FBC8FFF);
            const color<T>	DarkSlateBlue = color<T>(0x8FBC8FFF);
            const color<T>	DarkSlateGray = color<T>(0x2F4F4FFF);
            const color<T>	DarkTurquoise = color<T>(0x00CED1FF);
            const color<T>	DarkViolet = color<T>(0x9400D3FF);
            const color<T>	DeepPink = color<T>(0xFF1493FF);    
		 const color<T> DeepSkyBlue = color<T>(0x00BFFFFF);
		 const color<T> DimGray = color<T>(0x696969FF);
		 const color<T> DodgerBlue = color<T>(0x1E90FFFF);
		 const color<T> FireBrick = color<T>(0xB22222FF);
		 const color<T> FloralWhite = color<T>(0xFFFAF0FF);
		 const color<T> ForestGreen = color<T>(0x228B22FF);
		 const color<T> Fuchsia = color<T>(0xFF00FFFF);
		 const color<T> Gainsboro = color<T>(0xDCDCDCFF);
		 const color<T> GhostWhite = color<T>(0xF8F8FFFF);
		 const color<T> Gold = color<T>(0xFFD700FF);
		 const color<T> Goldenrod = color<T>(0xDAA520FF);
		 const color<T> Gray = color<T>(0x808080FF);
		 const color<T> Green = color<T>(0x008000FF);
		 const color<T> GreenYellow = color<T>(0xADFF2FFF);
		 const color<T> Honeydew = color<T>(0xF0FFF0FF);
		 const color<T> IndianRed = color<T>(0xCD5C5CFF);
		 const color<T> Indigo = color<T>(0x4B0082FF);
		 const color<T> Ivory = color<T>(0xFFFFF0FF);
		 const color<T> Khaki = color<T>(0xF0E68CFF);
		 const color<T> Lavender = color<T>(0xE6E6FAFF);
		 const color<T> LavenderBlush = color<T>(0xFFF0F5FF);
		 const color<T> LawnGreen = color<T>(0x7CFC00FF);
		 const color<T> LemonChiffon = color<T>(0xFFFACDFF);
		 const color<T> LightBlue = color<T>(0xADD8E6FF);
		 const color<T> LightCoral = color<T>(0xF08080FF);
		 const color<T> LightCyan = color<T>(0xE0FFFFFF);
		 const color<T> LightGoldenrodYellow = color<T>(0xFAFAD2FF);
		 const color<T> LightGreen = color<T>(0x90EE90FF);
		 const color<T> LightGrey = color<T>(0xD3D3D3FF);
		 const color<T> LightPink = color<T>(0x228B22FF);
		 const color<T> LightSalmon = color<T>(0xFFA07AFF);
		 const color<T> LightSeaGreen = color<T>(0x20B2AAFF);
		 const color<T> LightSkyBlue = color<T>(0x87CEFAFF);
		 const color<T> LightSlateGray = color<T>(0x778899FF);
		 const color<T> LightSteelBlue = color<T>(0xB0C4DEFF);
		 const color<T> LightYellow = color<T>(0xFFFFE0FF);
		 const color<T> Lime = color<T>(0x00FF00FF);
		 const color<T> LimeGreen = color<T>(0x32CD32FF);
		 const color<T> Linen = color<T>(0xFAF0E6FF);
		 const color<T> Magenta = color<T>(0xFF00FFFF);
		 const color<T> Maroon = color<T>(0x800000FF);
		 const color<T> MediumAquamarine = color<T>(0x66CDAAFF);
		 const color<T> MediumBlue = color<T>(0x0000CDFF);
		 const color<T> MediumOrchid = color<T>(0xBA55D3FF);
		 const color<T> MediumPurple = color<T>(0x9370DBFF);
		 const color<T> MediumSeaGreen = color<T>(0x3CB371FF);
		 const color<T> MediumSlateBlue = color<T>(0x7B68EEFF);
		 const color<T> MediumSpringGreen = color<T>(0x00FA9AFF);
		 const color<T> MediumTurquoise = color<T>(0x48D1CCFF);
		 const color<T> MediumVioletRed = color<T>(0xC71585FF);
		 const color<T> MidnightBlue = color<T>(0x191970FF);
		 const color<T> MintCream = color<T>(0xF5FFFAFF);
		 const color<T> MistyRose = color<T>(0xFFE4E1FF);
		 const color<T> Moccasin = color<T>(0xFFE4B5FF);
		 const color<T> NavajoWhite = color<T>(0xFFDEADFF);
		 const color<T> Navy = color<T>(0x000080FF);
		 const color<T> OldLace = color<T>(0xFDF5E6FF);
		 const color<T> Olive = color<T>(0x808000FF);
		 const color<T> OliveDrab = color<T>(0x6B8E23FF);
		 const color<T> Orange = color<T>(0xFFA500FF);
		 const color<T> OrangeRed = color<T>(0xFF4500FF);
		 const color<T> Orchid = color<T>(0xDA70D6FF);
		 const color<T> PaleGoldenrod = color<T>(0xEEE8AAFF);
		 const color<T> PaleGreen = color<T>(0x98FB98FF);
		 const color<T> PaleTurquoise = color<T>(0xAFEEEEFF);
		 const color<T> PaleVioletRed = color<T>(0xDB7093FF);
		 const color<T> PapayaWhip = color<T>(0xFFEFD5FF);
		 const color<T> PeachPuff = color<T>(0xFFDAB9FF);
		 const color<T> Peru = color<T>(0xCD853FFF);
		 const color<T> Pink = color<T>(0xFFC0CBFF);
		 const color<T> Plum = color<T>(0xDDA0DDFF);
		 const color<T> PowderBlue = color<T>(0xB0E0E6FF);
		 const color<T> Purple = color<T>(0x800080FF);
		 const color<T> Red = color<T>(0xFF0000FF);
		 const color<T> RosyBrown = color<T>(0xBC8F8FFF);
		 const color<T> RoyalBlue = color<T>(0x4169E1FF);
		 const color<T> SaddleBrown = color<T>(0x8B4513FF);
		 const color<T> Salmon = color<T>(0xFA8072FF);
		 const color<T> SandyBrown = color<T>(0xF4A460FF);
		 const color<T> SeaGreen = color<T>(0x2E8B57FF);
		 const color<T> Seashell = color<T>(0xFFF5EEFF);
		 const color<T> Sienna = color<T>(0xA0522DFF);
		 const color<T> Silver = color<T>(0xC0C0C0FF);
		 const color<T> SkyBlue = color<T>(0x87CEEBFF);
		 const color<T> SlateBlue = color<T>(0x6A5ACDFF);
		 const color<T> SlateGray = color<T>(0x708090FF);
		 const color<T> Snow = color<T>(0xFFFAFAFF);
		 const color<T> SpringGreen = color<T>(0x00FF7FFF);
		 const color<T> SteelBlue = color<T>(0x4682B4FF);
		 const color<T> Tan = color<T>(0xD2B48CFF);
		 const color<T> Teal = color<T>(0x008080FF);
		 const color<T> Thistle = color<T>(0xD8BFD8FF);
		 const color<T> Tomato = color<T>(0xFF6347FF);
		 const color<T> Turquoise = color<T>(0x40E0D0FF);
		 const color<T> Violet = color<T>(0xEE82EEFF);
		 const color<T> Wheat = color<T>(0xF5DEB3FF);
		 const color<T> White = color<T>(0xFFFFFFFF);
		 const color<T> WhiteSmoke = color<T>(0xF5F5F5FF);
		 const color<T> Yellow = color<T>(0xFFFF00FF);
		 const color<T> YellowGreen = color<T>(0x9ACD32FF); 
        };
        typedef colors_base<float> colors_t;
        typedef colors_base<double> colors_d;
    }
}

#endif /* COLORS_HPP */

