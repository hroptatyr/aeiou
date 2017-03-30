/*** tr_639_1_ja.c -- Japanes (ISO 639-1 JA) Nippon-siki transliterations
 *
 * Copyright (C) 2014-2017 Sebastian Freundt
 *
 * Author:  Sebastian Freundt <freundt@ga-group.nl>
 *
 * This file is part of aeiou.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the author nor the names of any contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***/
/* compile with translcc */

	[0x3042] = "a",
	[0x30a2] = "a",
	[0x3044] = "i",
	[0x30a4] = "i",
	[0x3046] = "u",
	[0x30a6] = "u",
	[0x3048] = "e",
	[0x30a8] = "e",
	[0x304a] = "o",
	[0x30aa] = "o",
	[0x304b] = "ka",
	[0x30ab] = "ka",
	[0x304f] = "\000\000\060\216kwa\0ku",
	[0x30af] = "\000\000\060\356kwa\0ku",
	[0x3051] = "ke",
	[0x30b1] = "ke",
	[0x3053] = "ko",
	[0x30b3] = "ko",
	[0x304d] = "\000\000\060\203kya\0\000\000\060\205kyu\0\000\000\060\207kyo\0ki",
	[0x30ad] = "\000\000\060\343kya\0\000\000\060\345kyu\0\000\000\060\347kyo\0ki",
	[0x3055] = "sa",
	[0x30b5] = "sa",
	[0x3059] = "su",
	[0x30b9] = "su",
	[0x305b] = "se",
	[0x30bb] = "se",
	[0x305d] = "so",
	[0x30bd] = "so",
	[0x3057] = "\000\000\060\203sya\0\000\000\060\205syu\0\000\000\060\207syo\0si",
	[0x30b7] = "\000\000\060\343sya\0\000\000\060\345syu\0\000\000\060\347syo\0si",
	[0x305f] = "ta",
	[0x30bf] = "ta",
	[0x3064] = "tu",
	[0x30c4] = "tu",
	[0x3066] = "te",
	[0x30c6] = "te",
	[0x3068] = "to",
	[0x30c8] = "to",
	[0x3061] = "\000\000\060\203tya\0\000\000\060\205tyu\0\000\000\060\207tyo\0ti",
	[0x30c1] = "\000\000\060\343tya\0\000\000\060\345tyu\0\000\000\060\347tyo\0ti",
	[0x306a] = "na",
	[0x30ca] = "na",
	[0x306c] = "nu",
	[0x30cc] = "nu",
	[0x306d] = "ne",
	[0x30cd] = "ne",
	[0x306e] = "no",
	[0x30ce] = "no",
	[0x306b] = "\000\000\060\203nya\0\000\000\060\205nyu\0\000\000\060\207nyo\0ni",
	[0x30cb] = "\000\000\060\343nya\0\000\000\060\345nyu\0\000\000\060\347nyo\0ni",
	[0x306f] = "ha",
	[0x30cf] = "ha",
	[0x3075] = "hu",
	[0x30d5] = "hu",
	[0x3078] = "he",
	[0x30d8] = "he",
	[0x307b] = "ho",
	[0x30db] = "ho",
	[0x3072] = "\000\000\060\203hya\0\000\000\060\205hyu\0\000\000\060\207hyo\0hi",
	[0x30d2] = "\000\000\060\343hya\0\000\000\060\345hyu\0\000\000\060\347hyo\0hi",
	[0x307e] = "ma",
	[0x30de] = "ma",
	[0x3080] = "mu",
	[0x30e0] = "mu",
	[0x3081] = "me",
	[0x30e1] = "me",
	[0x3082] = "mo",
	[0x30e2] = "mo",
	[0x307f] = "\000\000\060\203mya\0\000\000\060\205myu\0\000\000\060\207myo\0mi",
	[0x30df] = "\000\000\060\343mya\0\000\000\060\345myu\0\000\000\060\347myo\0mi",
	[0x3084] = "ya",
	[0x30e4] = "ya",
	[0x3086] = "yu",
	[0x30e6] = "yu",
	[0x3088] = "yo",
	[0x30e8] = "yo",
	[0x3089] = "ra",
	[0x30e9] = "ra",
	[0x308b] = "ru",
	[0x30eb] = "ru",
	[0x308c] = "re",
	[0x30ec] = "re",
	[0x308d] = "ro",
	[0x30ed] = "ro",
	[0x308a] = "\000\000\060\203rya\0\000\000\060\205ryu\0\000\000\060\207ryo\0ri",
	[0x30ea] = "\000\000\060\343rya\0\000\000\060\345ryu\0\000\000\060\347ryo\0ri",
	[0x308f] = "wa",
	[0x30ef] = "wa",
	[0x3091] = "se",
	[0x30f1] = "se",
	[0x3092] = "wo",
	[0x30f2] = "wo",
	[0x3090] = "wi",
	[0x30f0] = "wi",
	[0x3093] = "n",
	[0x30f3] = "n",
	[0x304c] = "ga",
	[0x30ac] = "ga",
	[0x3050] = "\000\000\060\x8egwa\0gu",
	[0x30b0] = "\000\000\060\xeegwa\0gu",
	[0x3052] = "ge",
	[0x30b2] = "ge",
	[0x3054] = "go",
	[0x30b4] = "go",
	[0x304e] = "\000\000\060\203gya\0\000\000\060\205gyu\0\000\000\060\207gyo\0gi",
	[0x30ae] = "\000\000\060\343gya\0\000\000\060\345gyu\0\000\000\060\347gyo\0gi",
	[0x3056] = "za",
	[0x30b6] = "za",
	[0x305a] = "zu",
	[0x30ba] = "zu",
	[0x305c] = "ze",
	[0x30bc] = "ze",
	[0x305e] = "zo",
	[0x30be] = "zo",
	[0x3058] = "\000\000\060\203zya\0\000\000\060\205zyu\0\000\000\060\207zyo\0zi",
	[0x30b8] = "\000\000\060\343zya\0\000\000\060\345zyu\0\000\000\060\347zyo\0zi",
	[0x3060] = "da",
	[0x30c0] = "da",
	[0x3065] = "du",
	[0x30c5] = "du",
	[0x3067] = "de",
	[0x30c7] = "de",
	[0x3069] = "do",
	[0x30c9] = "do",
	[0x3062] = "\000\000\060\203dya\0\000\000\060\205dyu\0\000\000\060\207dyo\0di",
	[0x30c2] = "\000\000\060\343dya\0\000\000\060\345dyu\0\000\000\060\347dyo\0di",
	[0x3070] = "ba",
	[0x30d0] = "ba",
	[0x3076] = "bu",
	[0x30d6] = "bu",
	[0x3079] = "be",
	[0x30d9] = "be",
	[0x307c] = "bo",
	[0x30dc] = "bo",
	[0x3073] = "\000\000\060\203bya\0\000\000\060\205byu\0\000\000\060\207byo\0bi",
	[0x30d3] = "\000\000\060\343bya\0\000\000\060\345byu\0\000\000\060\347byo\0bi",
	[0x3071] = "pa",
	[0x30d1] = "pa",
	[0x3077] = "pu",
	[0x30d7] = "pu",
	[0x307a] = "pe",
	[0x30da] = "pe",
	[0x307d] = "po",
	[0x30dd] = "po",
	[0x3074] = "\000\000\060\203pya\0\000\000\060\205pyu\0\000\000\060\207pyo\0pi",
	[0x30d4] = "\000\000\060\343pya\0\000\000\060\345pyu\0\000\000\060\347pyo\0pi",
