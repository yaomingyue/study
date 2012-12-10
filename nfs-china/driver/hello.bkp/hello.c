#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/tty.h>
#include <linux/tty_driver.h>
#include <linux/tty_flip.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/uaccess.h>
#include <asm/atomic.h>
#include <linux/usb.h>
#include <linux/usb/serial.h>

#define DEV_MAJOR 96
#define DEV_NAME "hello"

MODULE_LICENSE("Dual BSD/GPL");

static ssize_t hello_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
    return 1;
}
struct file_operations hello_fops = {
.owner = THIS_MODULE,
.read = hello_read,
};
static int hello_init(void)
{
    const int result = 0;
    const int scull_major = 0;
    const int scull_nr_devs = 0;

    //register_chrdev( 96, ”hello”, &scull_fops );
    //result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs,"scull");
   if(register_chrdev(DEV_MAJOR, DEV_NAME, &hello_fops)) {
   printk(DEV_NAME":register major failed. \r\n");
   return -1;
   }
   //devfs_mk_cdev(MKDEV(DEV_MAJOR, 0),S_IFCHR | S_IRUSR | S_IWUSR | S_IRGRP, DEV_NAME);

   printk(KERN_ALERT "yaomoon!\n");
   return 0;
}

static void hello_exit(void)
{
    unregister_chrdev(96,DEV_NAME);
    printk(KERN_ALERT "goodbye!\n");
}

module_init(hello_init);
module_exit(hello_exit);
