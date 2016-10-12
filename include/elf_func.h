#ifndef __ELF_FUNC_H__
#define __ELF_FUNC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include	<stdio.h>
#include	<string.h>
#include	<ar.h>

#include	"libelf.h"
#include	"symtypes.h"

extern int				Elf32_gettype		(FILE *fp);
extern Elf32_Ehdr*		Elf32_getehdr		(FILE *fp);
extern Elf32_Phdr*		Elf32_getphdr		( FILE *fp, Elf32_Ehdr *ehdr );
extern Elf32_Shdr*		Elf32_getshdr		( FILE *fp, Elf32_Ehdr *ehdr );
extern char*			Elf32_getstrtab		(FILE *fp, Elf32_Ehdr *ehdr, int off, int size);
extern void				swap_half		(void *vp);
extern void 			swap_long		(void *vp);
extern void				swap_ehdr		(Elf32_Ehdr *ehdr);
extern void				swap_phdr		(Elf32_Phdr *phdr);
extern void				swap_shdr		(Elf32_Shdr *shdr);
extern void				swap_stab		(Elf32_Sym  *sym );


#ifdef __cplusplus
}
#endif

#endif/*__ELF_FUNC_H__*/
