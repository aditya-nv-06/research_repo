#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ftrace.h>


//license for the code 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aditya");
MODULE_DESCRIPTION("A simple kernel hello world module for learning");
MODULE_VERSION("0.1");

//init_func
static int  __init start(void){
    // not printf here it is printk and k stands for kernel
    printk(KERN_INFO "Hello World! Kernel Module Loaded.\n");
    return 0;
}

//exit_func (doesn't return anything)
static void __exit stop(void){
    printk(KERN_INFO "Kernel module unloaded.\n");
}

module_init(start);
module_exit(stop);
