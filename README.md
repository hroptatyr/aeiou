ASCII Everywhere
================

No-frills, zero-dependency command-line tools to convert (transliterate)
between UTF-8 and ASCII.


Red tape
--------

+ no dependencies other than a POSIX system and a C99 compiler
+ licensed under [BSD3c][1]


Motivation
----------

We believe that ASCII is still the common denominator in automated data
oriented or manual data heavy work flows.  In those fields it is common
to interact simultaneously with lots of local peculiarities.

We do not believe that today's systems (i18n, l10n, locales, `LANG`
variables and whatnot) are suited for the most basic tasks, for example
rewriting a set of local date formats to ISO 8601, or times from
different local timezones as Zulu times.

The new Zulu timezone for character encodings is UTF-8 Unicode but
historically has been 7-bit ASCII as is evident in the DNS or protocols
like SMTP.

So called user-friendly rapid-development languages like Python don't
work at all when the environment isn't in sync with the expectations of
the author.  Heavy-duty tools like sort or grep behave differently for
different environments.  ASCII, however, seems to be the remedy to all
problems.


`translit`
----------

Tool to transliterate between UTF-8 encoded files and ASCII.  Based on
Sean Burke's [Text::Unidecode][2].  Unlike the perl version, `translit`
can maintain case:

    $ translit <<EOF
    ЧАЩА
    EOF
    CHASHCHA

and condense spaces:

    $ translit <<EOF
    ノーベル賞の
    EOF
    no--beru Shang no

Another source of controversy in Sean Burke's version (and many other
transliterators) is that certain characters transliterate to something
different in different languages.  The classic example being `ü` which
Germans would transcribe as `ue` whereas Spanish people would
transliterate `pingüino` as `pinguino`.

Language specific packs of transliterations can be generated with the
`translcc` tool.  The definitions themselves are plain C99 designated
arrays.  Language packs can be loaded by `-l|--lang`:

    $ translit -l tr_639_1_de.tr <<EOF
    Überschuß
    Äpfel
    KÖRBE
    EOF
    Ueberschuss
    Aepfel
    KOERBE

Furthermore one character of context can be used to produce compound
transliterations:

    $ translit -l tr_639_1_ru.tr <<EOF
    Такси
    EOF
    Taxi

    $ translit -i tr_639_1_ja.tr <<EOF
    シュヴァンク
    EOF
    syuvuanku


`aeiou`
-------

Tool to replace unicode codepoint strings (`\uxxxx` or `\Uxxxxxxxx`)
with their unicode character encoded as UTF-8, or vice versa.

Example:

    $ /bin/echo '\u307e\u30c4\u3057\u305f' | aeiou | translit
    matusita

    $ /bin/echo '\u307e\u30c4\u3057\u305f' | aeiou | aeiou -d
    \u307e\u30c4\u3057\u305f

Note: The shell's `echo` routine (e.g. zsh's) might already interpret
the unicode sequence.


  [1]: http://opensource.org/licenses/BSD-3-Clause
  [2]: http://search.cpan.org/~sburke/Text-Unidecode-1.30/lib/Text/Unidecode.pm
