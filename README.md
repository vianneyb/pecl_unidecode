# pecl_unidecode
Php extension to transform any non-latin characters to its equivalent in latin


# Build

* clone this repository into the ext folder in php source

* $ phpize

* $ ./configure --enable-unidecode

* $ make

# Test

* $ make test

# Install

* copy the file unidecode.so (in the ./modules folder) to your extension folder (ex: /usr/lib/php5/20090626/)

* add the extension to php by adding the line extension=unidecode.so in your php.ini




# Usage

* php -r "echo unidecode($my_non_latin_string);"

# Why this extension

* I made this extension because i needed a perfomant and customizable way of transliterate non latin characters. Since i didn't
find something useful (or complete) around the web or Pecl, i made my own.



# Copyright

* Adaptation from the work of Alexander Kuznetsov <alexkuz@gmail.com> (http://pgxn.org/dist/unidecode/0.0.5/)

* Original transliteration table from Python unidecode library (https://github.com/iki/unidecode)