/*
 * tuxctl-ioctl.c
 *
 * Driver (skeleton) for the mp2 tuxcontrollers for ECE391 at UIUC.
 *
 * Mark Murphy 2006
 * Andrew Ofisher 2007
 * Steve Lumetta 12-13 Sep 2009
 * Puskar Naha 2013
 */

#include <asm/current.h>
#include <asm/uaccess.h>

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/file.h>
#include <linux/miscdevice.h>
#include <linux/kdev_t.h>
#include <linux/tty.h>
#include <linux/spinlock.h>

#include "tuxctl-ld.h"
#include "tuxctl-ioctl.h"
#include "mtcp.h"

#define debug(str, ...) printk(KERN_DEBUG "%s: " str, __FUNCTION__, ## __VA_ARGS__)


/************************ Protocol Implementation *************************/

/* tuxctl_handle_packet()
 * IMPORTANT : Read the header for tuxctl_ldisc_data_callback() in
 * tuxctl-ld.c. It calls this function, so all warnings there apply
 * here as well.
 */


//spin lock 
static spinlock_t lock = SPIN_LOCK_UNLOCKED;
unsigned long flags;

//shared variables
static int dispNum, LEDIndicator, decimalPt;
static char buffer[20];


void tuxctl_handle_packet (struct tty_struct* tty, unsigned char* packet) {
    unsigned a, b, c;

    a = packet[0]; /* Avoid printk() sign extending the 8-bit */
    b = packet[1]; /* values when printing them. */
    c = packet[2];

    /*printk("packet : %x %x %x\n", a, b, c); */
}

/******** IMPORTANT NOTE: READ THIS BEFORE IMPLEMENTING THE IOCTLS ************
 *                                                                            *
 * The ioctls should not spend any time waiting for responses to the commands *
 * they send to the controller. The data is sent over the serial line at      *
 * 9600 BAUD. At this rate, a byte takes approximately 1 millisecond to       *
 * transmit; this means that there will be about 9 milliseconds between       *
 * the time you request that the low-level serial driver send the             *
 * 6-byte SET_LEDS packet and the time the 3-byte ACK packet finishes         *
 * arriving. This is far too long a time for a system call to take. The       *
 * ioctls should return immediately with success if their parameters are      *
 * valid.                                                                     *
 *                                                                            *
 ******************************************************************************/
//call tuxct_ioctl in input.c
// provide args correctly
//


int tuxctl_ioctl(struct tty_struct* tty, struct file* file,
                 unsigned cmd, unsigned long arg) {
    switch (cmd) {
        case TUX_INIT:
          tux_init_()
          return;
        case TUX_BUTTONS:
          tux_buttons_(arg);
          return;
        case TUX_SET_LED:
          tux_set_LED_()
          return;
        default:
            return -EINVAL;
    }
}

void tux_init_(){

}

void tux_buttons_(){

}

void tux_set_LED_(struct tty_struct* tty, unsigned long arg){
  int dispNumBitmask, LEDIndicatorBitmask, decimalPtBitmask;


  spin_lock_irqsave(lock, flags);    //spinlock

  dispNumBitmask = 0xFFFF;  //low 16 bits
  LEDIndicatorBitmask = 0xF0000;  //low bits on third byte [21:17]
  decimalPtBitmask = 0xF000000;  //low 4 bits on highest byte [27:14]


  dispNum = arg && dispNumBitmask;
  LEDIndicator = arg && LEDIndicatorBitmask;
  decimalPtBitmast = arg && decimalPtBitmask;
  
  spin_unlock_irqrestore(lock, flags);
 
	
  tuxctl_ldisc_put(tty,

  





}
