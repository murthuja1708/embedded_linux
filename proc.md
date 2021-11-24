# proc 

**Description**:

​				Proc filesystem is a pseudo file system which provides the information of cpu,memory that are stored in kernel data structures.Some of important files and their outputs are shown below.

**Command**

```bash
cat /proc/cpuinfo
```

**Description**

​			/proc/cpuinfo provides the information of processor like cpu family,cache size,model name.If system is multiple processor it gives information of each processor.

**Output**

![image-20211123173016832](/home/murthu/.config/Typora/typora-user-images/image-20211123173016832.png)

**Command**

```bash
cat proc/meminfo
```

**Description**

​			/proc/meminfo provides the information on memory  like total memory , how much memory is available for applications to load,how much memory is not registered for allocation by kernel,etc.

**Output**

![](/home/murthu/.config/Typora/typora-user-images/image-20211123180501590.png)

**command**

```bash
cat /proc/iomem
```

**Description**

​		This provides the address mapping of memories like RAM,ROM   in the system.  Total address range is between 0x00000000 to 0xffffffff

**Output**

​			![image-20211123182311424](/home/murthu/.config/Typora/typora-user-images/image-20211123182311424.png)



**Command**

```bash
cat /proc/ioports
```

**Description**

​		This provides the address mapping of these peripherals,as you can see i am addresses starting from 0x0000 to 0xffff getting in below ouput

**Output**

![image-20211123182409475](/home/murthu/.config/Typora/typora-user-images/image-20211123182409475.png)