/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_0.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Vianney Briois <vianney@evaneos.com>                              |
  +----------------------------------------------------------------------+
*/

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

PHP_MINFO_FUNCTION(unidecode);
PHP_FUNCTION(unidecode);


#ifdef ZTS
#define UNIDECODE_G(v) TSRMG(unidecode_globals_id, zend_unidecode_globals *, v)
#else
#define UNIDECODE_G(v) (unidecode_globals.v)
#endif

#endif
