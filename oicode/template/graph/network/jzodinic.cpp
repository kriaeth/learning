#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
struct sd
{
	int num, d; //终点，流量
};
const int inf = 0xfffffff;
sd mp[200005];
int layer[200005];//记录层数
vector<int>head[200005];
bool bfs(int u, int st)
{
	memset(layer, 0, sizeof(layer));
	queue<int>q;
	q.push(u);
	layer[u] = 1; //变为第一层
	int now;

	while (!q.empty())
	{
		now = q.front(); //取出队列中有的点
		q.pop();

		for (int j = head[now].size() - 1; j >= 0; j--)
		{
			int order = head[now][j];
			int end = mp[order].num;

			if (!mp[order].d/*如果连的边为0（没有容量），跳过*/
				|| layer[end]/*如果已经被标层，跳过*/)
				continue;

			layer[end] = layer[now] + 1; //层数加1
			q.push(end);//把标记的点放入队列
		}
	}

	return layer[st];//标记终点能否到达
}
int dfs(int u, int mn, int t)
{
	if (u == t) return
			mn; //如果两点重合，返回mn

	int ret = 0; //记录能走过的边

	for (int i = head[u].size() - 1; i >= 0; i--)
	{
		int j = head[u][i]; //记录标号
		int end = mp[j].num; //记录终点
		int now = mp[j].d; //记录流量

		if (!now/*流量为0，跳过*/ ||
			layer[end] - 1 !=
			layer[u]/*不是下一层的话，跳过*/)
			continue;

		int tmp = dfs(end, min(now,
							   mn - ret/*记录流量的最小值*/), t);

		if (!tmp/*流量为0，跳过*/) continue;

		mp[j].d -= tmp; /*正向边减*/
		mp[j ^ 1].d += tmp; /*反向边加*/
		ret += tmp; /*流量加*/

		if (ret == mn) return ret;
	}

	return ret;
}
int dinic(int u, int t)
{
	int ans = 0;

	while (bfs(u, t))  //当终点能到达时
	{
		ans += dfs(u, inf, t); //答案加
	}

	return ans;
}
int main()
{
	int cnt = 0, m, n, s, t;
	scanf("%d%d%d%d", &m, &n, &s, &t);

	for (int u, v, w, i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		mp[cnt].num = v,
				mp[cnt].d = w; //将边标号，终点为v，流量为容量，放入数组中
		head[u].push_back(
			cnt++);//u连编号为cnt的边 即表示u与v相连，流量为w 该边标号为cnt
		mp[cnt].num = u, mp[cnt].d = 0; //反向连边
		head[v].push_back(cnt++);
	}

	printf("%d", dinic(s, t));
	return 0;
}
