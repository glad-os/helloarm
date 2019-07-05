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


#ifndef SWIS_H
#define SWIS_H

	// SWI allocations
	#define		OS_SetMode										0x00000000
	#define		OS_SetColour									0x00000001
	#define		OS_ClearScreen									0x00000002
	#define		OS_PutPixel										0x00000003
	#define		OS_GetPixel										0x00000004
	#define		OS_SetCursorPosition							0x00000005
	#define		OS_PrintChar									0x00000006
	#define		OS_PrintString									0x00000007
	#define		OS_ReadVideoVariables							0x00000008
	#define		OS_ReadC										0x00000009
	#define		OS_ProcessBegin									0x0000000a
    #define     OS_ProcessExit                                  0x0000000b

#endif /*SWIS_H*/
