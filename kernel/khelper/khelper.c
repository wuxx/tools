/*                                                     
 * $Id: hello.c,v 1.5 2004/10/26 03:32:21 corbet Exp $ 
 * The code samples are covered by a dual BSD/GPL license from
 * Linux Device Drivers, Third Edition, by Jonathan Corbet, 
 * Alessanfdro Rubini, and Greg Kroah-Hartman.Copyright
 * 2005 O’Reilly Media, Inc., 0-596-00590-3.
 */                                                    
#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wuxx");
MODULE_DESCRIPTION("kernel helper tool");

static int reverse_open(struct inode *inode, struct file *file)
{
#if 0
    int err = 0;
    file->private_data = buffer_alloc(buffer_size);
    return err;
#endif
    return 0;
}

static struct file_operations khelper_fops = {
    .owner = THIS_MODULE,
    .open = reverse_open,
};

static struct miscdevice khelper_misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "khelper",
    .fops = &khelper_fops
};

static int khelper_init(void)
{
	printk(KERN_ALERT "Hello, world\n");
	//misc_register(&khelper_misc_device);
	return 0;
}

static void khelper_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(khelper_init);
module_exit(khelper_exit);
