#ifndef __ELF_FUNC_H__
#define __ELF_FUNC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ar.h>

#include	"libelf.h"
#include	"symtypes.h"

/*elf.c*/
extern int				Elf32_gettype			(FILE *fp);
extern Elf32_Ehdr*		Elf32_getehdr			(FILE *fp);
extern Elf32_Phdr*		Elf32_getphdr			( FILE *fp, Elf32_Ehdr *ehdr );
extern Elf32_Shdr*		Elf32_getshdr			( FILE *fp, Elf32_Ehdr *ehdr );
extern char*			Elf32_getstrtab			(FILE *fp, Elf32_Ehdr *ehdr, int off, int size);

extern void				swap_half				(void *vp);
extern void				swap_long				(void *vp);
extern void				swap_ehdr				(Elf32_Ehdr *ehdr);
extern void				swap_phdr				(Elf32_Phdr *phdr);
extern void				swap_shdr				(Elf32_Shdr *shdr);
extern void				swap_stab				(Elf32_Sym  *sym );

/*dwarf.c*/
extern void				parse_all_comp_units	(void);
extern void				release_all_comp_units	(void);

/*addr2line.c*/
extern int				searchLineInfo			(char **ppDebugLine, size_t *pSize, unsigned int srchAddr, char **ppFileName);
extern short			getShort				(char *pSrc);
extern int				getLong					(char *pSrc);
#ifdef __cplusplus
}
#endif

#endif/*__ELF_FUNC_H__*/
