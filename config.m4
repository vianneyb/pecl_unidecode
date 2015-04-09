PHP_ARG_ENABLE(unidecode, whether to enable Unidecode support,
[ --enable-unidecode   Enable Unidecode support])
if test "$PHP_UNIDECODE" = "yes"; then
  AC_DEFINE(HAVE_UNIDECODE, 1, [Whether you have Unidecode])
  PHP_NEW_EXTENSION(unidecode, unidecode.c, $ext_shared)
fi