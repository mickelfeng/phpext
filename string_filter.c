static char * replace_string (char * string, const char * source, const char * destination )
{
  char* tmp;
	char* sk = strstr (string, source);
	size_t size = strlen(string)+strlen(destination)+1;
	char* newstr = (char*)calloc (1, size);
	char* retstr = (char*)calloc (1, size);
	
	if (sk == NULL) return NULL;
	if (newstr == NULL) return NULL;
	if (retstr == NULL)
	{
		free (newstr);
		return NULL;
	}
	
	snprintf (newstr, size-1, "%s", string);
	sk = strstr (newstr, source);

	while (sk != NULL)
	{
		int pos = 0;
		memcpy (retstr+pos, newstr, sk - newstr);
		pos += sk - newstr;
		sk += strlen(source);
		memcpy (retstr+pos, destination, strlen(destination));
		pos += strlen(destination);
		memcpy (retstr+pos, sk, strlen(sk));

		tmp = newstr;
		newstr = retstr;
		retstr = tmp;

		memset (retstr, 0, size);
		sk = strstr (newstr, source);
	}
	free (retstr);
	return newstr;

}

PHP_FUNCTION(filter_string){
	//char *filter[]={'操你','操','fuck'};
    char *str,*arg,*temp,*bad;
	int str_len,len,bad_len,i;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &str, &str_len,&bad,&bad_len) == FAILURE) {
		return;
	}
	//for(i=0;i<strlen(filter);i++){
	   //replace_string (str,filter[i],"*");
	   //printf("%s",(filter+i));
	   //printf("hello");
	//}
    temp=replace_string (str,bad,"*");
	//printf("%s",temp);
	len = spprintf(&arg, 0, "%s.", temp);
	RETURN_STRINGL(arg, len, 0);
}

/* }}} */
