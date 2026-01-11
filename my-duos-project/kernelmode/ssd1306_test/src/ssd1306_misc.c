#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/types.h>

#include "ssd1306.h"
#include "ssd1306_misc.h"

static int ssd1306_misc_open(struct inode *inode, struct file *file) {
    struct miscdevice *mdev = file->private_data;
    struct ssd1306_data *data;

    if (!mdev)
        return -ENODEV;

    data = container_of(mdev, struct ssd1306_data, miscdev);
    file->private_data = data;

    return 0;
}

static ssize_t ssd1306_misc_write(struct file *file, const char __user *buf,
                                  size_t count, loff_t *ppos) {
    struct ssd1306_data *data = file->private_data;
    u8 *kbuf;
    int ret;

    if (!data || !data->client)
        return -ENODEV;

    if (count == 0)
        return 0;

    /*
     * 强烈建议：整屏刷新只接受 1024 字节
     * （避免你觉得“显示不完整”：写入不足时其余区域仍是旧内容）
     */
    if (count != SSD1306_FB_SIZE)
        return -EINVAL;

    kbuf = memdup_user(buf, count);
    if (IS_ERR(kbuf))
        return PTR_ERR(kbuf);

    mutex_lock(&data->lock);

    ret = ssd1306_set_full_window(data->client);
    if (!ret)
        ret = ssd1306_write_data_buf(data->client, kbuf, count);

    mutex_unlock(&data->lock);

    kfree(kbuf);

    if (ret)
        return ret;

    return count;
}

static const struct file_operations ssd1306_misc_fops = {
    .owner = THIS_MODULE,
    .open = ssd1306_misc_open,
    .write = ssd1306_misc_write,
    .llseek = no_llseek,
};

int ssd1306_misc_register(struct ssd1306_data *data) {
    int ret;

    if (!data || !data->client)
        return -EINVAL;

    data->miscdev.minor = MISC_DYNAMIC_MINOR;
    data->miscdev.name = SSD1306_NAME;
    data->miscdev.fops = &ssd1306_misc_fops;
    data->miscdev.parent = &data->client->dev;

    ret = misc_register(&data->miscdev);
    if (ret)
        dev_err(&data->client->dev, "misc_register failed: %d\n", ret);
    else
        dev_info(&data->client->dev, "misc ready: /dev/%s\n", SSD1306_NAME);

    return ret;
}

void ssd1306_misc_deregister(struct ssd1306_data *data) {
    if (!data)
        return;

    misc_deregister(&data->miscdev);
}
