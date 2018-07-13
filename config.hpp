//这个文件主要是为了　设定一些全局性质的变量
#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CV_VERSION_THREE_THREE

namespace traffic{
    enum
    {
        SR_DETECT_COLOR = 0x01,
        SR_DETECT_SHAPE = 0x02,
    };

    enum Color {GREEN,YELLOW,RED};
    enum MatDataType {D_8U,D_32F};

}
#endif
