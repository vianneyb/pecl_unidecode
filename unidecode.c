/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,        |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:              |
  | http://www.php.net/license/3_0.txt.                                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.            |
  +----------------------------------------------------------------------+
  | Author: Vianney Briois <vianney@evaneos.com>                         |
  +----------------------------------------------------------------------+

  // from the work of Alexander Kuznetsov <alexkuz@gmail.com>
*/



#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <stdint.h>

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "php_unidecode.h"
#include "data/mapping.h"



#if PHP_VERSION_ID >= 70000
# define ZPP_STRLEN_TYPE size_t
#else
# define ZPP_STRLEN_TYPE int
#endif



static int is_valid_char(uint32_t ch)
{
	return ch != -1 && (ch < 0xd800 || ch > 0xdfff);
}

/**
 * return the latin version of the char
 * @param  buf     input string
 * @param  idx     pos in the string
 * @param  str_len string length
 * @param  cp      char in 32bit
 * @return         [description]
 */
static int ordFromUtf8(uint8_t buf[], unsigned long *idx, ZPP_STRLEN_TYPE str_len, uint32_t *cp)
{
	int remunits;
	uint8_t nxt, msk;
	if (*idx >= str_len) {
		return -1;
	}
	nxt = buf[(*idx)++];

	if (nxt & 0x80) {
		msk = 0xe0;
		for (remunits = 1; (nxt & msk) != ((msk << 1) & 0xff); ++remunits) {
			msk = (msk >> 1) | 0x80;
			if (msk == 0xff) {
				return -1;
			}
		}
	} else {
		remunits = 0;
		msk = 0;
	}
	*cp = nxt & ~msk;
	while (remunits-- > 0) {
		*cp <<= 6;
		if (*idx >= str_len) {
			return -1;
		}
		*cp |= buf[(*idx)++] & 0x3f;
	}
	return 0;
}

static int utf8_to_utf32(uint8_t input[], uint32_t output[], ZPP_STRLEN_TYPE count, ZPP_STRLEN_TYPE *out_size)
{
	unsigned long idx = 0;
	for (*out_size = 0; *out_size < count && idx < count; ++*out_size) {
		int i = (int) *out_size;

		ordFromUtf8(input, &idx, count, &output[i]);
		if (!is_valid_char(output[i])) {
			return -1;
		}
	}

	return 0;
}




static zend_function_entry unidecode_functions[] = {
	PHP_FE(unidecode, NULL)
	{NULL, NULL, NULL, 0, 0}
};

zend_module_entry unidecode_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_UNIDECODE_EXTNAME,
	unidecode_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_MINFO(unidecode),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_UNIDECODE_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_UNIDECODE
ZEND_GET_MODULE(unidecode)
#endif


PHP_MINFO_FUNCTION(unidecode)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Unidecode support", "enabled");
	php_info_print_table_row(2, "Version", PHP_UNIDECODE_VERSION);
	php_info_print_table_end();
}





PHP_FUNCTION(unidecode)
{
	char *src;
	int src_len;
	ZPP_STRLEN_TYPE dst_len, src_uni_len;
	char* dst;
	int n = 0, start, end, i, res;
	uint32_t c, *src_uni, nb_char;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &src, &src_len) == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "We need a string parameter.\n");
		return;
	}
	if (!src_len) {
		RETURN_EMPTY_STRING();
	}

	src_uni_len = (src_len + 1) * 4;
	nb_char = sizeof(mapping_index) / sizeof(mapping_index[0]);

	// allocate enough space to write the new string in 32
	src_uni = emalloc(src_uni_len);

	// each char is replaced by its 32bit value
	res = utf8_to_utf32((uint8_t*)src, src_uni, src_len, &src_uni_len);

	if (res == -1) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "The string in parameter seems to not be a valid string.\n");
		efree(src_uni);
		RETURN_NULL();
	}


	for (i = 0; i < src_uni_len; ++i) {
		c = src_uni[i];
		if (c >= nb_char) {
			n++;
			continue;
		}
		start = mapping_index[c];
		if (c == nb_char - 1) {
			end = start + 1;
		} else {
			end = mapping_index[c + 1];
		}
		if (!start) {
			continue;
		}
		n += end - start;
	}
	dst_len = n;

	dst = emalloc(dst_len);

	n=0;
	for (i = 0; i < src_uni_len; ++i) {
		c = src_uni[i];

		if (c >= nb_char) {
			dst[n] = '?';
			n++;
			continue;
		}

		start = mapping_index[c];
		if (c == nb_char - 1) {
			end = start + 1;
		} else {
			end = mapping_index[c + 1];
		}

		if (!start) {
			continue;
		}

		strncpy(dst + n, mapping_chars + start, end - start);
		// *(dst + n + 1) = 0;
		n += end - start;
	}
	//terminate the string
	*(dst + n) = 0;
	efree(src_uni);


	RETURN_STRING(dst, 1);

}