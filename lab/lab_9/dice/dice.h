//
// Created by citrate on 11/23/21.
//

#ifndef DICE_H
#define DICE_H

#define DICE_DEVS 3  /* Number of dice devices */
#define DICE_NUM 2   /* Initial number of dice in a device */
#define GEN_SIDES 20 /* default number of sides of `arbitrary` dice game */

struct dice_dev{
    int num_remain;        /* number of dice not yet rolled */
    int num;               /* number of dice in this device */
    int dice_type;	       /* type of dice game:  regular; backgammon; generic */
    struct cdev dice_cdev; /* cdev object of dice */
};

// dice_type
#define TYPE_REGULAR 10
#define TYPE_BACKGAMMON 11
#define TYPE_GENERIC 12
#define MAX_STR 1024

#endif //DICE_H
