#ifndef PAGEDIR_H
#define PAGEDIR_H

#define PDE_P_MASK     0x00000001
#define PDE_RW_MASK    0x00000002
#define PDE_US_MASK    0x00000004
#define PDE_PWT_MASK   0x00000008
#define PDE_PCD_MASK   0x00000010
#define PDE_A_MASK     0x00000020
#define PDE_AVL1_MASK  0x00000040
#define PDE_PS_MASK    0x00000080
#define PDE_AVL2_MASK  0x00000F00
#define PDE_ADDR_MASK  0xFFFFF000

typedef uint32_t PDE_t;

#define PGE_P_MASK     0x00000001
#define PGE_RW_MASK    0x00000002
#define PGE_US_MASK    0x00000004
#define PGE_PWT_MASK   0x00000008
#define PGE_PCD_MASK   0x00000010
#define PGE_A_MASK     0x00000020
#define PGE_D_MASK     0x00000040
#define PGE_PAT_MASK   0x00000080
#define PGE_G_MASK     0x00000100
#define PGE_AVL_MASK   0x00000E00
#define PGE_ADDR_MASK  0xFFFFF000

typedef uint32_t PGE_t;

#define GET_PDE_ADDR(pde)    ((pde) & PDE_ADDR_MASK)
#define SET_PDE_ADDR(pde, addr) \
    ((pde) = ((pde) & ~PDE_ADDR_MASK) | ((addr) & PDE_ADDR_MASK))

#define GET_PGE_ADDR(pge)    ((pge) & PGE_ADDR_MASK)
#define SET_PGE_ADDR(pge, addr) \
    ((pge) = ((pge) & ~PGE_ADDR_MASK) | ((addr) & PGE_ADDR_MASK))

#define SET_FLAG(val, mask)   ((val) |= (mask))
#define CLEAR_FLAG(val, mask) ((val) &= ~(mask))
#define TEST_FLAG(val, mask)  (((val) & (mask)) != 0)

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
    PDE_t entry = 0;

    SET_FLAG(entry, PDE_P_MASK);
    SET_FLAG(entry, PDE_RW_MASK);
    SET_PDE_ADDR(entry, (uint32_t)table);

    (*dir)[index] = entry;
}

void map_pagetableentry(pagetable_t* table, uint32_t index) {
    PGE_t entry = 0;

    SET_FLAG(entry, PGE_P_MASK);
    SET_FLAG(entry, PGE_RW_MASK);
    SET_PGE_ADDR(entry, next_free);

    next_free += 0x1000;
    (*table)[index] = entry;
}
void* alloc(){
    void* page = (void *)PAGE_ALIGN(next_free);
    memset(page, 0, 4096);
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
