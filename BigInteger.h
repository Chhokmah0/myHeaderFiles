#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <vector>

#define LENGTH 8    // 数组的长度，乘法正常的最大数位受这个值影响，如果数很大时最中间那个数组会超过long long的限度
#define MAXN 100000000  //8位进位用，请根据上面的值修改
//无符号
struct BigInteger{
    std::vector<long long> value;

    BigInteger();
    ~BigInteger()= default;

    int size() const;
    void standardization(); //计算完成后用于标准化BigInteger
    void moveLeft();    //往左移动1位

    long long& operator[](int n);
    BigInteger& operator=(int other);
    BigInteger& operator=(char* other);
    BigInteger& operator=(const BigInteger& other);

    bool operator<(const BigInteger& other);
    bool operator<=(const BigInteger& other);

    friend BigInteger operator+(const BigInteger& a, const int& b);
    friend BigInteger operator+(const int& a, const BigInteger& b);
    friend BigInteger operator+(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator-(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator*(const BigInteger& a, const int& b);
    friend BigInteger operator*(const int& a, const BigInteger& b);
    friend BigInteger operator*(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator/(const BigInteger& a, const int& b);
    friend BigInteger operator/(const int& a, const BigInteger& b);
    friend BigInteger operator/(const BigInteger& a, const BigInteger& b);
};

#endif //BIGINTEGER_H
