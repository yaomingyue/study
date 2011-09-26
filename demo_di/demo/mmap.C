/*****************************************************************************
*  [Function Name]	static int adc_mmap( struct file *file,
*												  struct vm_area_struct * vma)
*
*  [Description]   	The routine implements mmap system call for mapping memory.
*
*  [Parameters]	   	flip:  <IN>  file structure of the device file
*					buf :  <IN>  Pointer to a virtual memory area which
*								  include mapping information.
*
*  [Return]			   0:   Map memory successfully.
*					  <0: 	Error occured.
*
*  [Note]
******************************************************************************/
static int adc_mmap(struct file *file, struct vm_area_struct * vma)
{
	unsigned long start; /* 起始物理地址 */
	unsigned long off;   /* 结束物理地址 */
	unsigned long len;   /* 地址长度 */

	DBG_PRINTK("vma->vm_start is %lx\n", vma->vm_start);
	DBG_PRINTK("vma->vm_end is %lx\n", vma->vm_end);
	DBG_PRINTK("vma->vm_end-vma->vm_start is %lx\n", vma->vm_end-vma->vm_start);
	DBG_PRINTK("vma->vm_pgoff is %lx\n",vma->vm_pgoff);

	/* Get semphore of mmap operation */
	if(down_interruptible(&g_p_adc_module->mmap_sem))
	{
		/* get semphore unsuccessfully */
		return -ERESTARTSYS;
	}

	/* Check parameter */
	/*检查页边界地址是否超出最大可能范围 */
	if (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
	{
		DBG_PRINTK("page number exceed the range of virtual address space.\n");
		up(&g_p_adc_module->mmap_sem);
		return -EINVAL;
	}

	/* Get page number of physical memory to be mapped */
	/* 获得偏移地址的页起始地址*/
	off = vma->vm_pgoff << PAGE_SHIFT;

	/* Set memory mapping address */
	/* 将起始地址设置为设备的起始物理地址*/
	start = ADC_MMAP_ADDR;

	/* Page align for getting length to be mapped */
	/* 将结束地址在页边界对齐 */
	len = PAGE_ALIGN((start & ~PAGE_MASK) + ADC_MEM_USE);
  /* 检查申请的地址长度是否超出允许影射的范围 */
	if((vma->vm_end - vma->vm_start + off) > len)
	{
		DBG_PRINTK("memory mapping length requested by application exceed the range.\n");
		up(&g_p_adc_module->mmap_sem);
		return -EINVAL;
	}

	/* Page align */
	/* 将起始地址在页边界取齐 */
	start &= PAGE_MASK;

	/* Get the start address of physical memory to be mapped */
  /* 获得结束物理地址 */
	off += start;

	/* Get page number of physical memory to be mapped */
	/* 将结束物理地址转换为页地址*/
	vma->vm_pgoff = off >> PAGE_SHIFT;

	/* Map memory to user space */
	/* 影射 */
	if(remap_pfn_range(vma,
			    		vma->vm_start,
			    		vma->vm_pgoff,
			    		vma->vm_end - vma->vm_start,
			    		vma->vm_page_prot))
	{
		DBG_PRINTK("map memory unsuccessfully.\n");
		up(&g_p_adc_module->mmap_sem);
		return -EAGAIN;
	}

	/* Get the size of ring buffer */
	g_p_adc_module->buffer_size = ADC_BUFFER_SIZE;

	/* Release the semaphore */
	up(&g_p_adc_module->mmap_sem);

	DBG_PRINTK("map memory successfully.\n");

	return 0;
}
