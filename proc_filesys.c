#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/version.h>

#define BUFFSIZE 100
#define AUTHOR "Rango"
MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);

static int uuid = 0;
module_param(uuid, int, 0);
#define MAX_SIZE 100;
static char data[MAX_SIZE];


static struct proc_dir_entry *test_proc_entry;
static struct proc_dir_entry *test_proc_entry2;
static struct proc_dir_entry *proc_parent;


static ssize_t read_fn(struct file *file, char __user *ubuf, size_t count, loff_t *ppos);
static ssize_t write_fn(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos);


/*function pointers to funcitons needed to be called when a read/write is called on specific file*/
static struct proc_ops test_procfs = {
	.proc_read = read_fn,
	.proc_write = write_fn,
};

//store data read in array 'data'
static ssize_t read_fn(struct file *file, char __user *ubuf, size_t count, loff_t *ppos){

	int length = 0;
	length = sprintf(ubuf, "\n %s\n ", data);
	return length;

}

//TODO- not sure how to accept data from user and put into array called 'data'
static ssize_t write_fn(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos){
	if(count > MAX_SIZE){
		count = MAX_SIZE;
	}
	
	return count;
}



void create_new_proc_entry(void){
	proc_parent = proc_mkdir("cse330", NULL);	//create new directory 
	test_proc_entry = proc_create("identity", 0666, proc_parent, &test_procfs);
	test_proc_entry2 = proc_create("statistics", 0666, proc_parent, &test_procfs);
	
}


static int __init initialize(void){
	create_new_proc_entry();
	return 0;
}

static void __exit clean_exit(void){
	remove_proc_entry("statistics", proc_parent);
	remove_proc_entry("identity", proc_parent);
	remove_proc_entry("cse330", NULL);
}

module_init(initialize);
module_exit(clean_exit);
