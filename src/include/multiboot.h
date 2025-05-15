
#ifndef MBOOT_HEADER 
#define MBOOT_HEADER 1

#include "../lib/common.h"

/*how many bytes from start of file to search for the header */ 
#define MBOOT_SEARCH            8192 
#define MBOOT_HEADER_ALIGN      4 

/*magic field */ 
#define MBOOT_HEADER_MAGIC      0x1BADB002 

/*this goes in eax */ 
#define MBOOT_BOOTLOADER_MAGIC  0x2BADB002  

/*align bootloader module */ 
#define MBOOT_MOD_ALIGN         0x00001000

/*alignment of multibnoot info structure*/ 
#define MBOOT_INFO_ALIGN        0x00000004 

/*all bootloader modules aligned on 4kb bounderies */ 
#define MBOOT_PAGE_ALIGN        0x00000001

/*must pass memory information to OS*/
#define MBOOT_MEMORY_INFO       0x00000002 

/*must pass video information to OS*/ 
#define MBOOT_VIDEO_MODE        0x00000004     

/*flag indecates the use of address filed in header*/
#define MBOOT_AOUT_KLUDGE       0x00010000 

/*is there basic lower/upper memory*/ 
#define MBOOT_INFO_MEMORY       0x00000001 

/*is there a boot device set */ 
#define MBOOT_INFO_BOOTDEV      0x00000002 

/*is the command line defined */ 
#define MBOOT_INFP_CMDLINE      0x00000004 

/*are the modules to do some taks with */ 
#define MBOOT_INFO_MODS         0x00000008 


/* These next two are mutually exclusive */

/* is there a symbol table loaded? */
#define MBOOT_INFO_AOUT_SYMS    0x00000010
/* is there an ELF section header table? */
#define MBOOT_INFO_ELF_SHDR     0X00000020

/* is there a full memory map? */
#define MBOOT_INFO_MEM_MAP      0x00000040

/* Is there drive info? */
#define MBOOT_INFO_DRIVE_INFO   0x00000080

/* Is there a config table? */
#define MBOOT_INFO_CONFIG_TABLE 0x00000100

/* Is there a boot loader name? */
#define MBOOT_INFO_BOOT_LOADER_NAME 0x00000200

/* Is there a APM table? */
#define MBOOT_INFO_APM_TABLE        0x00000400

/* Is there video information? */
#define MBOOT_INFO_VBE_INFO         0x00000800
#define MBOOT_INFO_FRAMEBUFFER_INFO 0x00001000



#ifndef ASM_FILE 


typedef unsigned char       uin8_t; 
typedef unsigned short      uin16_t; 
typedef unsigned int        uin32_t;
typedef unsigned long long  uin64_t;



struct mboot_header
{
    uin32_t  magic;
    uin32_t  flags; 
    uin32_t  checksum; 

    /*availabe only if MBOOT_AOUT_KLUDGE is set */ 
    uin32_t  header_addr; 
    uin32_t  load_addr; 
    uin32_t  load_end_addr; 
    uin32_t  bss_enf_addr;
    uin32_t  entry_addr; 

    /*availabe only if MBOOT_VIDEO_MODE IS SET*/ 
    uin32_t  mode_type;
    uin32_t  width;
    uin32_t  height;
    uin32_t  depth;
}; 


/*Symbol table for a.out format */ 
struct mboot_aout_symbol_table
{
    uin32_t  tabsize;
    uin32_t  strsize;
    uin32_t  addr; 
    uin32_t  reserved; 
};
typedef struct mboot_aout_symbol_table mboot_aout_symbol_table_t; 

/*section header table for elf*/
struct mboot_elf_section_header_table
{
    uin32_t  header_num;
    uin32_t  entry_size; 
    uin32_t  header_addr;
    uin32_t  shndx; 
};
typedef struct mboot_elf_section_header_table mboot_elf_section_header_table_t; 




#define MBOOT_FRAMEBUFFER_TYPE_INDEXED  0 
#define MBOOT_FRAMEBUFFER_TYPE_RGB      1       
#define MBOOT_FRAMEBUFFER_TYPE_EGA_TEXT 2 


struct mboot_info
{
    /*mboot info verson number*/
    uin32_t  flags;

    /*availabe memory from BIOS*/ 
    uin32_t  mem_lower;  /*below 1mb */  
    uin32_t  mem_upper;  /*above 1mb */ 

    /*root partition */ 
    uin32_t  boot_device; 

    /*kernel command line */ 
    uin32_t  cmdline;

    /*boot module list */ 
    uin32_t mods_count; 
    uin32_t mods_addr; 

    union{
        mboot_aout_symbol_table_t           aout_sym;
        mboot_elf_section_header_table_t    elf_sec; 
    }u;

    /*memory mapping buffer */ 
    uin32_t  mmap_length;
    uin32_t  mmap_addr;

    /*drive info buffer */
    uin32_t  drives_length;      /* bytes allocated for drivew info */ 
    uin32_t  drives_addr;        /*addres of info in memory*/

    /*ROM config */ 
    uin32_t  config_table; 

    /*boot loader name*/
    uin32_t  bootloader_name; 

    /*APM table*/
    uin32_t  apm_table; 

    /*Video Mode*/
    uin32_t  vbe_control_info;
    uin32_t  vbe_mode_info;
    uin16_t  vbe_mode;
    uin16_t  vbe_interface_seg;
    uin16_t  vbe_interface_off;
    uin16_t  vbe_interface_len;

    uin64_t  framebuffer_addr;
    uin32_t  framebuffer_pitch;
    uin32_t  framebuffer_width;
    uin32_t  framebuffer_height;
    uin8_t   framebuffer_bpp;

    /*frame buffer types*/
    uin8_t   framebuffer_type; 

    union
    {
    struct
    {
      uin32_t framebuffer_palette_addr;
      uin16_t framebuffer_palette_num_colors;
    };
    struct
    {
      uin8_t framebuffer_red_field_position;
      uin8_t framebuffer_red_mask_size;
      uin8_t framebuffer_green_field_position;
      uin8_t framebuffer_green_mask_size;
      uin8_t framebuffer_blue_field_position;
      uin8_t framebuffer_blue_mask_size;
    };
  };
};
typedef struct mboot_info mboot_info_t; 

struct mboot_color
{
    uin8_t   red;
    uin8_t   green; 
    uin8_t   blue; 

};

/*mmap types */ 
#define MBOOT_MEMORY_AVAILABE           1 
#define MBOOT_MEMORY_RESERVED           2 
#define MBOOT_MEMORY_ACPI_RECLAIMABLE   3 
#define MBOOT_MEMORY_NVS                4 
#define MBOOT_MEMORY_BADRAM             5 

struct mboot_mmap_entry
{
    uin32_t  size;
    uin64_t  addr; 
    uin64_t  len; 

    uin32_t   type; 

}__attribute__((packed));
typedef struct mboot_mmap_entry mboot_mmap_entry_t; 

/*module info*/ 
struct  mboot_module 
{
    /*bytes from mod_start to mod_end -1 */ 
    uin32_t  mod_start;
    uin32_t  mod_end; 

    uin32_t  cmdline; 

    /*16 bytes pad */ 
    uin32_t  pad; 
};
typedef struct mboot_module mboot_module_t; 


/*APM BIOS info */ 
struct mboot_apm_info
{
    uin16_t  version; 
    uin16_t  cseg; 
    uin16_t  dseg;
    uin16_t  flags;
    uin16_t  cseg_len; 
    uin16_t  cseg_16_len; 
    uin16_t  dseg_len;
}; 

#endif /* ASM_FILE */ 

#endif /*MBOOT_HEADER */ 
