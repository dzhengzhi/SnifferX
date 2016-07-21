# SnifferX
一个由Pure C++实现、完全基于异步IO、Windows环境下的网络嗅探器SDK  

##Work In Process.  
目前进度80%

##Feature
- 本嗅探器提供只截获数据包的核心功能，完全基于异步IO实现  
- 允许用户注册自己使用C++语言编写的数据包分析器（只需继承SnCustomAnalyzer并实现相应功能）  
- 允许用户的数据包分析器分析IP数据报、运输层甚至应用层的数据包  

##TODO
- 默认的数据包分析器
- 通用GUI
- 测试

##GUI
除了软件后期增加的通用GUI界面，当然用户也可以自行编写  

##LICENSE
The MIT License (MIT)
