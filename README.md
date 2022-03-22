# AIP650_TM1650Driver

#### 介绍
这是使用STM32 HAL库 的AIP650（也适合TM1650）驱动程序。


#### 软件架构
软件架构说明


#### 安装教程

1.  xxxx
2.  xxxx
3.  xxxx

#### 使用说明

1.  如果你想通过aip650或tm1650控制数码管显示数字，你可以使用“sendFullCmd”功能来实现你的想法。

2.  记得通信的数据格式是： {[0x48 + 亮度], [0x68 + 数1], [0x6A + 数2], [0x6C + 数3], [0x6E + 数4]}

3.  “copyCMD”函数提供了一个示例：数字1 - 4分别显示 b 8 3 0。

4.  本驱动中IO驱动速率极高。在STM32F030F4P6上测试通过。其他硬件平台可以自行调整 《AIP650.h》中的“#define TIME_UINT 1” 的大小即可

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
