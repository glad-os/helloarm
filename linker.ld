OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")		/* Define supported output formats - elf32-littlearm default */
OUTPUT_ARCH(arm)														/* Define the target architecture */
ENTRY(main)

SECTIONS
{

	/* for now compile to 0x400000 (2Mb start) */
	PROVIDE ( base = 0x400000 );
	
    .text base :
    {
       	PROVIDE (__text_start = .);
        *(.text); 
    }

    .data :
    {
       	PROVIDE (__data_start = .);
        *(.data); 
    }

    .bss :
    {
      	PROVIDE (__bss_start = .);
        *(.bss) *(COMMON); 
    }


    /* Define linker variable to reference end address of this section - required by gcc */
    PROVIDE (end   = .);
    PROVIDE (__end = .);

    /* The __EH_FRAME_BEGIN__ symbol is not used, but the linker thinks it needs it for some libraries */
    __EH_FRAME_BEGIN__ = 0;

}
