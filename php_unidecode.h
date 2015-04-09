#ifndef PHP_UNIDECODE_H
#define PHP_UNIDECODE_H 1


#define PHP_UNIDECODE_VERSION "1.0"
#define PHP_UNIDECODE_EXTNAME "unidecode"


extern zend_module_entry unidecode_module_entry;
#define phpext_unidecode_ptr &unidecode_module_entry

#ifdef PHP_WIN32
#define PHP_UNIDECODE_API __declspec(dllexport)
#else
#define PHP_UNIDECODE_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(unidecode);
PHP_MSHUTDOWN_FUNCTION(unidecode);
PHP_RINIT_FUNCTION(unidecode);
PHP_RSHUTDOWN_FUNCTION(unidecode);
PHP_MINFO_FUNCTION(unidecode);

PHP_FUNCTION(unidecode);


#ifdef ZTS
#define UNIDECODE_G(v) TSRMG(unidecode_globals_id, zend_unidecode_globals *, v)
#else
#define UNIDECODE_G(v) (unidecode_globals.v)
#endif

#endif
