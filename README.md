ASCII Everywhere
================

A set of command-line tools to convert between ASCII and UTF-8.

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
