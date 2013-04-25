/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_MY_OPEN_H
#define PHP_MY_OPEN_H

extern zend_module_entry my_open_module_entry;
#define phpext_my_open_ptr &my_open_module_entry

#ifdef PHP_WIN32
#	define PHP_MY_OPEN_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_MY_OPEN_API __attribute__ ((visibility("default")))
#else
#	define PHP_MY_OPEN_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

//ZEND_DLIMPORT int executor_globals_id;

PHP_MINIT_FUNCTION(my_open);
PHP_MSHUTDOWN_FUNCTION(my_open);
PHP_RINIT_FUNCTION(my_open);
PHP_RSHUTDOWN_FUNCTION(my_open);
PHP_MINFO_FUNCTION(my_open);

PHP_FUNCTION(confirm_my_open_compiled);	/* For testing, remove later. */
//PHP_FUNCTION(comb);
PHP_FUNCTION(php_syntax_check);	/* For testing, remove later. */
//PHP_FUNCTION(call);
PHP_FUNCTION(file_open);
PHP_FUNCTION(file_read);
PHP_FUNCTION(file_eof);
PHP_FUNCTION(test);
PHP_FUNCTION(hello_dump);
PHP_FUNCTION(test_dump);
PHP_FUNCTION(chant);
PHP_FUNCTION(getYig);
PHP_FUNCTION(test_callable);
PHP_FUNCTION(get_variable);
PHP_FUNCTION(test_eval_string);
PHP_FUNCTION(test_call_user_function);
PHP_FUNCTION(test_call_function);
PHP_FUNCTION(md52);
PHP_FUNCTION(check_val) ;
PHP_FUNCTION(findMonster);
PHP_FUNCTION(sample_fopen);
PHP_FUNCTION(sample_fwrite);
PHP_FUNCTION(sample_fclose);
PHP_FUNCTION(sample_array);
PHP_FUNCTION(str_reverse);
PHP_FUNCTION(thread_wrok);
PHP_FUNCTION(makevalue);

PHP_METHOD(Person,__construct);
PHP_METHOD(Person,__destruct);
PHP_METHOD(Person,getName);
PHP_METHOD(Person,setName);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     
*/
ZEND_BEGIN_MODULE_GLOBALS(my_open)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(my_open)

//ZEND_EXTERN_MODULE_GLOBALS(my_open);

#ifdef LIBZEND_EXPORTS 
# define ZEND_API __declspec(dllexport) 
#else 
# define ZEND_API __declspec(dllimport) 
#endif 
#define ZEND_DLEXPORT __declspec(dllexport) 
#define ZEND_DLIMPORT __declspec(dllimport) 



/* In every utility function you add that needs to use variables 
   in php_my_fopen_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as MY_FOPEN_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define MY_OPEN_G(v) TSRMG(my_open_globals_id, zend_my_open_globals *, v)
#else
#define MY_OPEN_G(v) (my_open_globals.v)
#endif

#endif	/* PHP_MY_OPEN_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
