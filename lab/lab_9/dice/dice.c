//
// Created by citrate on 11/23/21.
//

#include <linux/module.h>
#include <linux/printk.h>
//TODO: Add necessary header files
#include <linux/random.h>      // get_random_bytes
#include <linux/cdev.h>        // cdev
#include <linux/init.h>        // init
#include <linux/slab.h>        // kmalloc, kfree
#include <linux/uaccess.h>     // copy_to_user
#include <linux/fs.h>          // struct file
#include <linux/export.h>      // THIS_MODULE
#include <asm/uaccess.h>       // access_ok
#include <linux/minmax.h>      // minmax
#include "dice.h"

int dice_major;                /* Major number of dice devices */
int dice_devs = DICE_DEVS;     /* Number of dice devices */
int dice_num = DICE_NUM;       /* Initial number of dice in a device */
int gen_sides = GEN_SIDES;     /* Initial number of sides of `arbitrary` dice game */
struct dice_dev *dice_devices; /* An array of dice device */
struct class *dice_class;      /* Used for class */

static int __init dice_init(void);
static void __exit dice_exit(void);
static int dice_open(struct inode *inode, struct file *filp);
static int dice_release(struct inode *inode, struct file *filp);
static ssize_t dice_read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
static ssize_t dice_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp);

MODULE_DESCRIPTION("Grandpa's Dice");
MODULE_LICENSE("GPL");
module_init(dice_init);
module_exit(dice_exit);
//TODO: Make gen_sides a module parameter

static struct file_operations fops = {
        .read = dice_read,      // reads data from device, to userspace
        .write = dice_write,    // reads data from userspace, to device
        .open = dice_open,
        .release = dice_release,
};

static const char DICE_PATTERN[3][6][12] = {
    {"|     |  ","|     |  ","|  o  |  ","| o o |  ","| o o |  ","| o o |  "},
    {"|  o  |  ","| o o |  ","|     |  ","|     |  ","|  o  |  ","| o o |  "},
    {"|     |  ","|     |  ","| o o |  ","| o o |  ","| o o |  ","| o o |  "}
};

static const char DICE_BACKGAMMON[6][4] = {
    "2","4","8","16","32","64"
};

static int __init dice_init(void) {
    //TODO: Find Major number dynamically
    // Hint: alloc_chrdev_region
    dev_t dev;
    int ret = 0;
    int i = 0;
    ret = alloc_chrdev_region(&dev, 0, dice_devs, "Dice");
    if (ret < 0) {
        printk(KERN_WARNING "Dice: failed to allocate char device numbers\n");
        return ret;
    }
    dice_major = MAJOR(dev);

    //TODO: Allocate memory for dices
    dice_devices = kmalloc(dice_devs * sizeof(struct dice_dev), GFP_KERNEL);

    //TODO: create a class, loop through registering cdev and creating device
    // Hint: class_create, cdev_init, cdev_add, device_create
    if (IS_ERR(dice_class = class_create(THIS_MODULE, "Dice_Class"))) {
        printk(KERN_WARNING "Dice: failed to create class\n");
        return -1;
    }
    for (i = 0; i < DICE_DEVS; i++) {
        struct device *dev_ret;
        dev_t dev_dice = MKDEV(dice_major, i);
        cdev_init(&(dice_devices[i].dice_cdev), &fops);
        dice_devices[i].dice_cdev.owner = THIS_MODULE;
        dice_devices[i].num = dice_num;
        dice_devices[i].num_remain = dice_num;
        dice_devices[i].dice_type = 10+i;
        ret = cdev_add(&(dice_devices[i].dice_cdev), dev_dice, 1);
        if (ret < 0) {
            printk(KERN_WARNING "Dice: failed to add device to system\n");
            return ret;
        }
        if (IS_ERR(dev_ret = device_create(dice_class, NULL, dev_dice, NULL, "dice%d", i))) {
            printk(KERN_WARNING "Dice: failed to create device\n");
            return -1;
        }
    }
    printk(KERN_DEBUG "Dice: module inserted\n");
    return 0;
}

static void __exit dice_exit(void) {
    //TODO: release all resources
    // Hint: Pay attention to the order!
    // Hint: device_destroy, cdev_del, class_destroy, kfree, unregister_chrdev_region
    int i = 0;
    for (i = 0; i < dice_devs; i++) {
        device_destroy(dice_class, MKDEV(dice_major, i));
    }
    for (i = 0; i < dice_devs; i++) {
        cdev_del(&(dice_devices[i].dice_cdev));
    }
    class_destroy(dice_class);
    kfree(dice_devices);
    unregister_chrdev_region(MKDEV(dice_major, 0), dice_devs);
    printk(KERN_DEBUG "Dice: module removed\n");
}

static int dice_open(struct inode *inode, struct file *filp) {
    //TODO: Find which dice is opened
    // Hint: container_of, filp->private_data
    // int dice_minor = MINOR(inode->i_rdev);
    filp->private_data = container_of(inode->i_cdev, struct dice_dev, dice_cdev);
    return 0;
}

static int dice_release(struct inode *inode, struct file *filp) {
    //Do nothing here
    //If you allocate any resource in dice_open(), then you must release them here
    return 0;
}

static ssize_t dice_read(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
    //TODO: Generate dice patterns, generate random number
    // Attention: handle count and offp carefully
    // Hint: copy_to_user
    struct dice_dev *dice = (struct dice_dev *)filp->private_data;
    int i = 0, j = 0;
    // int rd[dice->num];
    int *rd = kmalloc((dice->num) * sizeof(int), GFP_KERNEL);
    int offset = 0;
    char kbuffer[MAX_STR];
    int dice_roll = min(dice->num_remain, 5);
    if (dice->num_remain == 0) {
        dice->num_remain = dice->num;
        return 0;
    }
    dice->num_remain -= dice_roll;
    // printk(KERN_DEBUG "Dice: dice_read called. Num remain: %d.\n", dice->num_remain);

    // generate random numbers...
    for (i = 0; i < dice_roll; i++) {
        get_random_bytes(&rd[i], sizeof(int));
        rd[i] = (rd[i] % 6 + 12) % 6;
    }
    if (dice->dice_type == TYPE_REGULAR) {
        for (i = 0; i < dice_roll; i++) {
            // snprintf: write formatted output to sized buffer
            offset += snprintf(kbuffer + offset, MAX_STR, "-------  ");
        }
        offset += snprintf(kbuffer + offset, MAX_STR, "\n");
        for (j = 0; j < 3; j++) {
            for (i = 0; i < dice_roll; i++) {
                offset += snprintf(kbuffer + offset, MAX_STR, "%s", DICE_PATTERN[j][rd[i]]);
            }
            offset += snprintf(kbuffer + offset, MAX_STR, "\n");
        }
        for (i = 0; i < dice_roll; i++) {
            offset += snprintf(kbuffer + offset, MAX_STR, "-------  ");
        }
        offset += snprintf(kbuffer + offset, MAX_STR, "\n");
    }
    else if (dice->dice_type == TYPE_BACKGAMMON) {
        for (i = 0; i < dice_roll; i++) {
            offset += snprintf(kbuffer + offset, MAX_STR, "%s ", DICE_BACKGAMMON[rd[i]]);
        }
        offset += snprintf(kbuffer + offset, MAX_STR, "\n");
    }
    else if (dice->dice_type == TYPE_GENERIC) {
        for (i = 0; i < dice_roll; i++) {
            offset += snprintf(kbuffer + offset, MAX_STR, "%d ", rd[i]);
        }
        offset += snprintf(kbuffer + offset, MAX_STR, "\n");
    }
    else {
        printk(KERN_NOTICE "Dice: wrong dice type: %d.\n", dice->dice_type);
        kfree(rd);
        return -1;
    }
    if (offset < 0) {
        kfree(rd);
        printk(KERN_NOTICE "Dice: snprintf error.\n");
        return -1;
    }
    if (*offp >= offset || count == 0) {
        printk(KERN_DEBUG "Dice: nothing printed. Read has ended.\n");
        dice->num_remain = dice->num;
        return 0;
    }
    if (*offp + count > offset) {
        count = offset - *offp;
    }
    if (access_ok(buff, count) == 0) {
        printk(KERN_NOTICE "Dice: error accessing user space buffer.\n");
        return -EACCES;
    }
    if (copy_to_user(buff, kbuffer + *offp, count) != 0) {
        printk(KERN_NOTICE "Dice: copy to user error.\n");
        return -EFAULT;
    }
    // *offp += count;
    kfree(rd);
    return count;
}

static ssize_t dice_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp) {
    //TODO: Read in number of dice
    // Attention: handle count and offp carefully
    // Hint: copy_from_user
    struct dice_dev *dice = (struct dice_dev *)(filp->private_data);
    char input_str[10];    // largest int only has 10 characters
    long knum = 0;
    int ret = 0;
    // printk(KERN_DEBUG "Dice: trying to read dice number from user.\n");
    if (count > 10) {
        printk(KERN_NOTICE "Dice: input number too large.\n");
        return -EINVAL;
    }
    if (access_ok(buff, count) == 0) {
        printk(KERN_NOTICE "Dice: error accessing user space buffer.\n");
        return -EACCES;
    }
    if (copy_from_user(input_str+(*offp), buff, count) != 0) {
        printk(KERN_NOTICE "Dice: error copying from user buffer to kernel.\n");
        return -EINVAL;
    }
    *offp += count;
    printk(KERN_DEBUG "Dice: the string from user is: %s.\n", input_str);
    input_str[count-1] = '\0';
    ret = kstrtol(input_str, 10, &knum);
    if (ret == -ERANGE) {
        printk(KERN_NOTICE "Dice: kstrtol overflow.\n");
        return ret;
    }
    if (ret == -EINVAL) {
        printk(KERN_NOTICE "Dice: kstrtol parsing error.\n");
        return ret;
    }
    dice_num = (int) knum;
    dice->num = dice_num;
    dice->num_remain = dice_num;
    return count;
}
