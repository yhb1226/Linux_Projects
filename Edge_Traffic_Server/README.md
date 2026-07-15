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

    c、存储方式的选择
    1.无序数组：存储快，查找费劲
```c
    #include <stdio.h>
#include <string.h>

#define MAX_CARS 100
#define PLATE_LEN 20

typedef struct {
    char plate[PLATE_LEN];
    char owner[50];
    int  parked_hours;
} Car;

Car parking_lot[MAX_CARS];
int car_count = 0;

int add_car(const char *plate, const char *owner, int hours) {
    if (car_count >= MAX_CARS) return -1;
    strncpy(parking_lot[car_count].plate, plate, PLATE_LEN-1);
    strncpy(parking_lot[car_count].owner, owner, 49);
    parking_lot[car_count].parked_hours = hours;
    car_count++;
    return 0;
}

int find_car(const char *plate) {
    for (int i = 0; i < car_count; i++) {
        if (strcmp(parking_lot[i].plate, plate) == 0)
            return i;
    }
    return -1;
}

int delete_car(const char *plate) {
    int pos = find_car(plate);
    if (pos == -1) return -1;
    if (pos != car_count - 1) {
        parking_lot[pos] = parking_lot[car_count - 1];
    }
    car_count--;
    return 0;
}

void print_all() {
    printf("当前停车场有 %d 辆车:\n", car_count);
    for (int i = 0; i < car_count; i++) {
        printf("[%d] 车牌:%s  车主:%s  已停:%d 小时\n",
               i, parking_lot[i].plate,
               parking_lot[i].owner,
               parking_lot[i].parked_hours);
    }
    printf("\n");
}

int main() {
    add_car("京A12345", "张三", 2);
    add_car("沪B67890", "李四", 5);
    add_car("粤C99999", "王五", 1);
    print_all();

    // 查找
    int idx = find_car("沪B67890");
    if (idx != -1)
        printf("找到：车主是 %s\n\n", parking_lot[idx].owner);

    // 删除
    delete_car("京A12345");
    print_all();

    return 0;
}

```

    2.有序数组
```c
#include <stdio.h>
#include <string.h>

#define MAX_CARS 100
#define PLATE_LEN 20

typedef struct {
    char plate[PLATE_LEN];
    char owner[50];
    int  parked_hours;
} Car;

Car parking_lot[MAX_CARS];
int car_count = 0;

// 有序插入：按车牌号从小到大排列（字典序）
int add_car_sorted(const char *plate, const char *owner, int hours) {
    if (car_count >= MAX_CARS) return -1;

    // 找到插入位置
    int pos = 0;
    while (pos < car_count && strcmp(parking_lot[pos].plate, plate) < 0) {
        pos++;
    }

    // 如果车牌已存在，可以选择拒绝或覆盖，这里拒绝
    if (pos < car_count && strcmp(parking_lot[pos].plate, plate) == 0) {
        return -2; // 车牌重复
    }

    // 将 pos 及之后的元素整体后移一位
    for (int i = car_count; i > pos; i--) {
        parking_lot[i] = parking_lot[i - 1];
    }

    // 插入新元素
    strncpy(parking_lot[pos].plate, plate, PLATE_LEN - 1);
    strncpy(parking_lot[pos].owner, owner, 49);
    parking_lot[pos].parked_hours = hours;
    car_count++;

    return 0;
}

// 二分查找：返回下标，找不到返回 -1
int find_car_sorted(const char *plate) {
    int left = 0, right = car_count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(parking_lot[mid].plate, plate);
        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// 有序删除：找到后把后面元素前移
int delete_car_sorted(const char *plate) {
    int pos = find_car_sorted(plate);   // O(log n) 查找
    if (pos == -1) return -1;

    // 后面的元素整体前移一位
    for (int i = pos; i < car_count - 1; i++) {
        parking_lot[i] = parking_lot[i + 1];
    }
    car_count--;
    return 0;
}

void print_all() {
    printf("当前停车场有 %d 辆车:\n", car_count);
    for (int i = 0; i < car_count; i++) {
        printf("[%d] 车牌:%-10s 车主:%-6s 已停:%d 小时\n",
               i, parking_lot[i].plate,
               parking_lot[i].owner,
               parking_lot[i].parked_hours);
    }
    printf("\n");
}

int main() {
    // 插入时自动保持有序
    add_car_sorted("沪B67890", "李四", 5);
    add_car_sorted("京A12345", "张三", 2);
    add_car_sorted("粤C99999", "王五", 1);
    print_all();

    // 二分查找
    int idx = find_car_sorted("沪B67890");
    if (idx != -1)
        printf("找到：车主是 %s\n\n", parking_lot[idx].owner);

    // 删除
    delete_car_sorted("京A12345");
    print_all();

    return 0;
}

```

    3.哈希表：高效的单点查询

    4.平衡二叉搜索树：有序的快速查找