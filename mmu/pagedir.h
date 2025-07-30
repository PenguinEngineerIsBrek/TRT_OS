#ifndef PAGEDIR_H
#define PAGEDIR_H
typedef union PDE_t {
    uint32_t value;
    struct{
        uint32_t P : 1;
        uint32_t RW : 1;
        uint32_t US : 1;
        uint32_t PWT : 1;
        uint32_t PCD : 1;
        uint32_t A : 1;
        uint32_t AVL1 : 1;
        uint32_t PS : 1;
        uint32_t AVL2 : 4;
        uint32_t ADDR : 20;
   } __attribute__((packed));
} PDE_t;

typedef union PGE_t {
    uint32_t value;
    struct{
        uint32_t P : 1;
        uint32_t RW : 1;
        uint32_t US : 1;
        uint32_t PWT : 1;
        uint32_t PCD : 1;
        uint32_t A : 1;
        uint32_t D : 1;
        uint32_t PAT : 1;
        uint32_t G : 1;
        uint32_t AVL : 3;
        uint32_t ADDR : 20;
    } __attribute__((packed));
} PGE_t;

typedef PDE_t pagedir_t[1024] __attribute__((aligned(4096)));
typedef PGE_t pagetable_t[1024] __attribute__((aligned(4096)));

#define PAGE_ALIGN(addr) ((addr + 4096 - 1) & ~(4096 - 1))

pagedir_t pagedir;
pagetable_t* pagetable;
uint32_t next_free = 0x0000;
uint32_t offset = 0x0000;
void init_paging(){
    asm volatile(
            "mov %0, %%cr3\n"
            "mov %%cr0, %%eax\n"
            "or $0x80000000, %%eax\n"
            "mov %%eax, %%cr0\n"
            : 
            : "r"(&pagedir)
            : "eax"
     );
}

void map_pagedirentry(pagedir_t* dir, uint32_t index, pagetable_t* table) {
    (*dir)[index].value = 0;
    (*dir)[index].P = 1;
    (*dir)[index].RW = 1;
    (*dir)[index].US = 0;
    (*dir)[index].ADDR = ((uint32_t)table) >> 12;
}
void map_pagetableentry(pagetable_t* table, uint32_t index) {
    (*table)[index].value = 0;
    (*table)[index].P = 1;
    (*table)[index].RW = 1;
    (*table)[index].US = 0;
    (*table)[index].ADDR = (next_free) >> 12;
    next_free += 0x1000;
}

void* alloc(){
    void* page = (void *)PAGE_ALIGN(next_free);
    return page;
}

void* allocpagetable(){
    pagetable = (pagetable_t*)alloc();
    for(int i = 0; i < 1024; i++){
        map_pagetableentry(pagetable, i);
    }
    return pagetable;
}

#endif
