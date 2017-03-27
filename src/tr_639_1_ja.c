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
	[0x304f] = "\x00\x00\x30\x8ekwa\0ku",
	[0x30af] = "\x00\x00\x30\xeekwa\0ku",
	[0x3051] = "ke",
	[0x30b1] = "ke",
	[0x3053] = "ko",
	[0x30b3] = "ko",
	[0x304d] = "\x00\x00\x30\x83kya\0\x00\x00\x30\x85kyu\0\x00\x00\x30\x87kyo\0ki",
	[0x30ad] = "\x00\x00\x30\xe3kya\0\x00\x00\x30\xe5kyu\0\x00\x00\x30\xe7kyo\0ki",
	[0x305f] = "ta",
	[0x30bf] = "ta",
	[0x3064] = "tu",
	[0x30c4] = "tu",
	[0x3066] = "te",
	[0x30c6] = "te",
	[0x3068] = "to",
	[0x30c8] = "to",
	[0x3061] = "\x00\x00\x30\x83tya\0\x00\x00\x30\x85tyu\0\x00\x00\x30\x87tyo\0ti",
	[0x30c1] = "\x00\x00\x30\xe3tya\0\x00\x00\x30\xe5tyu\0\x00\x00\x30\xe7tyo\0ti",
	[0x306a] = "na",
	[0x30ca] = "na",
	[0x306c] = "nu",
	[0x30cc] = "nu",
	[0x306d] = "ne",
	[0x30cd] = "ne",
	[0x306e] = "no",
	[0x30ce] = "no",
	[0x306b] = "\x00\x00\x30\x83nya\0\x00\x00\x30\x85nyu\0\x00\x00\x30\x87nyo\0ni",
	[0x30cb] = "\x00\x00\x30\xe3nya\0\x00\x00\x30\xe5nyu\0\x00\x00\x30\xe7nyo\0ni",
	[0x306f] = "ha",
	[0x30cf] = "ha",
	[0x3075] = "hu",
	[0x30d5] = "hu",
	[0x3078] = "he",
	[0x30d8] = "he",
	[0x307b] = "ho",
	[0x30db] = "ho",
	[0x3072] = "\x00\x00\x30\x83hya\0\x00\x00\x30\x85hyu\0\x00\x00\x30\x87hyo\0hi",
	[0x30d2] = "\x00\x00\x30\xe3hya\0\x00\x00\x30\xe5hyu\0\x00\x00\x30\xe7hyo\0hi",
	[0x307e] = "ma",
	[0x30de] = "ma",
	[0x3080] = "mu",
	[0x30e0] = "mu",
	[0x3081] = "me",
	[0x30e1] = "me",
	[0x3082] = "mo",
	[0x30e2] = "mo",
	[0x307f] = "\x00\x00\x30\x83mya\0\x00\x00\x30\x85myu\0\x00\x00\x30\x87myo\0mi",
	[0x30df] = "\x00\x00\x30\xe3mya\0\x00\x00\x30\xe5myu\0\x00\x00\x30\xe7myo\0mi",
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
	[0x308a] = "\x00\x00\x30\x83rya\0\x00\x00\x30\x85ryu\0\x00\x00\x30\x87ryo\0ri",
	[0x30ea] = "\x00\x00\x30\xe3rya\0\x00\x00\x30\xe5ryu\0\x00\x00\x30\xe7ryo\0ri",
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
	[0x3050] = "\x00\x00\x30\x8egwa\0gu",
	[0x30b0] = "\x00\x00\x30\xeegwa\0gu",
	[0x3052] = "ge",
	[0x30b2] = "ge",
	[0x3054] = "go",
	[0x30b4] = "go",
	[0x304e] = "\x00\x00\x30\x83gya\0\x00\x00\x30\x85gyu\0\x00\x00\x30\x87gyo\0gi",
	[0x30ae] = "\x00\x00\x30\xe3gya\0\x00\x00\x30\xe5gyu\0\x00\x00\x30\xe7gyo\0gi",
	[0x3056] = "za",
	[0x30b6] = "za",
	[0x305a] = "zu",
	[0x30ba] = "zu",
	[0x305c] = "ze",
	[0x30bc] = "ze",
	[0x305e] = "zo",
	[0x30be] = "zo",
	[0x3058] = "\x00\x00\x30\x83zya\0\x00\x00\x30\x85zyu\0\x00\x00\x30\x87zyo\0si",
	[0x30b8] = "\x00\x00\x30\xe3zya\0\x00\x00\x30\xe5zyu\0\x00\x00\x30\xe7zyo\0si",
	[0x3060] = "da",
	[0x30c0] = "da",
	[0x3065] = "du",
	[0x30c5] = "du",
	[0x3067] = "de",
	[0x30c7] = "de",
	[0x3069] = "do",
	[0x30c9] = "do",
	[0x3062] = "\x00\x00\x30\x83dya\0\x00\x00\x30\x85dyu\0\x00\x00\x30\x87dyo\0di",
	[0x30c2] = "\x00\x00\x30\xe3dya\0\x00\x00\x30\xe5dyu\0\x00\x00\x30\xe7dyo\0di",
	[0x3070] = "ba",
	[0x30d0] = "ba",
	[0x3076] = "bu",
	[0x30d6] = "bu",
	[0x3079] = "be",
	[0x30d9] = "be",
	[0x307c] = "bo",
	[0x30dc] = "bo",
	[0x3073] = "\x00\x00\x30\x83bya\0\x00\x00\x30\x85byu\0\x00\x00\x30\x87byo\0bi",
	[0x30d3] = "\x00\x00\x30\xe3bya\0\x00\x00\x30\xe5byu\0\x00\x00\x30\xe7byo\0bi",
	[0x3071] = "pa",
	[0x30d1] = "pa",
	[0x3077] = "pu",
	[0x30d7] = "pu",
	[0x307a] = "pe",
	[0x30da] = "pe",
	[0x307d] = "po",
	[0x30dd] = "po",
	[0x3074] = "\x00\x00\x30\x83pya\0\x00\x00\x30\x85pyu\0\x00\x00\x30\x87pyo\0pi",
	[0x30d4] = "\x00\x00\x30\xe3pya\0\x00\x00\x30\xe5pyu\0\x00\x00\x30\xe7pyo\0pi",
