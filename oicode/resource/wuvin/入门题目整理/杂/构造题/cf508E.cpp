#include<cstdio>
using namespace std;
/*
codeforces 注意选择编译器 
508E
这是一道神奇的构造题
从右往左构造
最右边的左括号的一对一定是（）【即距离为1】 
 因为他无法包含其他括号
 每一个括号要么等于他右边的括号的距离+2【即包含】
 要么为1【新建】
 看上去时间复杂度为（2^n）(有bug)
 
 其实可以从左枚举区间跨度，然后检验（这个方法不对 （（）（）（）））
 应该是枚举+枚举+检验（时间复杂度n^n）
 当然可以优化上述方法,分k块（n*2^k+n^(n/k)） 
 
 正解：经过尝试构造后发现。。。

将括号的dis设小不会更劣

如（（））变成（）（）更有利于加入其它的括号

于是从后往前依次考虑每个括号，使得它尽量包含少的括号

复杂度n^2 
*/
int L[605],R[605];
int main(){
	scanf("%d%d",&zero,&one);
	
	return 0;
}
