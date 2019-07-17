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



#include <stdint.h>



#ifndef SWI_H
#define SWI_H

	// SWI allocations
	#define		OS_SetMode				0x00000000
	#define		OS_SetColour				0x00000001
	#define		OS_ClearScreen				0x00000002
	#define		OS_PutPixel				0x00000003
	#define		OS_GetPixel				0x00000004
	#define		OS_SetCursorPosition			0x00000005
	#define		OS_PrintChar				0x00000006
	#define		OS_PrintString				0x00000007
	#define		OS_ReadVideoVariables			0x00000008
	#define		OS_ReadC				0x00000009
	#define		OS_ProcessBegin				0x0000000a
	#define		OS_ProcessExit				0x0000000b

	// up to a maximum of 4 register values can be passed in/out of an SWI using this structure
	struct _kernel_regs {
		uintptr_t r[ 4 ];
	};

	// for now, SWIs can take data in but don't yet get to return anything to the caller
	void _kernel_swi( unsigned int swi_number, struct _kernel_regs *in, struct _kernel_regs *out );

	// macro to invoke the SWI instruction [http://www.ethernut.de/en/documents/arm-inline-asm.html] -> asm(code : output operand list : input operand list : clobber list);
	// call SWI_INVOKE which allows SWI_ string constants to be expanded prior to then being injected into the SWI_GENERATE_ASM macro.
	#define SWI( n,p_in,p_out ) SWI_GENERATE_ASM(n,p_in,p_out)
	#define SWI_GENERATE_ASM( NR, PTR_IN, PTR_OUT ) __asm__ __volatile__ ( "MOV r0, %[in]\n\tMOV r1, %[out]\n\tSWI " #NR "\n\t" : : [in] "r" ( PTR_IN ), [out] "r" ( PTR_OUT ) );

#endif /*SWI_H*/
