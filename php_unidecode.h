#ifndef PHP_UNIDECODE_H
#define PHP_UNIDECODE_H 1
#define PHP_UNIDECODE_VERSION "1.0"
#define PHP_UNIDECODE_EXTNAME "unidecode"

PHP_FUNCTION(unidecode);

extern zend_module_entry unidecode_module_entry;
#define phpext_unidecode_ptr &unidecode_module_entry

#endif