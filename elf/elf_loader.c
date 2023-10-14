/*
  This file is part of MAMBO, a low-overhead dynamic binary modification tool:
      https://github.com/beehive-lab/mambo

  Copyright 2013-2016 Cosmin Gorgovan <cosmin at linux-geek dot org>
  Copyright 2017-2020 The University of Manchester

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#define DEBUG
#include <stdlib.h>
#include <stdio.h>
#include <libelf.h>
#include <fcntl.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <sys/mman.h>

#include "elf_loader.h"
#include "../dbm.h"
#include "../common.h"

#ifndef AT_MINSIGSTKSZ
  #define AT_MINSIGSTKSZ 51
#endif

#ifdef DEBUG
  #define debug(...) fprintf(stderr, __VA_ARGS__)
#else
  #define debug(...)
#endif

#ifdef MORELLOBSD
extern Elf_Auxinfo *__auxargs;
#include <cheri/cheric.h>
#endif

extern void *__ehdr_start;

#ifdef MORELLO

#include "cheriintrin.h"

void pp_cap(void *__capability ptr)
{
    uint64_t length = cheri_length_get(ptr);
    uint64_t address = cheri_address_get(ptr);
    uint64_t base = cheri_base_get(ptr);
    uint64_t flags = cheri_flags_get(ptr);
    uint64_t perms = cheri_perms_get(ptr);
    uint64_t type = cheri_type_get(ptr);
    bool tag = cheri_tag_get(ptr);

    uint64_t offset = cheri_offset_get(ptr);

    printf("Capability: %#lp\n", ptr);
    printf("Tag: %d, Perms: %04lx, Type: %lx, Address: %04lx, Base: %04lx, End: %04lx, Flags: %lx, "
           "Length: %04lx, Offset: %04lx\n",
           tag, perms, type, address, base, base + length, flags, length, offset);
}
#endif

uintptr_t * relo;

void load_segment(uintptr_t base_addr, ELF_PHDR *phdr, int fd, Elf32_Half type, bool is_interp) {
  uint32_t *mem;
  int prot = 0;
  uintptr_t aligned_vaddr, aligned_fsize, aligned_msize, page_offset, map_file_end;

#ifdef ENABLE_EXECUTE
  if (phdr->p_flags & PF_X) {
    prot |= PROT_EXEC;
  }
#endif

  if (phdr->p_flags & PF_W) {
    prot |= PROT_WRITE;
  }

  if (phdr->p_flags & PF_R) {
    prot |= PROT_READ;
  }

  //testing hack to enable execute
  prot |= PROT_EXEC;

  if (type == ET_DYN) {
    assert(base_addr != 0);
    phdr->p_vaddr += base_addr;
  }

  aligned_vaddr = align_lower(phdr->p_vaddr, PAGE_SIZE);
  page_offset = phdr->p_vaddr - aligned_vaddr;
   void * cap_base_addr = (void *)base_addr + ((void *)aligned_vaddr - (void *)base_addr );
  //if(cap_base_addr == 0x236000)
  //aligned_fsize = phdr->p_filesz;
  //else
  aligned_fsize = align_higher(phdr->p_filesz + page_offset, PAGE_SIZE);

  map_file_end = phdr->p_vaddr + phdr->p_filesz;
  aligned_msize = align_higher(phdr->p_memsz + page_offset, PAGE_SIZE);

  // Map a page-aligned file-backed segment including the (vaddr, vaddr + filesize) area
  #define MAP_EL_FILE (MAP_PRIVATE|MAP_FIXED)

  off_t offset = phdr->p_offset - page_offset;
  printf("\n\n\n\n\n----- mmap ----- \n");
  //prot = -1;
  printf("aligned_base_vaddr - %p, top_address - %p,aligned_fsize %p, prot %d, offset - %p, fd - %d\n", aligned_vaddr,aligned_vaddr + aligned_fsize ,aligned_fsize , prot, offset, fd );
 
  printf("\n Test address %p", cap_base_addr);

  mem = mmap(cap_base_addr, aligned_fsize, prot,
             MAP_EL_FILE, fd, offset);

  if(cap_base_addr == 0x200000){
    relo = mem;
    pp_cap(relo);
  }

  if(mem == MAP_FAILED){
    printf("Oh dear, something went wrong with mmap()! %s\n", strerror(errno));
  }
  if(cap_base_addr == 0x236000)
  {
    uint32_t align_offset = phdr->p_vaddr - aligned_vaddr;
    for(uint32_t i = (align_offset +  phdr->p_filesz) /4; i <  (aligned_fsize - phdr->p_filesz) /4; i++)
    {
      mem[i] = 0;
    }
  }
  assert(mem != MAP_FAILED);
  int flags = MAP_EL_FILE|(is_interp ? MAP_INTERP : MAP_APP);
  notify_vm_op(VM_MAP, aligned_vaddr, aligned_fsize,
               prot | ((phdr->p_flags & PF_X) ? PROT_EXEC : 0), flags, fd, offset);

  // Zero the area from (vaddr + filesize) to the end of the page
  if (phdr->p_flags & PF_W) {
    printf("\nmemset\n");
    //TODO this needs to be fixed as it is zeroing the relo section needed for the init capabilities. 
    //memset((void *)mem + phdr->p_filesz, 0, (aligned_vaddr + aligned_fsize) - map_file_end);
  }

  // Allocate anonymous pages if aligned memsize > filesize
  
  #define MAP_EL_ANON (MAP_EL_FILE)
  if ((aligned_msize > aligned_fsize) && (cap_base_addr == 0x236000)) {
    //void * remap_cap_base = cap_base_addr + ((void *)phdr->p_vaddr - (void *)cap_base_addr) + aligned_fsize;
    void * remap_cap_base = cheri_address_set(cap_base_addr, phdr->p_vaddr);
    printf("\nmapping non file space\n");
    printf("remap_cap_base - %p, top_address - %p,\n", remap_cap_base,aligned_msize-aligned_fsize  );

    mem = mmap( remap_cap_base  , aligned_msize-aligned_fsize , prot,
               MAP_ANON | MAP_PRIVATE, -1, 0);
    if(mem == MAP_FAILED)
      printf("Oh dear, something went wrong with mmap()! %s\n", strerror(errno));           
    assert(mem != MAP_FAILED);
    notify_vm_op(VM_MAP, aligned_vaddr + aligned_fsize, aligned_msize-aligned_fsize,
                 prot | ((phdr->p_flags & PF_X) ? PROT_EXEC : 0), MAP_EL_ANON, -1, 0);
  }


#ifdef ENABLE_EXECUTE
  if (phdr->p_flags & PF_X) {
    __clear_cache((char *)phdr->p_vaddr, (char *)phdr->p_vaddr + (char *)phdr->p_memsz);
  }
#endif

  if (!is_interp && (aligned_vaddr + aligned_msize) > global_data.brk) {
    global_data.brk = aligned_vaddr + aligned_msize;
  }
}

void * load_elf(char *filename, Elf **ret_elf, struct elf_loader_auxv *auxv, uintptr_t *entry_addr, bool is_interp, ELF_PHDR **ret_phdr, unsigned int * ret_phdr_num) {
  int fd;
  FILE *file,*file_elo;
  Elf *elf;
  Elf_Kind kind;
  ELF_EHDR *ehdr;
  ELF_PHDR *phdr;
  char interp[256];
  errno = 0;
  size_t phnum;

  fd = open(filename, O_RDONLY);
  if (fd < 0) {
    printf("Couldn't open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  
  if (elf_version(EV_CURRENT) == EV_NONE) {
    printf("Error setting ELF version\n");
    exit(EXIT_FAILURE);
  }
  
  elf = elf_begin(fd, ELF_C_READ, NULL);
  *ret_elf = elf;
  if (elf == NULL) {
    printf("Error opening ELF file: %s: %s\n", filename, elf_errmsg(-1));
    exit(EXIT_FAILURE);
  }
  
  kind = elf_kind(elf);
  if (kind != ELF_K_ELF) {
    printf("File %s isn't an ELF file\n", filename);
    exit(EXIT_FAILURE);
  }
  
  ehdr = ELF_GETEHDR(elf);
  if (ehdr == NULL) {
    printf("Error reading the ELF executable header: %s\n", elf_errmsg(-1));
    exit(EXIT_FAILURE);
  }
  
  if (ehdr->e_ident[EI_CLASS] != ELF_CLASS) {
    printf("Not a 32-bit ELF file\n");
    exit(EXIT_FAILURE);
  }
//FIXME Need to check the machine type
  if (ehdr->e_machine != EM_MACHINE) {
    printf("Not compiled for ARM\n");
    exit(EXIT_FAILURE);
  }

  file = fdopen(fd, "r");

  elf_getphdrnum(elf, &phnum);
  phdr = ELF_GETPHDR(elf);

  /* Allocate the whole memory region, using ASLR if enabled in the kernel */
  void *base_addr = NULL;
  uintptr_t min_addr = UINTPTR_MAX;
  uintptr_t max_addr = 0;

  *ret_phdr = (Elf64_Phdr *) malloc(phnum * sizeof(ELF_PHDR));
  *ret_phdr_num = phnum;

  for (int i = 0; i < phnum; i++) {
    (*ret_phdr)[i] = phdr[i]; 
    if (phdr[i].p_type == PT_LOAD) {
      uintptr_t end = phdr[i].p_vaddr + phdr[i].p_memsz;
      if (end > max_addr) {
        max_addr = end;
      }
      if (phdr[i].p_vaddr < min_addr) {
        min_addr = phdr[i].p_vaddr;
      }
    }
  }

  if (ehdr->e_type == ET_DYN) {
    assert(min_addr == 0);
  } else {
    assert(min_addr != 0);
  }

  base_addr = mmap((void *)min_addr, align_higher(max_addr - min_addr, PAGE_SIZE) ,  PROT_NONE, MAP_ANONYMOUS|MAP_PRIVATE , -1, 0);

  printf("\n1 Allocate memory region - Min Address = %x Max address = %x, base address = %x, size = %x\n",min_addr, align_higher(max_addr - min_addr, PAGE_SIZE),base_addr,(max_addr - min_addr));

  if (ehdr->e_type == ET_DYN) {
    assert(base_addr != MAP_FAILED);
    ehdr->e_entry += (uintptr_t)base_addr;
  } else {
    if(base_addr == MAP_FAILED){
       printf("Oh dear, something went wrong with mmap()! %s\n", strerror(errno));
    }
    assert(base_addr == (void*)min_addr);
  }


  /* entry address is the actual execution entry point, either in the interpreter
     (if one is used), or in the executable */
  *entry_addr = __builtin_cheri_address_set(base_addr,ehdr->e_entry);

  // AT_ENTRY in the AUXV points to the original executable
  if (!is_interp) {
    auxv->at_entry = ehdr->e_entry;
  }

  // Look for an INTERP header
  for (int i = 0; i < phnum; i++) {
    if (phdr[i].p_type == PT_INTERP) {
      debug("INTERP field found\n");
      assert(!is_interp);
      
      if (phdr[i].p_filesz > 255) {
        printf("INTERP filename longer than the buffer\n");
        while(1);
      }
      
      if (fseek(file, phdr[i].p_offset, SEEK_SET) != 0) {
        printf("Seek to INTERP field failed");
        while(1);
      }
      
      if(fread(interp, sizeof(char), phdr[i].p_filesz, file) != phdr[i].p_filesz) {
        printf("Failed reading INTERP string\n");
        while(1);
      }
      interp[phdr[i].p_filesz] = '\0';
      //TODO:AA Fix passing in phdr and pdhr-count - We need to deal with the capabilities of shared libraries.
      //load_elf(interp, ret_elf, auxv, entry_addr, true);
    }
   
  }

  if (is_interp) {
    auxv->at_base = 0;
  } else {
    auxv->at_phdr = 0;
    auxv->at_phnum = phnum;
  }

  for (int i = 0; i < phnum; i++) {
    debug("\np_type: 0x%x\n", phdr[i].p_type);
    debug("p_offset: 0x%x\n", phdr[i].p_offset);
    debug("p_vaddr: 0x%x\n", phdr[i].p_vaddr);
    debug("p_paddr: 0x%x\n", phdr[i].p_paddr);
    debug("p_filesz: 0x%x\n", phdr[i].p_filesz);
    debug("p_memsz: 0x%x\n", phdr[i].p_memsz);
    debug("p_flags: 0x%x\n", phdr[i].p_flags);
    debug("p_align: 0x%x\n", phdr[i].p_align);
    
    switch(phdr[i].p_type) {
      case PT_LOAD:
        load_segment(base_addr, &phdr[i], fd, ehdr->e_type, is_interp);
        if (is_interp) {
          if (phdr[i].p_offset == 0) {
            auxv->at_base = phdr[i].p_vaddr;
          }
        } else { // !is_interp
          if (phdr[i].p_offset == 0) {
            auxv->at_phdr = phdr[i].p_vaddr + ehdr->e_phoff;
          }
        }
        break;
      /*case PT_GNU_RELRO:
        assert(relo);
        file_elo = fdopen(fd, "r");
        pp_cap(relo);
        relo = relo + 0x25d0;
        printf("writing tp\n\n\n");
         pp_cap(relo);
        fseek(file_elo, phdr[i].p_offset, SEEK_SET);
        *relo = 0xDEADBEEF;
        printf("'\n\nrelo section vaddr %x, memsz %x, filesz %x\n\n",phdr[i].p_vaddr,phdr[i].p_memsz, phdr[i].p_filesz);
        u_int32_t * tempcheck = (u_int32_t *) malloc(sizeof(char) * phdr[i].p_memsz);
        fread(tempcheck,sizeof(char),phdr[i].p_memsz,file_elo);
        printf("\n\nchecking file \n\n");
        for(int  i = 0; i < phdr[i].p_memsz / 4; i++ )
          printf("-%d-", (u_int32_t *)tempcheck[i]);
          
          printf("\n\nchecking file \n\n");
        //load_segment(base_addr, &phdr[i], fd, ehdr->e_type, is_interp);
      */
      default:
        debug("Unhandled program header table entry type\n");
        break;
    }
  }

  if (is_interp) {
    assert(auxv->at_base);
  } else { // !is_interp
    assert(auxv->at_phdr);
  }
   return base_addr;
}

size_t find_stack_data_size(char *filename, int argc, char **argv, char **envp, struct elf_loader_auxv *auxv) {
  
  printf("starting stack size check\n");
  size_t size = (4 + argc) * sizeof(uintptr_t); // ARGC, ARGV[0], NULL after ARGs and ENVP
  size += 16; // AT_RANDOM
  size += strlen(filename) + 1;

  for (int i = 0; i < argc; i++) {
    size += strlen(argv[i]) + 1;
  }

  for (; *envp != NULL; envp++) {
    size += sizeof(uintptr_t) + strlen(*envp) + 1;
  }

  
#ifdef MORELLO
  ELF_AUXV_T *s_aux = getauxv();
#else 
  ELF_AUXV_T *s_aux = auxv;
#endif 

  while(s_aux->a_type != AT_NULL) {
    printf("SAUX  number %d\n",s_aux->a_type);
  #ifndef MORELLOBSD
    #ifdef MORELLO
      switch(s_aux->a_type) {
      case AT_PLATFORM:
      case AT_EXECFN: {
        char *s = (char *)s_aux->a_un.a_ptr;
        size += strlen(s) + 1;
      }
    } // switch
    #else
    switch(s_aux->a_type) {
      case AT_PLATFORM:
      case AT_EXECFN: {
        char *s = (char *)s_aux->a_un.a_val;
        size += strlen(s) + 1;
      }
    } // switch
    #endif
  #endif


    size += sizeof(*s_aux);
    s_aux++;
  } // while
  size += sizeof(*s_aux);

  return size;
}

char *copy_string_to_stack(char *string, char **stack_strings) {
  size_t len = strlen(string) + 1;
  *stack_strings -= len;
  strncpy(*stack_strings, string, len);
  return *stack_strings;
}

#define INITIAL_STACK_SIZE (4*1024*1024)
#define STACK_PROT  (PROT_READ | PROT_WRITE)
#ifdef MORELLOBSD
  #define STACK_FLAGS (MAP_PRIVATE|MAP_ANONYMOUS|MAP_STACK)
#else
  #define STACK_FLAGS (MAP_PRIVATE|MAP_ANONYMOUS|MAP_GROWSDOWN|MAP_STACK)
#endif
#define stack_push(val) stack[stack_i++] = (val);

void elf_run(uintptr_t entry_address, char *filename, int argc, char **argv, char **envp, struct elf_loader_auxv *auxv, ELF_PHDR * phdr, unsigned int phdr_num) {
  // Allocate a new stack for the execution of the application
  void *stack_space = mmap(NULL, INITIAL_STACK_SIZE, STACK_PROT, STACK_FLAGS, -1, 0);
  printf("\nstack_space - %#p \n ", stack_space);
  assert(stack_space != MAP_FAILED);
  notify_vm_op(VM_MAP, (uintptr_t)stack_space, INITIAL_STACK_SIZE, STACK_PROT, STACK_FLAGS, -1, 0);
  pp_cap(stack_space);


  // Grows up (towards lower addresses)
  char *stack_strings = stack_space + INITIAL_STACK_SIZE;

  printf("\nstack_strings - %#p  \n", stack_strings);
  // Grows down (towards higher addresses)
  size_t data_size = find_stack_data_size(filename, argc, argv, envp, auxv);
  //uintptr_t *stack = (uintptr_t *)align_lower_cap((uintptr_t *)(stack_space + INITIAL_STACK_SIZE - data_size), 16);
  uintptr_t *stack = __builtin_align_down(stack_space  + INITIAL_STACK_SIZE - data_size,16);
  printf("\nstack - %#p , stack_space - %#p \n",stack, stack_space);

  int stack_i = 0;

  // Copy args
  stack_push(argc + 1);
 uintptr_t argv_new = __builtin_align_up(&stack[stack_i],16);
  stack_push((uintptr_t)copy_string_to_stack(filename, &stack_strings));
  for (int i = 0; i < argc; i++) {
    uintptr_t argv_temp = (uintptr_t)copy_string_to_stack(argv[i], &stack_strings);
    if(i == 0)
      argv_new = argv_temp;
    stack_push(argv_temp);
  }
  stack_push((uintptr_t)NULL);


  uintptr_t envp_new;
  // Copy env
  uintptr_t envp_temp = (uintptr_t)copy_string_to_stack(*envp, &stack_strings);
  stack_push(envp_temp);
  envp_new = cheri_address_set( stack , &envp_temp);
  envp++;
  while (*envp != NULL) {
    uintptr_t envp_temp = (uintptr_t)copy_string_to_stack(*envp, &stack_strings);
    stack_push(envp_temp);
    envp++;
  }
  stack_push((uintptr_t)NULL);
  
  // Copy the Auxiliary Vector

 

#ifdef MORELLOBSD
  ELF_AUXV_T *s_aux = __auxargs;
#elif MORELLO
  ELF_AUXV_T *s_aux = getauxv();
#else 
   ELF_AUXV_T *s_aux = (ELF_AUXV_T *)(envp + 1);
#endif 


  ELF_AUXV_T *d_aux = (ELF_AUXV_T *)&stack[stack_i];
  //we need to know the start address of the new aux for the purecap crt
  ELF_AUXV_T *d_aux_start = (ELF_AUXV_T *)&stack[stack_i];
  while(s_aux->a_type != AT_NULL) {
    d_aux->a_type = s_aux->a_type;

    switch(s_aux->a_type) {

#ifndef MORELLOBSD
        case AT_CLKTCK:
        case AT_SECURE:      
        case AT_SYSINFO_EHDR:
#endif

      case AT_PAGESZ:
      case AT_HWCAP:
      case AT_HWCAP2:

      case AT_FLAGS:
      case AT_UID:
      case AT_EUID:
      case AT_GID:
      case AT_EGID:

#ifdef MORELLOBSD
      case AT_EHDRFLAGS:
      case AT_OSRELDATE:
      case AT_CANARY:
      case AT_CANARYLEN:
      case AT_NCPUS:
      case AT_PAGESIZES:
      case AT_PAGESIZESLEN:
      case AT_TIMEKEEP:
      case AT_STACKPROT:
      case AT_BSDFLAGS:
      case AT_ARGC:
      case AT_ENVC:
      
      case AT_PS_STRINGS:
      case AT_FXRNG:
      case AT_KPRELOAD:
      case AT_COUNT:
        d_aux->a_un.a_val = s_aux->a_un.a_val;
        break;

      case AT_ARGV:
      case AT_ENVV:
        d_aux->a_un.a_ptr = s_aux->a_un.a_ptr;
        printf("\nAT ARG + ENVV- %#p  \n", d_aux->a_un.a_ptr);
        break;
#endif  

      case AT_MINSIGSTKSZ:
      case AT_PHENT:
        d_aux->a_un.a_val = s_aux->a_un.a_val;
        break;
#ifdef MORELLOBSD
        case AT_EXECPATH:
        d_aux->a_un.a_val = (uintptr_t)copy_string_to_stack((char *)s_aux->a_un.a_ptr, &stack_strings);
        break;    

      case AT_PHDR:
        d_aux->a_un.a_ptr = phdr;
        printf("\nAT_PHDR- %#p  \n", phdr);
        break;

      case AT_PHNUM:
        d_aux->a_un.a_val = phdr_num;
        break;

#elif MORELLO
        case AT_CHERI_EXEC_RW_CAP:
        case AT_CHERI_EXEC_RX_CAP:
        case AT_CHERI_INTERP_RW_CAP:
        case AT_CHERI_INTERP_RX_CAP:
        case AT_CHERI_STACK_CAP:
        case AT_CHERI_SEAL_CAP:
        case AT_CHERI_CID_CAP:
        case AT_ARGC:
        case AT_ARGV:
        case AT_ENVC:
        case AT_ENVP:
         {
        d_aux->a_un.a_ptr = s_aux->a_un.a_ptr;
        break;
        }
        case AT_PHDR:
        d_aux->a_un.a_ptr = phdr;
        printf("\nAT_PHDR- %#p  \n", phdr);
        break;

      case AT_PHNUM:
        d_aux->a_un.a_val = phdr_num;
        break;

      case AT_RANDOM: {
        
        stack_strings -= 15;

        memcpy(stack_strings, (void *)s_aux->a_un.a_ptr, 16);
        d_aux->a_un.a_ptr = (uintptr_t)stack_strings;
        stack_strings--;
        break;
      }
      case AT_PLATFORM:
      case AT_EXECFN:
        d_aux->a_un.a_ptr = (uintptr_t)copy_string_to_stack((char *)s_aux->a_un.a_ptr, &stack_strings);
        break;    
    

#else

      case AT_RANDOM: {
        stack_strings -= 15;
        memcpy(stack_strings, (void *)s_aux->a_un.a_val, 16);
        d_aux->a_un.a_val = (uintptr_t)stack_strings;
        stack_strings--;
        break;
      }
      case AT_PLATFORM:
      case AT_EXECFN:
        d_aux->a_un.a_val = (uintptr_t)copy_string_to_stack((char *)s_aux->a_un.a_val, &stack_strings);
        break;    
    
      case AT_PHDR:

      d_aux->a_un.a_val = auxv->at_phdr;
        
        break;

      case AT_PHNUM:
        d_aux->a_un.a_val = auxv->at_phnum;
        break;
      
#endif     
    


      case AT_BASE:
        d_aux->a_un.a_val = auxv->at_base;
        break;

      case AT_ENTRY:
        d_aux->a_un.a_val = auxv->at_entry;
        break;  

      default:
        #ifdef __arm__
          #define auxv_type "%d"
        #elif __aarch64__
          #define auxv_type "%ld"
        #endif
        printf("Unhandled auxv entry type: " auxv_type "\n", s_aux->a_type);
        exit(EXIT_FAILURE);
        break;
    }
    
    s_aux++;
    d_aux++;

    stack_i += 2;
  }
  // End of list
  d_aux->a_type = AT_NULL;
  d_aux->a_un.a_val = 0;
  stack_i += 2;

  /* Stack:
  sp->argc     [LOW]
      argv[0]
      argv[1]
      ...
      argv[x]
      NULL
      envp[0]
      envp[1]
      ...
      envp[y]
      NULL
      auxv[0]
      auxv[1]
      ...
      auxv[z]  [HIGH]
  */
  assert((char *)&stack[stack_i] <= stack_strings);
  printf("\nDBM client entry\n");

  //AA TODO add argv pointer
  //extern void dbm_client_entry(uint argc, uintptr_t * argv ,uintptr_t * envp ,uintptr_t * auxv ,uintptr_t * stack_top, uintptr_t  addr)

  printf( "pre client entry checking \n");
  
  //for(char * temp = *(char *)argv_new; temp != NULL; temp++)
  //{
    printf("string - %s\n", argv_new);
    pp_cap(argv_new);
  //}

  dbm_client_entry(argc + 1,argv_new, envp_new , d_aux_start, &stack[0], entry_address);
  
  // If we return here, something is horribly wrong
  while(1);
}
