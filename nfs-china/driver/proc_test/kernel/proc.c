 /*This program is used to allocate memory in kernel
 and pass the physical address to userspace through proc file.*/

#include <linux/version.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/mm.h>


#define PROC_MEMSHARE_DIR "memshare"
#define PROC_MEMSHARE_PHYADDR "phymem_addr"
#define PROC_MEMSHARE_SIZE "phymem_size"


/*alloc one page. 4096 bytes*/
#define PAGE_ORDER 0
/*this value can get from PAGE_ORDER*/
#define PAGES_NUMBER 1


struct proc_dir_entry *proc_memshare_dir ;
unsigned long kernel_memaddr = 0;
unsigned long kernel_memsize= 0;


static int proc_read_phymem_addr(char *page, char **start, off_t off, int count)
{
        return sprintf(page, "%08lx\n", __pa(kernel_memaddr));
}
static int proc_read_phymem_size(char *page, char **start, off_t off, int count)
{
        return sprintf(page, "%lu\n", kernel_memsize);
}


 static int __init init(void)
 {
         /*build proc dir "memshare"and two proc files: phymem_addr, phymem_size in the dir*/
          proc_memshare_dir = proc_mkdir(PROC_MEMSHARE_DIR, NULL);
          create_proc_read_entry(PROC_MEMSHARE_PHYADDR, 0, proc_memshare_dir, proc_read_phymem_addr,NULL);
          create_proc_read_entry(PROC_MEMSHARE_SIZE, 0, proc_memshare_dir, proc_read_phymem_size,NULL);
 

          /*alloc one page*/
           kernel_memaddr =__get_free_pages(GFP_KERNEL, PAGE_ORDER);
          if(!kernel_memaddr)
          {
                 printk("Allocate memory failure!\n");
         }
         else
         {
                  SetPageReserved(virt_to_page(kernel_memaddr));


// 内核中申请到页面之后，要调用一下SetPageReserved，相当于告诉系统，这个页面我已经占了。对于每一个申请到的页面，应该都要这样做


             kernel_memsize = PAGES_NUMBER * PAGE_SIZE;
             printk("Allocate memory success!. The phy mem addr=%08lx, size=%lu\n", __pa(kernel_memaddr), kernel_memsize);
      }
      return 0;
}


static void __exit fini(void)
{
          printk("The content written by user is: %s\n", (unsigned char *) kernel_memaddr);
          ClearPageReserved(virt_to_page(kernel_memaddr));
          free_pages(kernel_memaddr, PAGE_ORDER);
          remove_proc_entry(PROC_MEMSHARE_PHYADDR, proc_memshare_dir);
          remove_proc_entry(PROC_MEMSHARE_SIZE, proc_memshare_dir);
          remove_proc_entry(PROC_MEMSHARE_DIR, NULL);


         return;
}
module_init(init);
module_exit(fini);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Godbach ([email]nylzhaowei@163.com[/email])");
MODULE_DESCRIPTION("Kernel memory share module.");
