/* I2C client example */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/i2c.h>

#define I2C_BUS			(1)
#define I2C_SLAVE_NAME		"ads1115"
#define I2C_SLAVE_ADDR		(0x48)

static struct i2c_adapter *my_i2c_adapter = NULL;
static struct i2c_client *my_i2c_client = NULL;

static const struct i2c_device_id my_i2c_table[] = {
	{ I2C_SLAVE_NAME, 0 },
	{}
};
MODULE_DEVICE_TABLE(i2c, my_i2c_table);

// protos
static int my_i2c_write(char *buf, unsigned int len);
static int my_i2c_read(char *buf, unsigned int len);

static int my_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	pr_info("In %s\n", __func__);
	return 0;
}

static void get_readings(void)
{
	char wbuf[3] = {0};
	char rbuf[2] = {0};
	int nwrite, nread;
	uint16_t val = 0;

	pr_info("In %s\n", __func__);

	wbuf[0] = 1;
	wbuf[1] = 0b11010101;
	wbuf[2] = 0b10000101;

	nwrite = my_i2c_write(wbuf, 3);
	if (nwrite != 3)
	{
		pr_err("nwrite=%d, error in i2c_write for config!\n", nwrite);
		//return;
	}

	msleep(5000);

	nwrite = my_i2c_write(rbuf, 1);
	if (nwrite != 1)
	{
		pr_err("Error in i2c_write for reg select!\n");
		return;
	}

	nread = my_i2c_read(rbuf, 2);
	if (nread != 2)
	{
		pr_err("Error in i2c_read for data!\n");
		return;
	}	

	val = rbuf[0] << 8 | rbuf[1];
	pr_info("Val = %d\n", val);
}

static int my_i2c_remove(struct i2c_client *client)
{
	pr_info("In %s\n", __func__);
	return 0;
}

static int my_i2c_write(char *buf, unsigned int len)
{
	int ret = i2c_master_send(my_i2c_client, buf, len);

	return ret;
}

static int my_i2c_read(char *buf, unsigned int len)
{
	int ret = i2c_master_recv(my_i2c_client, buf, len);

	return ret;
}

static struct i2c_driver my_i2c_driver = 
{
	.driver = 
	{
		.name = I2C_SLAVE_NAME,
		.owner = THIS_MODULE,
	},
	.probe = my_i2c_probe,
	.remove = my_i2c_remove,
	.id_table = my_i2c_table
};

static struct i2c_board_info my_i2c_board_info = 
{
	I2C_BOARD_INFO(I2C_SLAVE_NAME, I2C_SLAVE_ADDR)
};

static int __init my_init(void){
   int result = -1;

   my_i2c_adapter = i2c_get_adapter(I2C_BUS);
   if (IS_ERR(my_i2c_adapter))
   {
	   pr_err("i2c adapter error: %ld\n", PTR_ERR(my_i2c_adapter));
	   return result;
   }
   pr_info("Got i2c adapter for i2c bus: %d!\n", I2C_BUS);
   
   my_i2c_client = i2c_new_client_device(my_i2c_adapter, &my_i2c_board_info);

   if (IS_ERR(my_i2c_client))
   {
	pr_err("i2c client error: %ld!\n", PTR_ERR(my_i2c_client));
	return result;
   }
   
   pr_info("Got i2c device!\n");
   i2c_add_driver(&my_i2c_driver);
   result = 0;

   i2c_put_adapter(my_i2c_adapter);

   pr_info("i2c Device added!\n");

   msleep(5000);

   get_readings();

   return result;
}

static void __exit my_exit(void)
{
   i2c_unregister_device(my_i2c_client);
   i2c_del_driver(&my_i2c_driver);
   pr_info("Good bye from %s!\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("I2C client example");
