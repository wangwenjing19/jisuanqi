#ifndef MYHEADER_H
#define MYHEADER_H

// 当前处于哪种计算模式
enum MyStatus {
    MyStatuOrdinary,        // 普通计算
    MyStatuLog,             // 对数计算
    MyStatuPower,           // 幂运算
    MyStatuCompare,         // 比较运算
    MyStatuTri,             // 三角函数
    MyStatuFirst,           // 一元一次函数
    MyStatuQuadratic,       // 一元二次函数
    MyStatuInver,           // 反比例
    MyStatuExpLog,          // 指数对数函数
};

// 符号
enum Symbols{
    SymbolsAddition,        // 加
    SymbolsSubtraction,     // 减
    SymbolsMultiplication,  // 乘
    SymbolsDivision         // 除法
};

#endif // MYHEADER_H
