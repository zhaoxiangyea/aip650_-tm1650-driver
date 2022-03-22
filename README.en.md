# AIP650_TM1650Driver

#### Description
This is a AIP650(suit TM1650 well too) driver for STM32 in HAL library.


#### Software Architecture
Software architecture description

#### Installation

1.  If you want to control the nixie tube to display some numbers through aip650 or tm1650, 
	you can just use the "sendFullCmd" fucation to realize your idea.

2. remember the data format is {[0x48 + brightness], [0x68 + number1], [0x6A + number2], [0x6C + number3], [0x6E + number4]}

3. The "copycmd" function provides an example: the numbers 1 - 4 show B 8 3 0 respectively.

4. The IO drive speed in this drive is very high. The test passed on stm32f030f4p6. Other hardware platforms can adjust the size of "#define time_uint 1" in aip650. H

#### Instructions

1.  What's more, it can be change to any hardware platform too，if you change the "SDA_Output"、"SDA_Input" 
	and the "define"s for control the SCL GPIO and SDA GPIO
#### Contribution

1.  Fork the repository
2.  Create Feat_xxx branch
3.  Commit your code
4.  Create Pull Request


#### Gitee Feature

1.  You can use Readme\_XXX.md to support different languages, such as Readme\_en.md, Readme\_zh.md
2.  Gitee blog [blog.gitee.com](https://blog.gitee.com)
3.  Explore open source project [https://gitee.com/explore](https://gitee.com/explore)
4.  The most valuable open source project [GVP](https://gitee.com/gvp)
5.  The manual of Gitee [https://gitee.com/help](https://gitee.com/help)
6.  The most popular members  [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
