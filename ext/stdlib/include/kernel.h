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


#ifndef KERNEL_H
#define KERNEL_H

	// up to a maximum of 4 register values can be passed in/out of an SWI using this structure
	struct _kernel_regs {
		unsigned int r[ 4 ];
	};

	// for now, SWIs can take data in but don't yet get to return anything to the caller
	void _kernel_swi( unsigned int swi_number, struct _kernel_regs *in, struct _kernel_regs *out );

	// macro to invoke the SWI instruction [http://www.ethernut.de/en/documents/arm-inline-asm.html] -> asm(code : output operand list : input operand list : clobber list);
	// call SWI_INVOKE which allows SWI_ string constants to be expanded prior to then being injected into the SWI_GENERATE_ASM macro.
	#define SWI( n,p_in,p_out ) SWI_GENERATE_ASM(n,p_in,p_out)
	#define SWI_GENERATE_ASM( NR, PTR_IN, PTR_OUT ) __asm__ __volatile__ ( "MOV r0, %[in]\n\tMOV r1, %[out]\n\tSWI " #NR "\n\t" : : [in] "r" ( PTR_IN ), [out] "r" ( PTR_OUT ) );

#endif /*KERNEL_H*/
