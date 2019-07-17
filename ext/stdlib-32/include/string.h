/**
 * Copyright 2019 AbbeyCatUK
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef STRING_H
#define STRING_H

	// memmove, memcpy, strcpy, strlen, strchr, strcmp, strncmp, strncpy, strcat, strstr

	char * strchr( char *str, char c );
	unsigned int strncmp( const char *str1, const char *str2, unsigned int n );
	void *memmove( void *sourceaddr, void *destaddr, unsigned int length );
	char *strncat( char *s, char *ct, unsigned int n );
	char *strstr( char *cs, char *ct );

	// these originally also existed in USPiEnv
	void *memcpy( void *dst, void *src, unsigned int n );
	int strlen (const char *pString);
	int strcmp (const char *pString1, const char *pString2);
	char *strcpy (char *pDest, const char *pSrc);
	char *strncpy (char *pDest, const char *pSrc, unsigned long nMaxLen);
	char *strcat (char *pDest, const char *pSrc);


#endif /*STRING_H*/
