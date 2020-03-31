#include "BigInteger.h"
#include <cassert>
#include <cstring>

typedef long long ll;
using namespace std;

int getNumLength(ll a){
    int count = 0;
    while(a){
        a /= 10;
        count++;
    }
    return count;
}

BigInteger::BigInteger(){
    value.clear();
    value.push_back(0);
}

//返回长度，应该私有
int BigInteger::size() const{
    return value.size();
}

//标准化数组，应该私有
void BigInteger::standardization() {
    ll temp;
    int len = value.size();
    for (int i = 0; i < len-1; ++i) {
        if(value[i] < 0){
            value[i] += MAXN;
            value[i+1]--;
        } else {
            temp = value[i] / MAXN;
            value[i] %= MAXN;
            value[i + 1] += temp;
        }
    }
    for (int i = len-1; i > 0; --i) {
        if(value[i] == 0){
            value.pop_back();
        }else{
            break;
        }
    }
    temp = value[len-1]/MAXN;
    if(temp){
        value[len-1] %= MAXN;
        value.push_back(temp);
    }
}

void BigInteger::moveLeft() {
    for (int i = value.size()-1; i > 0; --i) {
        int temp = value[i] % 10;
        value[i] /= 10;
        if(i){
            value[i-1] += temp * MAXN;
        }
    }
    value[0] /= 10;
    standardization();
}

//赋值的时候使用，会延长数组，应该私有
ll& BigInteger::operator[](int n) {
    for (int i = value.size(); i <= n; ++i) {
        value.push_back(0);
    }
    return value[n];
}

BigInteger &BigInteger::operator=(int other) {
    value.clear();
    value.push_back(other);
    return *this;
}

BigInteger &BigInteger::operator=(char *other) {
    value.clear();
    int p = 0;
    int len = strlen(other);
    while(len > 0){
        p = (len-LENGTH>0) ? len-LENGTH:0;
        int temp = 0;
        for (int j = 0; j < LENGTH; ++j) {
            temp = temp*10 + (other[p++] - '0');
            if(p == len) break;
        }
        value.push_back(temp);
        len -= LENGTH;
    }
    standardization();
    return *this;
}

bool BigInteger::operator<=(const BigInteger &other) {
    if(size() > other.size()){
        return false;
    }else if (size() < other.size()){
        return true;
    }else{
        for (int i = size()-1; i >= 0; --i) {
            if(value[i] < other.value[i]){
                return true;
            }else if (value[i] > other.value[i]){
                return false;
            }
        }
        return true;
    }
}

BigInteger &BigInteger::operator=(const BigInteger& other) {
    if(this != &other) {
        value.clear();
        for (ll i : other.value) {
            value.push_back(i);
        }
    }
    return *this;
}

bool BigInteger::operator<(const BigInteger &other) {
    if(size() > other.size()){
        return false;
    }else if (size() < other.size()){
        return true;
    }else{
        for (int i = size()-1; i >= 0; --i) {
            if(value[i] < other.value[i]){
                return true;
            }else if (value[i] > other.value[i]){
                return false;
            }
        }
        return false;
    }
}

BigInteger operator+(const BigInteger &a, const int &b) {
    BigInteger temp;
    temp = b;
    return a + temp;
}

BigInteger operator+(const int &a, const BigInteger &b) {
    BigInteger temp;
    temp = a;
    return temp + b;
}

BigInteger operator+(const BigInteger &a, const BigInteger &b) {
    BigInteger temp,a0,b0;
    temp.value.clear();
    a0 = a;
    b0 = b;
    if(a0.size() < b0.size()){
        swap(a0,b0);
    }
    for (int i = 0; i < b0.size(); ++i) {
        temp.value.push_back(a.value[i]+b.value[i]);
    }
    for (int i = b0.size(); i < a0.size(); ++i) {
        temp.value.push_back(a0.value[i]);
    }
    temp.standardization();
    return temp;
}

BigInteger operator-(const BigInteger &a, const BigInteger &b) {
    BigInteger temp;
    temp = a;
    for (int i = 0; i < b.size(); ++i) {
        temp.value[i] -= b.value[i];
    }
    temp.standardization();
    return temp;
}

BigInteger operator*(const BigInteger &a, const int &b) {
    assert(b >= 0);
    BigInteger temp;
    temp = b;
    return a * temp;
}

BigInteger operator*(const int &a, const BigInteger &b) {
    return b*a;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b) {
    BigInteger temp;
    for (int i = 0; i < b.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
            temp[i+j] += a.value[j] * b.value[i];
        }
    }
    temp.standardization();
    return temp;
}

BigInteger operator/(const BigInteger &a, const int &b) {
    BigInteger temp;
    temp = b;
    return a/temp;
}

BigInteger operator/(const int &a, const BigInteger &b) {
    BigInteger temp;
    temp = a;
    return a/temp;
}

BigInteger operator/(const BigInteger &a, const BigInteger &b) {
    BigInteger tempA,tempB,b0,ans;
    b0 = b;
    tempA = a;
    tempB = b;
    assert(tempB<tempA);
    int lenA = getNumLength(a.value.back());
    int lenB = getNumLength(b.value.back());
    int dif = a.size()-b.size();
    if(dif) {
        //直接移动到a最大的上一个数组的位置，不移动到最大是为了防止要用除法使ab对齐
        for (int i = b.size() - 1; i >= 0; --i) {
            tempB[i + dif - 1] = b.value[i];
        }
        for (int i = 0; i < dif - 1; ++i) {
            tempB[i] = 0;
        }
        //移动n位移到与a对齐

        for (int i = 0; i < LENGTH + lenA - lenB; ++i) {
            tempB = tempB * 10;
        }
    }else{
        for (int i = 0; i < lenA - lenB; ++i) {
            tempB = tempB * 10;
        }
    }

    while(b0 <= tempB){
        int count = 0;
        while(tempB < tempA){
            tempA = tempA - tempB;
            count++;
        }
        ans = ans*10 + count;
        tempB.moveLeft();
    }

    return ans;
}
