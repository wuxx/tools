/*                                                     
 * $Id: hello.c,v 1.5 2004/10/26 03:32:21 corbet Exp $ 
 * The code samples are covered by a dual BSD/GPL license from
 * Linux Device Drivers, Third Edition, by Jonathan Corbet, 
 * Alessanfdro Rubini, and Greg Kroah-Hartman.Copyright
 * 2005 O’Reilly Media, Inc., 0-596-00590-3.
 */                                                    
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
	printk(KERN_ALERT "Hello, world\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
