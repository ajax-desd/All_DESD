/* I2C client example */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/i2c.h>

#define I2C_BUS			(3)
#define I2C_SLAVE_NAME		"my_i2c_stub"
#define I2C_SLAVE_ADDR		(0x25)
#define I2C_SLAVE_REG		(0x0)

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
	char buf= 'Z';

	pr_info("In %s\n", __func__);

	// i2c-stub only supports SMBUS xfers now!
	buf = i2c_smbus_read_byte_data(client, I2C_SLAVE_REG);
	pr_info("Value read from slave = %c\n", buf);

	return 0;
}

static int my_i2c_remove(struct i2c_client *client)
{
	pr_info("In %s\n", __func__);

	return 0;
}

static int __maybe_unused my_i2c_write(char *buf, unsigned int len)
{
	int ret = i2c_master_send(my_i2c_client, buf, len);

	return ret;
}

static int __maybe_unused my_i2c_read(char *buf, unsigned int len)
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
	pr_err("i2c client handle error: %ld!\n", PTR_ERR(my_i2c_client));
	return result;
   }
   result = 0;

   pr_info("Got i2c client handle!\n");

   // this will call the probe()
   i2c_add_driver(&my_i2c_driver);

   // reduce ref count for adapter
   i2c_put_adapter(my_i2c_adapter);

   pr_info("i2c slave device added!\n");

   return result;
}

static void __exit my_exit(void)
{
   i2c_unregister_device(my_i2c_client);
   pr_info("i2c client unregistered!\n");

   i2c_del_driver(&my_i2c_driver);
   pr_info("i2c_driver deleted!\n");

   pr_info("Good bye from %s!\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC EDD <edd@cdac.gov.in>");
MODULE_DESCRIPTION("I2C client example");
