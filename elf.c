#include	<stdio.h>
#include	<string.h>
#include	<ar.h>

#include	"elf_func.h"

inline void 	swap_half		(void *vp);
inline void 	swap_long		(void *vp);
void			swap_ehdr		(Elf32_Ehdr *ehdr);
void			swap_phdr		(Elf32_Phdr *phdr);
void			swap_shdr		(Elf32_Shdr *shdr);
void			swap_stab		(Elf32_Sym  *sym );

int				need_swap		= 0;
ulong_t			elf_start		= 0;	/* Start offset of current ELF file                             */

/**
 * util functions
 */
void swap_half (void *vp)
{
	char	t, *cp = (char *) vp;

	if (!need_swap)
		return;

	t = cp[0]; cp[0] = cp[1]; cp[1] = t;
}

void swap_long (void *vp)
{
	char	t, *cp = (char *) vp;

	if (!need_swap)
		return;

	t = cp[0]; cp[0] = cp[3]; cp[3] = t;
	t = cp[1]; cp[1] = cp[2]; cp[2] = t;
}

void swap_ehdr(Elf32_Ehdr *ehdr)
{
	swap_half((char *) &ehdr->e_type);
	swap_half((char *) &ehdr->e_machine);
	swap_long((char *) &ehdr->e_version);
	swap_long((char *) &ehdr->e_entry);
	swap_long((char *) &ehdr->e_phoff);
	swap_long((char *) &ehdr->e_shoff);
	swap_long((char *) &ehdr->e_flags);
	swap_half((char *) &ehdr->e_ehsize);
	swap_half((char *) &ehdr->e_phentsize);
	swap_half((char *) &ehdr->e_phnum);
	swap_half((char *) &ehdr->e_shentsize);
	swap_half((char *) &ehdr->e_shnum);
	swap_half((char *) &ehdr->e_shstrndx);
}

void swap_phdr(Elf32_Phdr *phdr)
{
	swap_long((char *) &phdr->p_type);
	swap_long((char *) &phdr->p_offset);
	swap_long((char *) &phdr->p_vaddr);
	swap_long((char *) &phdr->p_paddr);
	swap_long((char *) &phdr->p_filesz);
	swap_long((char *) &phdr->p_memsz);
	swap_long((char *) &phdr->p_flags);
}

void swap_shdr(Elf32_Shdr *shdr)
{
	swap_long((char *) &shdr->sh_name);
	swap_long((char *) &shdr->sh_type);
	swap_long((char *) &shdr->sh_flags);
	swap_long((char *) &shdr->sh_addr);
	swap_long((char *) &shdr->sh_offset);
	swap_long((char *) &shdr->sh_size);
	swap_long((char *) &shdr->sh_link);
	swap_long((char *) &shdr->sh_info);
	swap_long((char *) &shdr->sh_addralign);
	swap_long((char *) &shdr->sh_entsize);
}

void swap_stab(Elf32_Sym *sym)
{
	swap_long((char *)&sym->st_name);
	swap_long((char *)&sym->st_value);
	swap_long((char *)&sym->st_size);
	swap_half((char *)&sym->st_shndx);
}

/**
 * ELF operation functions
 */
int Elf32_gettype(FILE *fp)
{
	char	id[16];

	fseek(fp, 0, SEEK_SET);

	if (fread(id, 1, 16, fp) != 16)
		return(-1);

	if (!strncmp(id, ARMAG, SARMAG))
	{
		return(ELF_K_AR);

	}
	else if ((*id == 0x7F) && !strncmp(id+1, "ELF", 3))
	{
		return(ELF_K_ELF);
	}
	else
	{
		return(ELF_K_NONE);
	}
}

Elf32_Ehdr * Elf32_getehdr (FILE *fp)
{
	static Elf32_Ehdr	ehdr;
	int					i;

	fseek(fp, elf_start, SEEK_SET);

	if ((fread(&ehdr, sizeof(ehdr), 1, fp)) != 1)
		return((Elf32_Ehdr *) NULL);

	if (ehdr.e_ident[EI_DATA] == ELFDATA2MSB) need_swap = 1;
	else                                      need_swap = 0;

	swap_ehdr(&ehdr);

	return(&ehdr);
}

Elf32_Phdr* Elf32_getphdr( FILE *fp, Elf32_Ehdr *ehdr )
{
	int			i, j;
	Elf32_Phdr	*phdr = NULL;

	if (ehdr->e_phnum == 0)
		return(NULL);

	fseek(fp, elf_start + ehdr->e_phoff, SEEK_SET);

	phdr = (Elf32_Phdr *) malloc(ehdr->e_phentsize * ehdr->e_phnum);
	memset(phdr, 0, ehdr->e_phentsize * ehdr->e_phnum);

	if (fread(phdr, ehdr->e_phentsize, ehdr->e_phnum, fp) != ehdr->e_phnum)
		return((Elf32_Phdr*) NULL);

	for (i=0; i < ehdr->e_phnum; i++)
		swap_phdr(phdr+i);

	return(phdr);
}

Elf32_Shdr* Elf32_getshdr( FILE *fp, Elf32_Ehdr *ehdr )
{
	int			i;
	Elf32_Shdr	*shdr = NULL;

	if (ehdr->e_shnum == 0)
		return(NULL);

	fseek(fp, elf_start + ehdr->e_shoff, SEEK_SET);
	shdr = (Elf32_Shdr *) malloc(ehdr->e_shentsize * ehdr->e_shnum);

	if (fread(shdr, ehdr->e_shentsize, ehdr->e_shnum, fp) != ehdr->e_shnum)
		return((Elf32_Shdr*) NULL);

	for (i=0; i < ehdr->e_shnum; i++)
		swap_shdr(shdr+i);

	return(shdr);
}

char * Elf32_getstrtab(FILE *fp, Elf32_Ehdr *ehdr, int off, int size)
{
	char	*strp = NULL;

	strp = (char *) malloc(size);

	fseek(fp, elf_start + off, SEEK_SET);
	fread(strp, 1, size, fp);

	return(strp);
}