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

#include "stdio.h"
#include "swi.h"

int main( int argc, char **argv ) {

	struct _kernel_regs in, out;

	in.r[0] = 0x01;
	in.r[1] = 0x77;
	in.r[2] = 0x99;
	in.r[3] = 0xdd;
	_kernel_swi( OS_SetColour, &in, &out );

	sprintf( "Hello, userland\n" );

	in.r[0] = 0x01;
	in.r[1] = 0xff;
	in.r[2] = 0xff;
	in.r[3] = 0xff;
	_kernel_swi( OS_SetColour, &in, &out );

	// use the OS to exit this process formally
    _kernel_swi( OS_ProcessExit, &in, &out );
	return 0;

}
