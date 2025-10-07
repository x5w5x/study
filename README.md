
# 本项目仅用于代码学习
## 配套笔记：https://www.yuque.com/sanjiu-gc5ut/wghcok/qvdloxfk7hxa8b5a

本项目历经一个月的学习打磨，代码迭代了多个版本，最终形成了一套完整的代码框架，并编写了配套的笔记，供大家学习参考。
## 项目介绍
本项目为学习STM32**标准库**函数而累计的各种代码，方便**参考**以及**快速开发项目**

## 功能介绍
本项目实现了以下功能：
- led的驱动
- 蜂鸣器的驱动
- 按键的检测
- 计数器
- AD读取
- IC读取
- 哈哈哈哈
- 
- 
- 
- 
- 
- 
- 

    led_on()
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    }
    led_off()
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
    }

    OLED_Init();						//OLED初始化

	OLED_ShowString(1, 1, "F_SIZE:");	//显示静态字符串
	OLED_ShowHexNum(1, 8, *((__IO uint16_t *)(0x1FFFF7E0)), 4);		//使用指针读取指定地址下的闪存容量寄存器
	
	OLED_ShowString(2, 1, "U_ID:");		//显示静态字符串
	OLED_ShowHexNum(2, 6, *((__IO uint16_t *)(0x1FFFF7E8)), 4);		//使用指针读取指定地址下的产品唯一身份标识寄存器
	OLED_ShowHexNum(2, 11, *((__IO uint16_t *)(0x1FFFF7E8 + 0x02)), 4);
	OLED_ShowHexNum(3, 1, *((__IO uint32_t *)(0x1FFFF7E8 + 0x04)), 8);
	OLED_ShowHexNum(4, 1, *((__IO uint32_t *)(0x1FFFF7E8 + 0x08)), 8);

## 使用说明
1. 下载项目代码到STM32开发板
2. 编译并烧录代码

## 注意事项
- 本项目仅用于学习交流，请勿用于商业用途
- 本项目中的代码仅供参考，具体实现可能因个人需求而异
## 联系方式
- 邮箱：3457388139@qq.com
- QQ群：421041984