# 基于车辆信息识别网络传输与视频流推送

## 第一阶段、实现数据的接收和发送

### TCP网络编程

    1.发送数据
    a、对于字符串类型的数据，通常定义成数组，可以直接利用memcpy函数copy到内存中去，直接发送即可
    b、对于整数或者有多个小数位的浮点数数据，通常定义成int或者float类型的数据，但是此时就需要涉及到机器语言->大端语言的转换，利用htobe64函数
```c
    //数组装载字符串直接发送
    memcpy(buf + offset,p->car_color, COLOR_MAX_LEN);

    //发送时转成大端序后再copy发送
    uint64_t id_be = htobe64(p->student_id);
    memcpy(buf + offset, &id_be, sizeof(id_be));

    //接收时先由大端序转成机器语言后再接收
    uint64_t id_be;
    memcpy(&id_be, buf + offset, sizeof(id_be));
    p->student_id = be64toh(id_be);
```

    2.打包数据
    a.在打包数据过程中使用uint8_t的数组，因为在网络传输过程中，传输的字节流都是二进制数据，所以使用无符号整形数据更加安全和稳定,uint8_t也是和char一样，每个空间存储一个字节








    c语言补充
    a、对于结构体使用指针时候，结构体中如果有数组，那么在使用结构体指针时候就可以直接用在需要指针的函数里面，比如：
```c
    memcpy(buf + offset,p->car_color, COLOR_MAX_LEN);//此处car_color等三个都已经是数组了
```
    b、对于结构体利用sizeof得到的是结构体变量所有的字节数字节数加起来，比如：
```c
    //得到的是message_header_t结构体中所有变量的字节数
    int total_len = payload_len + sizeof(message_header_t);
```

    b、枚举的使用，枚举主要使用在有限个整数代表一些实际的意思中，把数字变成实际的可读文字，便于代码管理
```c



```