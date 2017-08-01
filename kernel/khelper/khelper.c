#include <linux/module.h>  
#include <linux/types.h>  
#include <linux/fs.h>  
#include <linux/errno.h>  
#include <linux/mm.h>  
#include <linux/sched.h>  
#include <linux/init.h>  
#include <linux/cdev.h>  
#include <asm/io.h>  
#include <asm/uaccess.h>  
#include <linux/slab.h>  
  
#define KHELPER_SIZE  0x1000 
#define MEM_CLEAR 0x1
#define KHELPER_MAJOR 200 
  
  
static int khelper_major = KHELPER_MAJOR;  

struct khelper_dev                                       
{                                                          
  struct cdev cdev;
  unsigned char mem[KHELPER_SIZE];
};  
  
  
struct khelper_dev *khelper_devp;

int khelper_open(struct inode *inode, struct file *filp)  
{  
  filp->private_data = khelper_devp;  
  return 0;  
}  

int khelper_release(struct inode *inode, struct file *filp)  
{  
  return 0;  
}  
  
static int khelper_ioctl(struct inode *inodep, struct file *filp, unsigned  
  int cmd, unsigned long arg)  
{  
  struct khelper_dev *dev = filp->private_data;
  
  
  switch (cmd)  
  {  
    case MEM_CLEAR:  
      memset(dev->mem, 0, KHELPER_SIZE);        
      printk(KERN_INFO "khelper is set to zero\n");  
      break;  
    default:  
      return  - EINVAL;  
  }  
  return 0;  
}  
  
static ssize_t khelper_read(struct file *filp, char __user *buf, size_t size,  
  loff_t *ppos)  
{  
  unsigned long p =  *ppos;
  unsigned int count = size;
  int ret = 0;  
  struct khelper_dev *dev = filp->private_data;
  
  printk(KERN_INFO "enter %s\n", __func__);

  if (p >= KHELPER_SIZE)  
    return count ?  - ENXIO: 0;  
  if (count > KHELPER_SIZE - p)
    count = KHELPER_SIZE - p;  
  
  if (copy_to_user(buf, (void*)(dev->mem + p), count))  
  {  
    ret =  - EFAULT;  
  }  
  else
  {
    *ppos += count;  
    ret = count;  
      
    printk(KERN_INFO "read %d bytes(s) from %d\n", count, p);  
  }  
  
  return ret;  
}  
  
static ssize_t khelper_write(struct file *filp, const char __user *buf,  
  size_t size, loff_t *ppos)  
{  
  unsigned long p =  *ppos;  
  unsigned int count = size;  
  int ret = 0;  
  struct khelper_dev *dev = filp->private_data;
    
  printk(KERN_INFO "enter %s\n", __func__);

  if (p >= KHELPER_SIZE)  
    return count ?  - ENXIO: 0;  
  if (count > KHELPER_SIZE - p)  
    count = KHELPER_SIZE - p;  
      
  if (copy_from_user(dev->mem + p, buf, count))  
    ret =  - EFAULT;  
  else  
  {  
    *ppos += count;  
    ret = count;  
      
    printk(KERN_INFO "written %d bytes(s) from %d\n", count, p);  
  }  
  
  return ret;  
}  
  
static loff_t khelper_llseek(struct file *filp, loff_t offset, int orig)  
{  
  loff_t ret = 0;  
  switch (orig)  
  {  
    case 0:
      if (offset < 0)  
      {  
        ret =  - EINVAL;  
        break;  
      }  
      if ((unsigned int)offset > KHELPER_SIZE)  
      {  
        ret =  - EINVAL;  
        break;  
      }  
      filp->f_pos = (unsigned int)offset;  
      ret = filp->f_pos;  
      break;  
    case 1:
      if ((filp->f_pos + offset) > KHELPER_SIZE)  
      {  
        ret =  - EINVAL;  
        break;  
      }  
      if ((filp->f_pos + offset) < 0)  
      {  
        ret =  - EINVAL;  
        break;  
      }  
      filp->f_pos += offset;  
      ret = filp->f_pos;  
      break;  
    default:  
      ret =  - EINVAL;  
      break;  
  }  
  return ret;  
}  
  
static const struct file_operations khelper_fops =  
{  
  .owner = THIS_MODULE,  
  .llseek = khelper_llseek,  
  .read = khelper_read,  
  .write = khelper_write,  
  /* .ioctl = khelper_ioctl,  */
  .open = khelper_open,  
  .release = khelper_release,  
};  
  
static void khelper_setup_cdev(struct khelper_dev *dev, int index)
{  
  int err, devno = MKDEV(khelper_major, index);
  
  cdev_init(&dev->cdev, &khelper_fops);
  dev->cdev.owner = THIS_MODULE;  
  dev->cdev.ops = &khelper_fops;  
  err = cdev_add(&dev->cdev, devno, 1);
  if (err)  
    printk(KERN_NOTICE "Error %d adding LED%d", err, index);  
}  
  
int khelper_init(void)  
{  
  int result;  
  dev_t devno = MKDEV(khelper_major, 0);  
  
  if (khelper_major)  
    result = register_chrdev_region(devno, 1, "khelper");  
  else
  {  
    result = alloc_chrdev_region(&devno, 0, 1, "khelper");  
    khelper_major = MAJOR(devno);  
  }    
  if (result < 0)  
    return result;  
      
  khelper_devp = kmalloc(sizeof(struct khelper_dev), GFP_KERNEL);  
  if (!khelper_devp)
  {  
    result =  - ENOMEM;  
    goto fail_malloc;  
  }  
  memset(khelper_devp, 0, sizeof(struct khelper_dev));  
    
  khelper_setup_cdev(khelper_devp, 0);
  return 0;  
  
fail_malloc: 
  unregister_chrdev_region(devno, 1);  
  return result;  
}  
  
void khelper_exit(void)  
{  
  cdev_del(&khelper_devp->cdev);
  kfree(khelper_devp);
  unregister_chrdev_region(MKDEV(khelper_major, 0), 1);
}  
  
MODULE_AUTHOR("wuxx");  
MODULE_LICENSE("Dual BSD/GPL");  
  
module_param(khelper_major, int, S_IRUGO);  
module_init(khelper_init);
module_exit(khelper_exit);
