## A Dice Character Device

## Usage

A simple test script is included. Be sure to run the test script under `su` mode, otherwise we could not change the number of the dice...

To tun the script...

```shell
su
# input password correctly
# we are not trying to steal your password :)
./test.sh
```

The script will make clean, make all, insmod, then roll the regular dice (2 dices, 8 dices, 10 dices and 30 dices). Then roll backgammon dice, and generic dice (2 dices in both cases). Finally rmmod, print the debug messages and make clean. You are welcome to make changes to the script to do more testing.

## Implementation of the Dice Device

The dice is implemented through a character device. We used the Linux Kernel API for character device driver, using the following steps:

- Fill in `struct file_operations` as desired:

  ```C
  static int dice_open(struct inode *inode, struct file *filp);
  static int dice_release(struct inode *inode, struct file *filp);
  static ssize_t dice_read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
  static ssize_t dice_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp);
  ```

  - **read**
    - such that we can `cat` (read) from the device, asking it to generate dice results;
  - **write**
    - such that we can `echo $number` (write )to the device, asking it to change dice numbers;
  - In particular, the struct `cdev` is stored in the `struct inode`, therefore the read write operation could not tell which device it is. To deal with this:
    - in **dice_open**, store the entire `dice_dev`  structure under the `void * private_data` under `file *filp`
    - The dice_dev structure can be obtained with a `inode *inode`, using the Macro `container_of`

- Allocate Major & Minor for the device (dynamically), `alloc_chrdev_region`
- Create a class `class_create`
- Initialize the three devices and register them; `cdev_init`, `cdev_add`
- In `dice_exit`, dis-allocate and destroy everything about the device in reverse order



References:
- cyc lab
- https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html